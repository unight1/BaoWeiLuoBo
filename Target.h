#ifndef __TARGET_H__
#define __TARGET_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
class Target : public Sprite {
public:
    // ������
    virtual ~Target() {};
    // ����˺�
    virtual void takeDamage(int damage);
    // �ж��Ƿ���
    bool isAlive() const;
    // ����Ѫ��
    void setHP(int HP);
    // ��ȡ�뾶
    int getRadius();
    //���ü���Ŀ��
    void setAllTarget();


protected:
    int HP;  // Ѫ��
    int maxHP; // ���Ѫ��
    int value;// ��ɱ����
    int radius;// �뾶
    ProgressTimer* Health = nullptr;// ��������ָ��
    Sprite* choose=nullptr;//ѡ�о���
    Target() {};// �ܱ����Ĺ��캯��
};

#endif // __TARGET_H__