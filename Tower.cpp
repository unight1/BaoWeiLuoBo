#include "Tower.h"
#include "Tower.h"
#include "Tower.h"
#include "Tower.h"
#include "Tower.h"
#include "audio/include/SimpleAudioEngine.h"
USING_NS_CC;

bool BottleTower_1::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("BottleLevel1.png");
    // �ӵ���ͼƬ
    Bullet = "BottleBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 200;
    damage = 10;
    attackInterval = 1.0f;

    consumption = 100;
    rotateSpeed = 180;
    cooldownTimer = 1.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void BottleTower_1::clicked(int& moneyScene) {
    Vec2 positionUp = Vec2(40, 120);
    Vec2 positionDelete = Vec2(40, -40);
   
    // ������ť
    auto towerUp = cocos2d::ui::Button::create("BottleUpgrade1.png", "BottleUpgrade1.png", "BottleUpgradeUn1.png");
    towerUp->setPosition(positionUp);
    this->bottom->addChild(towerUp, 4, "But");

    auto oldTower = this;
    Vec2 pos = oldTower->getPosition();

    // ����ť����¼�
    towerUp->addClickEventListener([=](Ref* sender) {
        if(!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerUpdata.mp3"); //��������������Ч
            // �ڵ�ǰλ�ô�������
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto tower = BottleTower_2::create();  // ������������                     
                tower->setPosition(pos);  // ��������λ��

                auto bot = Sprite::create("Bottom.png");
                bot->setPosition(bottom->getPosition());
                tower->bottom = bot;//
                tower->thisTowerPositionIS = oldTower->thisTowerPositionIS;//
                oldTower->thisTowerPositionIS->towerofThisPosition = tower;//

                oldTower->getParent()->addChild(bot, 1);
                oldTower->getParent()->addChild(tower, 2);

                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(-150);
                }
                bottom->removeFromParent();
                oldTower->removeFromParent();



            }
        }
        });

    // ���õ��״̬
    if (moneyScene >= 150)
    {
        towerUp->setEnabled(true);
    }
    else
    {
        towerUp->setEnabled(false);
    }

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("BottleRemove1.png", "BottleRemove1.png");
    towerDelete->setPosition(positionDelete);
    this->bottom->addChild(towerDelete, 4, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(60);
                }
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->bottom->removeFromParent();
                oldTower->removeFromParent();
            }
        }
        });
}

bool BottleTower_2::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("BottleLevel2.png");
    // �ӵ���ͼƬ
    Bullet = "BottleBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 250;
    damage = 15;
    attackInterval = 1.0f;

    consumption = 150;
    rotateSpeed = 180;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void BottleTower_2::clicked(int& moneyScene)
{

    Vec2 positionUp = Vec2(40, 120);
    Vec2 positionDelete = Vec2(40, -40);

    // ������ť
    auto towerUp = cocos2d::ui::Button::create("BottleUpgrade2.png", "BottleUpgrade2.png", "BottleUpgradeUn2.png");
    towerUp->setPosition(positionUp);
    this->bottom->addChild(towerUp, 4, "But");

    auto oldTower = this;
    Vec2 pos = oldTower->getPosition();

    // ����ť����¼�
    towerUp->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerUpdata.mp3"); //��������������Ч
            // �ڵ�ǰλ�ô�������
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto tower = BottleTower_3::create();  // ������������                     
                tower->setPosition(pos);  // ��������λ��
                

                auto bot = Sprite::create("Bottom.png");
                bot->setPosition(bottom->getPosition());
                tower->bottom = bot;//
                tower->thisTowerPositionIS = oldTower->thisTowerPositionIS;//
                oldTower->thisTowerPositionIS->towerofThisPosition = tower;//

                oldTower->getParent()->addChild(bot, 1);
                oldTower->getParent()->addChild(tower, 2);

                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(-250);
                }

                bottom->removeFromParent();
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });

    // ���õ��״̬
    if (moneyScene >= 250)
    {
        towerUp->setEnabled(true);
    }
    else
    {
        towerUp->setEnabled(false);
    }

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("BottleRemove2.png", "BottleRemove2.png");
    towerDelete->setPosition(positionDelete);
    this->bottom->addChild(towerDelete, 4, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(120);
                }
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->bottom->removeFromParent();
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });
}

