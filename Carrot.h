
#ifndef __CARROT_H__
#define __CARROT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class Carrot : public Sprite
{
private:
    int HP;                             //Ѫ��
    int MaxHP;                          //���Ѫ��
    Vec2 Position;                      //λ��
    Sprite* carrot;                     //�ܲ�����
    Sprite* carrot_HP;                  //Ѫ������
    Label* carrotHP;                    //Ѫ����ֵ

public:
    CREATE_FUNC(Carrot);

    void takeDamage(int damage);        //����˺�

    void setCarrotPosition(Vec2 pos);   //�����ܲ���λ��

    void putCarrot(int hp);                   //�����ܲ�

    Vec2 getCarrotPosition() const;     //��ȡ�ܲ���λ��

    bool isAlive();                     //�Ƿ���

    bool init() override;               // ��ʼ��

};

#endif // __CARROT_H__