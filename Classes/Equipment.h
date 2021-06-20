/*
���ܣ�װ��ģ��
���ߣ�����Դ
λ�ã�Class/model��ɸѡ����
��Ϸ���棺Cocos2d-x 4.0
*/
#pragma once
#ifndef _EQUIPMENT_
#define _EQUIPMENT_

#include <string>
#include <cocos2d.h>
USING_NS_CC;

class Equipment : public Ref
{
public:

	//�޸�װ����ֵ
	void changeData(int ATK, int DEF, int crit, int hasteScale);

	//��ȡװ����ֵ
	int getATK(); //������
	int getDEF(); //����
	int getCrit(); //������
	int getHasteScale(); //����or�����ٶ�

private:
	//������
	int attack;

	//����
	int defence;

	//������
	int critical;

	//�����ٶ�
	int hasteScale;
};

#endif // !_EQUIPMENT_

