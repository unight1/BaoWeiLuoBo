  #ifndef __MONSTERBASE_H__
#define __MONSTERBASE_H__

#include "Target.h"
#include "Carrot.h"

class Monster : public Target {
public:
    // �ƶ���ָ��λ��(��ֱ��)
    void moveTo(Vec2 position);
    //�γɶ�������
    virtual void moveToSequence(const std::vector<Vec2>& positions);
    // ������
    virtual ~Monster() {};

 

protected:
    int speed;//����
    int hurt;//�˺�
    Monster() {};// �ܱ����Ĺ��캯��
};

#endif // __MONSTERBASE_H__