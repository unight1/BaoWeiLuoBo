#ifndef __TOWERBASE_H__
#define __TOWERBASE_H__

#include "Target.h"
#include "MonsterBase.h"
#include "SceneMain.h"

USING_NS_CC;

class TowerPosition;

class Tower : public cocos2d::Sprite {
public:
    // ��ʼ������
    virtual bool init() override;
    // ���컨��
    int getConsumption() const;
    // ���
    float getRange() const;
    // �޸����
    void setRange(float range);
    // ������
    int getDamage() const;
    // �޸Ĺ�����
    void setDamage(int damage);
    // Ŀ��
    Target* getTarget() const;
    // �޸�Ŀ��
    void setTarget(Target* target);
    // ��������������ʱ��
    float getAttackDuration();
    // �������
    float getAttackInterval() const;
    // �޸Ĺ������
    void setAttackInterval(float attackInterval);

    // ���������Ĺ�������
    virtual void playAttackAnimation() = 0;
    // ִ�й����߼�
    virtual void attack() = 0;

    // ����߼�
    virtual void clicked(int &sceneMoney) = 0;

    Sprite* bottom = nullptr;
    TowerPosition* thisTowerPositionIS =nullptr;



protected:
    // ���컨��
    int consumption;
    // ���
    float range;
    // ������
    int damage;
    // Ŀ��
    Target* target;
    // ��������������ʱ��
    float attackDuration;
    // �������
    float attackInterval;
    // ��ȴ��ʱ��
    float cooldownTimer;
};

// ƿ����
class BottleTower : public Tower {
public:
    // ��ʼ������
    virtual bool init() override;
  //  CREATE_FUNC(BottleTower);
    // ����ѭ�����еĸ��º���
    void update(float delta);

    // ���������Ĺ�������
    void playAttackAnimation() override;
    // ִ�й����߼�
    void attack() override;
    // �����ӵ�
    void attackTarget();
protected:
    // ��ת�ٶ�
    float rotateSpeed;
    // �ӵ���ͼƬ
    std::string Bullet;
    // ��ըЧ��
    std::string Explosion;
};

// ̫����
class SunflowerTower : public Tower {
public:
    // ��ʼ������
    virtual bool init() override;
  //  CREATE_FUNC(SunflowerTower);
    // ����ѭ�����еĸ��º���
    void update(float delta);

    // ���������Ĺ�������
    void playAttackAnimation() override;
    // ִ�й����߼�
    void attack() override;
    // �����ӵ�
    void attackTarget();
protected:
    // �ӵ���ͼƬ
    std::string Bullet;
    // ��ըЧ��
    std::string Explosion;
};

// ������
class StarTower : public Tower {
public:
    // ��ʼ������
    virtual bool init() override;
   // CREATE_FUNC(StarTower);
    // ����ѭ�����еĸ��º���
    void update(float delta);

    // ���������Ĺ�������
    void playAttackAnimation() override;
    // ִ�й����߼�
    void attack() override;
    // �����ӵ�
    void attackTarget();
protected:
    // ��ը��Χ
    float bulletRange;
    // �ӵ���ͼƬ
    std::string Bullet;
    // ��ըЧ��
    std::string Explosion;
};

#endif // __TOWERBASE_H__