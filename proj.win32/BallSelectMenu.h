//This is the menu where you select your character
#include<cocos2d.h>
#include<ui/CocosGUI.h>
class BallSelectMenu :public cocos2d::Layer
{
	
public:
	bool _isMP;
	static cocos2d::Scene * createScene(bool isMP);
	virtual bool init();
	void switchToBattleField(int ballID);
	void backToMainMenu();
	void selectX();
	void selectH();
	void selectC();
	void startWithX();
	void startWithH();
	void startWithC();
	CREATE_FUNC(BallSelectMenu);
};
