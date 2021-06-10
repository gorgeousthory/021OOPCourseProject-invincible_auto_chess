/********************************************
 * ���ܣ�������Ϸ����
 * ���ߣ�Gorgeous, VenusHui
 * �汾��1.1.0.beta
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵���������������
 ********************************************/
#pragma once
#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include <cocos2d.h>
USING_NS_CC;

#include <LoginScene.h>
#include <ConfigController.h>

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

private:
	void menuExitCallBack(Ref* sender);

};

#endif