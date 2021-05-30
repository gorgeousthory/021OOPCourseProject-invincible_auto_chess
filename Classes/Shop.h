/********************************************
 * ���ܣ���Ϸ�̵�
 * ���ߣ�lxy
 * �汾��1.0.0
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵����
 ********************************************/
#pragma once

#include<cocos2d.h>
USING_NS_CC;

#include <string>
using std::string;

#include"Equipment.h"
#include<stdlib.h>//���ͷ�ļ����������������ˢ���̵����

#include<vector>
using namespace std;

class Shop : public Ref
{
public:
	virtual bool init();
	virtual bool init(int random);

	CREATE_FUNC(Shop);

	template<class ClassName,typename price>
	ClassName pieceIn(int money,int maxPiece,int pieceNum,ClassName A,typename price);//������/װ��

	template<class ClassName>
	int pieceOut(ClassName piece);//������/װ��

private:
	vector<ChessPiece>pieceList;
	Equipment gear;

};