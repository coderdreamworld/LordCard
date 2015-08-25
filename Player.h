#ifndef PLAYER_H
#define PLAYER_H

#include "Global.h"
#include "Clock.h"
#include "cocos2d.h"
#include "Strategy.h"
USING_NS_CC;


class Player:public cocos2d::Object,public cocos2d::Sprite
{
public:
	Player();
	~Player();

	/////////////////////////////
	//函数
	void changeToImageBegin();
	void changeToImagePlay();//地主 农民图片
	void changeToImageResult();//地主 农民哭笑
	void changeCloud(float dt);
	void SetPosition();
	void AddChild(Scene* scene);
	void clearSomeImage();
	bool isLord(int);

	void updateThreePoker(CCArray*arr);

	////////////
	void displayPokerNum();//显示牌数量
	void displayOutPoker();
	void updatePoker();
	void clearArray();
	void clearOutPoker();
	////////////
	void sortPoker();
	void sortSelectPoker();
	void sortOutPoker();
	////////////
	void Restart(Scene*);


	//数据成员
	CCArray* _arrayPoker;//手里目前拥有的扑克牌
	CCArray* _arraySelectPoker;//选择的牌
	CCArray* _arrayOutPoker;//打出的牌

	pSprite* _image;//玩家图片

	Sprite* _imageNotFollow;//不出
	Sprite* _imageCall;//叫地主
	Sprite* _imageRob;//抢地主
	Sprite* _imageNotCall;//不叫地主
	Sprite* _imageNotRob;//不抢地主
	Sprite* _imageJiabei;//加倍
	Sprite* _imageNotJiabei;//不加倍

	Clock* _clockLord;//叫地主倒计时
	Clock* _clockJiabei;//加倍倒计时
	Clock* _clockPlay;//出牌倒计时
	Number* _pokerNum;//显示牌数量


	bool _ifWantToBeLord;//当第一个叫地主时 是否叫了地主
	bool _ifJiabei;
	bool _isLord;
	bool _isWin;

	int _cloudNum;

private:
	CC_SYNTHESIZE(bool, _isMale, Male);//性别
	CC_SYNTHESIZE(PlayerLocation, _location, Location);//self left right
	//CC_SYNTHESIZE(PlayerType, _type, Type);//是地主还是农民
	//CC_SYNTHESIZE(Point, _playerAnchor, PlayerAnchor);//锚点
};



#endif