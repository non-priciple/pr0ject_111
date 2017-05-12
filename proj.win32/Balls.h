//This is the character
//default designed size is  480*480 p
//default designed radius=339 p
#include <cocos2d.h>
class Balls : public cocos2d::Sprite
{
private:
	unsigned int _level;
	int _radius;
	int _identity;                                                     //sync with the id of Character
public:
	virtual void useSkill();                                      //skill to be done
	static Balls* createWithFileName(const std::string & filename)
	{
		Balls *ball = new(std::nothrow) Balls;
		if (ball&&ball->initWithFile(filename) && ball->initStatus())
		{
			ball->autorelease();
			return ball;
		}
		CC_SAFE_DELETE(ball);
		return nullptr;
	}
	bool initStatus()
	{
		_level = 1;
		updateRadius();
	}
	void setID(int identity)
	{
		_identity = identity;
	}
	void updateRadius()                                          //update the radius and size when level changes
	{
		this->setScale(sqrt(_level) / 10);
		_radius = sqrt(_level) * 339 / 10;
	}
	void addLevel(const int delLevel)                              //after eating other balls,call this
	{
		_level += delLevel;
		if (_level > 100) _level = 100;								//the level limit should be adjusted later
	}
	void division(const cocos2d::Vec2 & vec)
	{

		_level = _level / 2;
		updateRadius();
	}
};

