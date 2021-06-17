/********************************************
 * ���ܣ�����ģ��
 * ���ߣ�VenusHui
 * �汾��1.0.3
 * λ�ã�Classes/model(ɸѡ��)
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵����
 ********************************************/
#pragma once
#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_

#include <vector>
using std::vector;

#include "ChessPiece.h"
#include "ConfigController.h"

class ChessBoard :public Ref
{
public:
	virtual bool init();

	static ChessBoard* getInstance();

	static void destroyInstance();

	~ChessBoard();

	// ����ʵ�������ľ���
	static double getDistance(PieceCoordinate* start, PieceCoordinate* end);

	// ��ȡ���A��ս�����Ӽ���
	vector<ChessPiece*>* getPlayerA_WarZone_Pieces();

	// ��ȡ���A��ս�����Ӽ���
	vector<ChessPiece*>* getPlayerA_PreZone_Pieces();

	// ��ȡ���B��ս�����Ӽ���
	vector<ChessPiece*>* getPlayerB_WarZone_Pieces();

	// ��ȡ���B��ս�����Ӽ���
	vector<ChessPiece*>* getPlayerB_PreZone_Pieces();

	CREATE_FUNC(ChessBoard);

private:
	static ChessBoard* instance;

	vector<ChessPiece*> _prtPlayerA_WarZone_Pieces[8]; // ��¼���A��ս�����Ӽ���

	vector<ChessPiece*> _prtPlayerA_PreZone_Pieces; // ��¼���A��ս�����Ӽ���

	vector<ChessPiece*> _prtPlayerB_WarZone_Pieces[8]; // ��¼���B��ս�����Ӽ���

	vector<ChessPiece*> _prtPlayerB_PreZone_Pieces; // ��¼���B��ս�����Ӽ���
};

#endif // !_CHESSBOARD_H_