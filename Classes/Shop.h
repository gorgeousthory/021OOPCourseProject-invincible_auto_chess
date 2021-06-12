/********************************************
 * ���ܣ���Ϸ�̵�
 * ���ߣ�lxy
 * �汾��1.0.0
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵����
 ********************************************/
#pragma once

#ifndef _SHOP_H_
#define _SHOP_H_

#include<stdlib.h>//���ͷ�ļ����������������ˢ���̵����
#include"ChessPiece.h"
using namespace std;

class Shop : public Ref
{
public:
	virtual bool init();
	virtual bool init(int random);

	CREATE_FUNC(Shop);

	template<class ClassName, typename price>
	ClassName pieceIn(int money, int maxPiece, int pieceNum, ClassName A, typename price);//������/װ��

	template<class ClassName>
	int pieceOut(ClassName piece);//������/װ��

private:
	//���ڳ��۵�����
	vector<ChessPiece*>pieceList;

	//���ڳ��۵�װ��
	Equipment gear;

};

#endif // !_SHOP_
