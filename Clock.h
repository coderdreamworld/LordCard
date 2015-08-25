#ifndef CLOCK_H
#define CLOCK_H

#include "cocos2d.h"
USING_NS_CC;

////////////////////////////////
enum ClockType
{
	_Lord=0,_Play,_Jiabei
};
class Clock :public cocos2d::Sprite
{
public:
	Clock();
	~Clock();
	static Clock* createLordClock();//叫地主倒计时
	static Clock* createJiabeiClock();//加倍倒计时
	static Clock* createPlayClock();//打牌倒计时
	bool decrease();
	void clear();

private:
	CC_SYNTHESIZE(int, _sec, Sec);
	ClockType _type;
};

////////////////////////////////
class Number :public cocos2d::Sprite
{
public:
	Number();
	~Number();
	static Number* create();
	void displayNum(int);
private:
	CC_SYNTHESIZE(int, _num, Num);
};

/////////////////////////////////////
class pSprite :public cocos2d::Sprite
{
public:
	pSprite();
	~pSprite();
	void create(__String*);
	void create(char*);
};

#endif