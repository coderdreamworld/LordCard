#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

int GamePlay::_multiple = 15;
int GamePlay::_lordTimes = 0;
int GamePlay::_askTimes = 0;
int GamePlay::dealSign = 0;

GamePlay::GamePlay()
{
	_arrayAllPoker = CCArray::create();
	_arrayAllPoker->retain();

	_threePoker = CCArray::create();
	_threePoker->retain();

	_threePokerSave = CCArray::create();
	_threePokerSave->retain();

	_arrayLastOutPoker = CCArray::create();
	_arrayLastOutPoker->retain();
}

GamePlay::~GamePlay()
{
	CC_SAFE_RELEASE(_arrayAllPoker);
}

Scene* GamePlay::createScene()
{
	auto scene = Scene::create();
	auto layer = GamePlay::create();
	scene->addChild(layer);

	return scene;
}

///////////////////////////////////调用具体初始化函数
bool GamePlay::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	visibleMiddleX = visibleSize.width / 2;
	visibleMiddleY2 = 130;
	visibleMiddleY3 = 257;
	LeftMiddle = Point(160, 305);
	RightMiddle = Point(800, 305);
	_state = DealPokers;
	_firstCall = Null;
	_lastRob = Null;
	ifFirstOut = true;

	bool isRet = false;

	do{
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Player/Player.plist", "Player/Player.png");
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Poker/Poker.plist", "Poker/Poker.png");
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Poker/s_Poker.plist", "Poker/s_Poker.png");
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("clock/clock.plist", "clock/clock.png");
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Number/number.plist", "Number/number.png");
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Cloud/cloud.plist", "Cloud/cloud.png");
		//SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/MusicEx_Normal.mp3", true);
		srand((unsigned)time(NULL));//初始化随机种子
		CC_BREAK_IF(!initBackground());
		CC_BREAK_IF(!initMenu());
		CC_BREAK_IF(!initPlayer());
		CC_BREAK_IF(!initAllPokers());	
		CC_BREAK_IF(!ShufflePoker());

		

		isRet = true;

	} while (0);

	

	return isRet;
}

////////////////////////////////////具体初始化函数
bool GamePlay::initBackground()
{
	bool isRet = false;
	do{
		auto bg = Sprite::create("Background/bg1.png");
		bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(bg);
		//this->removeChild(bg);

		/*auto test = Sprite::create("Menu/notFollow.png");
		test->setAnchorPoint(Vec2(0, 0));
		test->setPosition(175, 400);
		this->addChild(test);
		test->setZOrder(20);*/
		
		isRet = true;
	} while (0);
	return isRet;
} 

