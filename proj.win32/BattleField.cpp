//This is the battlefield where the main game runs
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
	scene->addChild(layerESC,2);
	return scene;
}
void BattleField::setCameraFollow(float del)
{
	float x2y2 = sqrt((x - 640)*(x - 640) + (y - 360)*(y - 360));
	float delX = 160*(x - 640)/x2y2*del;
	float delY = 160*(y - 360)/x2y2*del;
	this->setPosition(this->getPosition() - Vec2(delX, delY));
}
void BattleField::update(float del)
{
//	setCameraFollow(del);
	cocos2d::Vector<Node*> allballs;
	allballs = this->_BC->getChildren();
	for (auto target : allballs)
	{

		Balls* target_b = dynamic_cast<Balls*>(target);
		if (target_b != nullptr&&target_b->getID() != 0)
		{
			target_b->movement(x, y, this->_BC, 1);
			target_b->swallow(this->_BC);
			if (target_b != nullptr&&_keycode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE)
			{
				target_b->division(x, y, _keycode, this->_BC, this->k_listener);
				//this->unscheduleUpdate();
			}
			target_b->updateRadius();
		}
	}
	_keycode = cocos2d::EventKeyboard::KeyCode::KEY_NONE;

//	if (yourball != nullptr)
//		yourball->updateRadius();

}
bool Combat::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Balls* huaJi = Balls::createWithFileName("huaJi.png");
	huaJi->initStatus(4000, 1);
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
bool BattleField::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 originPos = Director::getInstance()->getVisibleOrigin();
	_BG = TMXTiledMap::create("BG.tmx");
	this->addChild(_BG,-1);
	_BG->setAnchorPoint(Vec2(0.5, 0.5));
	_BG->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2 + originPos.y));
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