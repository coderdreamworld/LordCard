#ifndef POKERCARD_H
#define POKERCARD_H

#include "cocos2d.h"
#include "Global.h"
//#include "GamePlayScene.h"

USING_NS_CC;

class Poker :public cocos2d::Sprite
{
public:
	Poker();
	Poker(int, int);
	~Poker();
	void backLeft();//�����ұ���
	void backRight();//�ұ���ұ���
	void front();//�Լ�����
	void s_front();//С������
	void copy(Poker*);

	void clickToUp();//��� ������
	void clickToDown();//��� ������

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
	
private:
	CC_SYNTHESIZE(PlayerLocation, _cardType, CardType);
	CC_SYNTHESIZE(bool, _isSelect, Select);//�Ƿ���ѡ	
	//CC_SYNTHESIZE(bool, _isClick, Click);//�Ƿ��ܱ����
	CC_SYNTHESIZE(int, _suit, Suit);//��ɫ
	CC_SYNTHESIZE(int, _num, Num);//��ֵ
	CC_SYNTHESIZE(PlayerType, _player, Player);//�������
	//CC_SYNTHESIZE(GamePlay*, _gameScene, GameScene);
	EventListenerTouchOneByOne* touchListener;
};


#endif