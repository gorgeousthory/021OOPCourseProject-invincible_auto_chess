#include "ChessPiece.h"

bool ChessPiece::init()
{
	return true;
}

void ChessPiece::initPieceInfo(int id)
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[3 * id][nameL].c_str());
	_pieceName = a.asString();
	a = Value(csv[3 * id][pathL].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[3 * id][costL].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//������������ֵ��ʼ��
	a = Value(csv[3 * id][hpL].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[3 * id][mpL].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[3 * id][attackL].c_str());
	_pieceCrtCondition.bAttack = a.asDouble();
	a = Value(csv[3 * id][defenceL].c_str());
	_pieceCrtCondition.bDefence = a.asDouble();
	a = Value(csv[3 * id][attackspeedL].c_str());
	_pieceCrtCondition.bAttackSpeed = a.asDouble();
	a = Value(csv[3 * id][attackscopeL].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[3 * id][criticalchanceL].c_str());
	_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[3 * id][criticaldamageL].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

const PieceCoordinate* ChessPiece::getPrtCoordinateByType(CoordinateType type)
{
	if (type == CoordinateType::logical)
	{
		return &_logCoordinate;
	}
	else
	{
		return &_realCoordinate;
	}
}


bool ChessPiece::updatePieceInfo(const double damage, PieceCoordinate* newRealCoordinate)
{
	/***********************************************
	* �������ӵ�ǰ��ֵʱ��Ҫ���ǵ�ǰװ��Ч����ʱ����
	* 1.ÿ���Ծ��״δ���������ʱ���ڳ�ʼ��ʱ���ǣ�
	* 2.Ϊ���������װ��������Ϊ�ⲿ�ַ���װ���ǿ鿼�ǣ���
	* ע�⣺ÿ���յ��˺��������Ϣ������װ��Ч��
	************************************************/

	// ��������ֵ
	_pieceCrtCondition.healthPoint -= (damage - _pieceCrtCondition.defence);
	if (_pieceCrtCondition.healthPoint < 0)
	{
		return false; // ����ʧ�ܣ���������ֱ���˳�
	}
}
