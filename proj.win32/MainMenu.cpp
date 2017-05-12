//This is the main menu
#include "MainMenu.h"
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
	startGame_button->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height /2.7+ originPos.y));
	startGame_button->setScale(0.5);
	//here to put the onclick event
	this->addChild(startGame_button);
	auto startGame_button_mp = Button::create("StartMenu_startbutton_MP.png");
	startGame_button_mp->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2.7-120+ originPos.y));
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
auto huaJi = Sprite::create("huaJi.png");
	huaJi->setScale(0.4);
	huaJi->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2 + originPos.y));
	this->addChild(huaJi,1,"HJ");
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
	auto moveTo = MoveTo::create(0.8,Vec2(x,y));
	this->getChildByName("HJ")->runAction(moveTo);
}
