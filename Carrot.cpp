#include "Carrot.h"

bool Carrot::init()
{
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

bool Carrot::isAlive() {
    return HP>0;
}

void Carrot::takeDamage(int damage)
{
    HP -= damage;
    Sprite* newCarrot = nullptr; // ����һ���µ�ָ�����洢�¾���

    if (HP <= MaxHP / 3)
    {
        newCarrot = Sprite::create("carrot11.png");
    }
    else if (HP <= MaxHP * 2 / 3)
    {
        newCarrot = Sprite::create("carrot10.png");
    }
    else
    {
        newCarrot = Sprite::create("carrot9.png");
    }

    if (newCarrot) {
        // �Ƴ��ɾ���
        this->removeChild(this->carrot, true);
        // �������Ա���� carrot Ϊ�¾��飬������λ��
        this->carrot = newCarrot;
        this->carrot->setPosition(Position);
        this->addChild(this->carrot);
    }

    // ����Ѫ������
    std::string text = std::to_string(HP);
    if (this->carrotHP) {
        this->removeChild(this->carrotHP, true);
    }
    this->carrotHP = Label::createWithTTF(text, "fonts/arial.ttf", 28);
    this->carrotHP->setTextColor(Color4B::BLACK);
    this->carrotHP->setPosition(Vec2(Position.x - 20, Position.y + 90));
    this->addChild(this->carrotHP);
}

void Carrot::setCarrotPosition(Vec2 pos)
{
    Position = pos;
}

Vec2 Carrot::getCarrotPosition() const
{
    return Position;
}

void Carrot::putCarrot(int hp) {
    // ��ʼ��HP
    MaxHP = HP = hp;
    // ��ʼ����ۺ�����
    auto carrot = Sprite::create("carrot1.png");
    carrot->setPosition(Position);
    addChild(carrot);

    // Ϊ�ܲ����Ѫ���Ŀ��ӻ�
    auto carrot_HP = Sprite::create("CarrotHP.png");
    carrot_HP->setPosition(Vec2(Position.x, Position.y + 90));
    addChild(carrot_HP);

    // ��ʼ��Label
    std::string text = std::to_string(HP); // ������ת��Ϊ�ַ���
    auto carrotHP = Label::createWithTTF(text, "fonts/arial.ttf", 28);
    carrotHP->setTextColor(Color4B::BLACK);
    carrotHP->setPosition(Vec2(Position.x - 20, Position.y + 90));
    addChild(carrotHP);

    //����ܲ����ܲ�Ť���¼�
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0); // ���ð�ť��͸����Ϊ0��ʹ�䲻�ɼ�
    BUTTON->setContentSize(Size(carrot->getContentSize().width, carrot->getContentSize().height));
    BUTTON->setPosition(Position); // ���ð�ťλ�����ܲ�������ͬ
    BUTTON->addClickEventListener([carrot](Ref* sender) {// ����ť����¼�
        // ����һ���յĶ�������
        auto animation = Animation::create();
        // ��Ӷ���֡
        for (int i = 1; i <= 8; i++) {
            char filename[100];
            sprintf(filename, "carrot%d.png", i);
            auto frame = SpriteFrame::create(filename, Rect(0, 0, 120, 120));
            animation->addSpriteFrame(frame);
        }

        // ���ö�������
        animation->setDelayPerUnit(0.1f); // ÿ��0.1�벥��һ֡
        animation->setLoops(1); // ��������һ��

        // ����������������
        auto animate = Animate::create(animation);

        // ����������Ӧ�õ�carrot������
        carrot->runAction(Spawn::create(animate, nullptr));
        });
    addChild(BUTTON);
}
