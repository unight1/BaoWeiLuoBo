// TowerPosition.cpp
#include "TowerPosition.h"

USING_NS_CC;

bool TowerPosition::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    // ��ʼ����������ۺ�����
    this->initWithFile("addTower.png");
    towerofThisPosition = nullptr;

    return true;
}

