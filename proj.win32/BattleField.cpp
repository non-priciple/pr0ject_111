//This is the battlefield where the main game runs
//BattleField coordinate system:
// x: -6400 to 6400
// y: -6400 to 6400
#include "BattleField.h"
#include "MainMenu.h"
#include "Balls.h"
USING_NS_CC;
Scene * BattleField::createScene(int ballID)
{
	auto scene = Scene::create();
	auto layerBattleField = BattleField::create();
	layerBattleField->_me = ballID;
	auto layerBC = Combat::create();
	scene->addChild(layerBattleField,1);
	auto layerESC = ESCMenu::create();
	layerBattleField->_BC = layerBC;
	layerBattleField->_ESC = layerESC;
	layerBattleField->addChild(layerBC,2);
	auto layerFail = FailMenu::create();
	layerBattleField->_fail = layerFail;
	scene->addChild(layerESC,2,0);
	scene->addChild(layerFail, 3);
	return scene;
}
void BattleField::setCameraFollow(float nodeX,float nodeY)
{
	Vec2 delVec = Vec2(640, 360) - this->getPosition() - Vec2(nodeX, nodeY);   //CAUTION!:coordinate system change
	this->setPosition(this->getPosition() + delVec);
}
void BattleField::update(float del)
{
	cocos2d::Vector<Node*> allballs;
	allballs = this->_BC->getChildren();
	float nowX = x - this->getPositionX();
	float nowY = y - this->getPositionY();
	float nodeSumX=0;
	float nodeSumY=0;
	int nodeCount=0;
	for (auto target : allballs)
	{
		Balls* target_b = dynamic_cast<Balls*>(target);
		if (target_b != nullptr&&target_b->getID() != 0)
		{
			target_b->movement(nowX, nowY, this->_BC, 1);
			target_b->swallow(this->_BC);
			if (target_b != nullptr&&_keycode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE)
			{
				target_b->division(nowX, nowY, _keycode, this->_BC);
			//	this->unscheduleUpdate();
			//	for debug using
			}
			if (target_b->getID() == 1)
			{
				nodeSumX += target_b->getPositionX();
				nodeSumY += target_b->getPositionY();
				nodeCount++;
			}
			target_b->updateRadius();
		}
	}
	if (nodeCount!=0)
	{
		setCameraFollow( nodeSumX / nodeCount, nodeSumY / nodeCount);
		//this->unscheduleUpdate();
		//for debug using¡ü
	}
	else
	{
		k_listener->setEnabled(false);
		_fail->setVisible(true);
	}
	_keycode = cocos2d::EventKeyboard::KeyCode::KEY_NONE;

}
bool Combat::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Balls* huaJi = Balls::createWithFileName("huaJi.png");
	huaJi->initStatus(1000, 1);
	huaJi->setPosition(Vec2(640,360));
	this->addChild(huaJi, 1, "HJ");
	return true;
}
void ESCMenu::quitToMainMenu()
{
	auto transition = TransitionPageTurn::create(0.8f, MainMenu::createScene(), true);
	Director::getInstance()->replaceScene(transition);
}
void ESCMenu::resumeToGame()
{
	this->setVisible(false);
}
bool ESCMenu::init()              //The menu shown when pressing ESC
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 originPos = Director::getInstance()->getVisibleOrigin();
	auto coverImg = Sprite::create("esc.png");
	coverImg->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2 + originPos.y));
	this->addChild(coverImg,0);
	auto buttonQuit = ui::Button::create("quit.png");
	buttonQuit->setPosition(Vec2(visibleSize.width / 2 + originPos.x - 370, visibleSize.height / 2 + originPos.y + 50));
	buttonQuit->addClickEventListener(ui::Widget::ccWidgetClickCallback(CC_CALLBACK_0(ESCMenu::quitToMainMenu, this)));
	auto buttonResume = ui::Button::create("resume.png");
	buttonResume->setPosition(Vec2(visibleSize.width / 2 + originPos.x + 360, visibleSize.height / 2 + originPos.y - 100));
	buttonResume->addClickEventListener(ui::Widget::ccWidgetClickCallback(CC_CALLBACK_0(ESCMenu::resumeToGame, this)));
	this->addChild(buttonQuit);
	this->addChild(buttonResume);
	this->setVisible(false);
	return true;
}
void FailMenu::failToSelectMenu()
{
	dynamic_cast<ESCMenu *>(this->getParent()->getChildByTag(0))->quitToMainMenu();
}
bool FailMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 originPos = Director::getInstance()->getVisibleOrigin();
	auto failImg = Sprite::create("fail.png");
	failImg->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2 + originPos.y));
	this->addChild(failImg);
	keyboardListener= EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event)
	{
		failToSelectMenu();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);
	keyboardListener->setEnabled(false);
	this->setVisible(false);
	return true;
}
bool BattleField::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 originPos = Director::getInstance()->getVisibleOrigin();
	x = visibleSize.width / 2 + originPos.x;
	y = visibleSize.height / 2 + originPos.y;
	_BG = TMXTiledMap::create("BG.tmx");
	this->addChild(_BG,-1);
	_BG->setAnchorPoint(Vec2(0.5,0.5));
	_BG->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2 + originPos.y));
	//this->schedule(schedule_selector(BattleField::update), 0.02f);
	//for debug using¡ü
	this->scheduleUpdate();
	auto m_listener = EventListenerMouse::create();
	m_listener->onMouseMove = [=](Event * event)
	{
		EventMouse* _event = (EventMouse *)event;
		x = _event->getCursorX();
		y = _event->getCursorY();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
	k_listener = EventListenerKeyboard::create();
	k_listener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			_ESC->setVisible(true);
		}
		else if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			_keycode = keycode;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(k_listener, this);
	return true;
}