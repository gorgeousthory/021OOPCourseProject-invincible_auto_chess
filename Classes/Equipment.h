#pragma once
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
	//���裬Ϊ�����õ���Ϊ��
	void give_yataghan(int m1) ;
	//���δ�����ĵ�����
	int get_yataghan() ;
	//����Ѿ����ĵģ�δ���ĵ�����
	int get_t_yataghan();

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
};