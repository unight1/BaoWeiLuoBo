#ifndef __OBSTACLEBASE_H__
#define __OBSTACLEBASE_H__

#include "Target.h"

class Obstacle : public Target {
public:
    // ������
    virtual ~Obstacle() {};

protected:
    Obstacle() {};// �ܱ����Ĺ��캯��
};

#endif // __OBSTACLEBASE_H__