bool BottleTower_3::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("BottleLevel3.png");
    // �ӵ���ͼƬ
    Bullet = "BottleBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 300;
    damage = 20;
    attackInterval = 1.0f;

    consumption = 250;
    rotateSpeed = 180;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void BottleTower_3::clicked(int& moneyScene)
{
    Vec2 positionDelete = Vec2(40, -40);   
    auto oldTower = this;
    Vec2 pos = oldTower->getPosition();

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("BottleRemove3.png", "BottleRemove3.png");
    towerDelete->setPosition(positionDelete);
    this->bottom->addChild(towerDelete, 4, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(150);
                }
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->bottom->removeFromParent();
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });
}

bool FireTower_1::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("FireBottleLevel1.png");
    // �ӵ���ͼƬ
    Bullet = "BottleBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 200;
    damage = 1000;
    attackInterval = 1.0f;

    consumption = 100;
    rotateSpeed = 180;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void FireTower_1::clicked(int& moneyScene) {
    Vec2 positionUp = Vec2(40, 120);
    Vec2 positionDelete = Vec2(40, -40);

    // ������ť
    auto towerUp = cocos2d::ui::Button::create("BottleUpgrade1.png", "BottleUpgrade1.png", "BottleUpgradeUn1.png");
    towerUp->setPosition(positionUp);
    this->bottom->addChild(towerUp, 4, "But");

    auto oldTower = this;
    Vec2 pos = oldTower->getPosition();

    // ����ť����¼�
    towerUp->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerUpdata.mp3"); //��������������Ч
            // �ڵ�ǰλ�ô�������
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto tower = FireTower_2::create();  // ������������                     
                tower->setPosition(pos);  // ��������λ��

                auto bot = Sprite::create("Bottom.png");
                bot->setPosition(bottom->getPosition());
                tower->bottom = bot;//
                tower->thisTowerPositionIS = oldTower->thisTowerPositionIS;//
                oldTower->thisTowerPositionIS->towerofThisPosition = tower;//

                oldTower->getParent()->addChild(bot, 1);
                oldTower->getParent()->addChild(tower, 2);

                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(-150);
                }
                bottom->removeFromParent();
                oldTower->removeFromParent();



            }
        }
        });

    // ���õ��״̬
    if (moneyScene >= 150)
    {
        towerUp->setEnabled(true);
    }
    else
    {
        towerUp->setEnabled(false);
    }

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("BottleRemove1.png", "BottleRemove1.png");
    towerDelete->setPosition(positionDelete);
    this->bottom->addChild(towerDelete, 4, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(60);
                }
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->bottom->removeFromParent();
                oldTower->removeFromParent();
            }
        }
        });
}

