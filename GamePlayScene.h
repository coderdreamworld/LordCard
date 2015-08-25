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
	//////////////////��Ա����
	////////��ʼ������
	bool initBackground();
	bool initMenu();
	bool initPlayer();
	bool initAllPokers();
	////////ϴ�Ʒ���
	bool ShufflePoker();
	void DealPoker(float dt);
	////////����
	void SelfUpdate(float dt);
	void RightUpdate(float dt);
	void LeftUpdate(float dt);
	/////////�е��� ����
	void playerCallLord();
	void npcCallLord();
	void playerFollowCard();
	void npcFollowCard();
	////////�˵��ص�
	void menuSettingCallback(cocos2d::Ref *sender);//����
	void menuAutoCallback(cocos2d::Ref *sender);//�й�
	void menuChatCallback(cocos2d::Ref *sender);//����
	void menuCallLordCallback(cocos2d::Ref *sender);//��
	void menuNotCallLordCallback(cocos2d::Ref *sender);//����
	void menuRobLordCallback(cocos2d::Ref *sender);//��
	void menuNotRobLordCallback(cocos2d::Ref *sender);//����
	void menuJiabeiLordCallback(cocos2d::Ref *sender);//�ӱ�
	void menuNotJiabeiLordCallback(cocos2d::Ref *sender);//���ӱ�
	void menuFollowCallback(cocos2d::Ref *sender);//����
	void menuNotFollowCallback(cocos2d::Ref *sender);//����
	void menuTipCallback(cocos2d::Ref *sender);//��ʾ

	void changeToDetermineLord();
	void changeToJiabei(float dt);
	void changeToPlayPoker(float dt);
	void changeToLordAndFarmer(float dt);

	////////������ĺ���
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

	////////���¿�ʼ
	void Restart();

	//////////////////���ݳ�Ա
	Player *_Self;//�Լ���λ��
	Player *_Left;//���λ��
	Player *_Right;//�ұ�λ��
	CCArray*  _arrayAllPoker;//���е���
	CCArray* _arrayLastOutPoker;//����Ҫѹ������
	CCArray* _threePoker;
	CCArray*_threePokerSave;
	Menu* _menu;//���� ���� �й�
	Menu* _callMenu;//�е���
	Menu* _robMenu;//������
	Menu* _jiabeiMenu;//�ӱ�
	MenuItemSprite* _follow;//����ѡ��
	MenuItemSprite* _follow1;//��һ�γ���ѡ��
	Menu* _playMenuFirst;//��һ�γ��Ʋ˵�
	Menu* _playMenu;//�����ܲ˵� ��ʾ 
	Label* _multipleLabel;//������ǩ


	PlayerLocation _Lord;

	static int _multiple;//�е����ı���
	static int _lordTimes;//���˼���
	static int _askTimes;//ѯ���˼���

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	State _state;//DealPokers  CallLord  PlayPoker

	PlayerLocation _WhoFirstCall;//˭�Ƚе���
	PlayerLocation _firstCall;//˭��һ�����˵���
	PlayerLocation _lastRob;//˭�����˵���

	PlayerLocation _lastOutPlayer;//�����Ƶ���
	PlayerType _lastOutPlayerType;//�����Ƶ��˵�����
	bool ifFirstOut;//�Ƿ��ǵ�һ�γ�

	int visibleMiddleX;//��Ļˮƽ�м�
	int visibleMiddleY1;//������һ��y��
	int visibleMiddleY2;//�Լ��Ƶ�λ��y��
	int visibleMiddleY3;//���� ������ display�Լ�����
	Point LeftMiddle;
	Point RightMiddle;
	static int dealSign;

};



#endif