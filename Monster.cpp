#include "Monster.h"
#include "SceneBase.h"


USING_NS_CC;

bool Sheep::init() {
    if (!Sprite::init()) {
        return false;
    }

    //在怪物身上添加一个不可见按钮，用于实现集火
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0);
    BUTTON->setContentSize(Size(this->getContentSize()));
    BUTTON->addClickEventListener([this](Ref* sender) {
        // 处理按钮点击事件
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(50, 50));
    addChild(BUTTON);

    // 初始化HP
    maxHP = HP = 100 + 3 * player.getDifficulty();
    // 初始化击杀奖励
    value = 50;
    // 初始化速度
    speed = 30;
    // 初始化半径
    radius = 10;
    //初始化伤害
    hurt = 1;

    return true;
}

void Sheep::moveToSequence(const std::vector<Vec2>& positions)
{
    this->stopAllActions(); // 停止当前进行中的动作

    Vector<FiniteTimeAction*> actions; // 创建一个动作数组
    Vec2 thisPosition = this->getPosition();
    for (Vec2 position : positions)
    {
        auto distance = position - thisPosition; // 计算移动距离
        thisPosition = position;
        auto duration = distance.length() / speed; // 计算移动时间
        auto move = MoveTo::create(duration, position); // 创建移动动作
        actions.pushBack(move); // 将移动动作添加到数组中
    }

    auto attacked = CallFunc::create([=]() {
        auto target = this->getParent();
        auto Scene = dynamic_cast<SceneBase*>(target);
        Scene->getCarrot()->takeDamage(hurt);//根据怪物的伤害对萝卜造成伤害
        this->setHP(0);//攻击后怪物死亡

        });
    auto sequenceAction = Sequence::create(actions); // 创建序列动作
    auto sequence = Sequence::create(sequenceAction, attacked, nullptr);

    // 创建一个空的动画对象
    auto animation = Animation::create();
    // 添加动画帧
    for (int i = 1; i <= 2; i++) {
        char filename[100];
        sprintf(filename, "Sheep%d.png", i);
        auto frame = SpriteFrame::create(filename, Rect(0, 0, 100, 100));
        animation->addSpriteFrame(frame);
    }

    // 设置动画属性
    animation->setDelayPerUnit(0.1f);//nf=每隔n秒播放一帧
    animation->setLoops(-1);//让动画一直循坏播放

    // 创建动画动作对象
    auto animate = Animate::create(animation);

    // 将动画动作应用到精灵对象上
    this->runAction(Spawn::create(animate,sequence,nullptr)); // 执行序列动作
}

bool Bird::init() {
    if (!Sprite::init()) {
        return false;
    }

    // 初始化怪物的外观和属性
    // 初始化HP
    maxHP = HP = 80 + 2 * player.getDifficulty();
    // 初始化击杀奖励
    value = 50;
    // 初始化速度
    speed = 60;
    // 初始化半径
    radius = 10;
    //初始化伤害
    hurt = 1;

    //在怪物身上添加一个不可见按钮，用于实现集火
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0);
    BUTTON->setContentSize(Size(20, 20));
    BUTTON->addClickEventListener([this](Ref* sender) {
        // 处理按钮点击事件
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(50, 50));
    addChild(BUTTON);

    return true;
}

void Bird::moveToSequence(const std::vector<Vec2>& positions)
{
    this->stopAllActions(); // 停止当前进行中的动作

    Vector<FiniteTimeAction*> actions; // 创建一个动作数组
    Vec2 thisPosition = this->getPosition();
    for (Vec2 position : positions)
    {
        auto distance = position - thisPosition; // 计算移动距离
        thisPosition = position;
        auto duration = distance.length() / speed; // 计算移动时间
        auto move = MoveTo::create(duration, position); // 创建移动动作
        actions.pushBack(move); // 将移动动作添加到数组中
    }

    auto attacked = CallFunc::create([=]() {
        auto target = this->getParent();
        auto Scene = dynamic_cast<SceneBase*>(target);
        Scene->getCarrot()->takeDamage(hurt);//根据怪物的伤害对萝卜造成伤害
        this->setHP(0);//攻击后怪物死亡

        });
    auto sequenceAction = Sequence::create(actions); // 创建序列动作
    auto sequence = Sequence::create(sequenceAction, attacked, nullptr);

    // 创建一个空的动画对象
    auto animation = Animation::create();
    // 添加动画帧
    for (int i = 1; i <= 2; i++) {
        char filename[100];
        sprintf(filename, "Bird%d.png", i);
        auto frame = SpriteFrame::create(filename, Rect(0, 0, 100, 100));
        animation->addSpriteFrame(frame);
    }

    // 设置动画属性
    animation->setDelayPerUnit(0.1f);
    animation->setLoops(-1);

    // 创建动画动作对象
    auto animate = Animate::create(animation);

    // 将动画动作应用到精灵对象上
    this->runAction(Spawn::create(animate, sequence, nullptr)); // 执行序列动作
}

