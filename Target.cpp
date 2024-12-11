#include "Target.h"
#include "SceneBase.h"
#include "Tower.h"
#include "audio/include/SimpleAudioEngine.h"
USING_NS_CC;

static Target* selectedTarget = nullptr; // ��֤ͬһʱ��ֻ��һ��ʵ�屻����
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
         
        //// ���������������Ƴ�Ŀ��
        //���+���ͼ��
        Sprite* jinbi = Sprite::create();
        if(value==50)
            jinbi->initWithFile("jinbi1.png");
        else if(value==75)
            jinbi->initWithFile("jinbi2.png");
        else
            jinbi->initWithFile("jinbi3.png");
        jinbi->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height));//�����ڹ���ͷ��
        addChild(jinbi);

        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("monsterhurt.mp3"); //�����ܻ���Ч

        this->runAction(Sequence::create(
            FadeOut::create(0.25f),// ����
            RemoveSelf::create(),
            nullptr
        ));
    }
    if (!Health) {
        // ����һ��Ѫ������
        auto Health = ProgressTimer::create(Sprite::create("ProgressAfter.png"));
        Sprite* Background = Sprite::create("ProgressInit.png");
        Health->setType(ProgressTimer::Type::BAR);
        Health->setMidpoint(Vec2(0, 0.5));  // ����Ѫ�����Ϊ����м�λ��
        Health->setBarChangeRate(Vec2(1, 0));  // ����Ѫ���ĳ�����ٷֱȱ仯

        // ��Ѫ��������ӵ�����ͷ����
        this->addChild(Background);
        this->addChild(Health);
        Background->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height));
        Health->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height));
        this->Health = Health;
    }
    if (HP < maxHP&& Health) {
        // ����Ѫ��������Ѫ���ٷֱȱ仯
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
        // ���������������Ƴ�Ŀ��
        this->runAction(Sequence::create(
            FadeOut::create(0.25f),// ����
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
    //���ڱ�ʶ��ѡ�еĹ���
    if (selectedTarget) {
        selectedTarget->removeChild(selectedTarget->choose, true);
        selectedTarget->choose = nullptr;
    }
    selectedTarget = this;
    if (!choose) {
        choose = Sprite::create("choose1.png");
        choose->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height));//�����ڹ���ͷ��
        addChild(choose);
    }
    else {
        this->removeChild(choose, true);
        choose = Sprite::create("choose1.png");
        choose->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height));//�����ڹ���ͷ��
        addChild(choose);
    }
}