/********************************************
 * ���ܣ�ȫ�ֱ���
 * ���ߣ�����Դ
 * �汾��1.0.0
 * λ�ã�Classes/model(ɸѡ��)
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵�������ڴ�����Ϸ��������Ҫһֱ���ֵ���
 ********************************************/
#pragma once
#ifndef _STATICPARAMETER_H_
#define _STATICPARAMETER_H_

#include"ChessBoard.h"
#include"Player.h"

class staticParamater
{
public:

	//��������
	static ChessBoard* boardPtr;

	//�������
	static Player* playerA;
	static Player* playerB;
};

#endif