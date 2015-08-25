#include"Player.h"

/////////////////////////////////////////////////
Player::Player()
{
	_arrayPoker = CCArray::create();
	_arrayPoker->retain();

	_arraySelectPoker = CCArray::create();
	_arraySelectPoker->retain();

	_arrayOutPoker = CCArray::create();
	_arrayOutPoker->retain();

	_pokerNum = Number::create();
	_clockLord = Clock::createLordClock();
	_clockJiabei = Clock::createJiabeiClock();
	_clockPlay = Clock::createPlayClock();
	_imageNotFollow = Sprite::create("Menu/notFollowOther.png");
	_imageCall = Sprite::create("Menu/callLordOther.png");
	_imageRob=Sprite::create("Menu/robLordOther.png");
	_imageNotCall = Sprite::create("Menu/notCallLordOther.png");
	_imageNotRob = Sprite::create("Menu/notRobLordOther.png");
	_imageJiabei = Sprite::create("Menu/jiabeiOther.png");
	_imageNotJiabei = Sprite::create("Menu/notjiabeiOther.png");

	_pokerNum->setVisible(false);
	_clockLord->setVisible(false);
	_clockJiabei->setVisible(false);
	_clockPlay->setVisible(false);
	_imageNotFollow->setVisible(false);
	_imageCall->setVisible(false);
	_imageRob->setVisible(false);
	_imageNotCall->setVisible(false);
	_imageNotRob->setVisible(false);
	_imageJiabei->setVisible(false);
	_imageNotJiabei->setVisible(false);

	_image = new pSprite();

	_ifWantToBeLord = false;
	_ifJiabei = false;
	_isLord = false;
	_isWin = false;

	_cloudNum = 1;

}

Player::~Player()
{
	CC_SAFE_RELEASE(_arrayPoker);
	CC_SAFE_RELEASE(_arraySelectPoker);
	CC_SAFE_RELEASE(_arrayOutPoker);

	CC_SAFE_RELEASE(_pokerNum);
	CC_SAFE_RELEASE(_clockLord);
	CC_SAFE_RELEASE(_clockJiabei);
	CC_SAFE_RELEASE(_clockPlay);
	CC_SAFE_RELEASE(_image);
	CC_SAFE_RELEASE(_imageNotFollow);
	CC_SAFE_RELEASE(_imageCall);
	CC_SAFE_RELEASE(_imageRob);
	CC_SAFE_RELEASE(_imageNotCall);
	CC_SAFE_RELEASE(_imageNotRob);
	CC_SAFE_RELEASE(_imageJiabei);
	CC_SAFE_RELEASE(_imageNotJiabei);

	if (_image)
		delete _image;

}

void Player::SetPosition()
{
	Point point;
	Point point1;
	Point point2;
	if (_location == Self)
	{
		point = Point(480, 260);	
		point1 = Point(480, 260);
		point2 = Point(392, 260);
	}
	else if (_location == Left)
	{
		point = Point(325, 360);
		point1 = Point(240 , 360);
		point2 = Point(240, 360);
		_pokerNum->setPosition(147, 305);
	}
	else if (_location == Right)
	{
		point = Point(960-325, 360);	
		point1 = Point(960 - 240, 360);
		point2 = Point(960 - 240, 360);
		_pokerNum->setPosition(813, 305);
	}
	_clockJiabei->setPosition(point1);
	_clockLord->setPosition(point1);
	_clockPlay->setPosition(point2);
	_imageCall->setPosition(point);
	_imageNotCall->setPosition(point);
	_imageNotFollow->setPosition(point);
	_imageRob->setPosition(point);
	_imageJiabei->setPosition(point);
	_imageNotJiabei->setPosition(point);
	_imageNotRob->setPosition(point);

}

void Player::AddChild(Scene* scene)
{
	this->SetPosition();
	scene->addChild(_clockLord,1);
	scene->addChild(_clockJiabei, 1);
	scene->addChild(_clockPlay,1);
	scene->addChild(_imageNotFollow);
	scene->addChild(_imageCall);
	scene->addChild(_imageRob);
	scene->addChild(_imageNotCall);
	scene->addChild(_imageNotRob);
	scene->addChild(_imageJiabei);
	scene->addChild(_imageNotJiabei);

	changeToImageBegin();
	scene->addChild(_image);
	if (_location == Left || _location == Right)
		scene->addChild(_pokerNum,1);
}

