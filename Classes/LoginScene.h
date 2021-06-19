/********************************************
 * ���ܣ�������Ϸ���棬������Դ����
 * ���ߣ�VenusHui
 * �汾��2.0.0
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵����������״̬�������LoginScene�����й���
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
#include "audio/include/AudioEngine.h"//��������

#include <list>
#include <string>
#include <Windows.h>
using namespace std;

#include "ConfigController.h"
#include "PlayScene.h"

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
	static MenuItemSprite* createGameButton(string name, string normalPicPath, string pressedPicPath, const ccMenuCallback& callback);

private:
	ProgressTimer* loadingBar; // ��Դ���ؽ�����

	ProgressFromTo* barAction; // ��������Ϊ

	unsigned int resCount; // ��ǰ���ص���Դ����

	unsigned int resTotal; // ��Ҫ���ص���Դ����

	list<string> dataPathList; // ��Ҫ���ص���Դ·����

	unsigned int _audioBgID;	//�������ֱ��

	// ��ʼ��ť�ĵ���¼�
	void menuStartCallBack(Ref* sender);

	// �˳���ť�ĵ���¼�
	void menuExitCallBack(Ref* sender);

	//	������ť�ĵ���¼�
	void menuMusicCallBack(Ref* sender);
};

#endif