void FireTower_1::attackTarget()
{
    // ��ȡĿ��λ��
    Target* thisTarget = this->target;

    // ��ȡ������ǰλ��
    cocos2d::Vec2 towerPosition = getPosition();
    // ���������������
    std::random_device rd;  // ��ȡ���������
    std::mt19937 gen(rd()); // ʹ��÷ɭ��ת�㷨���������
    std::uniform_int_distribution<> dis(0, 100); // ���巶Χ

    // ���������
    int randomNumber = dis(gen);
    int Damage;
    if (randomNumber < 10) {
        Damage = getDamage();
    }
    else {
        Damage = 1;
    }
    // �����ڵ�����
    auto bullet = Sprite::create(Bullet);
    bullet->setPosition(towerPosition);
    this->getParent()->addChild(bullet, 2);
    bullet->setVisible(false);

    // �ӵ�����
    auto bulletAction = CallFunc::create([=]() {
        cocos2d::Vec2 targetPosition = thisTarget->getPosition();
        // �����ӵ���ת����
        // ����Ŀ�귽������
        cocos2d::Vec2 direction = this->target->getPosition() - towerPosition;
        // ����Ŀ��Ƕ�
        float targetAngle = -CC_RADIANS_TO_DEGREES(direction.getAngle()) + 90;
        // ��ת����
        auto rotateAction = RotateTo::create(0, targetAngle);
        // ����һ����Ŀ���ƶ��Ķ���
        float distance = targetPosition.distance(towerPosition);
        float duration = distance / 2000; //�ӵ����ٶ�
        auto moveAction = MoveTo::create(duration, targetPosition);
        // ִ�ж���
        bullet->setVisible(true);
        bullet->runAction(
            Sequence::create(
                rotateAction,
                moveAction,
                // ����һ���ص���������Ŀ��λ�ô����ڵ���ըЧ��     
                CallFunc::create([=]() {
                    if (thisTarget && thisTarget->isAlive()) {
                        // ��Ŀ��λ�ô�����ըЧ��
                        auto explosion = Sprite::create(Explosion);
                        explosion->setPosition(targetPosition);
                        thisTarget->getParent()->addChild(explosion);
                        explosion->runAction(Sequence::create(
                            DelayTime::create(0.1f),
                            FadeOut::create(0.1f),// ����
                            RemoveSelf::create(),
                            nullptr
                        ));
                        // �����˺�
                        thisTarget->takeDamage(Damage);
                    }
                    // �Ƴ��ڵ�����
                    this->getParent()->removeChild(bullet, true);
                    }),
                nullptr));
        });

    // ���ж���
    bullet->runAction(
        Sequence::create(
            DelayTime::create(attackDuration),
            bulletAction,
            nullptr)
    );
}

bool FireTower_2::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("FireBottleLevel2.png");
    // �ӵ���ͼƬ
    Bullet = "BottleBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 250;
    damage = 1000;
    attackInterval = 1.0f;

    consumption = 150;
    rotateSpeed = 180;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void FireTower_2::clicked(int& moneyScene)
{

    Vec2 positionUp = Vec2(40, 120);
    Vec2 positionDelete = Vec2(40, -40);

    // ������ť
    auto towerUp = cocos2d::ui::Button::create("BottleUpgrade2.png", "BottleUpgrade2.png", "BottleUpgradeUn2.png");
    towerUp->setPosition(positionUp);
    this->bottom->addChild(towerUp, 4, "But");

    auto oldTower = this;
    Vec2 pos = oldTower->getPosition();

    // ����ť����¼�
    towerUp->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerUpdata.mp3"); //��������������Ч
            // �ڵ�ǰλ�ô�������
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto tower = FireTower_3::create();  // ������������                     
                tower->setPosition(pos);  // ��������λ��


                auto bot = Sprite::create("Bottom.png");
                bot->setPosition(bottom->getPosition());
                tower->bottom = bot;//
                tower->thisTowerPositionIS = oldTower->thisTowerPositionIS;//
                oldTower->thisTowerPositionIS->towerofThisPosition = tower;//

                oldTower->getParent()->addChild(bot, 1);
                oldTower->getParent()->addChild(tower, 2);

                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(-250);
                }

                bottom->removeFromParent();
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });

    // ���õ��״̬
    if (moneyScene >= 250)
    {
        towerUp->setEnabled(true);
    }
    else
    {
        towerUp->setEnabled(false);
    }

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("BottleRemove2.png", "BottleRemove2.png");
    towerDelete->setPosition(positionDelete);
    this->bottom->addChild(towerDelete, 4, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(120);
                }
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->bottom->removeFromParent();
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });
}

