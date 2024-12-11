  #ifndef __MONSTERBASE_H__
#define __MONSTERBASE_H__

#include "Target.h"
#include "Carrot.h"

class Monster : public Target {
public:
    // 移动到指定位置(走直线)
    void moveTo(Vec2 position);
    //形成动作序列
    virtual void moveToSequence(const std::vector<Vec2>& positions);
    // 虚析构
    virtual ~Monster() {};

 

protected:
    int speed;//移速
    int hurt;//伤害
    Monster() {};// 受保护的构造函数
};

#endif // __MONSTERBASE_H__