#include<iostream>
using namespace std;
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
	void give_yataghan(int m1) { yataghan += m1, used_yataghan += m1 <= 0 ? -m1: 0; };
	int get_yataghan() { return yataghan; };
	int get_t_yataghan() { return yataghan+used_yataghan; };

	void give_bow(int m1) { bow += m1, used_bow += m1 <= 0 ? -m1 : 0; };
	int get_bow() { return bow; };
	int get_t_bow() { return bow+used_bow; };

	void give_dagger(int m1) { dagger += m1, used_dagger += m1 <= 0 ? -m1 : 0; };
	int get_dagger() { return dagger; };
	int get_t_dagger() { return dagger+used_dagger; };

	void  give_ammoue(int m1) { ammoue += m1, used_ammoue += m1 <= 0 ? -m1 : 0; };
	int get_ammoue() { return ammoue; };
	int get_t_ammoue() { return ammoue+used_ammoue; };

	void  give_gem(int m1) { gem += m1, used_gem += m1 <= 0 ? -m1 : 0; };
	int get_gem() { return gem; };
	int get_t_gem() { return gem+used_gem; };

	//������ʹ����Ҳֻ��Ҫ�򵥵Ľӿں�������
};//give���������������Ϊ��������(�����������)
//װ����װ��֮���޷����٣���������ļ�����ָ��δ�ϳɵĻ���װ����������
//������װ������װ����������ı�,���ص�����Ҳ���ܵĻ���װ������