void FireTower_2::attackTarget()
{
    // ��ȡĿ��λ��
    Target* thisTarget = this->target;

    // ��ȡ������ǰλ��
    cocos2d::Vec2 towerPosition = getPosition();
    // ���������������
    std::random_device rd;  // ��ȡ���������
    std::mt19937 gen(rd()); // ʹ��÷ɭ��ת�㷨���������
    std::uniform_int_distribution<> dis(0, 100); // ���巶Χ

    // ���������
    int randomNumber = dis(gen);

    int Damage;
    if (randomNumber < 20) {
        Damage = getDamage();
    }
    else {
        Damage = 1;
    }
    // �����ڵ�����
    auto bullet = Sprite::create(Bullet);
    bullet->setPosition(towerPosition);
    this->getParent()->addChild(bullet, 2);
    bullet->setVisible(false);

    // �ӵ�����
    auto bulletAction = CallFunc::create([=]() {
        cocos2d::Vec2 targetPosition = thisTarget->getPosition();
        // �����ӵ���ת����
        // ����Ŀ�귽������
        cocos2d::Vec2 direction = this->target->getPosition() - towerPosition;
        // ����Ŀ��Ƕ�
        float targetAngle = -CC_RADIANS_TO_DEGREES(direction.getAngle()) + 90;
        // ��ת����
        auto rotateAction = RotateTo::create(0, targetAngle);
        // ����һ����Ŀ���ƶ��Ķ���
        float distance = targetPosition.distance(towerPosition);
        float duration = distance / 2000; //�ӵ����ٶ�
        auto moveAction = MoveTo::create(duration, targetPosition);
        // ִ�ж���
        bullet->setVisible(true);
        bullet->runAction(
            Sequence::create(
                rotateAction,
                moveAction,
                // ����һ���ص���������Ŀ��λ�ô����ڵ���ըЧ��     
                CallFunc::create([=]() {
                    if (thisTarget && thisTarget->isAlive()) {
                        // ��Ŀ��λ�ô�����ըЧ��
                        auto explosion = Sprite::create(Explosion);
                        explosion->setPosition(targetPosition);
                        thisTarget->getParent()->addChild(explosion);
                        explosion->runAction(Sequence::create(
                            DelayTime::create(0.1f),
                            FadeOut::create(0.1f),// ����
                            RemoveSelf::create(),
                            nullptr
                        ));
                        // �����˺�
                        thisTarget->takeDamage(Damage);
                    }
                    // �Ƴ��ڵ�����
                    this->getParent()->removeChild(bullet, true);
                    }),
                nullptr));
        });

    // ���ж���
    bullet->runAction(
        Sequence::create(
            DelayTime::create(attackDuration),
            bulletAction,
            nullptr)
    );
}

bool FireTower_3::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("FireBottleLevel3.png");
    // �ӵ���ͼƬ
    Bullet = "BottleBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 300;
    damage = 1000;
    attackInterval = 1.0f;

    consumption = 250;
    rotateSpeed = 180;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void FireTower_3::clicked(int& moneyScene)
{
    Vec2 positionDelete = Vec2(40, -40);
    auto oldTower = this;
    Vec2 pos = oldTower->getPosition();

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("BottleRemove3.png", "BottleRemove3.png");
    towerDelete->setPosition(positionDelete);
    this->bottom->addChild(towerDelete, 4, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(150);
                }
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->bottom->removeFromParent();
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });
}

