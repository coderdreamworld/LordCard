#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include "cocos2d.h"

class Login : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Login);

	static bool getSex();

private:
	void menuCloseCallback(cocos2d::Ref* pSender);
	static bool _Sex;
};

#endif // __HELLOWORLD_SCENE_H__