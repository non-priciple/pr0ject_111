//This is the battlefield where the main game runs
#include<cocos2d.h>
#include<SimpleAudioEngine.h>
class Combat :public cocos2d::Layer                   //class Combat is where to put all the balls and food
{
public:
	virtual bool init();
	CREATE_FUNC(Combat);
};
class BattleField : public cocos2d::Layer             //class BattleField is used as the parent node
{
public:
	//BackGround * _BG;
	int x;
	int y;
	cocos2d::EventKeyboard::KeyCode _keycode;
	cocos2d::EventListenerKeyboard *k_listener;
	void update(float del);
	int _me;
	cocos2d::TMXTiledMap * _BG;
	Combat * _BC;
	static cocos2d::Scene  *createScene(int ballID);
	virtual bool init();
	void setCameraFollow();
	CREATE_FUNC(BattleField);
};
/*class BackGround :public cocos2d::Layer
{

	virtual bool init();
	CREATE_FUNC(BackGround);
};*/