void FireTower_3::attackTarget()
{
    // ��ȡĿ��λ��
    Target* thisTarget = this->target;

    // ��ȡ������ǰλ��
    cocos2d::Vec2 towerPosition = getPosition();
    // ���������������
    std::random_device rd;  // ��ȡ���������
    std::mt19937 gen(rd()); // ʹ��÷ɭ��ת�㷨���������
    std::uniform_int_distribution<> dis(0, 100); // ���巶Χ

    // ���������
    int randomNumber = dis(gen);

    int Damage;
    if (randomNumber < 30) {
        Damage = getDamage();
    }
    else {
        Damage = 1;
    }
    // �����ڵ�����
    auto bullet = Sprite::create(Bullet);
    bullet->setPosition(towerPosition);
    this->getParent()->addChild(bullet, 2);
    bullet->setVisible(false);

    // �ӵ�����
    auto bulletAction = CallFunc::create([=]() {
        cocos2d::Vec2 targetPosition = thisTarget->getPosition();
        // �����ӵ���ת����
        // ����Ŀ�귽������
        cocos2d::Vec2 direction = this->target->getPosition() - towerPosition;
        // ����Ŀ��Ƕ�
        float targetAngle = -CC_RADIANS_TO_DEGREES(direction.getAngle()) + 90;
        // ��ת����
        auto rotateAction = RotateTo::create(0, targetAngle);
        // ����һ����Ŀ���ƶ��Ķ���
        float distance = targetPosition.distance(towerPosition);
        float duration = distance / 2000; //�ӵ����ٶ�
        auto moveAction = MoveTo::create(duration, targetPosition);
        // ִ�ж���
        bullet->setVisible(true);
        bullet->runAction(
            Sequence::create(
                rotateAction,
                moveAction,
                // ����һ���ص���������Ŀ��λ�ô����ڵ���ըЧ��     
                CallFunc::create([=]() {
                    if (thisTarget && thisTarget->isAlive()) {
                        // ��Ŀ��λ�ô�����ըЧ��
                        auto explosion = Sprite::create(Explosion);
                        explosion->setPosition(targetPosition);
                        thisTarget->getParent()->addChild(explosion);
                        explosion->runAction(Sequence::create(
                            DelayTime::create(0.1f),
                            FadeOut::create(0.1f),// ����
                            RemoveSelf::create(),
                            nullptr
                        ));
                        // �����˺�
                        thisTarget->takeDamage(Damage);
                    }
                    // �Ƴ��ڵ�����
                    this->getParent()->removeChild(bullet, true);
                    }),
                nullptr));
        });

    // ���ж���
    bullet->runAction(
        Sequence::create(
            DelayTime::create(attackDuration),
            bulletAction,
            nullptr)
    );
}

bool SunflowerTower_1::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("SunflowerLevel1.png");
    // �ӵ���ͼƬ
    Bullet = "SunflowerBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 250;
    damage = 10;
    attackInterval = 1.0f;

    consumption = 200;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void SunflowerTower_1::clicked(int& moneyScene) {
    Vec2 positionUp = Vec2(40, 120);
    Vec2 positionDelete = Vec2(40, -40);

    // ������ť
    auto towerUp = cocos2d::ui::Button::create("StarUpgrade1.png", "StarUpgrade1.png", "StarUpgradeUn1.png");
    towerUp->setPosition(positionUp);
    this->bottom->addChild(towerUp, 3, "But");

    auto oldTower = this;
    Vec2 pos = oldTower->getPosition();

    // ����ť����¼�
    towerUp->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerUpdata.mp3"); //��������������Ч
            // �ڵ�ǰλ�ô�������
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto tower = SunflowerTower_2::create();  // ������������                     
                tower->setPosition(pos);  // ��������λ��
                

                auto bot = Sprite::create("Bottom.png");
                bot->setPosition(bottom->getPosition());
                tower->bottom = bot;//
                tower->thisTowerPositionIS = oldTower->thisTowerPositionIS;//
                oldTower->thisTowerPositionIS->towerofThisPosition = tower;//

                oldTower->getParent()->addChild(bot, 1);
                oldTower->getParent()->addChild(tower, 2);

                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(-300);
                }
                bottom->removeFromParent();
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });

    // ���õ��״̬
    if (moneyScene >= 300)
    {
        towerUp->setEnabled(true);
    }
    else
    {
        towerUp->setEnabled(false);
    }

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("BottleRemove2.png", "BottleRemove2.png");
    towerDelete->setPosition(positionDelete);
    this->bottom->addChild(towerDelete, 3, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(120);
                }
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->bottom->removeFromParent();
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });
}

