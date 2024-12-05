#include "Monster.h"
#include "SceneBase.h"


USING_NS_CC;

bool Sheep::init() {
    if (!Sprite::init()) {
        return false;
    }

    //�ڹ����������һ�����ɼ���ť������ʵ�ּ���
    ui::Button* BUTTON = ui::Button::create("botton.png");
    BUTTON->setOpacity(0);
    BUTTON->setContentSize(Size(this->getContentSize().width, this->getContentSize().height));
    BUTTON->addClickEventListener([this](Ref* sender) {
        // ����ť����¼�
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    addChild(BUTTON);

    // ��ʼ��HP
    maxHP = HP = 100;
    // ��ʼ����ɱ����
    value = 50;
    // ��ʼ���ٶ�
    speed = 30;
    // ��ʼ���뾶
    radius = 10;
    //��ʼ���˺�
    hurt = 1;

    return true;
}

void Sheep::moveToSequence(const std::vector<Vec2>& positions)
{
    this->stopAllActions(); // ֹͣ��ǰ�����еĶ���

    Vector<FiniteTimeAction*> actions; // ����һ����������
    Vec2 thisPosition = this->getPosition();
    for (Vec2 position : positions)
    {
        auto distance = position - thisPosition; // �����ƶ�����
        thisPosition = position;
        auto duration = distance.length() / speed; // �����ƶ�ʱ��
        auto move = MoveTo::create(duration, position); // �����ƶ�����
        actions.pushBack(move); // ���ƶ�������ӵ�������
    }

    auto attacked = CallFunc::create([=]() {
        auto target = this->getParent();
        auto Scene = dynamic_cast<SceneBase*>(target);
        Scene->getCarrot()->takeDamage(hurt);//���ݹ�����˺����ܲ�����˺�
        this->setHP(0);//�������������

        });
    auto sequenceAction = Sequence::create(actions); // �������ж���
    auto sequence = Sequence::create(sequenceAction, attacked, nullptr);

    // ����һ���յĶ�������
    auto animation = Animation::create();
    // ��Ӷ���֡
    for (int i = 1; i <= 2; i++) {
        char filename[100];
        sprintf(filename, "Sheep%d.png", i);
        auto frame = SpriteFrame::create(filename, Rect(0, 0, 100, 100));
        animation->addSpriteFrame(frame);
    }

    // ���ö�������
    animation->setDelayPerUnit(0.1f);//nf=ÿ��n�벥��һ֡
    animation->setLoops(-1);//�ö���һֱѭ������

    // ����������������
    auto animate = Animate::create(animation);

    // ����������Ӧ�õ����������
    this->runAction(Spawn::create(animate,sequence,nullptr)); // ִ�����ж���
}

bool Bird::init() {
    if (!Sprite::init()) {
        return false;
    }

    // ��ʼ���������ۺ�����
    // ��ʼ��HP
    maxHP = HP = 80;
    // ��ʼ����ɱ����
    value = 50;
    // ��ʼ���ٶ�
    speed = 60;
    // ��ʼ���뾶
    radius = 10;
    //��ʼ���˺�
    hurt = 1;

    //�ڹ����������һ�����ɼ���ť������ʵ�ּ���
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

void Bird::moveToSequence(const std::vector<Vec2>& positions)
{
    this->stopAllActions(); // ֹͣ��ǰ�����еĶ���

    Vector<FiniteTimeAction*> actions; // ����һ����������
    Vec2 thisPosition = this->getPosition();
    for (Vec2 position : positions)
    {
        auto distance = position - thisPosition; // �����ƶ�����
        thisPosition = position;
        auto duration = distance.length() / speed; // �����ƶ�ʱ��
        auto move = MoveTo::create(duration, position); // �����ƶ�����
        actions.pushBack(move); // ���ƶ�������ӵ�������
    }

    auto attacked = CallFunc::create([=]() {
        auto target = this->getParent();
        auto Scene = dynamic_cast<SceneBase*>(target);
        Scene->getCarrot()->takeDamage(hurt);//���ݹ�����˺����ܲ�����˺�
        this->setHP(0);//�������������

        });
    auto sequenceAction = Sequence::create(actions); // �������ж���
    auto sequence = Sequence::create(sequenceAction, attacked, nullptr);

    // ����һ���յĶ�������
    auto animation = Animation::create();
    // ��Ӷ���֡
    for (int i = 1; i <= 2; i++) {
        char filename[100];
        sprintf(filename, "Bird%d.png", i);
        auto frame = SpriteFrame::create(filename, Rect(0, 0, 100, 100));
        animation->addSpriteFrame(frame);
    }

    // ���ö�������
    animation->setDelayPerUnit(0.1f);
    animation->setLoops(-1);

    // ����������������
    auto animate = Animate::create(animation);

    // ����������Ӧ�õ����������
    this->runAction(Spawn::create(animate, sequence, nullptr)); // ִ�����ж���
}

bool Star::init() {
    if (!Sprite::init()) {
        return false;
    }

    // ��ʼ���������ۺ�����
    // ��ʼ��HP
    maxHP = HP = 200;
    // ��ʼ����ɱ����
    value = 75;
    // ��ʼ���ٶ�
    speed = 50;
    // ��ʼ���뾶
    radius = 10;
    //��ʼ���˺�
    hurt = 2;

    //�ڹ����������һ�����ɼ���ť������ʵ�ּ���
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

void Star::moveToSequence(const std::vector<Vec2>& positions)
{
    this->stopAllActions(); // ֹͣ��ǰ�����еĶ���

    Vector<FiniteTimeAction*> actions; // ����һ����������
    Vec2 thisPosition = this->getPosition();
    for (Vec2 position : positions)
    {
        auto distance = position - thisPosition; // �����ƶ�����
        thisPosition = position;
        auto duration = distance.length() / speed; // �����ƶ�ʱ��
        auto move = MoveTo::create(duration, position); // �����ƶ�����
        actions.pushBack(move); // ���ƶ�������ӵ�������
    }

    auto attacked = CallFunc::create([=]() {
        auto target = this->getParent();
        auto Scene = dynamic_cast<SceneBase*>(target);
        Scene->getCarrot()->takeDamage(hurt);//���ݹ�����˺����ܲ�����˺�
        this->setHP(0);//�������������
        });
    auto sequenceAction = Sequence::create(actions); // �������ж���
    auto sequence = Sequence::create(sequenceAction, attacked, nullptr);

    // ����һ���յĶ�������
    auto animation = Animation::create();
    // ��Ӷ���֡
    for (int i = 1; i <= 2; i++) {
        char filename[100];
        sprintf(filename, "Star%d.png", i);
        auto frame = SpriteFrame::create(filename, Rect(0, 0, 100, 100));
        animation->addSpriteFrame(frame);
    }

    // ���ö�������
    animation->setDelayPerUnit(0.1f);
    animation->setLoops(-1);

    // ����������������
    auto animate = Animate::create(animation);

    // ����������Ӧ�õ����������
    this->runAction(Spawn::create(animate, sequence, nullptr)); // ִ�����ж���
}