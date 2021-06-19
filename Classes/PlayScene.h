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

#include "ui/CocosGUI.h" 
using namespace ui;

#include <vector>
using std::vector;

#include "LoginScene.h"
#include "ConfigController.h"
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Csv.h"
#include "Shop.h"
#include "Player.h"

#define ROW_BOARD			10
#define COL_BOARD			10

// ����¼���غ�
#define NOT_IN_BOARD		100
#define IN_WAR_ZONE			1
#define IN_READY_ZONE		2
#define READY_TO_WAR		3
#define WAR_TO_WAR			4
#define READY_TO_READY		5
#define WAR_TO_READY		6
#define NO_LIFT_CLICK_WAR	10
#define NO_LIFT_CLICK_READY 11

class PlayScene : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	// �������ӻ����̣� positionΪ(0, 0)λ����ƭͼƬ���½ǵ�ê������
	void createBoard(Vec2 position);

	// �������ӻ��̵꣬positionΪ��һ�ſ�Ƭ���½ǵ�ê������
	void createShop(Vec2 position);

	// �������ӻ����ӿ�Ƭ
	MenuItemSprite* createPieceCard(string pieceName, string piecePicPath, Vec2 position, const ccMenuCallback& callback);

	//���ӵĿ��ӻ�
	Sprite* createChessPiece(string pieceName, string piecePicPath, Vec2 position, int type = 1);

	// ����ת������
	static PieceCoordinate coordingRevert(CoordinateType originType, Vec2 originPosition);

	//���º���
	void update(float dt);

	CREATE_FUNC(PlayScene);

private:
	// ������
	Layer* playLayer;
	Menu* menu;

	// ��ǰ���״̬
	Sprite* mouseLiftPiece;

	// ����
	ChessBoard* chessBoardModel;
	vector<Sprite*> chessBoard[ROW_BOARD];
	vector<Sprite*> pieceBoard[ROW_BOARD];

	// �̵�
	Shop* shopModel;
	vector<MenuItemSprite*> shop;

	// ���
	Player* playerA;

	//��ʱ��
	float timeRemaining = 61.0f;
	Label* timeLabel = Label::createWithSystemFont("Time:60", "Arial", 60);

	// ��Դ���ؽ�����
	ProgressTimer* loadingBar;

	// ��������Ϊ
	ProgressFromTo* barAction;

	// �˳���ť�ĵ���¼�
	void menuExitCallBack(Ref* sender);

	// ����Ƭ�ĵ���¼�
	void menuPieceCardCallBack1(Ref* sender);
	void menuPieceCardCallBack2(Ref* sender);
	void menuPieceCardCallBack3(Ref* sender);
	void menuPieceCardCallBack4(Ref* sender);
	void menuPieceCardCallBack5(Ref* sender);
	void buyCard(const unsigned int num, ChessPiece* piece);

	// ˢ���̵�ĵ���¼�
	void menuFreshShopCallBack(Ref* sender);

	// ������ĵ���¼�
	void menuBuyExpCallBack(Ref* sender);

	//���»ص�
	virtual int onTouchBegan(Touch* touch, Event* event);

	//�ͷŻص�
	virtual void onTouchEnded(Touch* touch, Event* event);

	// �ƶ��ص�
	void onMouseMove(Event* event);

};

#endif