bool GamePlay::initMenu()
{
	bool isRet = false;
	do
	{
		//////////////////////菜单1
		//设置按钮
		auto settingNormal = Sprite::create("Menu/setting.png");
		auto settingSelected = Sprite::create("Menu/setting.png");
		MenuItemSprite *setting = MenuItemSprite::create(settingNormal, settingSelected,
			CC_CALLBACK_1(GamePlay::menuSettingCallback, this));
		//setting->setTag(ActionType::MenuItemSetting);
		setting->setPosition(Vec2(860, 600));

		//聊天按钮
		auto chatNormal = Sprite::create("Menu/chat1.png");
		auto chatSelected = Sprite::create("Menu/chat1.png");
		MenuItemSprite *chat = MenuItemSprite::create(chatNormal, chatSelected,
			CC_CALLBACK_1(GamePlay::menuChatCallback, this));
		//chat->setTag(ActionType::MenuItemSetting);
		chat->setPosition(Vec2(900, 20));

		//托管按钮
		auto autoOn = MenuItemImage::create("Menu/auto_on.png", "Menu/auto_on.png");
		auto autoOff = MenuItemImage::create("Menu/auto_off.png", "Menu/auto_off.png");
		auto autoToggle = MenuItemToggle::createWithCallback(
			CC_CALLBACK_1(GamePlay::menuAutoCallback, this),
			autoOff,
			autoOn,
			NULL);
		autoToggle->setPosition(Vec2(920, 600));

		//菜单1
		_menu = Menu::create(chat, setting, autoToggle, NULL);
		_menu->setPosition(Vec2::ZERO);
		this->addChild(_menu);

		///////////////////////叫地主菜单
		auto callNormal = Sprite::create("Menu/callLord.png");
		auto callSelected = Sprite::create("Menu/callLord.png");
		MenuItemSprite *call = MenuItemSprite::create(callNormal, callSelected,
			CC_CALLBACK_1(GamePlay::menuCallLordCallback, this));
		call->setPosition(Vec2(340, visibleMiddleY3));

		auto notCallNormal = Sprite::create("Menu/notCallLord.png");
		auto notCallSelected = Sprite::create("Menu/notCallLord.png");
		MenuItemSprite *notCall = MenuItemSprite::create(notCallNormal, notCallSelected,
			CC_CALLBACK_1(GamePlay::menuNotCallLordCallback, this));
		notCall->setPosition(Vec2(620, visibleMiddleY3));

		_callMenu = Menu::create(call,notCall, NULL);
		_callMenu->setPosition(Vec2::ZERO);
		this->addChild(_callMenu);

		_callMenu->setVisible(false);

		///////////////////////抢地主菜单
		auto robNormal = Sprite::create("Menu/robLord.png");
		auto robSelected = Sprite::create("Menu/robLord.png");
		MenuItemSprite *rob = MenuItemSprite::create(robNormal, robSelected,
			CC_CALLBACK_1(GamePlay::menuRobLordCallback, this));
		rob->setPosition(Vec2(340, visibleMiddleY3));

		auto notRobNormal = Sprite::create("Menu/notRobLord.png");
		auto notRobSelected = Sprite::create("Menu/notRobLord.png");
		MenuItemSprite *notRob = MenuItemSprite::create(notRobNormal, notRobSelected,
			CC_CALLBACK_1(GamePlay::menuNotRobLordCallback, this));
		notRob->setPosition(Vec2(620, visibleMiddleY3));

		_robMenu = Menu::create(rob, notRob, NULL);
		_robMenu->setPosition(Vec2::ZERO);
		this->addChild(_robMenu);

		_robMenu->setVisible(false);

		//////////////////////加倍菜单
		auto jiabeiNormal = Sprite::create("Menu/jiabei.png");
		auto jiabeiSelected = Sprite::create("Menu/jiabei.png");
		MenuItemSprite *jiabei = MenuItemSprite::create(jiabeiNormal, jiabeiSelected,
			CC_CALLBACK_1(GamePlay::menuJiabeiLordCallback, this));
		jiabei->setPosition(Vec2(340, visibleMiddleY3));

		auto notjiabeiNormal = Sprite::create("Menu/notjiabei.png");
		auto notjiabeiSelected = Sprite::create("Menu/notjiabei.png");
		MenuItemSprite *notjiabei = MenuItemSprite::create(notjiabeiNormal, notjiabeiSelected,
			CC_CALLBACK_1(GamePlay::menuNotJiabeiLordCallback, this));
		notjiabei->setPosition(Vec2(620, visibleMiddleY3));

		_jiabeiMenu = Menu::create(jiabei, notjiabei, NULL);
		_jiabeiMenu->setPosition(Vec2::ZERO);
		this->addChild(_jiabeiMenu);

		_jiabeiMenu->setVisible(false);

		//////////////////////第一次出牌菜单
		auto follow1Normal = Sprite::create("Menu/follow_on.png");
		auto follow1Selected = Sprite::create("Menu/follow_on.png");
		auto follow1Disabled = Sprite::create("Menu/follow_off.png");
		_follow1 = MenuItemSprite::create(follow1Normal, follow1Selected, follow1Disabled,
			CC_CALLBACK_1(GamePlay::menuFollowCallback, this));
		_follow1->setPosition(Vec2(520, visibleMiddleY3));
		_follow1->setEnabled(false);

		_playMenuFirst = Menu::create( _follow1, NULL);
		_playMenuFirst->setPosition(Vec2::ZERO);
		this->addChild(_playMenuFirst);

		_playMenuFirst->setVisible(false);

		///////////////////////出牌菜单	
		//不出
		auto notFollowNormal = Sprite::create("Menu/notFollow.png");
		auto notFollowSelected = Sprite::create("Menu/notFollow.png");
		MenuItemSprite *notFollow = MenuItemSprite::create(notFollowNormal, notFollowSelected,
			CC_CALLBACK_1(GamePlay::menuNotFollowCallback, this));
		notFollow->setPosition(Vec2(260, visibleMiddleY3));
		//提示
		auto tipNormal = Sprite::create("Menu/tip.png");
		auto tipSelected = Sprite::create("Menu/tip.png");
		MenuItemSprite *tip = MenuItemSprite::create(tipNormal, tipSelected,
			CC_CALLBACK_1(GamePlay::menuTipCallback, this));
		tip->setPosition(Vec2(524, visibleMiddleY3));
		//出牌
		auto followNormal = Sprite::create("Menu/follow_on.png");
		auto followSelected = Sprite::create("Menu/follow_on.png");
		auto followDisabled = Sprite::create("Menu/follow_off.png");
		_follow = MenuItemSprite::create(followNormal, followSelected, followDisabled,
			CC_CALLBACK_1(GamePlay::menuFollowCallback, this));
		_follow->setPosition(Vec2(700, visibleMiddleY3));
		_follow->setEnabled(false);
		//菜单
		_playMenu = Menu::create(notFollow, _follow, tip,NULL);
		_playMenu->setPosition(Vec2::ZERO);
		this->addChild(_playMenu);

		_playMenu->setVisible(false);

		////////////////////////////
		auto bei = Sprite::create("Menu/bei.png");
		bei->setPosition(600, 20);
		this->addChild(bei);

		__String *t_multiple = String::createWithFormat("%d", _multiple);

		TTFConfig ttfConfig("fonts/Marker Felt.ttf", 24, GlyphCollection::DYNAMIC);
		ttfConfig.outlineSize = 2;
		_multipleLabel = Label::createWithTTF(ttfConfig, t_multiple->getCString());
		_multipleLabel->setPosition(Vec2(700, 20));
		//_multipleLabel->enableShadow(Color4B(255, 255, 255, 128), Size(2.5, -1));
		_multipleLabel->setColor(Color3B::YELLOW);
		this->addChild(_multipleLabel);

		isRet = true;
	} while (0);

	return isRet;
}

