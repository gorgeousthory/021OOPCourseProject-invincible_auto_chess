#include<iostream>
#include<stdlib.h>
#include<time.h>
#include"ce.h"
using namespace std;
class Base_figure {
	int hp_max;           //Ѫ������
	int hp;               //����Ѫ��
	int mp_max;           //ħ��ֵ����
	int mp;               //����ħ��ֵ
	double o_attack_speed;//��¼��ʼ����+װ������
	int o_defense;        //��¼��ʼ����+װ������
	int o_attack;         //��¼��ʼ����+װ������
	double attack_speed;  //�����ٶ�,��ÿ�빥�����Σ�����Ƶ��
	int defense;          //������
	int attack;           //������
	int rank;             //�ȼ�
	int strike_rate;      //��������
	int gold;             //����������
	Condition my_condition;//��ʾbuff
	Equip my_equip;       //��ʾװ��

	void equip_combine();//װ���ϳ�
	void read_equip();
	//��Щ�����ⲿ������ã���д��private
public:
	virtual void skill()=0;//���ܺ���
	virtual void family_buff() = 0;//����buff
	virtual void promote_rank() = 0;//����Ӣ�����������ȼ�

	virtual void give_equip(int qua,int e_class);//����1��ʾ��������������2��ʾ�������ͣ����������

	virtual void read_condition();//����buff���޸���������
	virtual void give_condition(double s,int w_condition);//����ý�ɫ״̬

	int my_attack();//���ع�������,���ݱ����ʸ��ʷ��ر���������
	int attack_back(int blood);//�����˺�������͵ȡ�ظ�Ѫ��
	int been_attack(int os_at);//���ݶԷ���������Ѫ���۳�����hp���ҷ����˺�ֵ
	void attack_one(Base_figure& who_been_a);
	//�����Ǳ������Ķ���,���Ϻ���ʹ��ʱֻ��Ҫ����attack_one����//

	bool if_dead() { return hp <= 0 ? true : false; };//�ж��Ƿ�����
};

int Base_figure::my_attack()
{
	srand(time(NULL));
	int rate = rand() % 100 + 1;
	return rate <= strike_rate ? 2 * attack : attack;
}//����ģ��ı�������ֻ���ر�ӽ���������ȫ׼ȷ(̫����)

int Base_figure::attack_back(int blood)
{
	hp = (hp + blood * my_condition.get_suck()) <= hp_max ? hp + blood * my_condition.get_suck() : hp_max;
}//������ɵ��˺���Ѫ

int Base_figure::been_attack(int oa_at)
{
	double d_rate = defense / (100.0 + defense);//���˱���
	int blood = (oa_at * d_rate) * (my_condition.get_fragile() + 1);
	hp = hp - (oa_at * d_rate)*(my_condition.get_fragile()+1);
}

void Base_figure::attack_one(Base_figure& who_been_a)
{
	attack_back(who_been_a.been_attack(my_attack()));
}

void Base_figure::read_condition()
{
	attack = o_attack * (1+my_condition.get_inspire_attack());
	defense = o_defense * (1+my_condition.get_inspire_defence());
	attack_speed = o_attack_speed * (1+my_condition.get_inspire_speed());
	//Ŀǰ������conditionû���õ���һ����sleep һ���ǻ�Ѫ״̬����Ҫ����������������
}

void Base_figure::give_condition(double s, int w_condition)
{
	switch (w_condition)
	{
	case 1:
		my_condition.control_sleep(s);
		break;
	case 2:
		my_condition.control_fragile(s);
		break;
	case 3:
		my_condition.control_inspire_attack(s);
		break;
	case 4:
		my_condition.control_inspire_speed(s);
		break;
	case 5:
		my_condition.control_inspire_defence(s);
		break;
	case 6:
		my_condition.control_suck(s);
		break;
	case 7:
		my_condition.control_get_hp(s);
		break;
	default:
		break;
	}
}
/*����1 ���ڿ������ ��0Ϊ��0Ϊ��*/
/*���ڱ������,��ʾ�����������ٷ�֮40����д0.4*/
/*������ֵ���,��ʾ��ָ��ÿ���Ѫ800����д800*/
/*����2��ʾĳһ״̬:1,���� 2,���� 3,�������� 4,�������� 5,�������� 6,������Ѫ 7,��Ѫ״̬*/

void Base_figure::give_equip(int qua, int e_class)
{
	switch (e_class)
	{
	case 1:
		my_equip.give_yataghan(qua);
		break;
	case 2:
		my_equip.give_gem(qua);
		break;
	case 3:
		my_equip.give_dagger(qua);
		break;
	case 4:
		my_equip.give_ammoue(qua);
		break;
	case 5:
		my_equip.give_bow(qua);
		break;
	default:
		break;
	}
	read_equip();
	equip_combine();
}
/*����2��Ӧ��*/
/*1 ���� ������,2 ��ʯ ����ֵ,3 �̽� ��������,4 ���� ������,5 �� �����ٶ�*/

void Base_figure::read_equip()
{
	hp_max += my_equip.get_t_gem() * 150;
	o_attack_speed += my_equip.get_t_bow()*0.1;
	o_defense += my_equip.get_t_ammoue() * 10;
	o_attack += my_equip.get_t_yataghan() * 10;
	strike_rate += 10 * my_equip.get_t_dagger();
}
