#include "Carrot.h"
#include "audio/include/SimpleAudioEngine.h"

bool Carrot::init()
{
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

bool Carrot::isAlive() {
    return HP>0;
}

void Carrot::takeDamage(int damage)
{
    HP -= damage;
    // 播放受伤音效
    if (HP > 0) { // 确保萝卜还活着
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("carrothurt.mp3"); //播放受击音效
    }

    Sprite* newCarrot = nullptr; // 创建一个新的指针来存储新精灵

    if (HP <= MaxHP / 3)
    {
        newCarrot = Sprite::create("carrot11.png");
    }
    else if (HP <= MaxHP * 2 / 3)
    {
        newCarrot = Sprite::create("carrot10.png");
    }
    else
    {
        newCarrot = Sprite::create("carrot9.png");
    }

    if (newCarrot) {
        // 移除旧精灵
        this->removeChild(this->carrot, true);
        // 更新类成员变量 carrot 为新精灵，并设置位置
        this->carrot = newCarrot;
        this->carrot->setPosition(Position);
        this->addChild(this->carrot);
    }

    // 更新血量数字
    std::string text = std::to_string(HP);
    if (this->carrotHP) {
        this->removeChild(this->carrotHP, true);
    }
    this->carrotHP = Label::createWithTTF(text, "fonts/arial.ttf", 28);
    this->carrotHP->setTextColor(Color4B::BLACK);
    this->carrotHP->setPosition(Vec2(Position.x - 20, Position.y + 90));
    this->addChild(this->carrotHP);
}

void Carrot::setCarrotPosition(Vec2 pos)
{
    Position = pos;
}

Vec2 Carrot::getCarrotPosition() const
{
    return Position;
}

void Carrot::putCarrot(int hp) {
    // 初始化HP
    MaxHP = HP = hp;
    // 初始化外观和属性
    this->carrot = Sprite::create("carrot1.png"); // 假设1是满血的萝卜图片
    this->carrot->setPosition(Position);
    this->addChild(this->carrot);

    // 为萝卜添加血量的可视化
    this->carrot_HP = Sprite::create("CarrotHP.png");
    this->carrot_HP->setPosition(Vec2(Position.x, Position.y + 90));
    this->addChild(carrot_HP);

    // 初始化Label
    std::string text = std::to_string(HP); // 将数字转换为字符串
    this->carrotHP = Label::createWithTTF(text, "fonts/arial.ttf", 28);
    this->carrotHP->setTextColor(Color4B::BLACK);
    this->carrotHP->setPosition(Vec2(Position.x - 20, Position.y + 90));
    this->addChild(this->carrotHP);

    //点击萝卜，萝卜扭动事件
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0); // 设置按钮不透明度为0，使其不可见
    BUTTON->setContentSize(Size(this->carrot->getContentSize().width, this->carrot->getContentSize().height));
    BUTTON->setPosition(Position); // 设置按钮位置与萝卜精灵相同
    BUTTON->addClickEventListener([this](Ref* sender) {// 处理按钮点击事件
        
        // 创建一个空的动画对象
        auto animation = Animation::create();

        // 添加动画帧
        for (int i = 1; i <= 8; i++) {
            char filename[100];
            sprintf(filename, "carrot%d.png", i);
            auto frame = SpriteFrame::create(filename, Rect(0, 0, 120, 120));
            animation->addSpriteFrame(frame);
        }

        // 设置动画属性
        animation->setDelayPerUnit(0.1f); // 每隔0.1秒播放一帧
        animation->setLoops(1); // 动画播放一次

        // 创建动画动作对象
        auto animate = Animate::create(animation);

        // 动画完成后恢复carrot精灵到动画开始前的位置
        auto callback = [this]() {
            this->removeChild(this->carrot, true);
            if(HP==MaxHP)
                carrot = Sprite::create("carrot1.png");
            else {
                if (HP <= MaxHP / 3)
                {
                    carrot = Sprite::create("carrot11.png");
                }
                else if (HP <= MaxHP * 2 / 3)
                {
                    carrot = Sprite::create("carrot10.png");
                }
                else
                {
                    carrot = Sprite::create("carrot9.png");
                }
            }
            this->carrot->setPosition(Position);
            this->addChild(this->carrot);
        };

        // 将动画动作应用到carrot精灵上，并添加完成回调
        this->carrot->runAction(Sequence::create(animate, CallFunc::create(callback), nullptr));
        });
    this->addChild(BUTTON);
}
