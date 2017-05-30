//This is the menu where you select your character
#include<cocos2d.h>
class BallSelectMenu :public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(BallSelectMenu);
};
