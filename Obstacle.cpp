#include "Obstacle.h"

bool Grass::init() {
    if (!Sprite::init()) {
        return false;
    }

    // 初始化障碍物的外观和属性
    this->initWithFile("Grass.png");
    // 初始化HP，价值和半径
    maxHP = HP = 100;
    value = 14;
    radius = 10;

    //在障碍物身上添加一个不可见按钮，用于实现集火
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0);
    BUTTON->setContentSize(Size(this->getContentSize().width, this->getContentSize().height));
    BUTTON->addClickEventListener([this](Ref* sender) {
        // 处理按钮点击事件
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

    // 初始化障碍物的外观和属性
    this->initWithFile("Stone.png");
    // 初始化HP，价值和半径
    maxHP = HP = 200;
    value = 50;
    radius =20;

    //在障碍物身上添加一个不可见按钮，用于实现集火
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0);
    BUTTON->setContentSize(Size(this->getContentSize().width, this->getContentSize().height));
    BUTTON->addClickEventListener([this](Ref* sender) {
        // 处理按钮点击事件
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

    // 初始化障碍物的外观和属性
    this->initWithFile("Treasure.png");
    // 初始化HP，价值和半径
    maxHP = HP = 400;
    value = 75;
    radius =40;

    //在障碍物身上添加一个不可见按钮，用于实现集火
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0);
    BUTTON->setContentSize(Size(this->getContentSize().width, this->getContentSize().height));
    BUTTON->addClickEventListener([this](Ref* sender) {
        // 处理按钮点击事件
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
    addChild(BUTTON);

    return true;
}