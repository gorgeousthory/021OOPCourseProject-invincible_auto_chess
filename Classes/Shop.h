/********************************************
 * ���ܣ���Ϸ�̵�
 * ���ߣ�lxy�����γ�
 * �汾��1.0.0
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵�������������ˢ�º͹���ĺ���������ˢ���̵��
 * �������Ѿ�����ʹ�ã���Ҫע�⣬��������������ʹ
 * ����new��delete�����Թ��������ص�������������
 * ��delete��
 ********************************************/
#pragma once

#include<cocos2d.h>
USING_NS_CC;

#include <string>
using std::string;

#include"Equipment.h"
#include"ChessPiece.h"
#include<stdlib.h>//���ͷ�ļ����������������ˢ���̵����
#include<time.h>
#include<vector>
#define maxEquip 6//Ԥ���������װ����װ������
using namespace std;

class Shop : public Ref
{
public:
	virtual bool init();
	virtual bool init(int random);//�˺���������
	virtual void reFresh();//���øú���ˢ���̵�װ������ɫ

	CREATE_FUNC(Shop);

	template<class ClassName,typename price>
	ClassName pieceIn(int money,int maxPiece,int pieceNum,ClassName A,typename price,int which);//������

	int pieceInEquip(int money, int pieceNum, int price, int which);//��װ��

	template<class ClassName>
	int pieceOut(ClassName piece);//������/װ��

	//�����жϣ���ʾ��һ�ι�����Ϊ�Ƿ�ɹ�
	int ifGet();

private:
	vector<ChessPiece*>pieceList;
	int gear;//һ��������ʹ��һ��������¼����
	int judge;//������¼��һ�ι�����Ϊ�ǳɹ�����ʧ��
	//��0Ϊ��0Ϊ��
};