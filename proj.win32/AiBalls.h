#include"cocos2d.h"
#include"Balls.h"

USING_NS_CC;

class AiBalls :public Balls
{
public:
	//create AiBalls
	static AiBalls* createWithFileName(Layer*, const std::string&, int);

	//where is the aiball going to 
	int x_ai;
	int y_ai;
	int getDirection(Layer*, float);
};