#ifndef GLOBAL_H
#define GLOBAL_H

#include "cocos2d.h"
#include <vector>
USING_NS_CC;


const int CardWidth = 123;//牌的宽
const int CardHeight = 161;//牌的高
const int CardGap = 44;//牌与牌之间的间距



//花色
enum Suit
{
	Spade = 0,
	Heart,
	Club,
	Diamond,
	Joker,
	Back      //花色背面
};
//牌号
enum Brand
{
	Three = 0, Four, Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King,Ace,Two,BlackJoker,RedJoker
	                                             
};
enum PlayerLocation
{
	Left=0,Right,Self,
	Display,//显示打出的牌
	Up,
	Null
};
enum State{
	DealPokers,
	CallLord,
	DetermineLord,
	Jiabei,
	PlayPoker
};
enum PlayerSex
{
	BoyLeft=0,BoyRight,GirlLeft
};

enum PlayerType
{
	Lord=0,Farmer
};

//标签
enum BiaoQian
{
	FenShu,
	NpcTwoBuChu,
	NpcOneBuChu
};
//斗地主共有14种牌型
enum CARD_TYPE
{
	SINGLE_CARD = 1,		//单牌-
	PAIR_CARD,			//对子-
	THREE_CARD,				//3不带
	ROCKET_CARD,          //火箭
	BOMB_CARD,				//炸弹
	THREE_SINGLE_CARD,			//3带1-
	THREE_PAIR_CARD,			//3带2-
	BOMB_TWO_SINGLE_CARD,			//四个带2张单牌
	BOMB_TWO_PAIRS_CARD,		//四个带2对
	STRAIGHT_CARD,			//顺子-
	CONNECT_PAIRS_CARD,			//连对-
	AIRCRAFT_CARD,			//飞机不带-
	AIRCRAFT_SINGLE_CARD,	//飞机带单牌-
	AIRCRAFT_PAIR_CARD,	//飞机带对子-
	ERROR_CARD				//错误的牌型
};


#endif