// This is the main menu
#include<cocos2d.h>
class MainBG :public cocos2d::Layer
{
public:
	float x;
	float y;
	cocos2d::EventKeyboard::KeyCode _keycode;
	cocos2d::EventListenerKeyboard *k_listener;
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(MainBG);
	
};
class MainMenu :public cocos2d::Layer 
{
public:
	static cocos2d::Scene* createScene();
	void switchSceneToSelectSP();
	void switchSceneToSelectMP();
	virtual bool init();
	CREATE_FUNC(MainMenu);
};


