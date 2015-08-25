#include "Clock.h"
USING_NS_CC;
////////////////////////////////////////clock
Clock::Clock()
{
	
}

Clock::~Clock()
{

}

Clock* Clock::createLordClock()
{
	Clock *clock = new Clock();
	clock->_type = _Lord;
	clock->setSec(10);
	if (clock&&clock->initWithSpriteFrameName("clock_10.png"))
	{
		clock->autorelease();
	}

	return clock;
}

Clock* Clock::createJiabeiClock()
{
	Clock *clock = new Clock();
	clock->_type = _Jiabei;
	clock->setSec(5);
	if (clock&&clock->initWithSpriteFrameName("clock_5.png"))
	{
		clock->autorelease();
	}

	return clock;
}

Clock* Clock::createPlayClock()
{
	Clock *clock = new Clock();
	clock->_type = _Play;
	clock->setSec(25);
	if (clock&&clock->initWithSpriteFrameName("clock_25.png"))
	{
		clock->setVisible(false);
		clock->autorelease();
	}

	return clock;
}

bool Clock::decrease()
{
	if (this->_sec >= 2)
	{
		this->setSec(--_sec);
		__String* name = __String::createWithFormat("clock_%d.png", _sec);
		SpriteFrame *frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		this->setDisplayFrame(frame);

		return true;
	}
	else{
		this->clear();
		return false;
	}
}

void Clock::clear()
{
	this->setVisible(false);
	if (_type == _Lord)
		this->setSec(10);
	else if (_type == _Play)
		this->setSec(25);
	else if (_type==_Jiabei)
		this->setSec(5);
	__String* name = __String::createWithFormat("clock_%d.png", _sec);
	SpriteFrame *frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
	this->setDisplayFrame(frame);
}


///////////////////////////////////////////number
Number::Number()
{

}

Number::~Number()
{

}

Number* Number::create()
{
	Number *num = new Number();
	num->_num = 17;
	if (num&&num->initWithSpriteFrameName("17.png"))
	{
		num->setVisible(false);
		num->autorelease();
	}
	return num;
}

void Number::displayNum(int num)
{
	this->_num = num;
	__String* name = __String::createWithFormat("%d.png", _num);
	SpriteFrame *frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
	this->setDisplayFrame(frame);
}

/////////////////////////////////////////////////
pSprite::pSprite()
{}

pSprite::~pSprite()
{}

void pSprite::create(__String *name)
{
	if (this->initWithFile(name->getCString()))
	{
		this->autorelease();
	}
	else
	{
		SpriteFrame *frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		this->setDisplayFrame(frame);
	}
}
void pSprite::create(char *name)
{
	if (this->initWithFile(name))
	{
		this->autorelease();
	}
	else
	{
		SpriteFrame *frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
		this->setDisplayFrame(frame);
	}
}