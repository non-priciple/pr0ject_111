//This is the menu where you select your character
#include"BallSelectMenu.h"
#include"MainMenu.h"
#include"BattleField.h"
USING_NS_CC;
Scene *BallSelectMenu::createScene(bool isMP)
{
	auto scene = Scene::create();
	auto layer_ballSelectMenu = BallSelectMenu::create();
	layer_ballSelectMenu->_isMP = isMP;
	scene->addChild(layer_ballSelectMenu);
	return scene;
}
void BallSelectMenu::switchToBattleField(int ballID)
{
	auto transition = TransitionPageTurn::create(1.0f, BattleField::createScene(ballID), false);
	Director::getInstance()->replaceScene(transition);
}
void BallSelectMenu::backToMainMenu()
{
	auto transition = TransitionPageTurn::create(0.8f, MainMenu::createScene(), true);
	Director::getInstance()->replaceScene(transition);
}
void BallSelectMenu::selectC()
{
	this->getChildByName("selectedC")->setVisible(true);
	this->getChildByName("selectedH")->setVisible(false);
	this->getChildByName("selectedX")->setVisible(false);
	this->getChildByName("startC")->setVisible(true);
	this->getChildByName("startH")->setVisible(false);
	this->getChildByName("startX")->setVisible(false);
}
void BallSelectMenu::selectH()
{
	this->getChildByName("selectedC")->setVisible(false);
	this->getChildByName("selectedH")->setVisible(true);
	this->getChildByName("selectedX")->setVisible(false);
	this->getChildByName("startC")->setVisible(false);
	this->getChildByName("startH")->setVisible(true);
	this->getChildByName("startX")->setVisible(false);
}
void BallSelectMenu::selectX()
{
	this->getChildByName("selectedC")->setVisible(false);
	this->getChildByName("selectedH")->setVisible(false);
	this->getChildByName("selectedX")->setVisible(true);
	this->getChildByName("startC")->setVisible(false);
	this->getChildByName("startH")->setVisible(false);
	this->getChildByName("startX")->setVisible(true);
}
void BallSelectMenu::startWithC()
{
	switchToBattleField(1);
}
void BallSelectMenu::startWithH()
{
	switchToBattleField(3);
}
void BallSelectMenu::startWithX()
{
	switchToBattleField(2);
}
bool BallSelectMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 originPos = Director::getInstance()->getVisibleOrigin();
	auto backGround = Sprite::create("select.png");
	backGround->setPosition(Vec2(visibleSize.width / 2 + originPos.x, visibleSize.height / 2 + originPos.y));
	this->addChild(backGround);
	auto cryButton = ui::Button::create("cry_s.png");                                        //init the select buttons
	cryButton->setPosition(Vec2(270 + originPos.x, visibleSize.height / 2 + originPos.y + 50));
	cryButton->setScale(0.9);
	cryButton->setRotation(-15);
	cryButton->addClickEventListener(ui::Widget::ccWidgetClickCallback(CC_CALLBACK_0(BallSelectMenu::selectC, this)));
	auto selectedC = Sprite::create("selected.png");
	selectedC->setPosition(cryButton->getPosition());
	selectedC->setRotation(40);
	selectedC->setVisible(false);
	auto xibiButton = ui::Button::create("xibi_s.png");
	xibiButton->setPosition(Vec2(632 + originPos.x, visibleSize.height / 2 + originPos.y -10));
	xibiButton->setScale(0.9);
	xibiButton->setRotation(-2);
	xibiButton->addClickEventListener(ui::Widget::ccWidgetClickCallback(CC_CALLBACK_0(BallSelectMenu::selectX, this)));
	auto selectedX = Sprite::create("selected.png");
	selectedX->setPosition(xibiButton->getPosition());
	selectedX->setRotation(137);
	selectedX->setVisible(false);
	auto HJButton = ui::Button::create("HJ_s.png");
	HJButton->setPosition(Vec2(1000 + originPos.x, visibleSize.height / 2 + originPos.y + 40));
	HJButton->setScale(0.9);
	HJButton->setRotation(4);
	HJButton->addClickEventListener(ui::Widget::ccWidgetClickCallback(CC_CALLBACK_0(BallSelectMenu::selectH,this)));
	auto selectedH = Sprite::create("selected.png");
	selectedH->setPosition(HJButton->getPosition());
	selectedH->setRotation(245);
	selectedH->setVisible(false);
	this->addChild(cryButton,1);
	this->addChild(xibiButton,1);
	this->addChild(HJButton,1);
	this->addChild(selectedC,0,"selectedC");
	this->addChild(selectedH,0,"selectedH");
	this->addChild(selectedX,0,"selectedX");
	auto buttonStartH = ui::Button::create("selectStartH.png");
	buttonStartH->addClickEventListener(ui::Widget::ccWidgetClickCallback(CC_CALLBACK_0(BallSelectMenu::startWithH, this)));
	buttonStartH->setPosition(Vec2(1000, 80));
	buttonStartH->setScale(0.7);
	buttonStartH->setVisible(false);
	auto buttonStartX = ui::Button::create("selectStartX.png");
	buttonStartX->addClickEventListener(ui::Widget::ccWidgetClickCallback(CC_CALLBACK_0(BallSelectMenu::startWithX, this)));
	buttonStartX->setPosition(Vec2(1000, 80));
	buttonStartX->setScale(0.7);
	buttonStartX->setVisible(false);
	auto buttonStartC = ui::Button::create("selectStartC.png");
	buttonStartC->addClickEventListener(ui::Widget::ccWidgetClickCallback(CC_CALLBACK_0(BallSelectMenu::startWithC, this)));
	buttonStartC->setPosition(Vec2(1000, 80));
	buttonStartC->setScale(0.7);
	buttonStartC->setVisible(false);
	this->addChild(buttonStartC, 0, "startC");
	this->addChild(buttonStartH, 0, "startH");
	this->addChild(buttonStartX, 0, "startX");
	auto buttonBack = ui::Button::create("back.png");
	buttonBack->setPosition(Vec2(600, 60));
	buttonBack->setScale(0.66f);
	buttonBack->addClickEventListener(ui::Widget::ccWidgetClickCallback(CC_CALLBACK_0(BallSelectMenu::backToMainMenu, this)));
	this->addChild(buttonBack);
	return true;
}