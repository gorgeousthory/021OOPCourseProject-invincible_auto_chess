/********************************************
<<<<<<< Updated upstream
 * ���ܣ�������Ϸ����
=======
 * ���ܣ�������Ϸ���棬������Դ����
>>>>>>> Stashed changes
 * ���ߣ�VenusHui
 * �汾��1.0.0
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
#include "dirent.h"

#include "cocos2d.h"
USING_NS_CC;

#include "ui/CocosGUI.h" 
using namespace ui;

#include <list>
#include <string>
using namespace std;

#include <PlayScene.h>

class LoginScene : public Scene
{
public:
	static Scene* createScene();
	
	virtual bool init();

	// ��ȡ������Ҫ������Դ��·��
	list<string> getFileFromPath(string path);

	// ��Դ����
	void loadResources();

	// ������ɺ�Ļص�����
	void LoginScene::loadCallback(Ref* psender);

	CREATE_FUNC(LoginScene);

private:
	unsigned int resCount; // ��ǰ���ص���Դ����

	unsigned int resTotal; // ��Ҫ���ص���Դ����

	list<string> dataPathList; // ��Ҫ���ص���Դ·����
};

#endif