#include "Target.h"
#include "SceneBase.h"
#include "Tower.h"
#include "audio/include/SimpleAudioEngine.h"
USING_NS_CC;

static Target* selectedTarget = nullptr; // 保证同一时刻只有一个实体被集火
void Target::takeDamage(int damage) {
    HP -= damage;
    if (!isAlive()) {
        if (this == selectedTarget) {
            selectedTarget = nullptr;
        }
        auto scene = dynamic_cast<SceneBase*>(this->getParent());
        if (scene)
        {
            scene->updateMoney(value);
        }
         
        //// 播放死亡动画、移除目标
        //添加+金币图像
        Sprite* jinbi = Sprite::create();
        if(value==50)
            jinbi->initWithFile("jinbi1.png");
        else if(value==75)
            jinbi->initWithFile("jinbi2.png");
        else
            jinbi->initWithFile("jinbi3.png");
        jinbi->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height));//精灵在怪物头顶
        addChild(jinbi);

        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("monsterhurt.mp3"); //播放受击音效

        this->runAction(Sequence::create(
            FadeOut::create(0.25f),// 淡出
            RemoveSelf::create(),
            nullptr
        ));
    }
    if (!Health) {
        // 创建一个血条精灵
        auto Health = ProgressTimer::create(Sprite::create("ProgressAfter.png"));
        Sprite* Background = Sprite::create("ProgressInit.png");
        Health->setType(ProgressTimer::Type::BAR);
        Health->setMidpoint(Vec2(0, 0.5));  // 设置血条起点为左边中间位置
        Health->setBarChangeRate(Vec2(1, 0));  // 设置血条的长度随百分比变化

        // 将血条精灵添加到怪物头顶上
        this->addChild(Background);
        this->addChild(Health);
        Background->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height));
        Health->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height));
        this->Health = Health;
    }
    if (HP < maxHP&& Health) {
        // 设置血条长度随血量百分比变化
        float percent = static_cast<float>(HP * 100 / maxHP);
        this->Health->setPercentage(percent);
    }
}

bool Target::isAlive() const {
    return HP > 0;
}

void Target::setHP(int HP) {
    this->HP = HP;
    if (!isAlive()) {
        if (this == selectedTarget) {
            selectedTarget = nullptr;
        }
        // 播放死亡动画、移除目标
        this->runAction(Sequence::create(
            FadeOut::create(0.25f),// 淡出
            RemoveSelf::create(),
            nullptr
        ));

    }
}

int Target::getRadius() {
    return radius;
}

void Target::setAllTarget() {
    Vector<Node*> enemies = getScene()->getChildren();
    Target* nearestEnemy = nullptr;
    float minDistance = 999999;
    for (auto node : enemies) {
        auto tower = dynamic_cast<Tower*>(node);
        if (tower) {
            tower->setTarget(this);
        }
    }
    //用于标识被选中的怪物
    if (selectedTarget) {
        selectedTarget->removeChild(selectedTarget->choose, true);
        selectedTarget->choose = nullptr;
    }
    selectedTarget = this;
    if (!choose) {
        choose = Sprite::create("choose1.png");
        choose->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height));//精灵在怪物头顶
        addChild(choose);
    }
    else {
        this->removeChild(choose, true);
        choose = Sprite::create("choose1.png");
        choose->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height));//精灵在怪物头顶
        addChild(choose);
    }
}