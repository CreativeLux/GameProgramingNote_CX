//简单的输入实现
void InputHandler::handleInput()
{
    if(isPressed(BUTTON_X)) jump();
    else if(isPressed(BUTTON_Y)) fireGun();
    else if(isPressed(BUTTON_A)) swapWeapon();
    else if(isPressed(BUTTON_B)) actionD();
}
/******************************************************************************************************************************************************/

/* 命令模式：使用对象来代表游戏动作*/
/*一条游戏命令抽象为一个基类*/
class Command{
public:
    virtual ~Command(){}
    virtual void execute() = 0;
};
/*为不同的命令创建子类*/
class JumpCommand:public Command{
public:
    virtual void execute(){ jump(); }
};

class FireCommand:public Command{
 public:
    virtual void execute(){ fireGun(); }
};//......

class InputHandler{
public:
    void handleInput();//用于绑定命令
private:
    Command* buttonX_;
    Command* buttonY_;
    //......
};//这样就给每一个按钮储存了一个指向它的指针

void InputHandler:handleInput(){
    if(isPressed(BUTTON_X)) buttonX_->execute();
    if(isPressed(BUTTON_Y)) buttonY_->execute();
}//输入处理通过指针代理

/*之前简单调用每一个输入都会直接调用一个函数，现在增加了一个间接调用层。*/

/*********************************************************************************************************************************************/

/*再扩展一层，命令控制的对象也由外部传入，而不是让命令自身确定控制的对象*/
class Command{
public:
    virtual ~Command(){}
    virtual void execute(GameActor& actor) = 0;
};
class JumpCommand:public Command{
    public:
    virtual void execute(GameActor& actor){ actor.jump(); }
};//可以使用这个类让游戏中的任何角色跳跃

Command* InputHandler::handleInput(){
    if(isPressed(BUTTON_X)) return buttonX_;
    if(isPressed(BUTTON_Y)) return buttonY_;
    return NULL;
}//此处命令并不会立即执行，因为它不知道会被指派给哪一个GameActor执行，因此命令的调用被延迟到handleInput被调用之后

Command* command = InputHandler.handleInput();
if (command) {
    command->execute(actor);
}
/*上述目前只考虑了玩家驱动角色的情况，AI驱动角色时，改进后的命令模式可以照搬作为AI引擎与角色之间的接口，AI只要提供命令对象以供执行即可*/
/*这种方式将命令的输入与角色的表现进行了解耦，去除了函数直接调用这种紧耦合，可以是一个队列或者命令流*/