/********************************************
 * ���ܣ�����ģ��
 * ���ߣ�VenusHui
 * �汾��1.1.2
 * λ�ã�Classes/model(ɸѡ��)
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * �������ݣ����������ݶ�ȡģʽ��ͬʱƥ������
 * ���������
 ********************************************/
#pragma once
#ifndef _CHESSPIECE_H_
#define _CHESSPIECE_H_

#include"Csv.h"
#include "ConfigController.h"
#include"Equipment.h"
#include"Condition.h"

#include <string>
using std::string;

#define AdvancedM 0//һ��������Ӧ�У�����
#define Linear 3//һ���ߴ���Ӧ�У�����
#define Physics 6//һ�������Ӧ�У��̿�
#define History 9 //һ�����ٶ�Ӧ�У���ʦ
#define C_ 12//һ��c++��Ӧ�У�̹��
#define nameL 2//�������ֶ�Ӧ��
#define pathL 3//ͼƬ·����Ӧ��
#define costL 4//������Ӧ��
#define hpL 6//����ֵ��Ӧ��
#define mpL 7//ħ��ֵ��Ӧ��
#define attackL 9//��������Ӧ��
#define defenceL 11//��������Ӧ��
#define attackspeedL 12//���ٶ�Ӧ��
#define attackscopeL 13//���������Ӧ��
#define criticalchanceL 14//�������ʶ�Ӧ��
#define criticaldamageL 15//�����˺���Ӧ��

struct PieceInfo // ���������࣬�����ŵ��ǻ���ս�����ж��ı������
{
	double healthPoint; // ʵʱ����
	double healthPointM;//�������ֵ(��װ��֮��������������ʽ������װ���ͳ�ʼ�ϲ�)

	double magicPoint; // ʵʱ����
	double magicPointM; // �����(ͬ����ֵ)

	double attack; // ʵʱ������
	double bAttack;//�������������
	double equipAttack;//װ��+��ʼ

	double defence; // ʵʱ������
	double bDefence;//�������������
	double equpiDefence;//װ��+��ʼ

	double attackSpeed; // ʵʱ�����ٶ�
	double bAttackSpeed;//���������ٶ�
	double equipAttackSpeed; //װ�� + ��ʼ

	double attackScope; // ��������

	double criticalChance; // ��������

	double criticalDamage; // �����˺�

	Condition myCondition;//��ǰ״̬
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
	virtual bool init();

	// ��ʼ������״̬
	void initPieceInfo(int id);

	// ��������״̬
	bool updatePieceInfo(const double damage, PieceCoordinate* newRealCoordinate);

	// ��ȡ��������
	const string getPieceName() { return _pieceName; }

	// ��ȡ����ͼƬ·��
	const string getPicPath() { return _piecePicPath; }

	// ��ȡ��ǰ������ֵ
	const PieceInfo* getCrtPieceCondition() { return &_pieceCrtCondition; }

	// ��ȡ��ǰ�����Ǽ�
	const Level getPieceLevel() { return _pieceLevel; }

	// ��ȡ��ǰ����λ��
	const PieceCoordinate* getPrtCoordinateByType(CoordinateType type);

	// ���õ�ǰ�����Ǽ�
	void setPieceLevel(const Level newLevel) { _pieceLevel = newLevel; }

	CREATE_FUNC(ChessPiece);

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