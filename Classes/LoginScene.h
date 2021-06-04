/********************************************
 * ���ܣ�������Ϸ���棬������Դ����
 * ���ߣ�VenusHui
 * �汾��1.1.0
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵����
 ********************************************/
#pragma once
#ifndef _LOGINSCENE_H_
#define _LOGINSCENE_H_

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

#include "PlayScene.h"

#define HORIZONTAL_PIXEL_NUM 160
#define VERTICAL_PIXEL_NUM 90

class LoginScene : public Scene
{
public:
	static Scene* createScene();
	
	virtual bool init();

	// ��ȡ������Ҫ������Դ�ļ����µ������ļ�
	list<string> getFileFromPath(string path);

	// ��Դ����
	void loadResources();

	CREATE_FUNC(LoginScene);

	// ����һ��ͨ�ð�ť
	MenuItemSprite* createGameButton(string name, string normalPicPath, string pressedPicPath, const ccMenuCallback& callback);

private:
	unsigned int resCount; // ��ǰ���ص���Դ����

	unsigned int resTotal; // ��Ҫ���ص���Դ����

	list<string> dataPathList; // ��Ҫ���ص���Դ·����

	// ��ʼ��ť�ĵ���¼�
	void menuStartCallBack(Ref* sender);
};

#endif