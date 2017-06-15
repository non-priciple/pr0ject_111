//This is the main menu
#include "MainMenu.h"
#include"BallSelectMenu.h"
#include<ui/CocosGUI.h>
#include<SimpleAudioEngine.h>
#include"Balls.h"
USING_NS_CC;
using namespace ui;
void MainMenu::switchSceneToSelectSP()
{
	auto transition = TransitionPageTurn::create(1.2f, BallSelectMenu::createScene(0),false);
	Director::getInstance()->replaceScene(transition);
}
void MainMenu::switchSceneToSelectMP()
{
	auto transition = TransitionPageTurn::create(1.2f, BallSelectMenu::createScene(1), false);
	Director::getInstance()->replaceScene(transition);
}
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
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("titlemusic.mp3");
	//the Start Button
	auto startGame_button = Button::create("StartMenu_startbutton.png");
	startGame_button->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 3 + originPos.y));
	startGame_button->setScale(0.7);
	startGame_button->addClickEventListener(Widget::ccWidgetClickCallback(CC_CALLBACK_0(MainMenu::switchSceneToSelectSP,this)));
	this->addChild(startGame_button);	
	//auto startGame_button_mp = Button::create("StartMenu_startbutton_MP.png");
	//startGame_button_mp->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2.7 - 110 + originPos.y));
	//startGame_button_mp->setScale(0.6);
	//startGame_button_mp->addClickEventListener(Widget::ccWidgetClickCallback(CC_CALLBACK_0(MainMenu::switchSceneToSelectMP,this)));
	//this->addChild(startGame_button_mp);
	//the title logo
	auto titleLogo = Sprite::create("StartMenu_titlelogo.png");
	titleLogo->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 1.4 + originPos.y));
	titleLogo->setScale(0.7);
	this->addChild(titleLogo);
	if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("titlemusic.mp3", true);
	}
	return true;
}
bool MainBG::init()
{
	if (!Layer::init())
	{
		return false;
	}
	x = 640;
	y = 360;
	this->setLocalZOrder(-1);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 originPos = Director::getInstance()->getVisibleOrigin();
	auto backGround = Sprite::create("StartMenu_BG.png");
	backGround->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2 + originPos.y));
	this->addChild(backGround);
	Balls* huaJi = Balls::createWithFileName("greenhat.png");
	float isChange = CCRANDOM_0_1();
	if (isChange < 0.33f)huaJi->initWithFile("huaJi.png");
	else if (isChange < 0.66f)huaJi->initWithFile("teri.png");
	huaJi->initStatus(600,1);
	huaJi->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2 + originPos.y));
	huaJi->runAction(CCRepeatForever::create(RotateBy::create(2, 360)));
	this->addChild(huaJi, 1, "HJ");
	// test balls
/*	Balls*test1 = Balls::createWithFileName("huaji.png");
	test1->initStatus(300,0);
	test1->setPosition(Vec2(visibleSize.width / 2 + originPos.x + 300, visibleSize.height / 2 + originPos.y + 300));
	this->addChild(test1, 1);
	Balls*test2 = Balls::createWithFileName("huaji.png");
	test2->initStatus(100,0);
	test2->setPosition(Vec2(visibleSize.width / 2 + originPos.x - 300, visibleSize.height / 2 + originPos.y));
	this reateWithFileName("huaji.png");
	test3->initStatus(500,0);
	test3->setPosition(Vec2(visibleSize.width / 2 + originPos.x - 300, visibleSize.height / 2 + originPos.y + 300));
	this->addChild(test3, 1);
	Balls*test4 = Balls::createWithFileName("huaji.png");
	test4->initStatus(1000,0);
	test4->setPosition(Vec2(visibleSize.width / 2 + originPos.x - 300, visibleSize.height / 2 + originPos.y - 300));
	this->addChild(test4, 1);*/
	auto m_listener = EventListenerMouse::create();
	m_listener->onMouseMove = [=](Event* event)
	{
		EventMouse* _event = (EventMouse*)event;
		x = _event->getCursorX();
		y = _event->getCursorY();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
	k_listener = EventListenerKeyboard::create();
	k_listener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event)
	{
		_keycode = keycode;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(k_listener, this);
//	this->schedule(schedule_selector(MainBG::update), 0.03333f);
	this->scheduleUpdate();
	return true;
}
void MainBG::update(float dt)
{
	cocos2d::Vector<Node*> allballs;
	allballs = this->getChildren();
	for (auto target : allballs)
	{
		
		if (target->getPositionX() > 1280 || target->getPositionX() < 0 || target->getPositionY() > 720 || target->getPositionY() < 0)
		{
			target->setPosition(Vec2(640, 360));
		}
		Balls* target_b = dynamic_cast<Balls*>(target);
		if (target_b != nullptr&&target_b->getID() != 0)
		{
			target_b->LevelLimit();
			target_b->movement(x,y,this,1);
			target_b->swallow(this);
			if(target_b!=nullptr&&_keycode== EventKeyboard::KeyCode::KEY_SPACE)
				target_b->division(x, y, _keycode, this);
		}
	}
	_keycode = cocos2d::EventKeyboard::KeyCode::KEY_NONE;	
}
