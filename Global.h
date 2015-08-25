#ifndef GLOBAL_H
#define GLOBAL_H

#include "cocos2d.h"
#include <vector>
USING_NS_CC;


const int CardWidth = 123;//�ƵĿ�
const int CardHeight = 161;//�Ƶĸ�
const int CardGap = 44;//������֮��ļ��



//��ɫ
enum Suit
{
	Spade = 0,
	Heart,
	Club,
	Diamond,
	Joker,
	Back      //��ɫ����
};
//�ƺ�
enum Brand
{
	Three = 0, Four, Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King,Ace,Two,BlackJoker,RedJoker
	                                             
};
enum PlayerLocation
{
	Left=0,Right,Self,
	Display,//��ʾ�������
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

//��ǩ
enum BiaoQian
{
	FenShu,
	NpcTwoBuChu,
	NpcOneBuChu
};
//����������14������
enum CARD_TYPE
{
	SINGLE_CARD = 1,		//����-
	PAIR_CARD,			//����-
	THREE_CARD,				//3����
	ROCKET_CARD,          //���
	BOMB_CARD,				//ը��
	THREE_SINGLE_CARD,			//3��1-
	THREE_PAIR_CARD,			//3��2-
	BOMB_TWO_SINGLE_CARD,			//�ĸ���2�ŵ���
	BOMB_TWO_PAIRS_CARD,		//�ĸ���2��
	STRAIGHT_CARD,			//˳��-
	CONNECT_PAIRS_CARD,			//����-
	AIRCRAFT_CARD,			//�ɻ�����-
	AIRCRAFT_SINGLE_CARD,	//�ɻ�������-
	AIRCRAFT_PAIR_CARD,	//�ɻ�������-
	ERROR_CARD				//���������
};


#endif