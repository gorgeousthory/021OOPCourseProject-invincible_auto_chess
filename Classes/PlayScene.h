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

#include <vector>

#include <LoginScene.h>
#include <ConfigController.h>
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Csv.h"

#define ROW_BOARD			10
#define COL_BOARD			10

#define NOT_IN_BOARD		0
#define IN_WAR_ZONE			1
#define IN_READY_ZONE		2

class PlayScene : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	// �������ӻ�����
	void createBoard(Vec2 position);

	// �������ӻ����ӿ�Ƭ
	MenuItemSprite* createPieceCard(string pieceName, string piecePicPath, Vec2 position, const ccMenuCallback& callback);

	// ����ת������
	static PieceCoordinate* coordingrevert(Vec2 realPosition);

	CREATE_FUNC(PlayScene);

private:
	// ������
	Layer* playLayer;

	// ����
	vector<Sprite*> chessBoard[ROW_BOARD];

	// �˳���ť�ĵ���¼�
	void menuExitCallBack(Ref* sender);

	//���»ص�
	virtual int onTouchBegan(Touch* touch, Event* event);

	//�ͷŻص�
	virtual void onTouchEnded(Touch* touch, Event* event);

	// �ƶ��ص�
	void onMouseMove(Event* event);

};

#endif