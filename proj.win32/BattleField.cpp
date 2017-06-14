//This is the battlefield where the main game runs
//BattleField coordinate system:
// x: -5120 to 5120
// y: -5120 to 5120
#include "BattleField.h"
#include "MainMenu.h"
#include "Balls.h"
USING_NS_CC;
Scene * BattleField::createScene(int ballID)
{
	auto scene = Scene::create();
	auto layerBattleField = BattleField::create();
	auto layerBC = Combat::create(ballID);
	scene->addChild(layerBattleField,1);
	auto layerESC = ESCMenu::create();
	layerBattleField->_BC = layerBC;
	layerBattleField->_ESC = layerESC;
	layerBattleField->addChild(layerBC,2);
	auto layerFail = FailMenu::create();
	layerBattleField->_fail = layerFail;
	scene->addChild(layerESC,2,0);
	scene->addChild(layerFail, 3);
	auto layerScoreCounter = ScoreCounter::create();
	scene->addChild(layerScoreCounter,4,4);    //tag 4 for ScoreCounter
	auto layerFood = Food::create();
	layerBattleField->addChild(layerFood,1,"food");
	layerBattleField->_food = layerFood;
	return scene;
}
void BattleField::setCameraFollow()
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
	int nowNodeCount=0;
	for (auto target : allballs)
	{
		Balls* target_b = dynamic_cast<Balls*>(target);
		if (target_b != nullptr&&target_b->getID() ==1)
		{
			target_b->movement(nowX, nowY, this->_BC, 1);
			if (target_b->getPositionX() < -5120 + target_b->getRadius())target_b->setPositionX(-5120+target_b->getRadius());
			if (target_b->getPositionX() > 5120 - target_b->getRadius())target_b->setPositionX(5120-target_b->getRadius());
			if (target_b->getPositionY() < -5120 + target_b->getRadius())target_b->setPositionY(-5120+target_b->getRadius());
			if (target_b->getPositionY() > 5120 - target_b->getRadius())target_b->setPositionY(5120-target_b->getRadius());
			target_b->swallow(this->_food);
			if (target_b != nullptr&&_keycode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE&&nodeCount<8)
			{
				target_b->division(nowX, nowY, _keycode, this->_BC);
			//	this->unscheduleUpdate();
			//	for debug using
			}
			nodeSumX += target_b->getPositionX();
			nodeSumY += target_b->getPositionY();
			nowNodeCount++;
			target_b->updateRadius();
		}
	}
	nodeCount = nowNodeCount;
	if (nodeCount!=0)
	{
		nodeX = nodeSumX / nodeCount;
		nodeY = nodeSumY / nodeCount;
		setCameraFollow();
		//this->unscheduleUpdate();
		//for debug using¡ü
	}
	else
	{
		k_listener->setEnabled(false);
		(this->getParent()->getChildByTag(4))->unschedule(schedule_selector(ScoreCounter::scoreUpdate));
		dynamic_cast<LabelTTF *>(_fail->getChildByName("result"))->setString(dynamic_cast<LabelTTF *>(this->getParent()->getChildByTag(4))->getString());
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
	Balls * myBall;
	if(_meBall==1) myBall = Balls::createWithFileName("cry.png");
	else if(_meBall==2) myBall = Balls::createWithFileName("xibi.png");
	else if(_meBall==3) myBall = Balls::createWithFileName("huaJi.png");
	else return false;
	myBall->initStatus(10, 1);
	myBall->setPosition(Vec2(640,360));
	this->addChild(myBall, 1);
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
	auto result = LabelTTF::create("0", "arial", 60);
	result->setPosition(Vec2(640, 180));
	this->addChild(result,2,"result");
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
	_BG->setPosition(Vec2(0,0));
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
bool Food::init()
{
	if (!Layer::init())
	{
		return false;
	}
	foodCount = 0;
	foodCreator();
	this->schedule(schedule_selector(Food::foodRefresh), 1.5f);
}
void Food::foodRefresh(float del)
{
	auto cache = SpriteFrameCache::getInstance();
	while (foodCount < 1200)
	{
		int xPos = CCRANDOM_MINUS1_1() * 4800;
		int yPos = CCRANDOM_MINUS1_1() * 4800;
		float food_colour;
		food_colour = CCRANDOM_0_1();
		if (food_colour < 0.17)
		{
			auto food = Balls::createWithBallsFrame(cache->getSpriteFrameByName("red"));
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (food_colour < 0.34)
		{
			auto food = Balls::createWithBallsFrame(cache->getSpriteFrameByName("yellow"));
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (food_colour < 0.5)
		{
			auto food = Balls::createWithBallsFrame(cache->getSpriteFrameByName("blue"));
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (food_colour < 0.67)
		{
			auto food = Balls::createWithBallsFrame(cache->getSpriteFrameByName("green"));
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (food_colour < 0.84)
		{
			auto food = Balls::createWithBallsFrame(cache->getSpriteFrameByName("purple"));
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else
		{
			auto food = Balls::createWithBallsFrame(cache->getSpriteFrameByName("scolor"));
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
	}
}
void Food::foodCreator()
{
	SpriteFrameCache::getInstance()->destroyInstance();
	while (foodCount < 6)
	{
		int xPos = CCRANDOM_MINUS1_1() * 4800;
		int yPos = CCRANDOM_MINUS1_1() * 4800;
		if (foodCount==0) 
		{
			auto food = Balls::createWithFileName("food_r.png");
			SpriteFrameCache::getInstance()->addSpriteFrame(food->getSpriteFrame(), "red");
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (foodCount==1) 
		{
			auto food = Balls::createWithFileName("food_y.png");
			SpriteFrameCache::getInstance()->addSpriteFrame(food->getSpriteFrame(), "yellow");
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (foodCount==2) 
		{
			auto food = Balls::createWithFileName("food_b.png");
			SpriteFrameCache::getInstance()->addSpriteFrame(food->getSpriteFrame(), "blue");
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (foodCount==3) 
		{
			auto food = Balls::createWithFileName("food_g.png");
			SpriteFrameCache::getInstance()->addSpriteFrame(food->getSpriteFrame(), "green");
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else if (foodCount==4) 
		{
			auto food = Balls::createWithFileName("food_p.png");
			SpriteFrameCache::getInstance()->addSpriteFrame(food->getSpriteFrame(), "purple");
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
		else 
		{
			auto food = Balls::createWithFileName("food_s.png");
			SpriteFrameCache::getInstance()->addSpriteFrame(food->getSpriteFrame(), "scolor");
			food->setPosition(Vec2(xPos, yPos));
			food->initStatusMin();
			this->addChild(food);
			foodCount += 1;
		}
	}
}
bool ScoreCounter::init()
{
	if (!Layer::init())
	{
		return false;
	}
	score = 0;
	this->schedule(schedule_selector(ScoreCounter::scoreUpdate), 1.0f);
	auto scoreDisplay = LabelTTF::create("0", "arial", 38);
	auto timeBG = Sprite::create("time.png");
	timeBG->setPosition(Vec2(154, 680));
	timeBG->setScale(0.8);
	this->addChild(timeBG,0);
	scoreDisplay->setColor(Color3B::WHITE);
	scoreDisplay->setPosition(Vec2(150, 683));
	this->addChild(scoreDisplay, 1, "display");
	return true;
}
void ScoreCounter::scoreUpdate(float del)
{
	score++;
	dynamic_cast<LabelTTF *>(this->getChildByName("display"))->setString(__String::createWithFormat("%d:%d", (score / 60), (score % 60))->getCString());
}