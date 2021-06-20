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
#include"Csv.h"
USING_NS_CC;



class Equipment : public Ref
{
public:
	void init(int type);
	//��ȡװ����ֵ
	std::string getName();//װ������
	std::string getPath();//װ��·��
	int getCost();//װ���۸�
	int getATK();//������
	int getAttackLevel();//�����ȼ�
	int getDEF();//����
	int getDefenceLevel();//�����ȼ�
	int getHp();//����ֵ
	int getHpLevel();//����ֵ�ȼ�
	int getCrit();//������
	double getCritDamage();//�����˺�
	double getHasteScale();//����or�����ٶ�
	int getTag();//װ����ʶ

private:
	//��־,����ʶ�����ļ�װ��
	int tag;

	//����
	std::string name;

	//ͼƬ·��
	std::string path;

    //�����ȼ�
	int hpLevel;

	//����ֵ
	int hp;

	//�۸�
	int cost;

	//�����ȼ�
	int attackLevel;
	//������
	int attack;

	//�����ȼ�
	int defenceLevel;
	//����
	int defence;

	//������
	int critical;
	//�����˺�
	double criticalDamage;

	//�����ٶ�
	double hasteScale;
};

#endif // !_EQUIPMENT_