void Player::changeToImageBegin()
{
	
	if (_isMale == true && (_location == Self || _location == Left))//自己 左边 男
		_image->create("BoyLeft.png");
	if (_isMale == false && (_location == Self || _location == Left))//自己 左边 女
		_image->create("GirlLeft.png");
	if (_isMale == true && (_location == Right))//右 男
		_image->create("BoyRight.png");
	if (_isMale == false && (_location == Right))//右 女
		_image->create("GirlRight.png");
	Vec2 SelfAnchor = Vec2(50, 150);
	Vec2 LeftAnchor = Vec2(50, 390);
	Vec2 RightAchor = Vec2(910, 390);

	if (_location == Self)
	{
		_image->setPosition(SelfAnchor);
	}
	else if (_location == Left)
	{
		_image->setPosition(LeftAnchor);
	}
	else if (_location == Right)
	{
		_image->setPosition(RightAchor);
	}


}

void Player::changeToImagePlay()
{ 
	__String *name;
	if (_cloudNum < 8)
	{
		name = String::createWithFormat("cloud%d.png", _cloudNum);
	}
	else
	{
		if (_isMale)
			name = __String::create("Male");
		else
			name = __String::create("Female");
		if (_isLord)
			name->appendWithFormat("Lord");
		else
			name->appendWithFormat("Farmer");
		if (_location == Self || _location == Left)
			name->appendWithFormat("Left.png");
		else
			name->appendWithFormat("Right.png");
	}
	++_cloudNum;
	this->_image->create(name);

}

void Player::changeToImageResult()
{
	__String *name = __String::create("");
	if (_isMale)
		name->appendWithFormat("Male");
	else
		name->appendWithFormat("Female");
	if (_isLord)
		name->appendWithFormat("Lord");
	else
		name->appendWithFormat("Farmer");
	if (_location == Self || _location == Left)
		name->appendWithFormat("Left");
	else
		name->appendWithFormat("Right");
	if (_isWin)
		name->appendWithFormat("Laugh.png");
	else
		name->appendWithFormat("Cry.png");

	_image->create(name);

	/*Vec2 SelfAnchor = Vec2(50, 150);
	Vec2 LeftAnchor = Vec2(50, 390);
	Vec2 RightAchor = Vec2(910, 390);
	if (_location == Self)
	{
		_image->setPosition(SelfAnchor);
	}
	else if (_location == Left)
	{
		_image->setPosition(LeftAnchor);
	}
	else if (_location == Right)
	{
		_image->setPosition(RightAchor);
	}*/
}

void Player::clearSomeImage()
{
	_imageCall->setVisible(false);
	_imageNotCall->setVisible(false);
	_imageRob->setVisible(false);
	_imageNotRob->setVisible(false);
	_imageNotJiabei->setVisible(false);
	_imageJiabei->setVisible(false);
	_imageNotFollow->setVisible(false);

}

void Player::changeCloud(float dt)
{
	__String *name;
	if (_isMale)
		name = __String::create("Male");
	else
		name = __String::create("Female");
	if (_isLord)
		name->appendWithFormat("Lord");
	else
		name->appendWithFormat("Farmer");
	if (_location == Self || _location == Left)
		name->appendWithFormat("Left.png");
	else
		name->appendWithFormat("Right.png");

	this->_image->create(name);
}

bool Player::isLord(int times)
{
	if (isCallLord(this->_arrayPoker) == 3)
		return true;
	else if (isCallLord(this->_arrayPoker) == 2 && times < 2)
		return true;
	else if (isCallLord(this->_arrayPoker) == 1 && times < 1)
		return true;

	return false;
}

void Player::updateThreePoker(CCArray*arr)
{
	Point first;
	Point last;
	
	if (_location == Self){
		first = ((Poker*)_arrayPoker->getObjectAtIndex(0))->getPosition();
		last = ((Poker*)_arrayPoker->getLastObject())->getPosition();
		for (int i = 0; i < arr->count(); ++i)
		{
			Object*ob = arr->getObjectAtIndex(i);
			_arrayPoker->addObject(ob);
		}
		this->sortPoker();
		for (int i = 0; i < arr->count(); ++i)
		{
			Poker* pk = (Poker*)arr->getObjectAtIndex(i);
			pk->front();
		}
		Point t = last - first;
		Point avr = Point(t.x / 19, t.y);
		((Poker*)_arrayPoker->getObjectAtIndex(0))->setPosition(first);
		for (int i = 1; i < _arrayPoker->count(); ++i)
		{
			Poker*pk = (Poker*)_arrayPoker->getObjectAtIndex(i - 1);
			((Poker*)_arrayPoker->getObjectAtIndex(i))->setPosition(pk->getPosition() +Point(avr.x,0));
		}
		
	}
	else if (_location == Right){
		first = ((Poker*)_arrayPoker->getObjectAtIndex(0))->getPosition();
		last = ((Poker*)_arrayPoker->getLastObject())->getPosition();
		for (int i = 0; i < arr->count(); ++i)
		{
			Object*ob = arr->getObjectAtIndex(i);
			_arrayPoker->addObject(ob);
		}
		this->sortPoker();
		for (int i = 0; i < arr->count(); ++i)
		{
			Poker* pk = (Poker*)arr->getObjectAtIndex(i);
			pk->s_front();//backRight();
		}
		Point avr = Point((last - first).x / 19, (last - first).y / 19);
		((Poker*)_arrayPoker->getObjectAtIndex(0))->setPosition(first);
		for (int i = 1; i < _arrayPoker->count(); ++i)
		{
			Poker*pk = (Poker*)_arrayPoker->getObjectAtIndex(i - 1);
			((Poker*)_arrayPoker->getObjectAtIndex(i))->setPosition(pk->getPosition() + avr);
		}
	}
	else if (_location == Left){
		first = ((Poker*)_arrayPoker->getObjectAtIndex(0))->getPosition();
		last = ((Poker*)_arrayPoker->getLastObject())->getPosition();
		for (int i = 0; i < arr->count(); ++i)
		{
			Object*ob = arr->getObjectAtIndex(i);
			_arrayPoker->addObject(ob);
		}
		this->sortPoker();
		for (int i = 0; i < arr->count(); ++i)
		{
			Poker* pk = (Poker*)arr->getObjectAtIndex(i);
			pk->s_front();//backLeft();
		}
		Point avr = Point((last - first).x / 19, (last - first).y / 19);
		((Poker*)_arrayPoker->getObjectAtIndex(0))->setPosition(first);
		for (int i = 1; i < _arrayPoker->count(); ++i)
		{
			Poker*pk = (Poker*)_arrayPoker->getObjectAtIndex(i - 1);
			((Poker*)_arrayPoker->getObjectAtIndex(i))->setPosition(pk->getPosition() + avr);
		}
	}
	
}

