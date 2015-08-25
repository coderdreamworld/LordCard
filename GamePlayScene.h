#ifndef GAMEPLAYSCENE_H
#define GAMEPLAYSCENE_H

#include "cocos2d.h"
#include "PokerCard.h"
#include "Player.h"
#include "LoginScene.h"
#include "Strategy.h"

class GamePlay:public cocos2d::Layer
{
public:
	GamePlay();
	~GamePlay();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GamePlay);

private:
	//////////////////成员函数
	////////初始化函数
	bool initBackground();
	bool initMenu();
	bool initPlayer();
	bool initAllPokers();
	////////洗牌发牌
	bool ShufflePoker();
	void DealPoker(float dt);
	////////更新
	void SelfUpdate(float dt);
	void RightUpdate(float dt);
	void LeftUpdate(float dt);
	/////////叫地主 出牌
	void playerCallLord();
	void npcCallLord();
	void playerFollowCard();
	void npcFollowCard();
	////////菜单回调
	void menuSettingCallback(cocos2d::Ref *sender);//设置
	void menuAutoCallback(cocos2d::Ref *sender);//托管
	void menuChatCallback(cocos2d::Ref *sender);//聊天
	void menuCallLordCallback(cocos2d::Ref *sender);//叫
	void menuNotCallLordCallback(cocos2d::Ref *sender);//不叫
	void menuRobLordCallback(cocos2d::Ref *sender);//抢
	void menuNotRobLordCallback(cocos2d::Ref *sender);//不抢
	void menuJiabeiLordCallback(cocos2d::Ref *sender);//加倍
	void menuNotJiabeiLordCallback(cocos2d::Ref *sender);//不加倍
	void menuFollowCallback(cocos2d::Ref *sender);//出牌
	void menuNotFollowCallback(cocos2d::Ref *sender);//不出
	void menuTipCallback(cocos2d::Ref *sender);//提示

	void changeToDetermineLord();
	void changeToJiabei(float dt);
	void changeToPlayPoker(float dt);
	void changeToLordAndFarmer(float dt);

	////////更新里的函数
	void SelfCallLord();
	void SelfDetermineLord();
	void SelfJiabei();
	void SelfPlayPoker();

	void RightCallLord();
	void RightDetermineLord();
	void RightJiabei();
	void RightPlayPoker();

	void LeftCallLord();
	void LeftDetermineLord();
	void LeftJiabei();
	void LeftPlayPoker();

	////////////
	void aboutLastRob();
	void clearImagesOfCallLord();
	void changeMultiple();
	void delayDealThree(float dt);

	bool judgeSelfSelectPoker();

	void determinePlayerType();
	bool ifPokerOver();

	////////重新开始
	void Restart();

	//////////////////数据成员
	Player *_Self;//自己的位置
	Player *_Left;//左边位置
	Player *_Right;//右边位置
	CCArray*  _arrayAllPoker;//所有的牌
	CCArray* _arrayLastOutPoker;//即将要压它的牌
	CCArray* _threePoker;
	CCArray*_threePokerSave;
	Menu* _menu;//设置 聊天 托管
	Menu* _callMenu;//叫地主
	Menu* _robMenu;//抢地主
	Menu* _jiabeiMenu;//加倍
	MenuItemSprite* _follow;//出牌选项
	MenuItemSprite* _follow1;//第一次出牌选项
	Menu* _playMenuFirst;//第一次出牌菜单
	Menu* _playMenu;//出牌总菜单 提示 
	Label* _multipleLabel;//倍数标签


	PlayerLocation _Lord;

	static int _multiple;//叫地主的倍数
	static int _lordTimes;//叫了几次
	static int _askTimes;//询问了几次

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	State _state;//DealPokers  CallLord  PlayPoker

	PlayerLocation _WhoFirstCall;//谁先叫地主
	PlayerLocation _firstCall;//谁第一个叫了地主
	PlayerLocation _lastRob;//谁最后叫了地主

	PlayerLocation _lastOutPlayer;//最后出牌的人
	PlayerType _lastOutPlayerType;//最后出牌的人的类型
	bool ifFirstOut;//是否是第一次出

	int visibleMiddleX;//屏幕水平中间
	int visibleMiddleY1;//最下面一栏y轴
	int visibleMiddleY2;//自己牌的位置y轴
	int visibleMiddleY3;//出牌 抢地主 display自己的牌
	Point LeftMiddle;
	Point RightMiddle;
	static int dealSign;

};



#endif