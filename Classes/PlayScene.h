/********************************************
 * ���ܣ�������Ϸ����
 * ���ߣ�Gorgeous, VenusHui,����Դ
 * �汾��1.1.0.beta
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵������ԭ�еĻ����������һ����ʱ�����������һ����ť
 ********************************************/
#pragma once
#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include <cocos2d.h>
USING_NS_CC;

#include <LoginScene.h>
#include <ConfigController.h>
#include"Clock.h"

class PlayScene : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	// �������ӻ�����
	Vector<Sprite*> createChessBoard();

	// �������ӻ����ӿ�Ƭ
	MenuItemSprite* createPieceCard(string pieceName, string piecePicPath, const ccMenuCallback& callback);

	CREATE_FUNC(PlayScene);

	//����update����
	void update(float dt);

private:
	ProgressTimer* loadingBar; // ��Դ���ؽ�����

	ProgressFromTo* barAction; // ��������Ϊ

	void menuExitCallBack(Ref* sender);

	float remainingTime = 61.0f;

	float pastTime = 0;

	Label* timeLabel = Label::createWithSystemFont("Time:60", "Arial", 60);

};

#endif