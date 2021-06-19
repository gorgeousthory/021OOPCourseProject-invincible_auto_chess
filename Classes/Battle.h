/********************************************
 * ���ܣ����ӻ���ս��
 * ���ߣ�lxy
 * �汾��1.0.0
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵����ս�������У����û�а취�����κβ�����
 * �����ӻ��๥�����ɡ�
 ********************************************/

#pragma once
#include"Player.h"
#include"ChessBoard.h"

class Battle :public Ref
{
public:
	virtual bool init();

	//CREATE_FUNC(Battle);

	//�������
	double getDistance(PieceCoordinate start, PieceCoordinate end);

	void pieceBattle(ChessPiece *damageMaker, ChessPiece *victim);

	//Ϊÿһ������Ѱ���Լ��ĵ���
	void findEnemy(ChessPiece* damageMaker,int type );

	//���������ҵ��Լ����յ�����
	void findDstPosition();

	//������������ĺ���
	void calculatePosi(ChessPiece* a,ChessPiece* b);

	//����һ����ͨ��Ѱ·����,�������������߻��������ߵ��ƶ�
	//void normalTraceTrack(ChessPiece* origin, ChessPiece* destination);

	//����һ��������ǰ����������ָ���Ӹ��ĺ�����꣬���������������ӵ�ָ��
	void changeWarZonePtr(int x, int y, ChessPiece*);

	//������Χ�����������ܷ�(��ΧһȦ��,��Ҫע�⣬������������chesspiece�޹أ�chesspiece�Ǳ����µ����ӣ�xy�������Ѿ�ȷ��λ�õ������ṩ
	void enumerate(int x, int y, ChessPiece*);

	bool detect();//�����ҵ�ս�������Ƿ���ʣ�࣬���У�����й������ƶ�
	

private:
	//ս������
	ChessBoard* battleBoard;
	//���A��ս��Ŀ��
	//vector<ChessPiece*> battleDstA;
	//B��ս��Ŀ��
	//vector<ChessPiece*> battleDstB;
};