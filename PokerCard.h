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
	void backLeft();//左边玩家背面
	void backRight();//右边玩家背面
	void front();//自己正面
	void s_front();//小的牌面
	void copy(Poker*);

	void clickToUp();//点击 牌上移
	void clickToDown();//点击 牌下移

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
	
private:
	CC_SYNTHESIZE(PlayerLocation, _cardType, CardType);
	CC_SYNTHESIZE(bool, _isSelect, Select);//是否已选	
	//CC_SYNTHESIZE(bool, _isClick, Click);//是否能被点击
	CC_SYNTHESIZE(int, _suit, Suit);//花色
	CC_SYNTHESIZE(int, _num, Num);//牌值
	CC_SYNTHESIZE(PlayerType, _player, Player);//玩家类型
	//CC_SYNTHESIZE(GamePlay*, _gameScene, GameScene);
	EventListenerTouchOneByOne* touchListener;
};


#endif