bool SunflowerTower_2::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("SunflowerLevel2.png");
    // �ӵ���ͼƬ
    Bullet = "SunflowerBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 250;
    damage = 15;
    attackInterval = 1.0f;

    consumption = 200;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void SunflowerTower_2::clicked(int& moneyScene)
{
    Vec2 positionUp = Vec2(40, 120);
    Vec2 positionDelete = Vec2(40, -40);

    // ������ť
    auto towerUp = cocos2d::ui::Button::create("StarUpgrade2.png", "StarUpgrade2.png", "StarUpgradeUn2.png");
    towerUp->setPosition(positionUp);
    this->bottom->addChild(towerUp, 3, "But");

    auto oldTower = this;
    Vec2 pos = oldTower->getPosition();

    // ����ť����¼�
    towerUp->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerUpdata.mp3"); //��������������Ч
            // �ڵ�ǰλ�ô�������
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto tower = SunflowerTower_3::create();  // ������������                     
                tower->setPosition(pos);  // ��������λ��
                

                auto bot = Sprite::create("Bottom.png");
                bot->setPosition(bottom->getPosition());
                tower->bottom = bot;//
                tower->thisTowerPositionIS = oldTower->thisTowerPositionIS;//
                oldTower->thisTowerPositionIS->towerofThisPosition = tower;//

                oldTower->getParent()->addChild(bot, 1);
                oldTower->getParent()->addChild(tower, 2);

                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(-400);
                }
                bottom->removeFromParent();
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });

    // ���õ��״̬
    if (moneyScene >= 400)
    {
        towerUp->setEnabled(true);
    }
    else
    {
        towerUp->setEnabled(false);
    }

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("BottleRemove3.png", "BottleRemove3.png");
    towerDelete->setPosition(positionDelete);
    this->bottom->addChild(towerDelete, 3, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(150);
                }
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->bottom->removeFromParent();
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });
}

bool SunflowerTower_3::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("SunflowerLevel3.png");
    // �ӵ���ͼƬ
    Bullet = "SunflowerBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 250;
    damage = 25;
    attackInterval = 1.0f;

    consumption = 200;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void SunflowerTower_3::clicked(int& moneyScene)
{
    Vec2 positionDelete = Vec2(40, -40);
    auto oldTower = this;
    Vec2 pos = oldTower->getPosition();

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("StarRemove3.png", "StarRemove3.png");
    towerDelete->setPosition(positionDelete);
    this->bottom->addChild(towerDelete, 3, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(300);
                }
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->bottom->removeFromParent();
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });
}

bool StarTower_1::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("StarLevel1.png");
    // �ӵ���ͼƬ
    Bullet = "StarBulletLevel1.png";
    // ��ըЧ��
    Explosion = "StarBoom.png";
    // ������̡��������͹������
    range = 200;
    damage = 15;
    attackInterval = 1.0f;

    consumption = 200;
    bulletRange = 500;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void StarTower_1::clicked(int& moneyScene)
{
    Vec2 positionUp = Vec2(40, 120);
    Vec2 positionDelete = Vec2(40, -40);

    // ������ť
    auto towerUp = cocos2d::ui::Button::create("StarUpgrade1.png", "StarUpgrade1.png", "StarUpgradeUn1.png");
    towerUp->setPosition(positionUp);
    auto oldTower = this;

    oldTower->addChild(towerUp, 3, "But");
    Vec2 pos = oldTower->getPosition();

    // ����ť����¼�
    towerUp->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerUpdata.mp3"); //��������������Ч
            // �ڵ�ǰλ�ô�������
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto tower = StarTower_2::create();  // ������������                     
                tower->setPosition(pos);  // ��������λ��

                tower->bottom = nullptr;//
                tower->thisTowerPositionIS = oldTower->thisTowerPositionIS;//
                oldTower->thisTowerPositionIS->towerofThisPosition = tower;//

                oldTower->getParent()->addChild(tower, 2);

                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(-300);
                }
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });

    // ���õ��״̬
    if (moneyScene >= 300)
    {
        towerUp->setEnabled(true);
    }
    else
    {
        towerUp->setEnabled(false);
    }

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("BottleRemove2.png", "BottleRemove2.png");
    towerDelete->setPosition(positionDelete);
    oldTower->addChild(towerDelete, 3, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(120);
                }
                oldTower->bottom = nullptr;
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });
}

