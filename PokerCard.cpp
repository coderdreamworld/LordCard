#include "PokerCard.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

Poker::Poker()
{
	//_isClick = false;
	_isSelect = false;
}

Poker::Poker(int i, int j)
{
	//this->setClick(false);
	this->setSelect(false);
	this->setSuit(i);
	this->setNum(j);
}

Poker::~Poker()
{

}

void Poker::backLeft()
{
	_cardType = Left;
	if (this->initWithFile("Poker/CardBackLeft.png"))
	{
		this->autorelease();
	}
	else
	{
		SpriteFrame *frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Poker/CardBackLeft.png");
		this->setDisplayFrame(frame);
	}
}

void Poker::backRight()
{
	_cardType = Right;
	if (this->initWithFile("Poker/CardBackRight.png"))
	{
		this->autorelease();
	}
	else
	{
		SpriteFrame *frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Poker/CardBackRight.png");
		this->setDisplayFrame(frame);
	}
}

void Poker::front()
{
	_cardType = Self;
	__String *name;
	if (_suit==Spade)
	     name = __String::createWithFormat("Spade_%d.png",_num+3);
	else if (_suit==Heart)
		 name = __String::createWithFormat("Heart_%d.png",_num+3);
	else if (_suit==Club)
		name = __String::createWithFormat("Club_%d.png",_num+3);
	else if (_suit==Diamond)
		name = __String::createWithFormat("Diamond_%d.png",_num+3);
	else if (_suit == Joker)
	{
		if (_num==BlackJoker)
			name = __String::createWithFormat("BlackJoker.png");
		else if (_num==RedJoker)
			name = __String::createWithFormat("RedJoker.png");
	}

	if (this->initWithSpriteFrameName(name->getCString()))
	{
		this->autorelease();
	}
	else
	{
		SpriteFrame *frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		this->setDisplayFrame(frame);
	}
}

void Poker::s_front()
{
	_cardType = Display;
	__String *name;
	if (_suit == Spade)
		name = __String::createWithFormat("s_Spade_%d.png", _num + 3);
	else if (_suit == Heart)
		name = __String::createWithFormat("s_Heart_%d.png", _num + 3);
	else if (_suit == Club)
		name = __String::createWithFormat("s_Club_%d.png", _num + 3);
	else if (_suit == Diamond)
		name = __String::createWithFormat("s_Diamond_%d.png", _num + 3);
	else if (_suit == Joker)
	{
		if (_num == BlackJoker)
			name = __String::createWithFormat("s_BlackJoker.png");
		else if (_num == RedJoker)
			name = __String::createWithFormat("s_RedJoker.png");
	}

	if (this->initWithSpriteFrameName(name->getCString()))
	{
		this->autorelease();
	}
	else
	{
		SpriteFrame *frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		this->setDisplayFrame(frame);
	}
}

void Poker::copy(Poker*pk)
{
	_suit = pk->_suit;
	_num = pk->_num;
	_cardType = Null;
	this->s_front();
}

void Poker::clickToUp()
{
	if (_cardType == Self)
	{
		SimpleAudioEngine::getInstance()->playEffect("Sound/SpecSelectCard.mp3");
		this->setPosition(this->getPosition().x, this->getPosition().y + 20);
		this->_isSelect = true;
	}
}

void Poker::clickToDown()
{
	if (_cardType == Self)
	{
		SimpleAudioEngine::getInstance()->playEffect("Sound/SpecSelectCard.mp3");
		this->setPosition(this->getPosition().x, this->getPosition().y - 20);
		this->_isSelect = false;
	}
}

void Poker::onEnter()
{
	Sprite::onEnter();
	//触摸响应注册
	touchListener = EventListenerTouchOneByOne::create();//创建单点触摸事件监听器
	touchListener->onTouchBegan = CC_CALLBACK_2(Poker::onTouchBegan, this);//触摸开始
	touchListener->onTouchMoved = CC_CALLBACK_2(Poker::onTouchMoved, this);//触摸移动
	touchListener->onTouchEnded = CC_CALLBACK_2(Poker::onTouchEnded, this);//触摸结束
	touchListener->setSwallowTouches(true);//不向下吞并触摸
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//注册分发器
}

void Poker::onExit()
{
	//移除触摸响应
	_eventDispatcher->removeEventListenersForTarget(this);
	Sprite::onExit();
}

bool Poker::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	Size size = getContentSize();
	Rect rect(-size.width / 2, -size.height / 2, size.width, size.height);
	Point ptouch = convertTouchToNodeSpaceAR(pTouch); //由英文之意转换 触摸 到 节点空间
	if (rect.containsPoint(ptouch))
	{
		if (!_isSelect)
		{
			clickToUp();
		}
		else
		{
			clickToDown();
		}
		return true;
	}
	return false;
	//如果这里返回false触摸不被吞掉
}

void Poker::onTouchMoved(Touch *pTouch, Event *pEvent){

}
void Poker::onTouchEnded(Touch *pTouch, Event *pEvent){

}
void Poker::onTouchCancelled(Touch *pTouch, Event *pEvent){

}
