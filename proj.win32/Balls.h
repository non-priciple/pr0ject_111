//This is the character
//default designed size is  480*480 p          
//default designed radius=339 p                //set at 260 provides better user experience
#include <cocos2d.h>
#include<math.h>
class Balls : public cocos2d::Sprite
{
private:
	unsigned int _level;
	int _radius;
	int _identity;                                                     //sync with the id of Character;1 for Player,0 for computer
public:
	//skill to be done
	static Balls* createWithFileName(const std::string & filename)
	{
		Balls *ball = new(std::nothrow) Balls;
		if (ball&&ball->initWithFile(filename) && ball->initStatus(1, 0))
		{
			ball->autorelease();
			return ball;
		}
		CC_SAFE_DELETE(ball);
		return nullptr;
	}
	static Balls* createWithBallsFrame(cocos2d::SpriteFrame *spriteFrame)
	{
		Balls *sprite = new (std::nothrow) Balls();
		if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	bool initStatus(int tlevel, int id)
	{
		this->_level = tlevel;
		this->_identity = id;
		if (this != nullptr)
		this->updateRadius();
		return true;
	}
	void setID(int identity)
	{
		_identity = identity;
	}
	int getID()
	{
		return _identity;
	}
	int getRadius()
	{
		return _radius;
	}
	unsigned int getLevel()
	{
		return _level;
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
	float speed()
	{
		return sqrt(this->_level*1.5 / 10);
	}
	void division(float x, float y, cocos2d::EventKeyboard::KeyCode &_keycode, cocos2d::Layer* _Battelfield, cocos2d::EventListenerKeyboard* listener)//unfinished;
	{
		if (_keycode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE&&this->_level > 8)
		{
			this->_level = this->_level / 2;
			if (this != nullptr)
			this->updateRadius();
			Balls* substitute = this->createWithBallsFrame(this->getSpriteFrame());
			substitute->initStatus(this->_level, this->_identity);
			substitute->setPosition(this->getPosition());
			auto moveTo = cocos2d::MoveTo::create(0.1, cocos2d::Vec2(x, y));
			substitute->runAction(moveTo);
			_Battelfield->addChild(substitute, 1);
			
			
		}
	}
	void movement(float x, float y, cocos2d::Layer *_Battlefield,int player_id)
	{
		this->stopAllActions();
		auto moveTo = cocos2d::MoveTo::create(this->speed(), cocos2d::Vec2(x, y));
		this->runAction(moveTo);
		cocos2d::Vector<Node*> _allballs;
		_allballs = _Battlefield->getChildren();
		for (auto _target : _allballs)
		{
			Balls* the_target = dynamic_cast<Balls*>(_target);
			if (the_target != nullptr&&the_target->_identity == player_id &&the_target!=this)
			{
				float distance = cocos2d::ccpDistance(this->getPosition(), the_target->getPosition());
				if (distance < the_target->_radius + this->_radius)
				{
					this->stopAllActions();
					float _x = this->getPositionX() - the_target->getPositionX();
					float _y = this->getPositionY() - the_target->getPositionY();
					auto moveby = cocos2d::MoveBy::create(0.5, cocos2d::Vec2(_x, _y));
					this->runAction(moveby);
				}
		     }
		}
	}
	void swallow(cocos2d::Layer *_Battlefield)
	{
		cocos2d::Vector<Node*> _allballs;
		_allballs = _Battlefield->getChildren();
		for (auto _target : _allballs)
		{
			Balls* target_b = dynamic_cast<Balls*>(_target);
			if (target_b != nullptr&&target_b->_identity !=this->_identity)
			{
				float _distance = cocos2d::ccpDistance(target_b->getPosition(), this->getPosition());
				if (_distance <= this->_radius + target_b->_radius)
				{
					if (this->_level > target_b->_level)
					{
						_Battlefield->removeChild(target_b);
						this->addLevel(target_b->_level);
					}
					else if (this->_level < target_b->_level)
					{
						_Battlefield->removeChild(this);
					}
				}
			}
		}
	}

};