//////////////////
void Player::displayPokerNum()
{
	_pokerNum->setVisible(true);
	_pokerNum->displayNum(_arrayPoker->count());
}

void Player::displayOutPoker()
{
	
	if (_location == Self){
		_arrayOutPoker->removeAllObjects();
		_arrayOutPoker->addObjectsFromArray(_arraySelectPoker);
		int num = _arrayOutPoker->count() / 2;
		Point first = Point(480 - num * 20, 260);
		sortOutPoker();
		for (int i = 0; i < _arrayOutPoker->count(); ++i)
		{
			Poker* pk = (Poker*)_arrayOutPoker->getObjectAtIndex(i);
			//_arrayPoker->removeObject(pk);
			pk->front();
			pk->setZOrder(i);
			pk->setPosition(first + Point(i * 20, 0));
		}
	}
	else if (_location == Right){
		Point left = Point(175, 400);
		if (_arrayOutPoker->count()>9)
		{
			Point leftup = left + Point(0, 30);
			for (int i = 0; i < _arrayOutPoker->count(); ++i)
			{
				Poker* pk = (Poker*)_arrayOutPoker->getObjectAtIndex(i);
				if (i <= 9)
				{			
					pk->setPosition(leftup + Point(i * 20, 0));
				}
				else{
					pk->setPosition(left + Point((i - 9) * 20,0));
				}
				pk->setZOrder(i);
			}
		}
		else
		{
			for (int i = 0; i < _arrayOutPoker->count(); ++i)
			{
				Poker* pk = (Poker*)_arrayOutPoker->getObjectAtIndex(i);
				pk->setPosition(left + Point(i * 20, 0));
				pk->setZOrder(i);
			}
		}
	}
	else if (_location == Left){
		Point right = Point(785, 400);
		if (_arrayOutPoker->count()>9)
		{
			Point rightup = Point(right + Point(0, 30));
			for (int i = 0; i < _arrayOutPoker->count(); ++i)
			{
				Poker* pk = (Poker*)_arrayOutPoker->getObjectAtIndex(i);
				if (i <= 9)
				{
					pk->setPosition(rightup - Point((9-i) * 20, 0));
				}
				else{
					pk->setPosition(right - Point((i - 9) * 20, 0));
				}
				pk->setZOrder(i);
			}
		}
		else{
			for (int i = 0; i < _arrayOutPoker->count(); ++i)
			{
				Poker* pk = (Poker*)_arrayOutPoker->getObjectAtIndex(i);
				pk->setPosition(right - Point(i * 20, 0));
				pk->setZOrder(i);
			}
		}
	}

}

