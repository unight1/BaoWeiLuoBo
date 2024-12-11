#include "Carrot.h"
#include "audio/include/SimpleAudioEngine.h"

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
    // ����������Ч
    if (HP > 0) { // ȷ���ܲ�������
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("carrothurt.mp3"); //�����ܻ���Ч
    }

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
    this->carrot = Sprite::create("carrot1.png"); // ����1����Ѫ���ܲ�ͼƬ
    this->carrot->setPosition(Position);
    this->addChild(this->carrot);

    // Ϊ�ܲ����Ѫ���Ŀ��ӻ�
    this->carrot_HP = Sprite::create("CarrotHP.png");
    this->carrot_HP->setPosition(Vec2(Position.x, Position.y + 90));
    this->addChild(carrot_HP);

    // ��ʼ��Label
    std::string text = std::to_string(HP); // ������ת��Ϊ�ַ���
    this->carrotHP = Label::createWithTTF(text, "fonts/arial.ttf", 28);
    this->carrotHP->setTextColor(Color4B::BLACK);
    this->carrotHP->setPosition(Vec2(Position.x - 20, Position.y + 90));
    this->addChild(this->carrotHP);

    //����ܲ����ܲ�Ť���¼�
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0); // ���ð�ť��͸����Ϊ0��ʹ�䲻�ɼ�
    BUTTON->setContentSize(Size(this->carrot->getContentSize().width, this->carrot->getContentSize().height));
    BUTTON->setPosition(Position); // ���ð�ťλ�����ܲ�������ͬ
    BUTTON->addClickEventListener([this](Ref* sender) {// ����ť����¼�
        
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

        // ������ɺ�ָ�carrot���鵽������ʼǰ��λ��
        auto callback = [this]() {
            this->removeChild(this->carrot, true);
            if(HP==MaxHP)
                carrot = Sprite::create("carrot1.png");
            else {
                if (HP <= MaxHP / 3)
                {
                    carrot = Sprite::create("carrot11.png");
                }
                else if (HP <= MaxHP * 2 / 3)
                {
                    carrot = Sprite::create("carrot10.png");
                }
                else
                {
                    carrot = Sprite::create("carrot9.png");
                }
            }
            this->carrot->setPosition(Position);
            this->addChild(this->carrot);
        };

        // ����������Ӧ�õ�carrot�����ϣ��������ɻص�
        this->carrot->runAction(Sequence::create(animate, CallFunc::create(callback), nullptr));
        });
    this->addChild(BUTTON);
}
