//This is the menu where you select your character
#include<cocos2d.h>
class BallSelectMenu :public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	void switchToBattleField(int ballID);
	void selectX();
	void selectH();
	void selectC();
	void startWithX();
	void startWithH();
	void startWithC();
	CREATE_FUNC(BallSelectMenu);
};