void Player::updatePoker()
{
	for (int i = 0; i < _arrayOutPoker->count(); ++i)
	{
		Object *ob = _arrayOutPoker->getObjectAtIndex(i);
		_arrayPoker->removeObject(ob);
	}
	sortPoker();

	if (_location == Self){ 
		if (_arrayPoker->count() >= 17)
		{
			Point first = Point(175, 130);
			Point last = Point(875, 130);
			int gap = (875 - 175) / (_arrayPoker->count() - 1);
			/*Poker* pk =(Poker*) _arrayPoker->getObjectAtIndex(0);
			pk->setPosition(first);*/
			for (int i = 0; i < _arrayPoker->count(); ++i)
			{
				Poker* pk1 = (Poker*)_arrayPoker->getObjectAtIndex(i);
				pk1->setPosition(first+Point(i*gap,0));
				pk1->setZOrder(i);
			}

		}
		else
		{
			Point middle = Point(535, 130);
			int num = _arrayPoker->count() / 2;
			Point first = Point(middle.x - num * 20, middle.y);
			Poker* pk =(Poker*) _arrayPoker->getObjectAtIndex(0);
			pk->setPosition(first);
			pk->setZOrder(0);
			for (int i = 1; i < _arrayPoker->count(); ++i)
			{
				Poker* pk1 = (Poker*)_arrayPoker->getObjectAtIndex(i-1);
				Poker* pk2 = (Poker*)_arrayPoker->getObjectAtIndex(i);
				pk2->setPosition(pk1->getPosition() + Point(20, 0));
				pk2->setZOrder(i);

			}
		}
	}
	else if (_location == Right){
		Point middle = Point(600, 560);
		int num = _arrayPoker->count() / 2;
		Point first = Point(middle + Point(22 * num, 25 * num));
		((Poker*)_arrayPoker->getObjectAtIndex(0))->setPosition(first);
		for (int i = 1; i < _arrayPoker->count(); ++i)
		{
			Poker*pk = (Poker*)_arrayPoker->getObjectAtIndex(i - 1);
			((Poker*)_arrayPoker->getObjectAtIndex(i))->setPosition(pk->getPosition()-Point(22,25));
		}

	}
	else if (_location == Left){
		Point middle = Point(360, 560);
		int num = _arrayPoker->count() / 2;
		Point first = Point(middle + Point(-22 * num, 25 * num));
		((Poker*)_arrayPoker->getObjectAtIndex(0))->setPosition(first);
		for (int i = 1; i < _arrayPoker->count(); ++i)
		{
			Poker*pk = (Poker*)_arrayPoker->getObjectAtIndex(i - 1);
			((Poker*)_arrayPoker->getObjectAtIndex(i))->setPosition(pk->getPosition() - Point(-22, 25));
		}
	}
}

void Player::clearArray()
{
	_arraySelectPoker->removeAllObjects();
	_arrayOutPoker->removeAllObjects();
}

void Player::clearOutPoker()
{
	for (int i = 0; i < _arrayOutPoker->count(); ++i)
	{
		Poker* pk = (Poker*)_arrayOutPoker->getObjectAtIndex(i);
		pk->setVisible(false);
	}
}
//////////////////
void Player::sortPoker()
{
	for (int i = 0; i < _arrayPoker->count(); ++i)
		for (int j = 0; j < _arrayPoker->count() - i - 1; ++j)
		{
		Poker* pk1 = (Poker*)_arrayPoker->getObjectAtIndex(j);
		Poker *pk2 = (Poker*)_arrayPoker->getObjectAtIndex(j + 1);
		if (pk1->getNum() < pk2->getNum())
		{
			_arrayPoker->exchangeObjectAtIndex(j, j + 1);
		}
		}
	
	for (int i = 0; i < _arrayPoker->count(); ++i)
	{
		Poker* pk1 = (Poker*)_arrayPoker->getObjectAtIndex(i);
		pk1->setZOrder(i);
	}
}

void Player::sortSelectPoker()
{
	for (int i = 0; i < _arraySelectPoker->count(); ++i)
		for (int j = _arraySelectPoker->count() - i - 1; j > 0; --j)
		{
		Poker* pk1 = (Poker*)_arraySelectPoker->getObjectAtIndex(j);
		Poker *pk2 = (Poker*)_arraySelectPoker->getObjectAtIndex(j - 1);
		if (pk1->getNum() < pk2->getNum())
		{
			_arraySelectPoker->exchangeObjectAtIndex(j, j - 1);
		}
		}
}

void Player::sortOutPoker()
{
	for (int i = 0; i < _arrayOutPoker->count(); ++i)
		for (int j = _arrayOutPoker->count() - i - 1; j > 0; --j)
		{
		Poker* pk1 = (Poker*)_arrayOutPoker->getObjectAtIndex(j);
		Poker *pk2 = (Poker*)_arrayOutPoker->getObjectAtIndex(j - 1);
		if (pk1->getNum() < pk2->getNum())
		{
			_arrayOutPoker->exchangeObjectAtIndex(j, j - 1);
		}
		}
}

void Player::Restart(Scene* scene)
{
	_arrayPoker->removeAllObjects();
	_arraySelectPoker->removeAllObjects();
	_arrayOutPoker->removeAllObjects();
	changeToImageBegin();
	_pokerNum->setVisible(false);
	_ifJiabei = false;
	_ifWantToBeLord = false;
	
}


