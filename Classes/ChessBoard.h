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

#include "ChessPiece.h"
<<<<<<< Updated upstream
=======
#include "ConfigController.h"
>>>>>>> Stashed changes

class ChessBoard :public Ref
{
public:
	virtual bool init();

	CREATE_FUNC(ChessBoard);

	// �߼�������ʵ�������ת��
	PieceCoordinate* coordinateConvert(CoordinateType type, PieceCoordinate* oldPos, PieceCoordinate* newPos);

	// ����ʵ�������ľ���
	static double getDistance(PieceCoordinate* start, PieceCoordinate* end);

	// ��ȡ���A��ս�����Ӽ���
	Vector<ChessPiece*>* getPlayerA_WarZone_Pieces();

	// ��ȡ���A��ս�����Ӽ���
	Vector<ChessPiece*>* getPlayerA_PreZone_Pieces();

	// ��ȡ���B��ս�����Ӽ���
	Vector<ChessPiece*>* getPlayerB_WarZone_Pieces();

	// ��ȡ���B��ս�����Ӽ���
	Vector<ChessPiece*>* getPlayerB_PreZone_Pieces();

private:
	Vector<ChessPiece*> _prtPlayerA_WarZone_Pieces; // ��¼���A��ս�����Ӽ���

	Vector<ChessPiece*> _prtPlayerA_PreZone_Pieces; // ��¼���A��ս�����Ӽ���

	Vector<ChessPiece*> _prtPlayerB_WarZone_Pieces; // ��¼���B��ս�����Ӽ���

	Vector<ChessPiece*> _prtPlayerB_PreZone_Pieces; // ��¼���B��ս�����Ӽ���
};

#endif // !_CHESSBOARD_H_