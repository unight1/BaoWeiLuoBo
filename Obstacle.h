#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "ObstacleBase.h"

class Grass : public Obstacle {
public:
    CREATE_FUNC(Grass);

    virtual bool init() override;
};

class Stone : public Obstacle {
public:
    CREATE_FUNC(Stone);

    virtual bool init() override;
};

class Treasure : public Obstacle {
public:
    CREATE_FUNC(Treasure);

    virtual bool init() override;
};

#endif // __OBSTACLE_H__
