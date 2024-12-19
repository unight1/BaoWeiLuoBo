#ifndef __TOWER_H__
#define __TOWER_H__

#include "TowerBase.h"
#include "SceneBase.h"
#include "TowerPosition.h"

class BottleTower_1 : public BottleTower {
public:
    // ��ʼ������
    virtual bool init() override;
    CREATE_FUNC(BottleTower_1);

    virtual void clicked(int &moneyScene)override;
};

class BottleTower_2 : public BottleTower {
public:
    // ��ʼ������
    virtual bool init() override;
    CREATE_FUNC(BottleTower_2);

    virtual void clicked(int& moneyScene)override;
};

class BottleTower_3 : public BottleTower {
public:
    // ��ʼ������
    virtual bool init() override;
    CREATE_FUNC(BottleTower_3);

    virtual void clicked(int& moneyScene)override;
};

class SunflowerTower_1 : public SunflowerTower {
public:
    // ��ʼ������
    bool init() override;
    CREATE_FUNC(SunflowerTower_1);

    virtual void clicked(int& moneyScene)override ;
};

class SunflowerTower_2 : public SunflowerTower {
public:
    // ��ʼ������
    bool init() override;
    CREATE_FUNC(SunflowerTower_2);

    virtual void clicked(int& moneyScene)override;
};

class SunflowerTower_3 : public SunflowerTower {
public:
    // ��ʼ������
    bool init() override;
    CREATE_FUNC(SunflowerTower_3);

    virtual void clicked(int& moneyScene)override;
};

class StarTower_1 : public StarTower {
public:
    // ��ʼ������
    bool init() override;
    CREATE_FUNC(StarTower_1);

    virtual void clicked(int& moneyScene)override;
};

class StarTower_2 : public StarTower {
public:
    // ��ʼ������
    bool init() override;
    CREATE_FUNC(StarTower_2);

    virtual void clicked(int& moneyScene)override;
};

class StarTower_3 : public StarTower {
public:
    // ��ʼ������
    bool init() override;
    CREATE_FUNC(StarTower_3);

    virtual void clicked(int& moneyScene)override;
};
class FireTower_1 : public FireTower {
public:
    // ��ʼ������
    virtual bool init() override;
    CREATE_FUNC(FireTower_1);

    virtual void clicked(int& moneyScene)override;
    void attackTarget()override;
};

class FireTower_2 : public FireTower {
public:
    // ��ʼ������
    virtual bool init() override;
    CREATE_FUNC(FireTower_2);

    virtual void clicked(int& moneyScene)override;
    void attackTarget();
};

class FireTower_3 : public FireTower {
public:
    // ��ʼ������
    virtual bool init() override;
    CREATE_FUNC(FireTower_3);

    virtual void clicked(int& moneyScene)override;
    void attackTarget();
};

class ShitTower_1 : public ShitTower {
public:
    // ��ʼ������
    virtual bool init() override;
    CREATE_FUNC(ShitTower_1);

    virtual void clicked(int& moneyScene)override;
};

class ShitTower_2 : public ShitTower {
public:
    // ��ʼ������
    virtual bool init() override;
    CREATE_FUNC(ShitTower_2);

    virtual void clicked(int& moneyScene)override;
};

class ShitTower_3 : public ShitTower {
public:
    // ��ʼ������
    virtual bool init() override;
    CREATE_FUNC(ShitTower_3);

    virtual void clicked(int& moneyScene)override;
};
#endif // __TOWER_H__