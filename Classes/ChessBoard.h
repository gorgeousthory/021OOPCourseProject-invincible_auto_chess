/********************************************
 * ���ܣ�����ģ��
 * ���ߣ�����Դ
 * �汾��1.1.0
 * λ�ã�Classes/model(ɸѡ��)
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵������������һ�ε�����ģ�ͣ�������һ�������ж�
 * �ƶ��Ƿ���е��ַ����飬�޸��ڲ���������
 ********************************************/
#pragma once
#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_

#define BOARD_SIZE 8//�������̴�С

#include "ChessPiece.h"

#include "ConfigController.h"

using namespace std;


enum class CoordinateType { real, logical }; // ��������

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

	//���������ϵ����ӱ�ʾ���������Ӳ����ٷ�����
	bool setBoard(ChessPiece piece);

private:

	Vector<ChessPiece*> _prtPlayerA_WarZone_Pieces; // ��¼���A��ս�����Ӽ���

	Vector<ChessPiece*> _prtPlayerA_PreZone_Pieces; // ��¼���A��ս�����Ӽ���

	Vector<ChessPiece*> _prtPlayerB_WarZone_Pieces; // ��¼���B��ս�����Ӽ���

	Vector<ChessPiece*> _prtPlayerB_PreZone_Pieces; // ��¼���B��ս�����Ӽ���

	//��¼����������Ϊ������������
	//������ȷ���Ƿ�����ƶ����޷�ȷ������λ�õľ���������ʲô
	char board[BOARD_SIZE][BOARD_SIZE];

};

#endif // !_CHESSBOARD_H_