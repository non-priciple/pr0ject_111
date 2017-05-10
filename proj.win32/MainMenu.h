// This is the main menu
#include<cocos2d.h>
#include<SimpleAudioEngine.h>
class MainMenu :public cocos2d::Layer 
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainMenu);
};
class MainBG :public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(MainBG);
};

