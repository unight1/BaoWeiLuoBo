//#include "HelloWorldScene.h"
//#include "SimpleAudioEngine.h"//Cocos2d-x��Ϸ�����е���Ƶ������ͷ�ļ�
//#include "Obstacle.h"
//#include "Monster.h"
//#include "Tower.h"
//#include "Carrot.h"
//#include "TowerPosition.h"
//#include "ui/CocosGUI.h"
//
//USING_NS_CC; //using namespace cocos2d
//
//Sprite* plusIcon;
//
//Scene* HelloWorld::createScene()
//{
//    return HelloWorld::create();
//}
//// ��ӡ���õĴ�����Ϣ�����������ļ�������ʱ�δ���
//static void problemLoading(const char* filename)
//{
//    printf("Error while loading: %s\n", filename);
//    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
//}
//
//// on "init" you need to initialize your instance
//bool HelloWorld::init()
//{
//    // �����˸���Scene��init()�������г�ʼ���������ʼ��ʧ�ܣ��򷵻�false
//    if (!Scene::init())
//    {
//        return false;
//    }
//
//
//    // �ӵ�ǰ·���»��tmx�ļ�������tmx��ͼ����ʾ
//    std::string file = "level 1.tmx";
//    auto map = TMXTiledMap::create(file);
//    this->addChild(map, 0);     // ��ӵ������У���ʾ�ڵ�0��
//
//    // ��ȡ�ܲ������
//    TMXObjectGroup* carrotObjects = map->getObjectGroup("Carrot");
//
//    // ��ȡ�ܲ������λ����Ϣ
//    const auto& firstCarrotObject = carrotObjects->getObjects().at(0);
//    float xC = firstCarrotObject.asValueMap().at("x").asFloat() + 60;
//    float yC = firstCarrotObject.asValueMap().at("y").asFloat() + 70;
//
//    // �����ܲ��������ڵ�ͼ�ϵ�λ��
//    Vec2 carrotPosition = Vec2(xC, yC);
//    Carrot* carrot = Carrot::create();
//    carrot->setPosition(Vec2(xC, yC));
//    this->addChild(carrot, 1);      // ��ӵ������У���ʾ�ڵ�1�㣬ȷ���ڵ�ͼ�Ϸ���ʾ
//
//    TMXObjectGroup* towerPositions = map->getObjectGroup("TowerPosition");
//    // ����λ�ö���
//    ValueVector towerPositionsVector = towerPositions->getObjects();
//    
//    for (const auto& towerPosition : towerPositionsVector)
//    {
//        // ��ȡ����λ�ö����λ����Ϣ
//        float xP = towerPosition.asValueMap().at("x").asFloat() + 50;
//        float yP = towerPosition.asValueMap().at("y").asFloat() + 50;
//
//        // ��������λ�ò������ڵ�ͼ�ϵ�λ��
//        Vec2 position = Vec2(xP, yP);
//        TowerPosition* towerPos = TowerPosition::create();
//        towerPos->setPosition(position);
//        towerPos->setVisible(false);        // ��ʼ��ʱ����Ϊ����״̬
//        this->addChild(towerPos, 1);        // ��ӵ������У���ʾ�ڵ�1�㣬ȷ���ڵ�ͼ�Ϸ���ʾ
//
//        float xB = 40;
//        float yB = 100;
//        Vec2 positionButton = Vec2(xB, yB);
//        // ������ť
//        auto button = cocos2d::ui::Button::create("CloseNormal.png", "CloseNormal.png");
//        button->setPosition(positionButton);
//        button->addClickEventListener(CC_CALLBACK_1(HelloWorld::onButtonClick, this));  // ��Ӱ�ť����ص�����
//        towerPos->addChild(button, 2);
//    }
//    
//    // �������¼������������ڴ�������λ�ö������ʾ������
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);
//    listener->onTouchBegan = [&](Touch* touch, Event* event)
//        {
//            for (Node* child : this->getChildren())
//            {
//                TowerPosition* towerPos = dynamic_cast<TowerPosition*>(child);
//                if (towerPos && towerPos->getBoundingBox().containsPoint(touch->getLocation()))
//                {
//                    if (towerPos->towerofThisPosition)
//                        towerPos->setVisible(false);
//                    else
//                        towerPos->setVisible(true);
//                }
//                else if (towerPos)
//                {
//                    towerPos->setVisible(false);
//                }
//            }
//            return true;
//        };
//
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//
//
//    //------------------------------------------------------------------------------------------------------------//
//     
//    //int money = 0;
//    //// ͨ������ getInstance() �������Ի�ȡ����ǰ�ĵ��ݶ���
//    //// ���ڻ�ȡ��Ϸ���ڵĿɼ���С�����ص���һ�� Size ���󣬰����˴��ڵĿ�Ⱥ͸߶�
//    //auto visibleSize = Director::getInstance()->getVisibleSize();
//    //// ���ڻ�ȡ��Ϸ���ڵ�ԭ��λ�ã����ص���һ�� Vec2 ���󣬰�����ԭ��� x �� y ���ꡣ
//    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//
//    //// ��Ӵ��С�X��ͼ��Ĳ˵�������ò˵�����˳������������޸�����
//    //// ��ӡ��رա�ͼ�����˳���������һ���Զ��ͷŶ���
//    ////auto closeItem = MenuItemImage::create(
//    ////                                       "CloseNormal.png",
//    ////                                       "CloseSelected.png",
//    ////                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//
//    ////if (closeItem == nullptr ||
//    ////    closeItem->getContentSize().width <= 0 ||
//    ////    closeItem->getContentSize().height <= 0)
//    ////{
//    ////    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
//    ////}
//    ////else
//    ////{
//    ////    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
//    ////    float y = origin.y + closeItem->getContentSize().height/2;
//    ////    closeItem->setPosition(Vec2(x,y));// �������½�
//    ////}
//    ////// �����˵�����������һ���Զ��ͷŶ���
//    ////auto menu = Menu::create(closeItem, NULL);
//    ////menu->setPosition(Vec2::ZERO);
//    ////this->addChild(menu, 1);
//
//
//
//    ////auto moveAction = MoveTo::create(3.0f, Vec2(0, 0)); // ��2���������½��ƶ�100������
//    ////closeItem->runAction(moveAction);
//
//    ////TestObstacle* obstacle1 = TestObstacle::create();
//    ////obstacle1->setPosition(Vec2(100, 200));
//    ////obstacle1->setObstaclePosition(10, 20, 10, 20);
//    ////this->addChild(obstacle1);
//
//    ////obstacle1->takeDamage(100, money);
//
//    TestMonster* Monster = TestMonster::create();
//    Monster->setPosition(Vec2(200 + 50, 500 + 50));
//    this->addChild(Monster);
//    std::vector<cocos2d::Vec2> path = {
//    cocos2d::Vec2(200 + 50, 100 + 50),
//    cocos2d::Vec2(400 + 50, 100 + 50),
//    cocos2d::Vec2(400 + 50, 300 + 50),
//    cocos2d::Vec2(300 + 50, 300 + 50),
//    cocos2d::Vec2(300 + 50, 500 + 50),
//    cocos2d::Vec2(500 + 50, 500 + 50),
//    cocos2d::Vec2(500 + 50, 100 + 50),
//    cocos2d::Vec2(700 + 50, 100 + 50),
//    cocos2d::Vec2(700 + 50, 300 + 50),
//    cocos2d::Vec2(950 + 50, 300 + 50)
//    };
//    Monster->moveToSequence(path);
//    //Monster->moveTo(Vec2(100, 200));
//
//
//    /*TestMonster* Monster2 = TestMonster::create();
//    Monster2->setPosition(Vec2(500, 700));
//    Monster2->moveTo(Vec2(20, 10));
//    this->addChild(Monster2);
//
//    TestMonster* Monster3 = TestMonster::create();
//    Monster3->setPosition(Vec2(1000, 900));
//    Monster3->moveTo(Vec2(20, 10));
//    this->addChild(Monster3);*/
//
//
//    //TestTower* TestTower = TestTower::create();
//    //TestTower->setPosition(Vec2(50, 50));
//    //this->addChild(TestTower);
//
//
//    //------------------------------------------------------------------------------------------------------------//
//
//
//    // ��������ξ���
//    //// ��������ξ���
//    //auto triangle = DrawNode::create();
//    //Color4F color(10, 10, 0, 1); // �����ɫ
//
//    //// ���������ε���������
//    //Vec2 vertices[] = {
//    //    Vec2(0, 50), // ��һ������
//    //    Vec2(-50, -50), // �ڶ�������
//    //    Vec2(50, -50) // ����������
//    //};
//
//    //// ����������
//    //triangle->drawPolygon(vertices, 3, color, 0, color); // �����ֱ�Ϊ�������顢���������������ɫ���߿��ȡ��߿���ɫ
//
//    //// ����λ�ò���ӵ�������
//    //triangle->setPosition(Vec2(100, 100));
//    //addChild(triangle);
//
//
//
//
//
//
//
//
//    //Monster->takeDamage(100, money);
//
//
//    //auto sprite = Obstacle::create("cat.png");
//
//    //// ���þ���ĳ�ʼλ��
//    //sprite->setPosition(Vec2(100,100));
//
//    //// ��������ӵ�������
//    //this->addChild(sprite);
//
//    //auto action = MoveTo::create(5.0f, Vec2(10, 10));
//    //sprite->runAction(action);
//    ////auto action = MoveTo::create(5.0f, Vec2(100, 200));
//    ////sprite->runAction(action);
//
//    //this->scheduleOnce([=](float dt) {
//    //    sprite->removeFromParentAndCleanup(true);
//    //    }, 3.0f, "remove_sprite");
//
//
//    /////////////////////////////
//    // 3. add your codes below...
//
//    // add a label shows "Hello World"
//    // create and initialize a label
//
//    // ���ڴ���һ������TrueType�����ļ��ı�ǩ����
//    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);//�ı����ݡ������ļ�·���������С
//    //if (label == nullptr)
//    //{
//    //    problemLoading("'fonts/Marker Felt.ttf'");
//    //}
//    //else
//    //{
//    //    // position the label on the center of the screen
//    //    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//    //                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    //    // add the label as a child to this layer
//    //    this->addChild(label, 1);
//    //}
//
//     //add "HelloWorld" splash screen"
//     // 
//    //auto sprite = Sprite::create("pic1.png");
//
//
//    //if (sprite == nullptr)
//    //{
//    //    problemLoading("'HelloWorld.png'");
//    //}
//    //else
//    //{
//    //    // position the sprite on the center of the screen
//    //    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
//
//    //    // add the sprite as a child to this layer
//    //    this->addChild(sprite, 0);
//    //}
//
//    //// ����һ���յĶ�������
//    //auto animation = Animation::create();
//
//    //// ��Ӷ���֡
//    //for (int i = 1; i <= 2; i++) {
//    //    char filename[100];
//    //    sprintf(filename, "pic%d.png", i);
//    //    auto frame = SpriteFrame::create(filename, Rect(0, 0, 70, 70));
//    //    animation->addSpriteFrame(frame);
//    //}
//
//    //// ���ö�������
//    //animation->setDelayPerUnit(0.08f);
//    //animation->setLoops(-1);
//
//    //// ����������������
//    //auto animate = Animate::create(animation);
//
//    //// ����������Ӧ�õ����������
//    //sprite->runAction(animate);
//
//
//    return true;
//}
//
//void HelloWorld::menuCloseCallback(Ref* pSender)
//{
//    //���������ֹͣ��Ϸѭ�������ͷ����е���Դ��
//    Director::getInstance()->end();
//
//    //���ϣ����iOS�з���ԭ������������˳�Ӧ�ó��򣬿���ע�͵��������������������Ĵ��룬
//    //����һ����Ϊ��game_scene_close_event�����Զ����¼�����RootViewController.mm�ļ��еĴ��봦��
//
//    //EventCustom customEndEvent("game_scene_close_event");
//    //_eventDispatcher->dispatchEvent(&customEndEvent);
//}
//
//void HelloWorld::onButtonClick(cocos2d::Ref* sender)
//{
//    // �ڵ�ǰλ�ô����������߼�����
//    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
//    if (button)
//    {
//        auto tower = TestTower::create();  // ������������
//        tower->setPosition(button->getParent()->getPosition());  // ��������λ��
//        auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
//        if (thisTowerPosition)
//        {
//            thisTowerPosition->towerofThisPosition = tower;
//        }
//        this->addChild(tower, 3);  // ��������ӵ�������
//        button->getParent()->setVisible(false);
//    }
//}