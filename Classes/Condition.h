/********************************************
 * ���ܣ�����״̬
 * ���ߣ�����Դ
 * �汾��1.1.0
 * λ�ã�Classes/model(ɸѡ��)
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵����������һ���汾�����˲��ֱ�������
 * ���໹û�м̳�Ref������̳к������������
 ********************************************/
#pragma once

#ifndef _CONDITION_H_
#define _CONDITION_H
#include<iostream>
//using namespace std;

class Condition
{
private:

	bool sleep = false;

	double fragile = 0;//����

	double inspireAttack = 0;//����������

	double inspireSpeed = 0;//���ٹ���

	double inspireDefence = 0;//��������

	double suck = 0;//������Ѫ

	double getHp = 0;//��Ѫ״̬
public:

	void controlSleep(bool s1);

	bool getSleep();

	void controlFragile(double f1);

	double getFragile();

	void controlInspireAttack(double a1);

	double getInspireAttack();

	void controlInspireSpeed(double s1);

	double getInspireSpeed();

	void controlInspireDefence(double d1);

	double getInspireDefence();

	void controlSuck(double s1);

	double getSuck();

	void controlGetHp(double g1);

	double getGetHp();

};//����ֻ��ҪһЩ�򵥵Ľӿں���

#endif // !_CONDITION_H_