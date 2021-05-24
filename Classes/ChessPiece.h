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

#include "cocos2d.h"
#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInterval.h"
USING_NS_CC;

#include "ConfigController.h"
#include "ChessBoard.h"

#include <string>
using std::string;

struct PieceInfo // ���������࣬�����ŵ��ǻ���ս�����ж��ı������
{
	double healthPoint; // ����
	
	double magicPoint; // ����

	double attack; // ������
	
	double defence; // ������
	
	double attackSpeed; // �����ٶ�

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