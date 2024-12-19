#include "TowerBase.h"

// Tower����ʵ��
bool Tower::init() {
    if (!Sprite::init()) {
        return false;
    }

    return true;
}

int Tower::getConsumption() const
{
    return consumption;
}

float Tower::getRange() const {
    return range;
}

void Tower::setRange(float range) {
    this->range = range;
}

int Tower::getDamage() const {
    return damage;
}

void Tower::setDamage(int damage) {
    this->damage = damage;
}

Target* Tower::getTarget() const {
    return target;
}

void Tower::setTarget(Target* target) {
    this->target = target;
}

float Tower::getAttackDuration() {
    return attackDuration;
}

float Tower::getAttackInterval() const {
    return attackInterval;
}

void Tower::setAttackInterval(float attackInterval) {
    this->attackInterval = attackInterval;
}


// bottleTower����ʵ��
bool BottleTower::init() {
    if (!Sprite::init()) {
        return false;
    }

    return true;
}

void BottleTower::update(float delta) {
    // ������ȴ��ʱ��
    cooldownTimer -= delta;

    if (cooldownTimer <= 0) {
        // ��ȴ���������й���
        cooldownTimer = 0.0f;
        attack();
    }
}

void BottleTower::attack() {
    // �ж��Ƿ��������
    float thisdistance = 0;
    if (target && target->isAlive()) {
        thisdistance = getPosition().distance(target->getPosition());
    }

    if (target && target->isAlive() && thisdistance + target->getRadius() <= getRange()) {
        // ����������Ŀ��
    }
    else {
        // ��������
        // ѡ������ھ�����������ĵ���
        Vector<Node*> enemies = getScene()->getChildren();
        Target* nearestEnemy = nullptr;
        float minDistance = 999999;
        for (auto node : enemies) {
            auto enemy = dynamic_cast<Monster*>(node);
            if (enemy && enemy->isAlive()) {
                float distance = getPosition().distance(enemy->getPosition());
                if (enemy->isAlive() && distance + enemy->getRadius() <= getRange() && distance < minDistance) {
                    nearestEnemy = enemy;
                    minDistance = distance;
                }
            }
        }
        // ����е�������̣���������Ŀ��
        if (nearestEnemy) {
            setTarget(nearestEnemy);
        }
        else {
            setTarget(nullptr);
        }
    }

    // �������ȷ��Ŀ�꣬����
    if (target && target->isAlive()) {
        auto seq = Sequence::create(
            CallFunc::create([this]() {
                if (target && target->isAlive()) {
                    // һ��ֻ��ִ��һ����������
                    cooldownTimer = 99999;
                    // ���Ź�������
                    playAttackAnimation();
                    // ��������
                    attackTarget();
                }
                }),
            nullptr
        );
        this->runAction(seq);
    }
}

void BottleTower::playAttackAnimation() {
    // ����������ת����
    // ��ȡ������ǰλ�úͷ���
    cocos2d::Vec2 towerPosition = getPosition();
    float towerAngle = this->getRotation();
    // ����Ŀ�귽������
    cocos2d::Vec2 direction = this->target->getPosition() - towerPosition;
    // ����Ŀ��Ƕ�
    float targetAngle = -CC_RADIANS_TO_DEGREES(direction.getAngle()) + 90;
    // ������תʱ��
    float rotate = targetAngle - towerAngle;
    while (rotate > 180) {
        rotate -= 360;
    }
    while (rotate < -180) {
        rotate += 360;
    }
    float rotateTime = abs(rotate / rotateSpeed);

    // ���ÿ���ʱ��
    attackDuration = rotateTime + 0.075f;

    // ����һ�� RotateTo ��������������ת��Ŀ��Ƕ�
    auto rotateAction = RotateTo::create(rotateTime, targetAngle);

    // ������ģ�⿪�𶯻�
    // ����һ�� ScaleTo �������������� 0.1 ������ X ���������ŵ� 0.8 ��
    auto scaleXOut = ScaleTo::create(0.1f, 1.0f, 0.8f);
    // ����һ�� ScaleTo �������������� 0.1 ������ X �����ϻָ���ԭʼ��С
    auto scaleXIn = ScaleTo::create(0.1f, 1.0f, 1.0f);

    // ������ȴ��ʱ��
    auto callbackAction = CallFunc::create([=]() {
        cooldownTimer = attackInterval;
        });

    // �ڹ���������������ת�����Ϳ��𶯻�
    auto sequenceAction = Sequence::create(rotateAction, scaleXOut, scaleXIn, callbackAction, nullptr);
    runAction(sequenceAction);

}

