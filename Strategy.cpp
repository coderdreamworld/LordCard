#include "Strategy.h"

std::vector<Info> makeInfo(CCArray *arr)
{

	std::vector<Info>vec;
	int a[15];
	for (int i = 0; i < 15; ++i)
		a[i] = 0;
	for (int i = 0; i < arr->count(); ++i)
	{
		Poker* pk = (Poker*)arr->getObjectAtIndex(i);
		++a[pk->getNum()];
	}
	for (int i = 0; i < 15; ++i)
	{
		if (a[i] != 0)
		{
			Info info;
			info._brand = i;
			info._num = a[i];
			vec.push_back(info);
		}
	}
	return vec;
}

int isCallLord(CCArray* arr)
{
	int point = 0;
	int mul = 0;
	
	std::vector<Info>vec = makeInfo(arr);
	for (int i = 0; i < vec.size(); ++i)
	{
		if (vec[i]._brand == RedJoker)
			point += 4;
		if (vec[i]._brand == BlackJoker)
			point += 3;
		if (vec[i]._brand == Two)
			point += (2 * vec[i]._num);
	}
	if (point >= 7)
		mul = 3;
	else if (point >= 5)
		mul = 2;
	else if (point >= 3)
		mul = 1;

	return mul;
}

void splitPoker(CCArray* arr)
{

}

int cardType(CCArray* arr)
{
	if (isSingle(arr))
		return SINGLE_CARD;
	else if (isPair(arr))
		return PAIR_CARD;
	else if (isThree(arr))
		return THREE_CARD;
	else if (isRocket(arr))
		return ROCKET_CARD;
	else if (isBomb(arr))
		return BOMB_CARD;
	else if (isThreeSingle(arr))
		return THREE_SINGLE_CARD;
	else if (isThreePair(arr))
		return THREE_PAIR_CARD;
	else if (isBombTwoSingle(arr))
		return BOMB_TWO_SINGLE_CARD;
	else if (isBombTwoPairs(arr))
		return BOMB_TWO_PAIRS_CARD;
	else if (isStraight(arr))
		return STRAIGHT_CARD;
	else if (isConnectPairs(arr))
		return CONNECT_PAIRS_CARD;
	else if (isAircraft(arr))
		return AIRCRAFT_CARD;
	else if (isAircraftSingle(arr))
		return AIRCRAFT_SINGLE_CARD;
	else if (isAircraftPair(arr))
		return AIRCRAFT_PAIR_CARD;

	return ERROR_CARD;
	
}

