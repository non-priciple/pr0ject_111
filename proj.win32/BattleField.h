//This is the battlefield where the main game runs
#include<cocos2d.h>
#include<SimpleAudioEngine.h>
#include<ui\CocosGUI.h>
#include<math.h>
class ESCMenu :public cocos2d::Layer
{
public:
	virtual bool init();
	void quitToMainMenu();
	void resumeToGame();
	CREATE_FUNC(ESCMenu);
};
class FailMenu :public cocos2d::Layer
{
public:
	virtual bool init();
	void failToSelectMenu();
	void setCallBackOn();
	cocos2d::EventListenerKeyboard *keyboardListener;
	CREATE_FUNC(FailMenu);
};
class Combat :public cocos2d::Layer                   //class Combat is where to put all the balls and food
{
public:
	int foodCount;
	int _meBall;
	
	void foodRefresh(float del);
	void foodCreator();
	virtual bool init();
	Combat(int meBall) :_meBall(meBall) {}
	static Combat * create(int meBall) 
	{ 
		Combat *pRet = new(std::nothrow) Combat(meBall); 
		if (pRet && pRet->init()) 
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
	}
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
	cocos2d::TMXTiledMap * _BG;
	Combat * _BC;
	ESCMenu * _ESC;
	FailMenu * _fail;
	static cocos2d::Scene  *createScene(int ballID);
	virtual bool init();
	void setCameraFollow(float nodeX,float nodeY);
	CREATE_FUNC(BattleField);
};
/*class BackGround :public cocos2d::Layer
{

	virtual bool init();
	CREATE_FUNC(BackGround);
};*/



