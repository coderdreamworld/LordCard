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
	static Clock* createLordClock();//�е�������ʱ
	static Clock* createJiabeiClock();//�ӱ�����ʱ
	static Clock* createPlayClock();//���Ƶ���ʱ
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