#include "Obstacle.h"

bool Grass::init() {
    if (!Sprite::init()) {
        return false;
    }

    // ��ʼ���ϰ������ۺ�����
    this->initWithFile("Grass.png");
    // ��ʼ��HP����ֵ�Ͱ뾶
    maxHP = HP = 100;
    value = 14;
    radius = 10;

    //���ϰ����������һ�����ɼ���ť������ʵ�ּ���
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0);
    BUTTON->setContentSize(Size(this->getContentSize().width, this->getContentSize().height));
    BUTTON->addClickEventListener([this](Ref* sender) {
        // ����ť����¼�
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
    addChild(BUTTON);

    return true;
}

bool Stone::init() {
    if (!Sprite::init()) {
        return false;
    }

    // ��ʼ���ϰ������ۺ�����
    this->initWithFile("Stone.png");
    // ��ʼ��HP����ֵ�Ͱ뾶
    maxHP = HP = 200;
    value = 50;
    radius =20;

    //���ϰ����������һ�����ɼ���ť������ʵ�ּ���
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0);
    BUTTON->setContentSize(Size(this->getContentSize().width, this->getContentSize().height));
    BUTTON->addClickEventListener([this](Ref* sender) {
        // ����ť����¼�
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
    addChild(BUTTON);

    return true;
}

bool Treasure::init() {
    if (!Sprite::init()) {
        return false;
    }

    // ��ʼ���ϰ������ۺ�����
    this->initWithFile("Treasure.png");
    // ��ʼ��HP����ֵ�Ͱ뾶
    maxHP = HP = 400;
    value = 75;
    radius =40;

    //���ϰ����������һ�����ɼ���ť������ʵ�ּ���
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0);
    BUTTON->setContentSize(Size(this->getContentSize().width, this->getContentSize().height));
    BUTTON->addClickEventListener([this](Ref* sender) {
        // ����ť����¼�
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
    addChild(BUTTON);

    return true;
}