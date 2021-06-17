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

#include"ChessPiece.h"

class ChessBoard :public Ref
{
public:

	CREATE_FUNC(ChessBoard);

	virtual bool init();

	//CREATE_FUNC(ChessBoard);

	// �߼�������ʵ�������ת��,ת���Ϊ��ս�����½ǵ�һ�����̶�Ӧ�ľ���
	PieceCoordinate* coordinateConvert(CoordinateType type, PieceCoordinate* oldPos, PieceCoordinate* newPos, Sprite* sprite);

	// ��ȡ���A��ս�����Ӽ���
	vector<ChessPiece*>* getPlayerA_WarZone_Pieces();

	// ��ȡ���A��ս�����Ӽ���
	vector<ChessPiece*>* getPlayerA_PreZone_Pieces();

	// ��ȡ���B��ս�����Ӽ���
	vector<ChessPiece*>* getPlayerB_WarZone_Pieces();

	// ��ȡ���B��ս�����Ӽ���
	vector<ChessPiece*>* getPlayerB_PreZone_Pieces();

	//���������ϵ����ӱ�ʾ���������Ӳ����ٷ�����
	//bool setBoard(ChessPiece &piece);

	//����Ƿ������̷�Χ��
	static bool isInBoard(Vec2 posi);

private:

	static int turn;

	vector<ChessPiece*> _prtPlayerA_WarZone_Pieces; // ��¼���A��ս�����Ӽ���

	vector<ChessPiece*> _prtPlayerA_PreZone_Pieces; // ��¼���A��ս�����Ӽ���

	vector<ChessPiece*> _prtPlayerB_WarZone_Pieces; // ��¼���B��ս�����Ӽ���

	vector<ChessPiece*> _prtPlayerB_PreZone_Pieces; // ��¼���B��ս�����Ӽ���

	//��¼����������Ϊ������������
	//������ȷ���Ƿ�����ƶ����޷�ȷ������λ�õľ���������ʲô
	vector<Sprite*>board[BOARD_SIZE];

};

#endif // !_CHESSBOARD_H_