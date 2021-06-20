/********************************************
 * ���ܣ����м�ʱ
 * ���ߣ�����Դ
 * �汾��1.0.0
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵����
 ********************************************/
#pragma once

#ifndef _CLOCK_H
#define _CLOCK_H

#include <sys/stat.h>
#include <io.h>
#include <process.h>

 // Linux�е�C++�⣬Win32�汾�ο�https://github.com/tronkko/dirent  Copyright (C) 1998-2019 Toni Ronkko
#include "dirent.h" 

#include "cocos2d.h"
USING_NS_CC;

#include "ui/CocosGUI.h" 
using namespace ui;

#include <list>
#include <string>
using namespace std;


class Clock :public	Layer
{
public:

	static Layer* createLayer();
	//init����
	virtual bool init();

	void update(float dt);

private:

	Label* timeLabel = Label::createWithSystemFont("Time:60", "Arial", 60);

	float remainingTime = 61.0f;

	Vec2 position;
};
#endif
