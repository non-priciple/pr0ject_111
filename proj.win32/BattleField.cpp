//This is the battlefield where the main game runs
#include "BattleField.h"
USING_NS_CC;
Scene * BattleField::createScene(int ballID)
{
	auto scene = Scene::create();
	auto layerBattleField = BattleField::create();
	layerBattleField->_me = ballID;
	auto layerBC = Combat::create();
	scene->addChild(layerBattleField);
	layerBattleField->_BC = layerBC;
	layerBattleField->addChild(layerBC);
	return scene;
}
void BattleField::update(float del)
{
	setCameraFollow();

}
bool Combat::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}
void BattleField::setCameraFollow()
{

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
	this->addChild(_BG);
	_BG->setAnchorPoint(Vec2(0.5, 0.5));
	_BG->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2 + originPos.y));
	this->schedule(schedule_selector(BattleField::update), 0.0333f);
	return true;
}