#include "AfterBattle.h"

bool AfterBattle::init()
{
	return false;
}

/*
���ã������������������ĸ������ﻹ��ʣ������ӣ�Ȼ��������ӵ��Ǽ������˺�
�����б�����װ��ChessPiece��vector
˵����
*/
void AfterBattle::damage(vector<ChessPiece*> A, vector<ChessPiece*> B,Player a,Player b)
{
	int damage = 0;
	if (A.size() > 0) {//Ӯ������A
		for (int i = 0; i < static_cast<int>(A.size()); i++) {
			damage += static_cast<int>(A[i]->getPieceLevel());
		}
		a.hpDecrease(damage);
	}
	else if (B.size() > 0) {
		for (int i = 0; i < static_cast<int>(B.size()); i++) {
			damage += static_cast<int>(B[i]->getPieceLevel());
		}
		b.hpDecrease(damage);
	}
}

/*
���ܣ�����Ƿ����������
���������������
*/
bool AfterBattle::detect(Player a, Player b)
{
	if (a.getHp() < 0 || b.getHp() < 0) {
		return true;
	}
	else {
		return false;
	}
}



