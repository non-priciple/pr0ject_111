#include"cocos2d.h"
#include"Balls.h"

USING_NS_CC;

class AiBalls :public Balls
{
	int SUBId;
public:
	//create AiBalls
	static AiBalls* createWithFileName(Layer*, const std::string&, int, int, int);

	//where is the aiball going to 
	int x_ai_2_1;
	int y_ai_2_1;

	Vec2& getNewPosition(int);
	Vec2& getOriginalPosition(int);
	Vec2& _getDirection(AiBalls*target_p, float nodeX, float nodeY, int BGlevel);
};