bool Star::init() {
    if (!Sprite::init()) {
        return false;
    }

    // 初始化怪物的外观和属性
    // 初始化HP
    maxHP = HP = 200 + 2 * player.getDifficulty();
    // 初始化击杀奖励
    value = 75;
    // 初始化速度
    speed = 50;
    // 初始化半径
    radius = 10;
    //初始化伤害
    hurt = 2;

    //在怪物身上添加一个不可见按钮，用于实现集火
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0);
    BUTTON->setContentSize(Size(this->getContentSize().width, this->getContentSize().height));
    BUTTON->addClickEventListener([this](Ref* sender) {
        // 处理按钮点击事件
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(50,50));
    addChild(BUTTON);

    return true;
}

void Star::moveToSequence(const std::vector<Vec2>& positions)
{
    this->stopAllActions(); // 停止当前进行中的动作

    Vector<FiniteTimeAction*> actions; // 创建一个动作数组
    Vec2 thisPosition = this->getPosition();
    for (Vec2 position : positions)
    {
        auto distance = position - thisPosition; // 计算移动距离
        thisPosition = position;
        auto duration = distance.length() / speed; // 计算移动时间
        auto move = MoveTo::create(duration, position); // 创建移动动作
        actions.pushBack(move); // 将移动动作添加到数组中
    }

    auto attacked = CallFunc::create([=]() {
        auto target = this->getParent();
        auto Scene = dynamic_cast<SceneBase*>(target);
        Scene->getCarrot()->takeDamage(hurt);//根据怪物的伤害对萝卜造成伤害
        this->setHP(0);//攻击后怪物死亡
        });
    auto sequenceAction = Sequence::create(actions); // 创建序列动作
    auto sequence = Sequence::create(sequenceAction, attacked, nullptr);

    // 创建一个空的动画对象
    auto animation = Animation::create();
    // 添加动画帧
    for (int i = 1; i <= 2; i++) {
        char filename[100];
        sprintf(filename, "Star%d.png", i);
        auto frame = SpriteFrame::create(filename, Rect(0, 0, 100, 100));
        animation->addSpriteFrame(frame);
    }

    // 设置动画属性
    animation->setDelayPerUnit(0.1f);
    animation->setLoops(-1);

    // 创建动画动作对象
    auto animate = Animate::create(animation);

    // 将动画动作应用到精灵对象上
    this->runAction(Spawn::create(animate, sequence, nullptr)); // 执行序列动作
}

bool Boss::init() {
    if (!Sprite::init()) {
        return false;
    }

    //在怪物身上添加一个不可见按钮，用于实现集火
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0);
    BUTTON->setContentSize(Size(this->getContentSize().width, this->getContentSize().height));
    BUTTON->addClickEventListener([this](Ref* sender) {
        // 处理按钮点击事件
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(50, 50));
    addChild(BUTTON);

    // 初始化HP
    maxHP = HP = 300 + 2 * player.getDifficulty();
    // 初始化击杀奖励
    value = 50;
    // 初始化速度
    speed = 40;
    // 初始化半径
    radius = 10;
    //初始化伤害
    hurt = 10;

    return true;
}

void Boss::moveToSequence(const std::vector<Vec2>& positions)
{
    this->stopAllActions(); // 停止当前进行中的动作

    Vector<FiniteTimeAction*> actions; // 创建一个动作数组
    Vec2 thisPosition = this->getPosition();
    for (Vec2 position : positions)
    {
        auto distance = position - thisPosition; // 计算移动距离
        thisPosition = position;
        auto duration = distance.length() / speed; // 计算移动时间
        auto move = MoveTo::create(duration, position); // 创建移动动作
        actions.pushBack(move); // 将移动动作添加到数组中
    }

    auto attacked = CallFunc::create([=]() {
        auto target = this->getParent();
        auto Scene = dynamic_cast<SceneBase*>(target);
        Scene->getCarrot()->takeDamage(hurt);//根据怪物的伤害对萝卜造成伤害
        this->setHP(0);//攻击后怪物死亡

        });
    auto sequenceAction = Sequence::create(actions); // 创建序列动作
    auto sequence = Sequence::create(sequenceAction, attacked, nullptr);

    // 创建一个空的动画对象
    auto animation = Animation::create();
    // 添加动画帧
    for (int i = 1; i <= 2; i++) {
        char filename[100];
        sprintf(filename, "Boss%d.png", i);
        auto frame = SpriteFrame::create(filename, Rect(0, 0, 200, 200));
        animation->addSpriteFrame(frame);
    }

    // 设置动画属性
    animation->setDelayPerUnit(0.1f);//nf=每隔n秒播放一帧
    animation->setLoops(-1);//让动画一直循坏播放

    // 创建动画动作对象
    auto animate = Animate::create(animation);

    // 将动画动作应用到精灵对象上
    this->runAction(Spawn::create(animate, sequence, nullptr)); // 执行序列动作
}



//治疗技能
void Boss::cure() 
{
    // 创建随机数生成器
    std::random_device rd;  // 获取随机数种子
    std::mt19937 gen(rd()); // 使用梅森旋转算法生成随机数
    std::uniform_int_distribution<> dis(0, 100); // 定义范围

    // 生成随机数
    int randomNumber = dis(gen);
    if (randomNumber < 5)
    {
        if (HP + 50 < maxHP)
            HP += 50;
        else
            HP = maxHP;
    }
}
