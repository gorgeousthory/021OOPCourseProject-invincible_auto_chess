/********************************************
 * ���ܣ�����ģ��
 * ���ߣ�hjh
 * �汾��1.0.0
 * λ�ã�Classes/model(ɸѡ��)
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵����Ŀǰ�д�����ƽ׶Σ������������ݳ�Ա
 * ���ӿڡ�
 ********************************************/
#pragma once
#ifndef _CHESSPIECE_H_
#define _CHESSPIECE_H_

#include <cocos2d.h>
USING_NS_CC;

#include <string>
using std::string;

// ����ֻ�������Ǽ�������ö�ٿ���
enum level { Level1, Level2, Level3 };

struct PieceInfo // ��ǰ������ֵ�ṹ��
{
	// ��ǰѪ��
	double healthPoint;

	// ��ǰ����
	double magicPoint;

	// ��ǰ������
	double attack;

	// ��ǰ������
	double defence;

	// ��ǰ�����ٶ�
	double attackSpeed;
};

class ChessPiece : public Ref
{
public:
	virtual bool init();

	CREATE_FUNC(ChessPiece);

	// ��ʼ������״̬
	bool initialPieceInfo();

	// ��������״̬
	bool updatePieceInfo(const double damage);

	// ��ȡ��������
	const string getPieceName() { return pieceName; }

	// ��ȡ��ǰ����״̬�ṹ��
	const PieceInfo* getCrtPieceCondition() { return &pieceCrtCondition; }

	// ��ȡ��ǰ�����Ǽ�
	const int getPieceLevel() { return pieceLevel; }

	// ���õ�ǰ�����Ǽ�
	void setPieceLevel(const int newLevel) { pieceLevel = newLevel; }
private:
	// ����
	string pieceName;

	// �Ǽ�
	int pieceLevel;

	// ��ǰ������ֵ
	PieceInfo pieceCrtCondition;

	// ��ǰװ��Ч��
	PieceInfo equipEffect;

	// һֻһ������������
	int piecePerCost;

	// ���ȼ�����Ѫ��
	double pieceBaseHealthPoint[3];

	// ���ȼ���������
	double pieceBaseMagicPoint[3];

	// ���ȼ�����������
	double pieceBaseAttack[3];

	// ���ȼ�����������
	double pieceBaseDefence[3];

	// ���ȼ����������ٶ�
	double pieceBaseAttackSpeed[3];
};

#endif