bool judgeOutPoker(CCArray*follow, CCArray*lastOut)
{
	if (lastOut->count() == 0)
	{
		if (cardType(follow)<ERROR_CARD&&cardType(follow)>0)
		return true;

		return false;
	}
	else{
		/////////火箭 炸弹
		if (cardType(follow) == ROCKET_CARD)
			return true;
		if (cardType(lastOut) == ROCKET_CARD)
			return false;
		if (cardType(follow) == BOMB_CARD&&cardType(lastOut) != ROCKET_CARD&&cardType(lastOut) != BOMB_CARD)
			return true;
		/////////牌型相同
		if (cardType(follow) == cardType(lastOut)&&cardType(follow)!=ERROR_CARD)
		{
			if (cardType(follow) == SINGLE_CARD&&isSingleLarger(follow, lastOut))
				return true;
			if (cardType(follow) == PAIR_CARD&&isPairLarger(follow, lastOut))
				return true;
			if (cardType(follow) == THREE_CARD&&isThreeLarger(follow, lastOut))
				return true;
			if (cardType(follow) == BOMB_CARD&&isBombLarger(follow, lastOut))
				return true;
			if (cardType(follow) == THREE_SINGLE_CARD&&isThreeSingleLarger(follow, lastOut))
				return true;
			if (cardType(follow) == THREE_PAIR_CARD&&isThreePairLarger(follow, lastOut))
				return true;
			if (cardType(follow) == BOMB_TWO_SINGLE_CARD&&isBombTwoSingleLarger(follow, lastOut))
				return true;
			if (cardType(follow) == BOMB_TWO_PAIRS_CARD&&isBombTwoPairsLarger(follow, lastOut))
				return true;
			if (cardType(follow) == STRAIGHT_CARD&&isStraightLarger(follow, lastOut))
				return true;
			if (cardType(follow) == CONNECT_PAIRS_CARD&&isConnectPairsLarger(follow, lastOut))
				return true;
			if (cardType(follow) == AIRCRAFT_CARD&&isAircraftLarger(follow, lastOut))
				return true;
			if (cardType(follow) == AIRCRAFT_SINGLE_CARD&&isAircraftSingleLarger(follow, lastOut))
				return true;
			if (cardType(follow) == AIRCRAFT_PAIR_CARD&&isAircraftPairLarger(follow, lastOut))
				return true;
		}
	}
	return false;
}
///////////////////
bool isSingle(CCArray* arr)		//单牌-
{
	if (arr->count() == 1)
		return true;

	return false;
}
bool isPair(CCArray* arr)			//对子-
{
	if (arr->count() == 2)
	{
		Poker*pk1 =(Poker*) arr->getObjectAtIndex(0);
		Poker*pk2 = (Poker*)arr->getObjectAtIndex(1);
		if (pk1->getNum() == pk2->getNum())
			return true;
	}
	return false;
}
bool isThree(CCArray* arr)					//3不带-
{
	if (arr->count() == 3)
	{
		Poker*pk1 = (Poker*)arr->getObjectAtIndex(0);
		Poker*pk2 = (Poker*)arr->getObjectAtIndex(1);
		Poker*pk3 = (Poker*)arr->getObjectAtIndex(2);
		if (pk1->getNum() == pk2->getNum() && pk3->getNum() == pk2->getNum())
			return true;
	}
	return false;
}
bool isRocket(CCArray* arr)                //火箭
{
	sort(arr);
	if (arr->count() == 2)
	{
		Poker*pk1 = (Poker*)arr->getObjectAtIndex(0);
		Poker*pk2 = (Poker*)arr->getObjectAtIndex(1);
		if (pk1->getNum() ==BlackJoker && pk2->getNum() == RedJoker)
			return true;
	}
	return false;
}
bool isBomb(CCArray* arr)					//炸弹
{
	if (arr->count() == 4)
	{
		Poker*pk1 = (Poker*)arr->getObjectAtIndex(0);
		Poker*pk2 = (Poker*)arr->getObjectAtIndex(1);
		Poker*pk3 = (Poker*)arr->getObjectAtIndex(2);
		Poker*pk4 = (Poker*)arr->getObjectAtIndex(3);
		if (pk1->getNum() == pk2->getNum() && pk3->getNum() == pk2->getNum() && pk3->getNum() == pk4->getNum())
			return true;
	}
	return false;
}
bool isThreeSingle(CCArray* arr)				//3带1-
{
	sort(arr);
	if (arr->count() == 4)
	{
		Poker*pk1 = (Poker*)arr->getObjectAtIndex(0);
		Poker*pk2 = (Poker*)arr->getObjectAtIndex(1);
		Poker*pk3 = (Poker*)arr->getObjectAtIndex(2);
		Poker*pk4 = (Poker*)arr->getObjectAtIndex(3);
		if ((pk1->getNum() == pk2->getNum() && pk3->getNum() == pk2->getNum() && pk3->getNum() != pk4->getNum()) 
			|| (pk1->getNum() != pk2->getNum() && pk3->getNum() == pk2->getNum() && pk3->getNum() == pk4->getNum()))
			return true;
	}
	return false;
}
bool isThreePair(CCArray* arr)				//3带2-
{
	sort(arr);
	if (arr->count() == 5)
	{
		Poker*pk1 = (Poker*)arr->getObjectAtIndex(0);
		Poker*pk2 = (Poker*)arr->getObjectAtIndex(1);
		Poker*pk3 = (Poker*)arr->getObjectAtIndex(2);
		Poker*pk4 = (Poker*)arr->getObjectAtIndex(3);
		Poker*pk5 = (Poker*)arr->getObjectAtIndex(4);
		if ((pk1->getNum() == pk2->getNum() && pk3->getNum() == pk2->getNum() && pk3->getNum() != pk4->getNum() && pk4->getNum() == pk5->getNum())
			|| (pk1->getNum() == pk2->getNum() && pk3->getNum() != pk2->getNum() && pk3->getNum() == pk4->getNum() && pk5->getNum() == pk4->getNum()))
			return true;
	}
	return false;
}
bool isBombTwoSingle(CCArray* arr)				//四个带2张单牌
{
	sort(arr);
	if (arr->count() == 6)
	{
		Poker*pk1 = (Poker*)arr->getObjectAtIndex(0);
		Poker*pk2 = (Poker*)arr->getObjectAtIndex(1);
		Poker*pk3 = (Poker*)arr->getObjectAtIndex(2);
		Poker*pk4 = (Poker*)arr->getObjectAtIndex(3);
		Poker*pk5 = (Poker*)arr->getObjectAtIndex(4);
		Poker*pk6 = (Poker*)arr->getObjectAtIndex(5);
		if ((pk1->getNum() == pk2->getNum() && pk2->getNum() == pk3->getNum() && pk3->getNum() == pk4->getNum())
			|| (pk4->getNum() == pk5->getNum() && pk5->getNum() == pk6->getNum() && pk3->getNum() == pk4->getNum()))
		
			return true;
	}
	return false;
}
bool isBombTwoPairs(CCArray* arr)			//四个带2对
{
	sort(arr);
	if (arr->count() == 8)
	{
		Poker*pk1 = (Poker*)arr->getObjectAtIndex(0);
		Poker*pk2 = (Poker*)arr->getObjectAtIndex(1);
		Poker*pk3 = (Poker*)arr->getObjectAtIndex(2);
		Poker*pk4 = (Poker*)arr->getObjectAtIndex(3);
		Poker*pk5 = (Poker*)arr->getObjectAtIndex(4);
		Poker*pk6 = (Poker*)arr->getObjectAtIndex(5);
		Poker*pk7 = (Poker*)arr->getObjectAtIndex(6);
		Poker*pk8 = (Poker*)arr->getObjectAtIndex(7);
		if ((pk1->getNum() == pk2->getNum() && pk2->getNum() == pk3->getNum() && pk3->getNum() == pk4->getNum()
			&& pk5->getNum() == pk6->getNum() && pk7->getNum() == pk8->getNum())
			|| (pk6->getNum() == pk7->getNum() && pk5->getNum() == pk6->getNum() && pk7->getNum() == pk8->getNum()
			&& pk1->getNum() == pk2->getNum() && pk3->getNum() == pk4->getNum())
			|| ( pk5->getNum() == pk6->getNum() && pk3->getNum() == pk4->getNum() && pk5->getNum() == pk4->getNum()
			&& pk1->getNum() == pk2->getNum() && pk7->getNum() == pk8->getNum()))
			return true;
	}
	return false;
}
bool isStraight(CCArray* arr)				//顺子-
{
	sort(arr);
	if (arr->count() >= 5 && ((Poker*)(arr->getLastObject()))->getNum() < Two)
	{
		for (int i = 0; i < arr->count() - 1; ++i)
		{
			Poker*pk1 = (Poker*)arr->getObjectAtIndex(i);
			Poker*pk2 = (Poker*)arr->getObjectAtIndex(i+1);
			if (pk2->getNum() - pk1->getNum() != 1)
				return false;
		}
		return true;
	}
	return false;
}
bool isConnectPairs(CCArray* arr)				//连对-
{
	sort(arr);
	if (arr->count()>0&&arr->count() % 2 == 0 && ((Poker*)(arr->getLastObject()))->getNum() < Two)
	{
		for (int i = 0; i < arr->count(); i += 2)
		{
			Poker*pk1 = (Poker*)arr->getObjectAtIndex(i);
			Poker*pk2 = (Poker*)arr->getObjectAtIndex(i + 1);
			if (pk1->getNum() != pk2->getNum())
				return false;
		}
		for (int i = 0; i < arr->count(); i += 2)
		{
			Poker*pk1 = (Poker*)arr->getObjectAtIndex(i);
			Poker*pk2 = (Poker*)arr->getObjectAtIndex(i + 2);
			if (pk2->getNum() - pk1->getNum()!=1)
				return false;
		}
		return true;
	}
	return false;
}
bool isAircraft(CCArray* arr)				//飞机不带-
{
	sort(arr);
	if (arr->count()>0 && arr->count() % 3 == 0 && arr->count()>3 && ((Poker*)(arr->getLastObject()))->getNum() < Two)
	{
		int a[12];
		for (int i = 0; i < 12; ++i)
			a[i] = 0;
		for (int i = 0; i < arr->count(); ++i)
		{
			Poker*pk = (Poker*)arr->getObjectAtIndex(i);
			++a[pk->getNum()];
		}

		int num = arr->count()%3;
		int *b = new int[num];
		int cnt = 0;
		for (int i = 0; i < 12; ++i)
		{
			if (a[i] == 3)
			{
				b[cnt] = i;
				++cnt;
			}
		}
		if (cnt < num)
		{
			delete[]b;
			return false;
		}
		for (int i = 0; i < num-1; ++i)
		{
			if (b[i + 1] - b[i] != 1)
			{
				delete[]b;
				return false;
			}
		}
		delete[]b;
		return true;
	}
	return false;
}
bool isAircraftSingle(CCArray* arr)		//飞机带单牌-
{
	sort(arr);
	if ((arr->count() == 8 || arr->count() == 12 || arr->count() == 16 || arr->count() == 20) && ((Poker*)(arr->getLastObject()))->getNum() < Two)
	{
		int a[12];
		for (int i = 0; i < 12; ++i)
			a[i] = 0;
		for (int i = 0; i < arr->count(); ++i)
		{
			Poker*pk = (Poker*)arr->getObjectAtIndex(i);
			++a[pk->getNum()];
		}

		int num = arr->count() / 4;
		int *b = new int[num];
		int cnt = 0;
		for (int i = 0; i < 12; ++i)
		{
			if (a[i] == 3)
			{
				b[cnt] = i;
				++cnt;
			}
		}
		if (cnt < num)
		{
			delete[]b;
			return false;
		}
		for (int i = 0; i < num - 1; ++i)
		{
			if (b[i + 1] - b[i] != 1)
			{
				delete[]b;
				return false;
			}
		}
		delete[]b;
		return true;

	} 
	return false;

}
bool isAircraftPair(CCArray* arr)		//飞机带对子-
{
	sort(arr);
	if ((arr->count() == 10 || arr->count() == 15 || arr->count() == 20) && ((Poker*)(arr->getLastObject()))->getNum() < Two)
	{
		int a[12];
		for (int i = 0; i < 12; ++i)
			a[i] = 0;
		for (int i = 0; i < arr->count(); ++i)
		{
			Poker*pk = (Poker*)arr->getObjectAtIndex(i);
			++a[pk->getNum()];
		}
        ///////////飞机
		int num = arr->count() / 5;
		int *b = new int[num];
		int cnt = 0;
		for (int i = 0; i < 12; ++i)
		{
			if (a[i] == 3)
			{
				b[cnt] = i;
				++cnt;
			}
		}
		if (cnt < num)
		{
			delete[]b;
			return false;
		}
		for (int i = 0; i < num - 1; ++i)
		{
			if (b[i + 1] - b[i] != 1)
			{
				delete[]b;
				return false;
			}
		}
		delete[]b;
        /////////对子
		int cnt1 = 0;
		for (int i = 0; i < 12; ++i)
		{
			if (a[i] == 2)
			{
				++cnt1;
			}
		}
		if (cnt1 != num)
			return false;

		return true;
	}
	return false;
}
bool isError(CCArray* arr)				//错误的牌型
{
	if (!(
		isSingle(arr) || isPair(arr) || isThree(arr) || isRocket(arr) || isBomb(arr) || isThreeSingle(arr) ||
		isThreePair(arr) || isBombTwoSingle(arr) || isBombTwoPairs(arr) || isStraight(arr) || isConnectPairs(arr) ||
		isAircraft(arr) || isAircraftSingle(arr) || isAircraftPair(arr)
		))
		return false;
	return true;
}
///////////////////
bool isSingleLarger(CCArray* follow, CCArray*lastOut)
{
	Poker*pk = (Poker*)follow->getObjectAtIndex(0);
	Poker*pk1 = (Poker*)lastOut->getObjectAtIndex(0);
	if (pk->getNum() > pk1->getNum())
		return true;

	return false;
}
bool isPairLarger(CCArray* follow, CCArray*lastOut)
{
	Poker*pk = (Poker*)follow->getObjectAtIndex(0);
	Poker*pk1 = (Poker*)lastOut->getObjectAtIndex(0);
	if (pk->getNum() > pk1->getNum())
		return true;

	return false;
}
bool isThreeLarger(CCArray* follow, CCArray*lastOut)
{
	Poker*pk = (Poker*)follow->getObjectAtIndex(0);
	Poker*pk1 = (Poker*)lastOut->getObjectAtIndex(0);
	if (pk->getNum() > pk1->getNum())
		return true;

	return false;
}
bool isBombLarger(CCArray* follow, CCArray*lastOut)
{
	Poker*pk = (Poker*)follow->getObjectAtIndex(0);
	Poker*pk1 = (Poker*)lastOut->getObjectAtIndex(0);
	if (pk->getNum() > pk1->getNum())
		return true;

	return false;
}
bool isThreeSingleLarger(CCArray* follow, CCArray*lastOut)
{
	int followNum=0, lastNum=0;
	int a[13];
	for (int i = 0; i < 13; ++i)
		a[i] = 0;
	for (int i = 0; i < follow->count(); ++i)
	{
		Poker*pk = (Poker*)follow->getObjectAtIndex(i);
		++a[pk->getNum()];
	}
	for (int i = 0; i < 13; ++i)
		if (a[i] == 3)
			followNum = i;

	int b[13];
	for (int i = 0; i < 13; ++i)
		b[i] = 0;
	for (int i = 0; i < lastOut->count(); ++i)
	{
		Poker*pk = (Poker*)lastOut->getObjectAtIndex(i);
		++b[pk->getNum()];
	}
	for (int i = 0; i < 13; ++i)
		if (b[i] == 3)
			lastNum = i;

	if (followNum > lastNum)
		return true;

	return false;
}
bool isThreePairLarger(CCArray* follow, CCArray*lastOut)
{
	int followNum = 0, lastNum = 0;
	int a[13];
	for (int i = 0; i < 13; ++i)
		a[i] = 0;
	for (int i = 0; i < follow->count(); ++i)
	{
		Poker*pk = (Poker*)follow->getObjectAtIndex(i);
		++a[pk->getNum()];
	}
	for (int i = 0; i < 13; ++i)
		if (a[i] == 3)
			followNum = i;

	int b[13];
	for (int i = 0; i < 13; ++i)
		b[i] = 0;
	for (int i = 0; i < lastOut->count(); ++i)
	{
		Poker*pk = (Poker*)lastOut->getObjectAtIndex(i);
		++b[pk->getNum()];
	}
	for (int i = 0; i < 13; ++i)
		if (b[i] == 3)
			lastNum = i;

	if (followNum > lastNum)
		return true;

	return false;
}
bool isBombTwoSingleLarger(CCArray* follow, CCArray*lastOut)
{
	int followNum = 0, lastNum = 0;
	int a[13];
	for (int i = 0; i < 13; ++i)
		a[i] = 0;
	for (int i = 0; i < follow->count(); ++i)
	{
		Poker*pk = (Poker*)follow->getObjectAtIndex(i);
		++a[pk->getNum()];
	}
	for (int i = 0; i < 13; ++i)
		if (a[i] == 4)
			followNum = i;

	int b[13];
	for (int i = 0; i < 13; ++i)
		b[i] = 0;
	for (int i = 0; i < lastOut->count(); ++i)
	{
		Poker*pk = (Poker*)lastOut->getObjectAtIndex(i);
		++b[pk->getNum()];
	}
	for (int i = 0; i < 13; ++i)
		if (b[i] == 4)
			lastNum = i;

	if (followNum > lastNum)
		return true;

	return false;
}
bool isBombTwoPairsLarger(CCArray* follow, CCArray*lastOut)
{
	int followNum = 0, lastNum = 0;
	int a[13];
	for (int i = 0; i < 13; ++i)
		a[i] = 0;
	for (int i = 0; i < follow->count(); ++i)
	{
		Poker*pk = (Poker*)follow->getObjectAtIndex(i);
		++a[pk->getNum()];
	}
	for (int i = 0; i < 13; ++i)
		if (a[i] == 4)
			followNum = i;

	int b[13];
	for (int i = 0; i < 13; ++i)
		b[i] = 0;
	for (int i = 0; i < lastOut->count(); ++i)
	{
		Poker*pk = (Poker*)lastOut->getObjectAtIndex(i);
		++b[pk->getNum()];
	}
	for (int i = 0; i < 13; ++i)
		if (b[i] == 4)
			lastNum = i;

	if (followNum > lastNum)
		return true;

	return false;
}
bool isStraightLarger(CCArray* follow, CCArray*lastOut)
{
	if (follow->count() == lastOut->count())
	{
		Poker*pk = (Poker*)follow->getObjectAtIndex(0);
		Poker*pk1 = (Poker*)lastOut->getObjectAtIndex(0);
		if (pk->getNum()>pk1->getNum())
			return true;
	}
	return false;
}
bool isConnectPairsLarger(CCArray* follow, CCArray*lastOut)
{
	if (follow->count() == lastOut->count())
	{
		Poker*pk = (Poker*)follow->getObjectAtIndex(0);
		Poker*pk1 = (Poker*)lastOut->getObjectAtIndex(0);
		if (pk->getNum()>pk1->getNum())
			return true;
	}
	return false;
}
bool isAircraftLarger(CCArray* follow, CCArray*lastOut)
{
	if (follow->count() == lastOut->count())
	{
		int followNum = 0, lastNum = 0;
		int a[12];
		for (int i = 0; i < 12; ++i)
			a[i] = 0;
		for (int i = 0; i < follow->count(); ++i)
		{
			Poker*pk = (Poker*)follow->getObjectAtIndex(i);
			++a[pk->getNum()];
		}
		for (int i = 0; i < 12; ++i)
			if (a[i] == 3)
			{
			followNum = i;
			break;
			}

		int b[12];
		for (int i = 0; i < 12; ++i)
			b[i] = 0;
		for (int i = 0; i < lastOut->count(); ++i)
		{
			Poker*pk = (Poker*)lastOut->getObjectAtIndex(i);
			++b[pk->getNum()];
		}
		for (int i = 0; i < 12; ++i)
			if (b[i] == 3)
			{
			lastNum = i;
			break;
			}

		if (followNum > lastNum)
			return true;
	}

	return false;
}
bool isAircraftSingleLarger(CCArray* follow, CCArray*lastOut)
{
	if (follow->count() == lastOut->count())
	{
		int followNum = 0, lastNum = 0;
		int a[12];
		for (int i = 0; i < 12; ++i)
			a[i] = 0;
		for (int i = 0; i < follow->count(); ++i)
		{
			Poker*pk = (Poker*)follow->getObjectAtIndex(i);
			++a[pk->getNum()];
		}
		for (int i = 0; i < 12; ++i)
			if (a[i] == 3)
			{
			followNum = i;
			break;
			}

		int b[12];
		for (int i = 0; i < 12; ++i)
			b[i] = 0;
		for (int i = 0; i < lastOut->count(); ++i)
		{
			Poker*pk = (Poker*)lastOut->getObjectAtIndex(i);
			++b[pk->getNum()];
		}
		for (int i = 0; i < 12; ++i)
			if (b[i] == 3)
			{
			lastNum = i;
			break;
			}

		if (followNum > lastNum)
			return true;
	}

	return false;
}
bool isAircraftPairLarger(CCArray* follow, CCArray*lastOut)
{
	if (follow->count() == lastOut->count())
	{
		int followNum = 0, lastNum = 0;
		int a[12];
		for (int i = 0; i < 12; ++i)
			a[i] = 0;
		for (int i = 0; i < follow->count(); ++i)
		{
			Poker*pk = (Poker*)follow->getObjectAtIndex(i);
			++a[pk->getNum()];
		}
		for (int i = 0; i < 12; ++i)
			if (a[i] == 3)
			{
			followNum = i;
			break;
			}

		int b[12];
		for (int i = 0; i < 12; ++i)
			b[i] = 0;
		for (int i = 0; i < lastOut->count(); ++i)
		{
			Poker*pk = (Poker*)lastOut->getObjectAtIndex(i);
			++b[pk->getNum()];
		}
		for (int i = 0; i < 12; ++i)
			if (b[i] == 3)
			{
			lastNum = i;
			break;
			}

		if (followNum > lastNum)
			return true;
	}

	return false;
}

////////////////////
void sort(CCArray* arr)
{
	for (int i = 0; i < arr->count(); ++i)
		for (int j = 0; j < arr->count() - i - 1; ++j)
		{
		Poker* pk1 = (Poker*)arr->getObjectAtIndex(j);
		Poker *pk2 = (Poker*)arr->getObjectAtIndex(j + 1);
		if (pk1->getNum() < pk2->getNum())
		{
			arr->exchangeObjectAtIndex(j, j + 1);
		}
		}
}