bool GamePlay::initPlayer()
{
	bool isRet = false;
	do{
		/*auto follow_on = Sprite::create("follow_on.png");
		follow_on->setPosition(400, 250);
		this->addChild(follow_on);*/

		_Self = new Player();
		_Left = new Player();
		_Right = new Player();


		_Self->setMale(Login::getSex());//
		_Left->setMale(false);
		_Right->setMale(false);

		_Self->setLocation(Self);
		_Left->setLocation(Left);
		_Right->setLocation(Right);

		/*this->addChild(_Self->returnImage());
		this->addChild(_Left->returnImage());
		this->addChild(_Right->returnImage());*/

		_Self->AddChild((Scene*)this);
		_Left->AddChild((Scene*)this);
		_Right->AddChild((Scene*)this);

		isRet = true;
	} while (0);
	return isRet;
}

bool GamePlay::initAllPokers()
{
	bool isRet = false;
	do{
		
		//创造前52张牌
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 13; ++j)
			{
			Poker* poker = new Poker(i, j);
			_arrayAllPoker->addObject(poker);
			
			}
		//创造大王
		Poker *rJ = new Poker(Joker, RedJoker);
		_arrayAllPoker->addObject(rJ);
		
		//创造小王
		Poker *bJ = new Poker(Joker, BlackJoker);
		_arrayAllPoker->addObject(bJ);
		

		for (int i = 0; i < 3; ++i)
		{
			Poker*three = new Poker();
			_threePoker->addObject(three);
		}

		isRet = true;
	} while (0);

	return isRet;
}

/////////////////////////////////////洗发牌 设置谁是首先叫地主
bool GamePlay::ShufflePoker()
{
	bool isRet = false;
	do
	{
		//////////////////////////////随机一下谁先叫地主
		int firstcall = 0;// rand() % 3;
		switch (firstcall)
		{
		case 0:
			_WhoFirstCall = Self;
			break;
		case 1:
			_WhoFirstCall = Left;
			break;
		default:
			_WhoFirstCall = Right;
			break;
		}
		//////////////////////////////洗牌
		for (int i = 0; i < 54; ++i)
		{
			Poker *poker1 = (Poker*)_arrayAllPoker->randomObject();
			Poker *poker2 = (Poker*)_arrayAllPoker->randomObject();
			_arrayAllPoker->exchangeObject(poker1, poker2);
		}
		//////////////////////////////分牌
		for (int i = 0; i < 51; ++i)
		{

			if (i % 3 == 0)
				_Self->_arrayPoker->addObject(_arrayAllPoker->getObjectAtIndex(i));
			else if (i % 3 == 1)
				_Right->_arrayPoker->addObject(_arrayAllPoker->getObjectAtIndex(i));
			else
				_Left->_arrayPoker->addObject(_arrayAllPoker->getObjectAtIndex(i));
		}
		for (int i = 51; i < 54; ++i)
			_threePokerSave->addObject(_arrayAllPoker->getObjectAtIndex(i));
		
		///////////////////////////////发牌
		//初始化牌的样子
		for (int i = 0; i < 17; ++i)
		{
			((Poker*)_Self->_arrayPoker->getObjectAtIndex(i))->front();
			//((Poker*)_Self->_arrayPoker->getObjectAtIndex(i))->s_front();
			((Poker*)_Left->_arrayPoker->getObjectAtIndex(i))->s_front();
			((Poker*)_Right->_arrayPoker->getObjectAtIndex(i))->s_front();
		//	((Poker*)_Left->_arrayPoker->getObjectAtIndex(i))->backLeft();
		//	((Poker*)_Right->_arrayPoker->getObjectAtIndex(i))->backRight();
		}
		for (int i = 0; i < 3; ++i)
		{
			Poker*pk = (Poker*)_threePoker->getObjectAtIndex(i);
			Poker*pksave = (Poker*)_threePokerSave->getObjectAtIndex(i);
			pk->copy(pksave);
		}
		//对Self的牌排序
		for (int i = 0; i < 17; ++i)
			for (int j = 0; j < 16 - i; ++j)
			{
			Poker *pk1 = (Poker*)_Self->_arrayPoker->getObjectAtIndex(j);
			Poker*pk2 = (Poker*)_Self->_arrayPoker->getObjectAtIndex(j+1);
			//大的在前 小的在后
			if (pk1->getNum()<pk2->getNum())
				_Self->_arrayPoker->exchangeObjectAtIndex(j, j + 1);
			}
		//对Left的牌排序
		for (int i = 0; i < 17; ++i)
			for (int j = 0; j < 16 - i; ++j)
			{
			Poker *pk1 = (Poker*)_Left->_arrayPoker->getObjectAtIndex(j);
			Poker*pk2 = (Poker*)_Left->_arrayPoker->getObjectAtIndex(j + 1);
			//大的在前 小的在后
			if (pk1->getNum()<pk2->getNum())
				_Left->_arrayPoker->exchangeObjectAtIndex(j, j + 1);
			}
		//对Right的牌排序
		for (int i = 0; i < 17; ++i)
			for (int j = 0; j < 16 - i; ++j)
			{
			Poker *pk1 = (Poker*)_Right->_arrayPoker->getObjectAtIndex(j);
			Poker*pk2 = (Poker*)_Right->_arrayPoker->getObjectAtIndex(j + 1);
			//大的在前 小的在后
			if (pk1->getNum()<pk2->getNum())
				_Right->_arrayPoker->exchangeObjectAtIndex(j, j + 1);
			}

		//对三张牌排序
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 2 - i; ++j)
			{
			Poker *pk1 = (Poker*)_threePoker->getObjectAtIndex(j);
			Poker*pk2 = (Poker*)_threePoker->getObjectAtIndex(j + 1);
			//大的在前 小的在后
			if (pk1->getNum()<pk2->getNum())
				_threePoker->exchangeObjectAtIndex(j, j + 1);
			}

		

		SimpleAudioEngine::getInstance()->playEffect("Sound/Special_Dispatch.mp3");
		this->schedule(schedule_selector(GamePlay::DealPoker), 0.20f);

		//_Self->_arrayPoker->removeObjectAtIndex(0);
		/*Poker*t = (Poker*)_Self->_arrayPoker->getObjectAtIndex(0);
		_Self->_arrayPoker->removeObjectAtIndex(0);
		_Left->_arrayPoker->addObject(t);*/

	
		isRet = true;
	} while (0);

	return isRet;
}

