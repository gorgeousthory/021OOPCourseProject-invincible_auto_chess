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



class Equip {
	int yataghan = 0;//������ÿװ��һ�Ѽӹ̶�������
	int bow = 0;//����ÿװ��һ�Ѽӹ����ٶ�
	int dagger = 0;//�̽����ӱ�������
	int ammoue = 0;//�ף��ӷ�����
	int gem = 0;//��ʯ��������ֵ
	//������ı����ȱ�ʾ����װ����������Ҳ����������ʾһ��װ����������ֵ��

	int used_yataghan = 0;//������ÿװ��һ�Ѽӹ̶�������
	int used_bow = 0;//����ÿװ��һ�Ѽӹ����ٶ�
	int used_dagger = 0;//�̽����ӱ�������
	int used_ammoue = 0;//�ף��ӷ�����
	int used_gem = 0;//��ʯ��������ֵ
public:
	void give_yataghan(int m1) ;
	int get_yataghan() ;
	int get_t_yataghan() ;

	void give_bow(int m1) ;
	int get_bow() ;
	int get_t_bow() ;

	void give_dagger(int m1) ;
	int get_dagger() ;
	int get_t_dagger() ;

	void  give_ammoue(int m1) ;
	int get_ammoue() ;
	int get_t_ammoue() ;

	void  give_gem(int m1) ;
	int get_gem() ;
	int get_t_gem() ;

	//������ʹ����Ҳֻ��Ҫ�򵥵Ľӿں�������
};//give���������������Ϊ��������(�����������)
//װ����װ��֮���޷����٣���������ļ�����ָ��δ�ϳɵĻ���װ����������
//������װ������װ����������ı�,���ص�����Ҳ���ܵĻ���װ������

#endif // !_EQUIPMENT_

