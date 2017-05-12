//This is the main menu
#include "MainMenu.h"
#include"Balls.h"
#include<ui/CocosGUI.h>
USING_NS_CC;
using namespace ui;
Scene* MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer_mainMenu = MainMenu::create();
	auto layer_mainBG = MainBG::create();
	scene->addChild(layer_mainMenu);
	scene->addChild(layer_mainBG);
	return scene;
}
bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 originPos = Director::getInstance()->getVisibleOrigin();
	//this->_localZOrder = 2;
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("titlemusic.mp3");
	//the Start Button
	auto startGame_button = Button::create("StartMenu_startbutton.png");
	startGame_button->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2.7 + originPos.y));
	startGame_button->setScale(0.5);
	//here to put the onclick event
	this->addChild(startGame_button);
	auto startGame_button_mp = Button::create("StartMenu_startbutton_MP.png");
	startGame_button_mp->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2.7 - 120 + originPos.y));
	startGame_button_mp->setScale(0.5);
	//here to put the onclick event mp
	this->addChild(startGame_button_mp);
	//the title logo
	auto titleLogo = Sprite::create("StartMenu_titlelogo.png");
	titleLogo->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 1.4 + originPos.y));
	titleLogo->setScale(0.7);
	this->addChild(titleLogo);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("titlemusic.mp3", true);
	return true;
}
bool MainBG::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->setLocalZOrder(-1);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 originPos = Director::getInstance()->getVisibleOrigin();
	auto backGround = Sprite::create("StartMenu_BG.png");
	backGround->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2 + originPos.y));
	this->addChild(backGround);
	Balls* huaJi = Balls::createWithFileName("huaJi.png");
	huaJi->initStatus(10);
	huaJi->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2 + originPos.y));
	this->addChild(huaJi, 1, "HJ");


	// test balls
	Balls*test1 = Balls::createWithFileName("test.png");
	test1->initStatus(3);
	test1->setPosition(Vec2(visibleSize.width / 2 + originPos.x + 300, visibleSize.height / 2 + originPos.y + 300));
	this->addChild(test1, 1);
	Balls*test2 = Balls::createWithFileName("test.png");
	test2->initStatus(1);
	test2->setPosition(Vec2(visibleSize.width / 2 + originPos.x - 300, visibleSize.height / 2 + originPos.y));
	this->addChild(test2, 1);
	Balls*test3 = Balls::createWithFileName("test.png");
	test3->initStatus(5);
	test3->setPosition(Vec2(visibleSize.width / 2 + originPos.x - 300, visibleSize.height / 2 + originPos.y + 300));
	this->addChild(test3, 1);
	Balls*test4 = Balls::createWithFileName("test.png");
	test4->initStatus(12);
	test4->setPosition(Vec2(visibleSize.width / 2 + originPos.x - 300, visibleSize.height / 2 + originPos.y - 300));
	this->addChild(test4, 1);
	//
	auto listener = EventListenerMouse::create();
	listener->onMouseMove = [=](Event* event)
	{
		EventMouse* _event = (EventMouse*)event;
		x = _event->getCursorX();
		y = _event->getCursorY();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->schedule(schedule_selector(MainBG::update), 0.1f);
	return true;
}

void MainBG::update(float dt)
{
	this->getChildByName("HJ")->stopAllActions();
	auto moveTo = MoveTo::create(0.8, Vec2(x, y));
	this->getChildByName("HJ")->runAction(moveTo);
	Balls* _yourball = dynamic_cast<Balls*>(this->getChildByName("HJ"));
	_yourball->swallow(this);
	_yourball->updateRadius();
}
