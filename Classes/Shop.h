/********************************************
 * ���ܣ���Ϸ�̵�
 * ���ߣ�lxy&&ljc
 * �汾��1.1.0
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵�����޸���ͷ�ļ����⣬��ljc֮ǰ�汾�ϲ� 
 ********************************************/
#pragma once

#ifndef _SHOP_H_
#define _SHOP_H_

#include<stdlib.h>//���ͷ�ļ����������������ˢ���̵����
#include"Storage.h"
#include<time.h>

#define maxEquip 6//Ԥ������װ�������
using namespace std;

class Shop : public Ref
{
public:

	CREATE_FUNC(Shop);

	virtual bool init();
	virtual bool refresh();//���øú���ˢ���̵�

	template<class ClassName,typename price>
	bool qualification(int money, int maxPiece, int pieceNum, ClassName* A, typename price);

	template<class ClassName>
	ClassName pieceIn(ClassName* A);//������\

	int pieceInEquip();//��װ��

	template<class ClassName>
	int pieceOut(ClassName piece);//������/װ��
	
private:
	//���ڳ��۵�����
	vector<ChessPiece*>pieceList;

	//���ڳ��۵�װ��
	int gear;
};

#endif // !_SHOP_
