#ifndef STRATEGY_H
#define STRATEGY_H

#include "Global.h" 
#include "cocos2d.h"
#include "PokerCard.h"

#include "vector"
#include<algorithm>
#include <string>
#include <deque>

USING_NS_CC;
class Poker;

//每种牌号的信息
struct Info
{
	int _brand;//牌值
	int _num; //牌数量
	CCArray* _arr; //集合牌
};
//保存电脑牌型
struct CardType :public CCObject
{
	CARD_TYPE _type;
	std::vector<Poker*> _vec;
};



std::vector<Info> makeInfo(CCArray *arr);
int isCallLord(CCArray* arr);
void splitPoker(CCArray* arr);

int cardType(CCArray* arr);
bool judgeOutPoker(CCArray*follow, CCArray*lastOut);

bool isSingle(CCArray* arr);		//单牌-
bool isPair(CCArray* arr);			//对子-
bool isThree(CCArray* arr);					//3不带-
bool isRocket(CCArray* arr);                //火箭
bool isBomb(CCArray* arr);					//炸弹
bool isThreeSingle(CCArray* arr);				//3带1-
bool isThreePair(CCArray* arr);				//3带2-
bool isBombTwoSingle(CCArray* arr);				//四个带2张单牌
bool isBombTwoPairs(CCArray* arr);			//四个带2对
bool isStraight(CCArray* arr);				//顺子-
bool isConnectPairs(CCArray* arr);				//连对-
bool isAircraft(CCArray* arr);				//飞机不带-
bool isAircraftSingle(CCArray* arr);		//飞机带单牌-
bool isAircraftPair(CCArray* arr);		//飞机带对子-
bool isError(CCArray* arr);				//错误的牌型

bool isSingleLarger(CCArray* follow, CCArray*lastOut);
bool isPairLarger(CCArray* follow, CCArray*lastOut);
bool isThreeLarger(CCArray* follow, CCArray*lastOut);
bool isBombLarger(CCArray* follow, CCArray*lastOut);
bool isThreeSingleLarger(CCArray* follow, CCArray*lastOut);
bool isThreePairLarger(CCArray* follow, CCArray*lastOut);
bool isBombTwoSingleLarger(CCArray* follow, CCArray*lastOut);
bool isBombTwoPairsLarger(CCArray* follow, CCArray*lastOut);
bool isStraightLarger(CCArray* follow, CCArray*lastOut);
bool isConnectPairsLarger(CCArray* follow, CCArray*lastOut);
bool isAircraftLarger(CCArray* follow, CCArray*lastOut);
bool isAircraftSingleLarger(CCArray* follow, CCArray*lastOut);
bool isAircraftPairLarger(CCArray* follow, CCArray*lastOut);

void sort(CCArray* arr);




#endif