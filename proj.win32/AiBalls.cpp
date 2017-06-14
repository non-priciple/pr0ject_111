#include"AiBalls.h"

USING_NS_CC;

AiBalls* AiBalls::createWithFileName(Layer*lSender, const std::string& filename, int ID)
{
	AiBalls* zz = new(std::nothrow) AiBalls;
	if (zz&&zz->initWithFile(filename) && zz->initStatus(100, ID))
	{
		zz->autorelease();
		lSender->addChild(zz, 1);
		zz->setPosition(Vec2(CCRANDOM_0_1() * 1280, CCRANDOM_0_1() * 720));
		return zz;
	}
	CC_SAFE_DELETE(zz);
	return nullptr;
}

int AiBalls::getDirection(Layer* lSender, float dt)
{
	int distance, x0, y0;

	cocos2d::Vector<Node*> allballs;
	allballs = this->getChildren();

	for (auto target : allballs)
	{
		Balls* target_p = dynamic_cast<Balls*>(target);
		if (target_p->getID() == 1)
		{
			x0 = this->getPositionX() - target_p->getPositionX();
			y0 = this->getPositionY() - target_p->getPositionY();

			distance = (x0*x0) + (y0*y0);

			if (distance <= 500)
			{
				x_ai = target_p->getPositionX();
				y_ai = target_p->getPositionY();
				return 0;
			}
		}
	}

	if (distance>500)
	{
		x_ai = CCRANDOM_0_1() * 1280;
		y_ai = CCRANDOM_0_1() * 720;

		return 0;
	}
	return 0;
}