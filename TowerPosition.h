#ifndef __TOWERBASE__
#define __TOWERBASE__

#include "tower.h"
#include "cocos2d.h"

// ����һ������������
class TowerPosition : public cocos2d::Sprite
{
public:
    CREATE_FUNC(TowerPosition);
    // ������
    virtual ~TowerPosition() {};
    // ��ʼ������
    virtual bool init() override;

    Tower* towerofThisPosition = nullptr;
};

#endif // __TOWERBASE__