void GamePlay::DealPoker(float dt)
{
	//发牌
	if (dealSign < _Self->_arrayPoker->count())
	{
		int middle = visibleMiddleX + 55;
		//////////////////self更新牌位置
		Poker *pk = (Poker*)(_Self->_arrayPoker->getObjectAtIndex(dealSign));
		if (dealSign == 0)
		{
			pk->setPosition(middle, visibleMiddleY2);
			
		}
		else
		{
			pk->setPosition(((Poker*)(_Self->_arrayPoker->getObjectAtIndex(dealSign - 1)))->getPosition().x + CardGap, visibleMiddleY2);
			int move = CardGap / 2; //(dealSign + 1);
			for (int i = 0; i <= dealSign; ++i)
			{
				Poker *temp = ((Poker*)(_Self->_arrayPoker->getObjectAtIndex(i)));
				temp->setPosition(temp->getPosition().x - move, temp->getPosition().y);
			}

		}
		this->addChild(pk);

		/////////////////left
		//Point move
		Poker *pk1 = (Poker*)(_Left->_arrayPoker->getObjectAtIndex(dealSign));
		if (dealSign == 0)
		{
			pk1->setPosition(360,560);//LeftMiddle

		}
		else
		{
			pk1->setPosition(((Poker*)(_Left->_arrayPoker->getObjectAtIndex(dealSign - 1)))->getPosition()-Point(22,25));//Point(4.4,5)
			Point move1 = Point(-2.2f,-2.5f); //(dealSign + 1);
			for (int i = 0; i <= dealSign; ++i)
			{
				Poker *temp = ((Poker*)(_Left->_arrayPoker->getObjectAtIndex(i)));
				temp->setPosition(temp->getPosition()-move1);
			}
		}
		this->addChild(pk1);
		/////////////////right
		Poker *pk2 = (Poker*)(_Right->_arrayPoker->getObjectAtIndex(dealSign));
		if (dealSign == 0)
		{
			pk2->setPosition(600,560);//RightMiddle

		}
		else
		{
			pk2->setPosition(((Poker*)(_Right->_arrayPoker->getObjectAtIndex(dealSign - 1)))->getPosition() - Point(-22,25));//Point(-4.4,5)
			Point move2 = Point(2.2f, -2.5f); //(dealSign + 1);
			for (int i = 0; i <= dealSign; ++i)
			{
				Poker *temp = ((Poker*)(_Right->_arrayPoker->getObjectAtIndex(i)));
				temp->setPosition(temp->getPosition() - move2);
			}
		}
		this->addChild(pk2);


		++dealSign;
	}
	//发完牌
	else
	{
		/*_Self->_arrayPoker->removeObjectAtIndex(0);
		Poker*t = (Poker*)_Self->_arrayPoker->getObjectAtIndex(0);
		t->setPosition(600, 600);*/
		/*((Poker*)(_Left->_arrayPoker->getLastObject()))->setPosition(600, 600);
		this->addChild(((Poker*)(_Left->_arrayPoker->getLastObject())));*/

		_state = CallLord;
		this->unschedule(schedule_selector(GamePlay::DealPoker));
		if (_WhoFirstCall == Self)
			this->schedule(schedule_selector(GamePlay::SelfUpdate), 1.0f);
		else if (_WhoFirstCall == Left)
			this->schedule(schedule_selector(GamePlay::LeftUpdate), 1.0f);
		else if (_WhoFirstCall == Right)
			this->schedule(schedule_selector(GamePlay::RightUpdate), 1.0f);
	}
}

/////////////////////////////////////更新
void GamePlay::SelfUpdate(float dt)
{
	//叫抢地主阶段
	if (_state == CallLord)
		SelfCallLord();
	//确认地主
	else if (_state == DetermineLord)
		SelfDetermineLord();
	//加倍
	else if (_state == Jiabei)
		SelfJiabei();
	//打牌阶段
	else if (_state == PlayPoker)
	{
		SelfPlayPoker();
	}
}

void GamePlay::RightUpdate(float dt)
{
    //叫抢地主阶段
	if (_state == CallLord)
		RightCallLord();
	//确认地主
	else if (_state == DetermineLord)
		RightDetermineLord();
	//加倍
	else if (_state == Jiabei)
		RightJiabei();
	//打牌阶段
	else if (_state == PlayPoker)
	{
		RightPlayPoker();
	}
}

void GamePlay::LeftUpdate(float dt)
{

     //叫抢地主阶段
	if (_state == CallLord)
		LeftCallLord();
	//确认地主
	else if (_state == DetermineLord)
		LeftDetermineLord();
	//加倍
	else if (_state == Jiabei)
		LeftJiabei(); 
	//打牌阶段
	else if (_state == PlayPoker)
	{
		LeftPlayPoker();
	}
}

