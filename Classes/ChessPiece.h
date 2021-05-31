/********************************************
 * ���ܣ�����ģ��
 * ���ߣ�����Դ
 * �汾��1.2.0
 * λ�ã�Classes/model(ɸѡ��)
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * �������ݣ��ϲ������е��������������ݣ�����
 * ��Ҫ�������޸ģ����к����ľ���ʵ��û��д�꣬
 * ϸ�����ڴ˺�����ɡ�
 ********************************************/
#pragma once
#ifndef _CHESSPIECE_H_
#define _CHESSPIECE_H_

#include "cocos2d.h"
#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInterval.h"
USING_NS_CC;

#include "ConfigController.h"
#include "ChessBoard.h"
#include "Equipment.h"
#include "Condition.h"

#include <string>
using std::string;

struct PieceInfo // ���������࣬�����ŵ��ǻ���ս�����ж��ı������
{
	double healthPoint; // ����
	double healthPointM;//�������ֵ
	
	double magicPoint; // ����
	double magicPoint; // �����

	double attack; // ������
	double equipAttack;//װ��+��ʼ
	
	double defence; // ������
	double equpiDefence;//װ��+��ʼ

	double attackSpeed; // �����ٶ�
	double equipAttackSpeed; //װ�� + ��ʼ

	double attackScope; // ��������

	double criticalChance; // ��������

	double criticalDamage; // �����˺�
};

enum class CoordinateType{ real, logical }; // ��������

class PieceCoordinate // ��������
{
public:
	// ��ȡ���Ӻ�����
	int getX() const { return _x; }

	// ��ȡ����������
	int getY() const { return _y; }

	// �������Ӻ�����
	void setX(const int x) { _x = x; }

	// ��������������
	void setY(const int y) { _y = y; }

private:
	int _x; // ������

	int _y; // ������

	CoordinateType _type; // ��������
};

// ����ֻ�������Ǽ�������ö�ٿ���
enum class Level { level1, level2, level3 };

class ChessPiece : public Ref
{
public:
	// ��ʼ������״̬
	virtual bool init(int id);
	virtual bool init();

	// ��ʼ������״̬
	void initPieceIfo(int id);

	// ��������״̬
	bool updatePieceInfo(const double damage, PieceCoordinate* newRealCoordinate);

	// ��ȡ��������
	const string getPieceName() { return _pieceName; }

	// ��ȡ��ǰ������ֵ
	const PieceInfo* getCrtPieceCondition() { return &_pieceCrtCondition; }

	// ��ȡ��ǰ�����Ǽ�
	const Level getPieceLevel() { return _pieceLevel; }

	// ��ȡ��ǰ����λ��
	const PieceCoordinate* getPrtCoordinateByType(CoordinateType type);

	// ���õ�ǰ�����Ǽ�
	void setPieceLevel(const Level newLevel) { _pieceLevel = newLevel; }

	CREATE_FUNC(ChessPiece);

	//���ܺ������̳�
	virtual void skill() = 0;
	
	//� �̳�
	virtual void familyBuff() = 0;

	//�����Ǽ�
	virtual void promoteRank() = 0;

	//�ṩװ��
	virtual void giveEquip(int equipNum, int equipType);

	//����buff���޸���������
	virtual void readCondition();

	virtual void setCondition(double s,int Condition);

	//���ع�������
	int myAttack();

	//��������Ѫ����
	int attackBack(int blood);

	//����������������,���ݶԷ�hp��Ѫ���۳������hp���ҷ����˺�
	int beenAttack(int attack);

	//���湥��������package��������������ã�����A��Ϊ�������Ķ���
	void attackOne(ChessPiece A);

	//�ж������Ƿ�����
	bool ifDead();

private:
	string _pieceName; // ����
	
	string _piecePicPath; // ģ��ͼƬ���·��
	
	string _pieceDataPath; // ���������ڿ��е�key
	
	Level _pieceLevel; // �Ǽ�

	int _piecePerCost; // һֻһ������������

	PieceInfo _pieceCrtCondition; // ��ǰ������ֵ
	
	PieceInfo _buffEffect; // ��ǰװ��(���)Ч���ӳ�

	PieceCoordinate _logCoordinate; // ���ӵ��߼�λ��

	PieceCoordinate _realCoordinate; // ���ӵ�ʵ��λ��
};

#endif