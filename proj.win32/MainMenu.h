// This is the main menu
#include<cocos2d.h>
#include<SimpleAudioEngine.h>
class MainBG :public cocos2d::Layer
{
public:
	float x;
	float y;
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(MainBG);
};
class MainMenu :public cocos2d::Layer 
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainMenu);
};


