#include "MonsterBase.h"
#include "SceneBase.h"
#include "Tower.h"

USING_NS_CC;



void Monster::moveTo(Vec2 position)
{
    this->stopAllActions(); // 停止当前进行中的动作
    auto distance = position - this->getPosition(); // 计算移动距离
    auto duration = distance.length() / speed; // 计算移动时间

    auto move = MoveTo::create(duration, position); // 创建移动动作
    this->runAction(move); // 执行移动动作
}

void Monster::moveToSequence(const std::vector<Vec2>& positions)
{
    this->stopAllActions(); // 停止当前进行中的动作

    Vector<FiniteTimeAction*> actions; // 创建一个动作数组
    Vec2 thisPosition = this->getPosition();
    for (Vec2 position : positions)//遍历坐标数组
    {
        auto distance = position - thisPosition; // 计算移动距离
        thisPosition = position;
        auto duration = distance.length() / speed; // 计算移动时间
        auto move = MoveTo::create(duration, position); // 创建移动动作
        actions.pushBack(move); // 将移动动作添加到数组中
    }

    //创建攻击动作
    auto attacked = CallFunc::create([=]() {
        auto target = this->getParent();
        auto scene = dynamic_cast<Carrot*>(target);
        scene->takeDamage(hurt);//根据怪物的伤害对萝卜造成伤害
        this->setHP(0);//攻击后怪物死亡

        });

    //将攻击动作与移动动作序列结合
    auto sequenceAction = Sequence::create(actions); // 创建序列动作
    auto sequence = Sequence::create(sequenceAction, attacked, nullptr);

    this->runAction(sequence); // 执行序列动作
}
