#include "Tower.h"
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
    cooldownTimer = 0.0f;
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