///////////////////////////////////////
void GamePlay::changeToDetermineLord()
{
	if (this->_askTimes == 3)
	{
		_state = DetermineLord;
		this->unschedule(schedule_selector(GamePlay::SelfUpdate));
		this->unschedule(schedule_selector(GamePlay::RightUpdate));
		this->unschedule(schedule_selector(GamePlay::LeftUpdate));
		////////////////////只有一个人叫
		if (_lastRob == _firstCall)
		{
			if (_lastRob != Null)
			{
				_Lord = _lastRob;
				this->scheduleOnce(schedule_selector(GamePlay::changeToJiabei), 1.0f);
			}
			else
				Restart();
		}
		////////////////////不止一个人叫
		else
		{
			if (_firstCall == Self){
				_robMenu->setVisible(true);
				_Self->clearSomeImage();
				//显示倒计时
				_Self->_clockLord->setVisible(true);
						this->schedule(schedule_selector(GamePlay::SelfUpdate), 1.0f);
			
			}
			//
			else if (_firstCall == Right){
				_Right->clearSomeImage();
						scheduleOnce(schedule_selector(GamePlay::RightUpdate), 1.0f);
			
			}
			//
			else if (_firstCall == Left){
				_Left->clearSomeImage();
						scheduleOnce(schedule_selector(GamePlay::LeftUpdate), 1.0f);
				
			}
		}
		//
		
		//_state = Jiabei;
		this->clearImagesOfCallLord();
	}
}
void GamePlay::changeToJiabei(float dt)
{
	this->unschedule(schedule_selector(GamePlay::SelfUpdate));
	_Self->clearSomeImage();
	_Right->clearSomeImage();
	_Left->clearSomeImage();
	_Self->_clockLord->clear();
	_callMenu->setVisible(false);
	_robMenu->setVisible(false);
	_state = Jiabei;

	if (_Lord == Self)
	{
		_Self->updateThreePoker(_threePokerSave); 
		for (int i = 0; i < 3; ++i)
		{
			Poker* pk = (Poker*)_threePokerSave->getObjectAtIndex(i);
			pk->setPosition(pk->getPosition() + Point(0, 20));
			this->addChild(pk);
		}
		this->scheduleOnce(schedule_selector(GamePlay::delayDealThree), 0.7f);
	}
	else if (_Lord == Right){
		_Right->updateThreePoker(_threePokerSave);
		for (int i = 0; i < 3; ++i)
		{
			Poker* pk = (Poker*)_threePokerSave->getObjectAtIndex(i);
			this->addChild(pk);
		}
	}
	else if (_Lord == Left){
		_Left->updateThreePoker(_threePokerSave);
		for (int i = 0; i < 3; ++i)
		{
			Poker* pk = (Poker*)_threePokerSave->getObjectAtIndex(i);
			this->addChild(pk);
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		Poker* pk = (Poker*)_threePoker->getObjectAtIndex(i);
		if (i == 0)
			pk->setPosition(450, 600);
		else
		{
			Poker* pk1 = (Poker*)_threePoker->getObjectAtIndex(i-1);
			pk->setPosition(pk1->getPosition() + Point(20, 0));
		}
		this->addChild(pk);
	}

	if (_Lord == Self)
	{
		_Self->_isLord = true;
	}
	else if (_Lord == Right)
	{
		_Right->_isLord = true;
	}
	else if (_Lord == Left)
	{
		_Left->_isLord = true;
	}

	this->schedule(schedule_selector(GamePlay::changeToLordAndFarmer), 0.12f);

	this->schedule(schedule_selector(GamePlay::SelfUpdate), 1.0f);
	this->scheduleOnce(schedule_selector(GamePlay::RightUpdate), 1.0f);
	this->scheduleOnce(schedule_selector(GamePlay::LeftUpdate), 1.0f);

	

}
void GamePlay::changeToPlayPoker(float dt)
{
	_state = PlayPoker;
	_Self->clearSomeImage();
	_Right->clearSomeImage();
	_Left->clearSomeImage();
	if (_Lord == Self)
		this->schedule(schedule_selector(GamePlay::SelfUpdate), 1.0f);
	else if (_Lord == Right)
		this->scheduleOnce(schedule_selector(GamePlay::RightUpdate), 1.0f);
	else if (_Lord == Left)
		this->scheduleOnce(schedule_selector(GamePlay::LeftUpdate), 1.0f);

}

///////////////////////////////////////
void GamePlay::SelfCallLord()
{
	_Self->clearSomeImage();
	//显示菜单
	if (_lordTimes == 0)
		_callMenu->setVisible(true);
	else
		_robMenu->setVisible(true);

	this->changeToDetermineLord();
	//显示倒计时
	_Self->_clockLord->setVisible(true);
	if (!_Self->_clockLord->decrease())//倒计时结束
	{
		++this->_askTimes;
		if (_lordTimes == 0)
			_Self->_imageNotCall->setVisible(true);
		else
			_Self->_imageNotRob->setVisible(true);

		_callMenu->setVisible(false);
		this->schedule(schedule_selector(GamePlay::RightUpdate), 1.0f);
		this->unschedule(schedule_selector(GamePlay::SelfUpdate));

	}
}
void GamePlay::SelfDetermineLord()
{
	if (!_Self->_clockLord->decrease())//倒计时结束
	{
		aboutLastRob();
		_robMenu->setVisible(false);
		_Self->_imageNotRob->setVisible(true);
		this->scheduleOnce(schedule_selector(GamePlay::changeToJiabei), 1.0f);
	}
}
void GamePlay::SelfJiabei()
{
	_jiabeiMenu->setVisible(true);
	_Self->_clockJiabei->setVisible(true);
	if (!_Self->_clockJiabei->decrease())
	{
		_Self->_imageNotJiabei->setVisible(true);
		_jiabeiMenu->setVisible(false);
		this->unschedule(schedule_selector(GamePlay::SelfUpdate));
		this->scheduleOnce(schedule_selector(GamePlay::changeToPlayPoker), 1.5f);
	}

}
void GamePlay::SelfPlayPoker()
{
	//清除上回合的残留
	_Self->clearSomeImage();
	_Self->clearOutPoker();
	_Self->clearArray();
	//显示
	_Self->_clockPlay->setVisible(true);
	//第一次出牌 或别人不要
	if (ifFirstOut || _lastOutPlayer == Self)
	{
		_follow1->setEnabled(false);
		_playMenuFirst->setVisible(true);
		////////////倒计时结束
		if (!_Self->_clockPlay->decrease())
		{		
			ifFirstOut = false;
			/////////////出最小的
			{
				Poker* temp = (Poker*)_Self->_arrayPoker->getObjectAtIndex(0);
				_Self->_arraySelectPoker->addObject(temp);
			}
			_Self->_clockPlay->setVisible(false);
			_playMenuFirst->setVisible(false);
			this->unschedule(schedule_selector(GamePlay::SelfUpdate));
			this->scheduleOnce(schedule_selector(GamePlay::RightUpdate),1.0f);
		}
	    ////////////出牌
		if (judgeSelfSelectPoker())
		{
			_follow1->setEnabled(true);
		}
		else{
			_follow1->setEnabled(false);
		}

	}
	else
	{
		_follow->setEnabled(false);
		_playMenu->setVisible(true);
		////////////倒计时结束
		if (!_Self->_clockPlay->decrease()){
			_Self->_imageNotFollow->setVisible(true);
			_Self->_clockPlay->setVisible(false);
			_playMenu->setVisible(false);

			this->unschedule(schedule_selector(GamePlay::SelfUpdate));
			this->scheduleOnce(schedule_selector(GamePlay::RightUpdate), 1.0f);
 		}
		////////////出牌
		if (judgeSelfSelectPoker())
		{
			_follow1->setEnabled(true);
		}
		else{
			_follow1->setEnabled(false);
		}
	}
}

void GamePlay::RightCallLord()
{
	_Right->clearSomeImage();
	++this->_askTimes;

	//判断是否叫地主
	if (_Right->isLord(this->_lordTimes))
	{
		if (_lordTimes == 0)//自己先叫
		{
			_firstCall = Right;
			_Right->_imageCall->setVisible(true);

		}
		else//自己抢
		{
			_Right->_imageRob->setVisible(true);
			_multiple *= 2;
			changeMultiple();
		}

		_Right->_ifWantToBeLord = true;
		++this->_lordTimes;
		_lastRob = Right;
	}
	else
	{
		if (_lordTimes == 0)
			_Right->_imageNotCall->setVisible(true);
		else
			_Right->_imageNotRob->setVisible(true);
	}
	this->schedule(schedule_selector(GamePlay::LeftUpdate), 1.0f);
	this->unschedule(schedule_selector(GamePlay::RightUpdate));

	this->changeToDetermineLord();
}
void GamePlay::RightDetermineLord()
{
	_Right->clearSomeImage();
	if (_Right->isLord(this->_lordTimes))
	{
		_Right->clearSomeImage();
		_Lord = Right;
		_Right->_imageRob->setVisible(true);
		_multiple *= 2;
		changeMultiple();
	}
	else
	{
		aboutLastRob();
		_Right->_imageNotRob->setVisible(true);
	}

	this->scheduleOnce(schedule_selector(GamePlay::changeToJiabei), 1.0f);
}
void GamePlay::RightJiabei()
{
	if (_Right->isLord(_lordTimes))
	{
		_multiple *= 2;
		_Right->_imageJiabei->setVisible(true);
		changeMultiple();
	}
	else{
		_Right->_imageNotJiabei->setVisible(true);
	}
    
}
void GamePlay::RightPlayPoker()
{
	_Right->clearSomeImage();
	if (ifFirstOut || _lastOutPlayer == Right){
		ifFirstOut = false;
		///////////////////////随便出
		{

		}
		this->scheduleOnce(schedule_selector(GamePlay::LeftUpdate), 1.0f);
		
	}
	else{//是否打上家
		//if (1)//出牌
		{
			////////////////更新牌位置
			{

			}
			_Right->displayPokerNum();
			/////////////////显示打出的牌
			{

			}
			if (ifPokerOver())
				Restart();
			else
			{
				_lastOutPlayer = Right;
				determinePlayerType();
				/////////////////更新_lastoutpoker
				{

				}
				this->scheduleOnce(schedule_selector(GamePlay::LeftUpdate), 1.0f);
			}
			
		}
		//else//不出
		{
			_Right->_imageNotFollow->setVisible(true);

			this->scheduleOnce(schedule_selector(GamePlay::LeftUpdate), 1.0f);
		}
			

	}
}

void GamePlay::LeftCallLord()
{
	++this->_askTimes;

	//判断是否叫地主
	if (_Left->isLord(this->_lordTimes))
	{
		if (_lordTimes == 0)//自己先叫
		{
			_firstCall = Left;
			_Left->_imageCall->setVisible(true);
		}
		else//自己抢
		{
			_Left->_imageRob->setVisible(true);
			_multiple *= 2;
			changeMultiple();
		}

		_Left->_ifWantToBeLord = true;
		++this->_lordTimes;
		_lastRob = Left;
	}
	else
	{
		if (_lordTimes == 0)
			_Left->_imageNotCall->setVisible(true);
		else
			_Left->_imageNotRob->setVisible(true);
	}

	this->schedule(schedule_selector(GamePlay::SelfUpdate), 1.0f);
	this->unschedule(schedule_selector(GamePlay::LeftUpdate));

	this->changeToDetermineLord();
}
void GamePlay::LeftDetermineLord()
{
	_Left->clearSomeImage();
	if (_Left->isLord(this->_lordTimes))
	{
		_Lord = Left;
		_Left->_imageRob->setVisible(true);
		_multiple *= 2;
		changeMultiple();
	}
	else
	{
		aboutLastRob();
		_Left->_imageNotRob->setVisible(true);
	}

	this->scheduleOnce(schedule_selector(GamePlay::changeToJiabei), 1.0f);
}
void GamePlay::LeftJiabei()
{
	if (_Left->isLord(_lordTimes))
	{
		_multiple *= 2;
		_Left->_imageJiabei->setVisible(true);
		changeMultiple();
	}
	else
	{
		_Left->_imageNotJiabei->setVisible(true);
	}
}
void GamePlay::LeftPlayPoker()
{
	_Left ->clearSomeImage();
	if (ifFirstOut || _lastOutPlayer == Left){
		ifFirstOut = false;
		///////////////////////随便出
		{

		}
		this->schedule(schedule_selector(GamePlay::SelfUpdate), 1.0f);

	}
	else{//是否打上家
		//if (1)//出牌
			{
				////////////////更新牌位置
				{

				}
				_Left->displayPokerNum();
				/////////////////显示打出的牌
				{

				}
				if (ifPokerOver())
					Restart();
				else
				{
					_lastOutPlayer = Left;
					determinePlayerType();
					/////////////////更新_lastoutpoker
					{

					}
					this->schedule(schedule_selector(GamePlay::SelfUpdate), 1.0f);
				}

			}
		//else//不出
		{
			_Left->_imageNotFollow->setVisible(true);

			this->schedule(schedule_selector(GamePlay::SelfUpdate), 1.0f);
		}


	}
}


//////////////////////////////////////菜单回调函数
//设置
void GamePlay::menuSettingCallback(cocos2d::Ref *sender)
{}
//托管
void GamePlay::menuAutoCallback(cocos2d::Ref *sender)
{}
//聊天
void GamePlay::menuChatCallback(cocos2d::Ref *sender)
{}
//叫地主
void GamePlay::menuCallLordCallback(cocos2d::Ref *sender)
{
	if (_state == CallLord)
	{   
		if (_lordTimes == 0)
			_firstCall = Self;
		++_lordTimes;
		++this->_askTimes;
		_lastRob = Self;
		_Self->_ifWantToBeLord = true; 
		//
		_Self->_clockLord->clear();
		_Self->clearSomeImage();
		_Self->_imageCall->setVisible(true);
		_callMenu->setVisible(false);

		this->schedule(schedule_selector(GamePlay::RightUpdate), 1.0f);
		this->unschedule(schedule_selector(GamePlay::SelfUpdate));
	}
	
}
//不叫
void GamePlay::menuNotCallLordCallback(cocos2d::Ref *sender)
{
	if (_state == CallLord)
	{
		++this->_askTimes;

		_Self->_clockLord->clear();
		_Self->clearSomeImage();
		_Self->_imageNotCall->setVisible(true);
		_callMenu->setVisible(false);

		this->schedule(schedule_selector(GamePlay::RightUpdate), 1.0f);
		this->unschedule(schedule_selector(GamePlay::SelfUpdate));
	}
	
}
//抢
void GamePlay::menuRobLordCallback(cocos2d::Ref *sender)
{
	if (_state == CallLord)
	{
		++_lordTimes;
		++this->_askTimes;
		_lastRob = Self;
		_Self->_ifWantToBeLord = true;


		this->scheduleOnce(schedule_selector(GamePlay::RightUpdate), 1.0f);
		this->unschedule(schedule_selector(GamePlay::SelfUpdate));
		this->changeToDetermineLord();
	}
	else if (_state == DetermineLord)
	{
		_Lord = Self;
		this->scheduleOnce(schedule_selector(GamePlay::changeToJiabei), 1.0f);
	}
	_multiple *= 2;
	changeMultiple();
	_Self->clearSomeImage();
	_Self->_imageRob->setVisible(true);
	_Self->_clockLord->clear();
	_robMenu->setVisible(false);
}
//不抢
void GamePlay::menuNotRobLordCallback(cocos2d::Ref *sender)
{
	if (_state == CallLord)
	{
		++this->_askTimes;

		this->scheduleOnce(schedule_selector(GamePlay::RightUpdate), 1.0f);
		this->unschedule(schedule_selector(GamePlay::SelfUpdate));
		this->changeToDetermineLord();
	}
	else if (_state == DetermineLord)
	{
		aboutLastRob();
		/*if (_Left->_ifWantToBeLord)
			_Lord = Left;
		else if (_Right->_ifWantToBeLord)
			_Lord = Right;*/

		this->scheduleOnce(schedule_selector(GamePlay::changeToJiabei), 1.0f);
	}
	_Self->clearSomeImage();
	_Self->_imageNotRob->setVisible(true);
	_Self->_clockLord->clear();
	_robMenu->setVisible(false);
}
//加倍
void GamePlay::menuJiabeiLordCallback(cocos2d::Ref *sender)
{
	_multiple *= 2;
	_Self->_imageJiabei->setVisible(true);
	_Self->_clockJiabei->clear();
	changeMultiple();
	_jiabeiMenu->setVisible(false);
	this->unschedule(schedule_selector(GamePlay::SelfUpdate));
	this->scheduleOnce(schedule_selector(GamePlay::changeToPlayPoker), 1.5f);
}
//不加倍
void GamePlay::menuNotJiabeiLordCallback(cocos2d::Ref *sender)
{
	_Self->_imageNotJiabei->setVisible(true);
	_Self->_clockJiabei->clear();
	_jiabeiMenu->setVisible(false);
	this->unschedule(schedule_selector(GamePlay::SelfUpdate));
	this->scheduleOnce(schedule_selector(GamePlay::changeToPlayPoker), 1.5f);
}
//出牌
void GamePlay::menuFollowCallback(cocos2d::Ref *sender)
{
	_playMenu->setVisible(false);
	_playMenuFirst->setVisible(false);
	_Self->_clockPlay->clear();
	//////////////////////显示出的牌
	{
		_Self->displayOutPoker();
	}
	//////////////////////更新牌位置
	{
		_Self->updatePoker();
	}
	if (ifPokerOver()){
		Restart();
	}
	else{
		_lastOutPlayer = Self;
		determinePlayerType();
		///////////////////////更新lastoutarr
		{
			_arrayLastOutPoker->removeAllObjects();
			_arrayLastOutPoker->addObjectsFromArray(_Self->_arrayOutPoker);
		}

		this->unschedule(schedule_selector(GamePlay::SelfUpdate));
		this->scheduleOnce(schedule_selector(GamePlay::RightUpdate), 1.0f);
	}
}
//不出
void GamePlay::menuNotFollowCallback(cocos2d::Ref *sender)
{
	_Self->_imageNotFollow->setVisible(true);
	_Self->_clockPlay->clear();
	_playMenu->setVisible(false);
	_playMenuFirst->setVisible(false);

	this->unschedule(schedule_selector(GamePlay::SelfUpdate));
	this->scheduleOnce(schedule_selector(GamePlay::RightUpdate), 1.0f);
}
//提示
void GamePlay::menuTipCallback(cocos2d::Ref *sender)
{}



///////////////////////////////////////////
void GamePlay::aboutLastRob()
{
	if (_lastRob == Null)
		Restart();
	else
		_Lord = _lastRob;
}
void GamePlay::clearImagesOfCallLord()
{

}
void GamePlay::changeMultiple()
{
	__String *t = String::createWithFormat("%d", this->_multiple);
	_multipleLabel->setString(t->getCString());
}
void GamePlay::delayDealThree(float dt)
{
	for (int i = 0; i < 3; ++i)
	{
		Poker* pk = (Poker*)_threePokerSave->getObjectAtIndex(i);
		pk->setPosition(pk->getPosition() - Point(0, 20));
		//this->addChild(pk);
	}
}
void GamePlay::changeToLordAndFarmer(float dt)
{
	_Self->changeToImagePlay();
	_Right->changeToImagePlay();
	_Left->changeToImagePlay();
	_Right->displayPokerNum();
	_Left->displayPokerNum();
	if (_Self->_cloudNum >= 9)
		this->unschedule(schedule_selector(GamePlay::changeToLordAndFarmer));

}

bool GamePlay::judgeSelfSelectPoker()
{
	for (int i = 0; i < _Self->_arrayPoker->count(); ++i)
	{
		Poker* pk = (Poker*)_Self->_arrayPoker->getObjectAtIndex(i);
		if (pk->getSelect())
			_Self->_arraySelectPoker->addObject(pk); 
	}
	if (judgeOutPoker(_Self->_arraySelectPoker, _arrayLastOutPoker))
		return true;
	
	return false;
}

void GamePlay::determinePlayerType()
{
	if (_Lord == Self)
		_lastOutPlayerType = Lord;
	else if (_Lord == Right)
		_lastOutPlayerType = Farmer;
	else if (_Lord == Left)
		_lastOutPlayerType = Farmer;
}
bool GamePlay::ifPokerOver()
{
	if (_Self->_arrayPoker->count() == 0 || _Right->_arrayPoker->count() == 0 || _Left->_arrayPoker->count() == 0)
		return true;

	return false;
}

///////////////////////////////////////重新开始 
void GamePlay::Restart()
{
	_Lord = Null;
	_multiple = 1;
	_lordTimes = 0;
	_askTimes = 0;
	_WhoFirstCall = Null;
	_firstCall = Null;
	_lastRob = Null;
	dealSign = 0;

	CCObject* object;
	CCARRAY_FOREACH(_arrayAllPoker, object){
		Poker* pk = (Poker*)object;
		pk->setCardType(Null);
		pk->setSelect(false);
		//pk->setClick(false);
		pk->setVisible(false);
	}

	_threePoker->removeAllObjects();
	_threePokerSave->removeAllObjects();

	_Self->Restart((Scene*)this);
	_Right->Restart((Scene*)this);
	_Left->Restart((Scene*)this);

	this->ShufflePoker();
	
}
