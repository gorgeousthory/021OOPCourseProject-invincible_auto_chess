#include "ChessPiece.h"

bool ChessPiece::init()
{
	if (!ChessPiece::init())
		return false;

	return true;
}

bool ChessPiece::initialPieceInfo()
{
	

	return true;
}

bool ChessPiece::updatePieceInfo(const double damage)
{
	/***********************************************
	* �������ӵ�ǰ��ֵʱ��Ҫ���ǵ�ǰװ��Ч����ʱ����
	* 1.ÿ���Ծ��״δ���������ʱ���ڳ�ʼ��ʱ���ǣ�
	* 2.Ϊ���������װ��������Ϊ�ⲿ�ַ���װ���ǿ鿼�ǣ���
	* ע�⣺ÿ���յ��˺��������Ϣ������װ��Ч��
	************************************************/
	
	pieceCrtCondition.healthPoint -= damage;
	

	// �������
	if (getCrtPieceCondition()->healthPoint > 0)
	{
		return true; // ���³ɹ�
	}
	else
	{
		return false; // ����ʧ�ܣ���������
	}
}
