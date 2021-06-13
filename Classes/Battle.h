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
	double getDistance(PieceCoordinate* start, PieceCoordinate* end);

	void pieceBattle(ChessPiece &damageMaker, ChessPiece &victim);

	ChessPiece* findEnemy(ChessPiece* damageMaker, Player enemy);

	//����һ����ͨ��Ѱ·����,�������������߻��������ߵ��ƶ�
	void normalTraceTrack(ChessPiece* origin, ChessPiece* destination);

	bool detect(Player A);//�����ҵ�ս�������Ƿ���ʣ�࣬���У�����й������ƶ�

private:
	Player player1;
	Player player2;
};