bool StarTower_2::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("StarLevel2.png");
    // �ӵ���ͼƬ
    Bullet = "StarBulletLevel2.png";
    // ��ըЧ��
    Explosion = "StarBoom.png";
    // ������̡��������͹������
    range = 250;
    damage = 20;
    attackInterval = 1.0f;

    consumption = 200;
    bulletRange = 500;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void StarTower_2::clicked(int& moneyScene)
{
    Vec2 positionUp = Vec2(45, 120);
    Vec2 positionDelete = Vec2(45, -40);

    // ������ť
    auto towerUp = cocos2d::ui::Button::create("StarUpgrade2.png", "StarUpgrade2.png", "StarUpgradeUn2.png");
    towerUp->setPosition(positionUp);
    auto oldTower = this;

    oldTower->addChild(towerUp, 3, "But");
    Vec2 pos = oldTower->getPosition();

    // ����ť����¼�
    towerUp->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerUpdata.mp3"); //��������������Ч
            // �ڵ�ǰλ�ô�������
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto tower = StarTower_3::create();  // ������������                     
                tower->setPosition(pos);  // ��������λ��
                

                tower->bottom = nullptr;//
                tower->thisTowerPositionIS = oldTower->thisTowerPositionIS;//
                oldTower->thisTowerPositionIS->towerofThisPosition = tower;//

                oldTower->getParent()->addChild(tower, 2);

                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(-400);
                }
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });

    // ���õ��״̬
    if (moneyScene >= 400)
    {
        towerUp->setEnabled(true);
    }
    else
    {
        towerUp->setEnabled(false);
    }

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("BottleRemove3.png", "BottleRemove3.png");
    towerDelete->setPosition(positionDelete);
    oldTower->addChild(towerDelete, 3, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(150);
                }
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });
}

bool StarTower_3::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("StarLevel3.png");
    // �ӵ���ͼƬ
    Bullet = "StarBulletLevel3.png";
    // ��ըЧ��
    Explosion = "StarBoom.png";
    // ������̡��������͹������
    range = 300;
    damage = 25;
    attackInterval = 1.0f;

    consumption = 200;
    bulletRange = 500;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void StarTower_3::clicked(int& moneyScene)
{
    Vec2 positionDelete = Vec2(50, -40);
    auto oldTower = this;
    Vec2 pos = oldTower->getPosition();

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("StarRemove3.png", "StarRemove3.png");
    towerDelete->setPosition(positionDelete);
    oldTower->addChild(towerDelete, 3, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(300);
                }
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });
}








