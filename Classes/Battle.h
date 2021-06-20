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

	CREATE_FUNC(Battle);

	//�������
	double getDistance(PieceCoordinate start, PieceCoordinate end);

	//���ӹ���
	void pieceBattle(ChessPiece *damageMaker, ChessPiece *victim);

	//Ϊһ������Ѱ���Լ��ĵ���,���ǵ���
	void findEnemy(ChessPiece* damageMaker,int type );

	//Ϊ��������Ѱ���Լ��ĵ���,ʹ����for c++11�ı�����������findEnemy�����в��ɸ�Ϊiterator����
	void arrangeEnemy();

	//�������е������ҵ��Լ����յ�����(ChessBoard ���ս�����ڵ��������Ӷ�����)
	void findDstPosition();
	//��һ�������ҵ��Լ����յ����꣬Ҳ��˳�������Ĺ���Ŀ������ӵ���������Ҳ���
	void findPerDstPosition(ChessPiece* );

	//������������ĺ���
	void calculatePosi(ChessPiece* a,ChessPiece* b);

	//����һ����ͨ��Ѱ·����,�������������߻��������ߵ��ƶ�
	//void normalTraceTrack(ChessPiece* origin, ChessPiece* destination);

	//����һ��������ǰ����������ָ���Ӹ��ĺ�����꣬���������������ӵ�ָ��
	void changeWarZonePtr(int x, int y, ChessPiece*);

	//������Χ�����������ܷ�(��ΧһȦ��,��Ҫע�⣬������������chesspiece�޹أ�chesspiece�Ǳ����µ����ӣ�xy�������Ѿ�ȷ��λ�õ������ṩ
	void enumerate(int x, int y, ChessPiece*);

	/*������ս���л�������ѡ������������л��������ӵ��жϣ�
	* 1.�Լ��Ƿ��������������Ҫ������Ӧ�������������
	* 2.�Լ��Ĺ���Ŀ���Ƿ��Ѿ����������������Ҫ��Ŀ��
	* 3.�Լ���ǰ�Ĺ���Ŀ���Ƿ����Լ��Ĺ�����Χ�ڣ������ݽ��������ͬ���ж�
	* 4.����ڣ��򹥻�
	* 5.������ڣ����ƶ�
	* 6.�����������ȱ������������������ֻҪ��ǰ�غ�δ��������������Ӧ����
	* 7.int type ��������������������������һ�����˻���1������� 2����AI
	* return 0�������ˣ�return 1 ������move�� return 2������ attack
	* */
	int battleChoice(ChessPiece*,int type);

	//����������ѡ���ƶ�,�᷵���ƶ���Ŀ�ĵص�,���޸�chesspiece������
	void moveAction(ChessPiece*);

	//����������ѡ�񣺹���
	void attackAction(ChessPiece*);
	
	//�ж��Ƿ�ս�����������δ�����򷵻�0��ƽ�ַ���1�����Aʤ����2�����Bʤ������3
	int ifEnd();

	//����ս������
	void setBoard(ChessBoard*);

	//���ս�����̵�ָ��
	ChessBoard* getChessBoard();

private:
	//ս������
	ChessBoard* battleBoard;
	//���A��ս��Ŀ��
	//vector<ChessPiece*> battleDstA;
	//B��ս��Ŀ��
	//vector<ChessPiece*> battleDstB;
};