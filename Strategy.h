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

//ÿ���ƺŵ���Ϣ
struct Info
{
	int _brand;//��ֵ
	int _num; //������
	CCArray* _arr; //������
};
//�����������
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

bool isSingle(CCArray* arr);		//����-
bool isPair(CCArray* arr);			//����-
bool isThree(CCArray* arr);					//3����-
bool isRocket(CCArray* arr);                //���
bool isBomb(CCArray* arr);					//ը��
bool isThreeSingle(CCArray* arr);				//3��1-
bool isThreePair(CCArray* arr);				//3��2-
bool isBombTwoSingle(CCArray* arr);				//�ĸ���2�ŵ���
bool isBombTwoPairs(CCArray* arr);			//�ĸ���2��
bool isStraight(CCArray* arr);				//˳��-
bool isConnectPairs(CCArray* arr);				//����-
bool isAircraft(CCArray* arr);				//�ɻ�����-
bool isAircraftSingle(CCArray* arr);		//�ɻ�������-
bool isAircraftPair(CCArray* arr);		//�ɻ�������-
bool isError(CCArray* arr);				//���������

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