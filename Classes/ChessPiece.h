/********************************************
 * ���ܣ�����ģ��
 * ���ߣ�����Դ,���γ�
 * �汾��1.2.0
 * λ�ã�Classes/model(ɸѡ��)
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * �������ݣ�����������߼�����󲿷ֹ��ܵ�ʵ��
 ********************************************/
#pragma once
#ifndef _CHESSPIECE_H_
#define _CHESSPIECE_H_

#include "cocos2d.h"
#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInterval.h"
#include<time.h>
#include<stdlib.h>
USING_NS_CC;

#include "ConfigController.h"
#include "ChessBoard.h"
#include "Equipment.h"
#include "Condition.h"
#include<vector>
#include <string>
#include<cmath>
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
//װ���ӳ�ʼ�ĺ����ǳ�ʼ���Լ���װ�����ԣ���Ӧ����һ����ս��ʱ������
//�����ݿ�����ʱ�����ʼ����������ʼ��װ��������readEquipmentһ��

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

	//��������������Ǽ�����ע�ⲻ��ɾ����ʹ������
	virtual void promoteRank() = 0;

	//�ṩװ��,giveEquip����package ֱ�ӵ��ü���
	void equipCombine();//װ���ϳ�
	void readEquipment();//��ȡװ������
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
	void attackOne(ChessPiece& A);

	//�ж������Ƿ�����
	bool ifDead();

	//������ʵ�����ӵ��ƶ�(�߼���,��һ������һ����Ҳ����ֻ��������һ��)��Ϊ�������ƶ�����Ҫ����Է�����vector��һ��ָ��
	void chessMoveLogicalOne(Vector<ChessPiece*>* Oc);//ָ���ȡ�������̵ĳ�Ա��������
	//�ߵ�Ŀ��Ź�����ΪĿ��

	//��������ʵ�ִ̿������ӵ���Ծ�ƶ�(�߼��ϣ�һ��)��Ϊ�������ƶ�����Ҫ����Է�����vector��һ��ָ��
	void chessMoveLogicalJump(Vector<ChessPiece*>* Oc);

private:
	string _pieceName; // ����
	
	string _piecePicPath; // ģ��ͼƬ���·��
	
	string _pieceDataPath; // ���������ڿ��е�key
	
	Level _pieceLevel; // �Ǽ�

	Condition _pieceCondition;//����״̬

	Equip _pieceEquipment;//����װ��

	int _piecePerCost; // һֻһ������������

	PieceInfo _pieceCrtCondition; // ��ǰ������ֵ
	
	PieceInfo _buffEffect; // ��ǰװ��(���)Ч���ӳ�

	PieceCoordinate _logCoordinate; // ���ӵ��߼�λ��

	PieceCoordinate _realCoordinate; // ���ӵ�ʵ��λ��
};
//----------------------------------------------------------------------------------------------------------------------------------
//�ָ��ߣ����������ӻ���������������Ǹ��־������ӵ�����
//----------------------------------------------------------------------------------------------------------------------------------
/*tank*/
class tank : public ChessPiece
{
	static int oRankTank;//��¼һ��tank������
	static int twRankTank;//��¼����tank����
public:
	//��ʼ������
	tank();
	//��������
	~tank();
	//������¼�����캯���漰���ĵط��϶�,���ÿ��ƣ��ɴ��Լ����Ƽ�1��
	void IncreaseOne() { oRankTank++; }
	void DecreaseOne() { oRankTank--; }
	void IncreaseTwo() { twRankTank++; }
	void DecreaseTwo() { twRankTank--; }
	//���ܺ���
	void skill();
	//����buff �ճ�����
	void familyBuff();
	//��������
	void promoteRank();
};

/*mage*/
class mage : public ChessPiece
{
	static int oRankMage;//��¼һ��Mage������
	static int twRankMage;//��¼����Mage����
public:
	mage();
	~mage();
	//������һ�����캯���漰���ĵط��϶࣬�ɴ��Լ����Ƽ�1��
	void Increase() { oRankMage++; }
	void Decrease() { oRankMage--; }
	void IncreaseTwo() { twRankMage++; }
	void DecreaseTwo() { twRankMage--; }
	//���ܺ���
	void skill();
	//����buff �ճ�����
	void familyBuff();
	//��������
	void promoteRank();
};

/*stalker*/
class stalker : public ChessPiece
{
	static int oRankStalker;//��¼һ��stalker������
	static int twRankStalker;//��¼����stalker����
public:
	stalker();
	~stalker();
	//������һ�����캯���漰���ĵط��϶࣬�ɴ��Լ����Ƽ�1��
	void Increase() { oRankStalker++; }
	void Decrease() { oRankStalker--; }
	void IncreaseTwo() { twRankStalker++; }
	void DecreaseTwo() { twRankStalker--; }
	//���ܺ���
	void skill();
	//����buff �ճ�����
	void familyBuff();
	//��������
	void promoteRank();
};

/*therapist*/
class therapist : public ChessPiece
{
	static int oRankTherapist;//��¼һ��therapist������
	static int twRankTherapist;//��¼����therapist����
public:
	therapist();
	~therapist();
	//������һ�����캯���漰���ĵط��϶࣬�ɴ��Լ����Ƽ�1��
	void Increase() { oRankTherapist++; }
	void Decrease() { oRankTherapist--; }
	void IncreaseTwo() { twRankTherapist++; }
	void DecreaseTwo() { twRankTherapist--; }
	//���ܺ���
	void skill();
	//����buff �ճ�����
	void familyBuff();
	//��������
	void promoteRank();
};

/*shotter*/
class shotter : public ChessPiece
{
	static int oRankShotter;//��¼һ��shotter������
	static int twRankShotter;//��¼����shotter����
public:
	shotter();
	~shotter();
	//������һ�����캯���漰���ĵط��϶࣬�ɴ��Լ����Ƽ�1��
	void Increase() { oRankShotter++; }
	void Decrease() { oRankShotter--; }
	void IncreaseTwo() { twRankShotter++; }
	void DecreaseTwo() { twRankShotter--; }
	//���ܺ���
	void skill();
	//����buff �ճ�����
	void familyBuff();
	//��������
	void promoteRank();
};
#endif