bool ShitTower_1::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("ShitTowerlevel1.png");
    // ������̡��������͹������
    range = 0;
    damage = 14;
    attackInterval = 1.0f;
    Bullet = "jinbi3.png";
    consumption = 0;
    cooldownTimer = 3.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void ShitTower_1::clicked(int& moneyScene)
{
    Vec2 positionUp = Vec2(25, 120);
    Vec2 positionDelete = Vec2(25, -40);

    // ������ť
    auto towerUp = cocos2d::ui::Button::create("BottleUpgrade1.png", "BottleUpgrade1.png", "BottleUpgradeUn1.png");
    towerUp->setPosition(positionUp);
    auto oldTower = this;

    oldTower->addChild(towerUp, 3, "But");
    Vec2 pos = oldTower->getPosition();

    // ����ť����¼�
    towerUp->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerUpdata.mp3"); //��������������Ч
            // �ڵ�ǰλ�ô�������
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto tower = ShitTower_2::create();  // ������������                     
                tower->setPosition(pos);  // ��������λ��

                tower->bottom = nullptr;//
                tower->thisTowerPositionIS = oldTower->thisTowerPositionIS;//
                oldTower->thisTowerPositionIS->towerofThisPosition = tower;//

                oldTower->getParent()->addChild(tower, 2);

                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(-150);
                }
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });

    // ���õ��״̬
    if (moneyScene >= 150)
    {
        towerUp->setEnabled(true);
    }
    else
    {
        towerUp->setEnabled(false);
    }

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("BottleRemove1.png", "BottleRemove1.png");
    towerDelete->setPosition(positionDelete);
    oldTower->addChild(towerDelete, 3, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(60);
                }
                oldTower->bottom = nullptr;
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });
}

bool ShitTower_2::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("ShitTowerlevel2.png");

    // ������̡��������͹������
    range = 0;
    damage = 50;
    attackInterval = 1.0f;
    Bullet = "jinbi1.png";
    consumption = 0;
    cooldownTimer = 3.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void ShitTower_2::clicked(int& moneyScene)
{
    Vec2 positionUp = Vec2(30, 120);
    Vec2 positionDelete = Vec2(30, -40);

    // ������ť
    auto towerUp = cocos2d::ui::Button::create("BottleUpgrade2.png", "BottleUpgrade2.png", "BottleUpgradeUn2.png");
    towerUp->setPosition(positionUp);
    auto oldTower = this;

    oldTower->addChild(towerUp, 3, "But");
    Vec2 pos = oldTower->getPosition();

    // ����ť����¼�
    towerUp->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerUpdata.mp3"); //��������������Ч
            // �ڵ�ǰλ�ô�������
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto tower = ShitTower_3::create();  // ������������                     
                tower->setPosition(pos);  // ��������λ��


                tower->bottom = nullptr;//
                tower->thisTowerPositionIS = oldTower->thisTowerPositionIS;//
                oldTower->thisTowerPositionIS->towerofThisPosition = tower;//

                oldTower->getParent()->addChild(tower, 2);

                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(-250);
                }
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });

    // ���õ��״̬
    if (moneyScene >= 250)
    {
        towerUp->setEnabled(true);
    }
    else
    {
        towerUp->setEnabled(false);
    }

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("BottleRemove2.png", "BottleRemove2.png");
    towerDelete->setPosition(positionDelete);
    oldTower->addChild(towerDelete, 3, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(120);
                }
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });
}

bool ShitTower_3::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("ShitTowerlevel3.png");
    // ������̡��������͹������
    range = 0;
    damage = 75;
    attackInterval = 1.0f;
    Bullet = "jinbi2.png";
    consumption = 0;
    cooldownTimer = 3.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

void ShitTower_3::clicked(int& moneyScene)
{
    Vec2 positionDelete = Vec2(30, -40);
    auto oldTower = this;
    Vec2 pos = oldTower->getPosition();

    // ɾ����ť
    auto towerDelete = cocos2d::ui::Button::create("BottleRemove3.png", "BottleRemove3.png");
    towerDelete->setPosition(positionDelete);
    oldTower->addChild(towerDelete, 3, "But");

    towerDelete->addClickEventListener([=](Ref* sender) {
        if (!oldTower->getTarget())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSell.mp3"); //��������������Ч
            auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
            if (button)
            {
                auto s = dynamic_cast<SceneBase*>(oldTower->getParent());
                if (s)
                {
                    s->updateMoney(150);
                }
                oldTower->thisTowerPositionIS->towerofThisPosition = nullptr;
                oldTower->setVisible(false);
                oldTower->removeFromParent();
            }
        }
        });
}