void BottleTower::attackTarget() {

    // ��ȡĿ��λ��
    Target* thisTarget = this->target;
    cocos2d::Vec2 targetPosition = thisTarget->getPosition();
    // ��ȡ������ǰλ��
    cocos2d::Vec2 towerPosition = getPosition();
    int Damage = getDamage();
    // �����ڵ�����
    auto bullet = Sprite::create(Bullet);
    bullet->setPosition(towerPosition);
    this->getParent()->addChild(bullet, 2);
    bullet->setVisible(false);

    // �ӵ�����
    auto bulletAction = CallFunc::create([=]() {
       
        // �����ӵ���ת����
        // ����Ŀ�귽������
        cocos2d::Vec2 direction = targetPosition - towerPosition;
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



// sunTower����ʵ��
bool SunflowerTower::init() {
    if (!Sprite::init()) {
        return false;
    }

    return true;
}

void SunflowerTower::update(float delta) {
    // ������ȴ��ʱ��
    cooldownTimer -= delta;

    if (cooldownTimer <= 0) {
        // ��ȴ���������й���
        cooldownTimer = 0.0f;
        attack();
    }
}

void SunflowerTower::attack() {
    // �ж��Ƿ��������
    float thisdistance = 0;
    if (target && target->isAlive()) {
        thisdistance = getPosition().distance(target->getPosition());
    }

    if (target && target->isAlive() && thisdistance + target->getRadius() <= getRange()) {
        // ����������Ŀ��
    }
    else {
        // ��������
        // ѡ������ھ�����������ĵ���
        Vector<Node*> enemies = getScene()->getChildren();
        Target* nearestEnemy = nullptr;
        float minDistance = 999999;
        for (auto node : enemies) {
            auto enemy = dynamic_cast<Monster*>(node);
            if (enemy && enemy->isAlive()) {
                float distance = getPosition().distance(enemy->getPosition());
                if (enemy->isAlive() && distance + enemy->getRadius() <= getRange() && distance < minDistance) {
                    nearestEnemy = enemy;
                    minDistance = distance;
                }
            }
        }
        // ����е�������̣���������Ŀ��
        if (nearestEnemy) {
            setTarget(nearestEnemy);
        }
        else {
            setTarget(nullptr);
        }
    }

    // �������ȷ��Ŀ�꣬����
    if (target && target->isAlive()) {
        auto seq = Sequence::create(
            CallFunc::create([this]() {
                if (getTarget()) {
                    // һ��ֻ��ִ��һ����������
                    cooldownTimer = 99999;
                    // ���Ź�������
                    playAttackAnimation();
                    // ��������
                    attackTarget();
                }
                }),
            nullptr
        );
        this->runAction(seq);
    }
}

void SunflowerTower::playAttackAnimation() {
    // �����ڵ�����
    auto bullet = Sprite::create(Bullet);
    bullet->setPosition(this->getPosition());
    this->getParent()->addChild(bullet);
    auto setCooldownTimer = CallFunc::create([=]() { cooldownTimer = attackInterval; });
    // ̫����Ч
    bullet->runAction(
        Sequence::create(
            ScaleTo::create(0.15f, 3.0f, 3.0f),// ����
            FadeOut::create(0.05f),// ����
            RemoveSelf::create(),// �Ƴ��ڵ�����
            setCooldownTimer,
            nullptr)
    );
}

void SunflowerTower::attackTarget() {
    // ������������е�Ŀ��
    Vector<Node*> enemies = getScene()->getChildren();
    for (auto node : enemies) {
        auto enemy = dynamic_cast<Target*>(node);
        if (enemy && enemy->isAlive()) {
            float distance = getPosition().distance(enemy->getPosition());
            if (distance + enemy->getRadius() <= getRange()) {
                enemy->takeDamage(getDamage());
                // ��Ŀ��λ�ô�����ըЧ��
                auto explosion = Sprite::create(Explosion);
                explosion->setPosition(enemy->getPosition());
                this->getParent()->addChild(explosion);
                explosion->runAction(Sequence::create(
                    DelayTime::create(0.1f),
                    FadeOut::create(0.1f),// ����
                    RemoveSelf::create(),
                    nullptr
                ));
            }
        }
    }
}



// starTower����ʵ��
bool StarTower::init() {
    if (!Sprite::init()) {
        return false;
    }

    return true;
}

void StarTower::update(float delta) {
    // ������ȴ��ʱ��
    cooldownTimer -= delta;

    if (cooldownTimer <= 0) {
        // ��ȴ���������й���
        cooldownTimer = 0.0f;
        attack();
    }
}

void StarTower::attack() {
    // �ж��Ƿ��������
    float thisdistance = 0;
    if (target && target->isAlive()) {
        thisdistance = getPosition().distance(target->getPosition());
    }

    if (target && target->isAlive() && thisdistance + target->getRadius() <= getRange()) {
        // ����������Ŀ��
    }
    else {
        // ��������
        // ѡ������ھ�����������ĵ���
        Vector<Node*> enemies = getScene()->getChildren();
        Target* nearestEnemy = nullptr;
        float minDistance = 999999;
        for (auto node : enemies) {
            auto enemy = dynamic_cast<Monster*>(node);
            if (enemy && enemy->isAlive()) {
                float distance = getPosition().distance(enemy->getPosition());
                if (enemy->isAlive() && distance + enemy->getRadius() <= getRange() && distance < minDistance) {
                    nearestEnemy = enemy;
                    minDistance = distance;
                }
            }
        }
        // ����е�������̣���������Ŀ��
        if (nearestEnemy) {
            setTarget(nearestEnemy);
        }
        else {
            setTarget(nullptr);
        }
    }

    // �������ȷ��Ŀ�꣬����
    if (target && target->isAlive()) {
        auto seq = Sequence::create(
            CallFunc::create([this]() {
                if (getTarget()) {
                    // һ��ֻ��ִ��һ����������
                    cooldownTimer = 99999;
                    // ���Ź�������
                    playAttackAnimation();
                    // ��������
                    attackTarget();
                }
                }),
            nullptr
        );
        this->runAction(seq);
    }
}

void StarTower::playAttackAnimation() {
    cooldownTimer = attackInterval;
    // û�п��𶯻�
}

void StarTower::attackTarget() {
    // ��ȡĿ��λ��
    Target* thisTarget = this->target;
    cocos2d::Vec2 targetPosition = thisTarget->getPosition();
    // ��ȡ������ǰλ�úͷ���
    cocos2d::Vec2 towerPosition = getPosition();
    int Damage = getDamage();
    // �����ڵ�����
    auto bullet = Sprite::create(Bullet);
    bullet->setPosition(towerPosition);
    this->getParent()->addChild(bullet, 2);
    bullet->setVisible(false);

    // �ӵ�����
    auto bulletAction = CallFunc::create([=]() {
        // ����һ����Ŀ���ƶ��Ķ���
        float distance = targetPosition.distance(towerPosition);
        float duration = distance / 1000; //�ӵ����ٶ�
        auto moveAction = MoveTo::create(duration, targetPosition);
        // ִ�ж���
        bullet->setVisible(true);
        bullet->runAction(
            Sequence::create(
                moveAction,
                // ����һ���ص���������Ŀ��λ�ô����ڵ���ըЧ��
                CallFunc::create([=]() {
                    if (thisTarget && thisTarget->isAlive()) {
                        // ��Ŀ��λ�ô�����ըЧ��
                        auto explosion = Sprite::create(Explosion);
                        explosion->setPosition(thisTarget->getPosition());
                        this->getParent()->addChild(explosion);
                        explosion->runAction(Sequence::create(
                            ScaleTo::create(0.1f, 1.5f, 1.5f),// ����
                            FadeOut::create(0.05f),// ����
                            RemoveSelf::create(),// �Ƴ��ڵ�����
                            nullptr
                        ));
                        // ��Ŀ������˺�
                        thisTarget->takeDamage(Damage * 0.5);
                        // �����˺�
                        Vector<Node*> enemies = getScene()->getChildren();
                        for (auto node : enemies) {
                            auto enemy = dynamic_cast<Target*>(node);
                            if (enemy && enemy->isAlive()) {
                                float distance = getPosition().distance(enemy->getPosition());
                                if (distance + enemy->getRadius() <= bulletRange) {
                                    enemy->takeDamage(Damage * 0.5);
                                }
                            }
                        }
                    }
                    // �Ƴ��ڵ�����
                    this->getParent()->removeChild(bullet, true);
                    }),
                nullptr));
        });

    // ���ж���
    bullet->runAction(
        Sequence::create(
            bulletAction,
            nullptr)
    );
}
// FireTower����ʵ��
bool FireTower::init() {
    if (!Sprite::init()) {
        return false;
    }

    return true;
}

void FireTower::update(float delta) {
    // ������ȴ��ʱ��
    cooldownTimer -= delta;

    if (cooldownTimer <= 0) {
        // ��ȴ���������й���
        cooldownTimer = 0.0f;
        attack();
    }
}

void FireTower::attack() {
    // �ж��Ƿ��������
    float thisdistance = 0;
    if (target && target->isAlive()) {
        thisdistance = getPosition().distance(target->getPosition());
    }

    if (target && target->isAlive() && thisdistance + target->getRadius() <= getRange()) {
        // ����������Ŀ��
    }
    else {
        // ��������
        // ѡ������ھ�����������ĵ���
        Vector<Node*> enemies = getScene()->getChildren();
        Target* nearestEnemy = nullptr;
        float minDistance = 999999;
        for (auto node : enemies) {
            auto enemy = dynamic_cast<Monster*>(node);
            if (enemy && enemy->isAlive()) {
                float distance = getPosition().distance(enemy->getPosition());
                if (enemy->isAlive() && distance + enemy->getRadius() <= getRange() && distance < minDistance) {
                    nearestEnemy = enemy;
                    minDistance = distance;
                }
            }
        }
        // ����е�������̣���������Ŀ��
        if (nearestEnemy) {
            setTarget(nearestEnemy);
        }
        else {
            setTarget(nullptr);
        }
    }

    // �������ȷ��Ŀ�꣬����
    if (target && target->isAlive()) {
        auto seq = Sequence::create(
            CallFunc::create([this]() {
                if (target && target->isAlive()) {
                    // һ��ֻ��ִ��һ����������
                    cooldownTimer = 99999;
                    // ���Ź�������
                    playAttackAnimation();
                    // ��������
                    attackTarget();
                }
                }),
            nullptr
        );
        this->runAction(seq);
    }
}

void FireTower::playAttackAnimation() {
    // ����������ת����
    // ��ȡ������ǰλ�úͷ���
    cocos2d::Vec2 towerPosition = getPosition();
    float towerAngle = this->getRotation();
    // ����Ŀ�귽������
    cocos2d::Vec2 direction = this->target->getPosition() - towerPosition;
    // ����Ŀ��Ƕ�
    float targetAngle = -CC_RADIANS_TO_DEGREES(direction.getAngle()) + 90;
    // ������תʱ��
    float rotate = targetAngle - towerAngle;
    while (rotate > 180) {
        rotate -= 360;
    }
    while (rotate < -180) {
        rotate += 360;
    }
    float rotateTime = abs(rotate / rotateSpeed);

    // ���ÿ���ʱ��
    attackDuration = rotateTime + 0.075f;

    // ����һ�� RotateTo ��������������ת��Ŀ��Ƕ�
    auto rotateAction = RotateTo::create(rotateTime, targetAngle);

    // ������ģ�⿪�𶯻�
    // ����һ�� ScaleTo �������������� 0.1 ������ X ���������ŵ� 0.8 ��
    auto scaleXOut = ScaleTo::create(0.1f, 1.0f, 0.8f);
    // ����һ�� ScaleTo �������������� 0.1 ������ X �����ϻָ���ԭʼ��С
    auto scaleXIn = ScaleTo::create(0.1f, 1.0f, 1.0f);

    // ������ȴ��ʱ��
    auto callbackAction = CallFunc::create([=]() {
        cooldownTimer = attackInterval;
        });

    // �ڹ���������������ת�����Ϳ��𶯻�
    auto sequenceAction = Sequence::create(rotateAction, scaleXOut, scaleXIn, callbackAction, nullptr);
    runAction(sequenceAction);

}

// ShitTower����ʵ��
bool ShitTower::init() {
    if (!Sprite::init()) {
        return false;
    }

    return true;
}

void ShitTower::update(float delta) {
    // ������ȴ��ʱ��
    cooldownTimer -= delta;

    if (cooldownTimer <= 0) {
        // ��ȴ���������й���
        cooldownTimer = 5.0f;
        attack();
    }
}

void ShitTower::attack() {
    playAttackAnimation();
    attackTarget();
}

void ShitTower::playAttackAnimation() {
    //���+���ͼ��
    auto bullet = Sprite::create(Bullet);
    bullet->setPosition(this->getPosition());
    this->getParent()->addChild(bullet,3);
    
    bullet->runAction(
        Sequence::create(
            FadeOut::create(0.1f),// ����
            RemoveSelf::create(),// �Ƴ����ͼ��
            nullptr)
    );
}

void ShitTower::attackTarget() {
    auto Damage = getDamage();
    auto s = dynamic_cast<SceneBase*>(this->getParent());
    if (s)
    {
        s->updateMoney(Damage);
    }
}
