/********************************************
 * ���ܣ�������Ϸ����
 * ���ߣ�Gorgeous
 * �汾��1.0.1
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵����
 ********************************************/
#pragma once
#ifndef _LOGINSCENE_H_
#define _LOGINSCENE_H_

#include <cocos2d.h>
USING_NS_CC;

class LoginScene : public Scene
{
public:
	static Scene* createScene();
	
	virtual bool init();

	CREATE_FUNC(LoginScene);

private:
	
};

#endif