/********************************************
 * ���ܣ�������Ϸ����
 * ���ߣ�Gorgeous
 * �汾��1.0.1
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵����
 ********************************************/
#pragma once
#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include <cocos2d.h>
USING_NS_CC;

class PlayScene : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(PlayScene);

private:

};

#endif