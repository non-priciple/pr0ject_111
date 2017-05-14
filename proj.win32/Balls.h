//This is the character
//default designed size is  480*480 p          //maybe a little problem
//default designed radius=339 p                //set at 260 provides better user experience
#include <cocos2d.h>

class Balls : public cocos2d::Sprite
{
private:
	unsigned int _level;
	int _radius;
	int _identity;                                                     //sync with the id of Character
public:
	//skill to be done
	static Balls* createWithFileName(const std::string & filename)
	{
		Balls *ball = new(std::nothrow) Balls;
		if (ball&&ball->initWithFile(filename) && ball->initStatus(1))
		{
			ball->autorelease();
			return ball;
		}
		CC_SAFE_DELETE(ball);
		return nullptr;
	}

	bool initStatus(int tlevel)
	{
		_level = tlevel;
		updateRadius();
		return true;
	}
	void setID(int identity)
	{
		_identity = identity;
	}
	void updateRadius()                                          //update the radius and size when level changes
	{
		this->setScale(sqrt(_level) / 10);
		_radius = sqrt(_level) * 260 / 10;
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
	void swallow(cocos2d::Layer *_Battlefield)
	{
		cocos2d::Vector<Node*> _allballs;
		_allballs = _Battlefield->getChildren();
		for (auto _target : _allballs)
		{
			if (_target->isVisible())
			{
				Balls* _target_b = dynamic_cast<Balls*>(_target);
				if (_target_b != nullptr)
				{
					float _distance = cocos2d::ccpDistance(_target->getPosition(), this->getPosition());
					if (_distance <= this->_radius + _target_b->_radius)
					{
						if (this->_level > _target_b->_level)
						{
							_target->setVisible(false);
							this->addLevel(_target_b->_level);
						}
						else if (this->_level < _target_b->_level)
						{
							this->setVisible(false);
							this->_level = 1;
						}
					}
				}

			}

		}
	}

};
