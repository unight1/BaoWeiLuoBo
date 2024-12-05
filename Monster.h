#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "MonsterBase.h"

class Sheep : public Monster {
public:
    CREATE_FUNC(Sheep);

    virtual void moveToSequence(const std::vector<Vec2>& positions) override;
    virtual bool init() override;

};


class Bird : public Monster {
public:
    CREATE_FUNC(Bird);

    virtual void moveToSequence(const std::vector<Vec2>& positions) override;
    virtual bool init() override;

};

class Star : public Monster {
public:
    CREATE_FUNC(Star);

    virtual void moveToSequence(const std::vector<Vec2>& positions) override;
    virtual bool init() override;

};
#endif // __MONSTER_H__