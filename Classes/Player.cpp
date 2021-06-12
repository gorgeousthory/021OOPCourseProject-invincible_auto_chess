#include"Player.h"

bool Player::init()
{
	if (!Player::init()) {
		return false;
	}
	else {
		return true;
	}
}

bool Player::buyLevel(int coin, int level)
{
	if (coin < 4 || 10 == level) {
		return false; //promotion failure
	}
	else {
		return true;
	}
}
/*
���ã��������ﵱǰ�ȼ�
˵����1.����Ѿ��ڴ˺����п۳��������ظ�����
	  2.���и��ȼ��йص����ݾ��ڴ˺������޸ģ������ڱ��ظ�����
*/
void Player::promote()
{
	//�����Ϳ�Ǯ
	experience = experience + 1;
	money = money - 4;

	//�޸����ݣ��ֱ���3����6����10���޸�һ��

	//������Ӧ�ȼ�
	if (3 == experience || 6 == experience || 10 == experience) {
		maxPieceStorage++;
		maxPieceBattle++;
	}
}

/*
���ã�ս��������۳���Ӧhp
˵�����ú�����δ��ɣ�������Ķ����������ж�����ȷ�۳�hp
	  ����Ķ�Ӧ�ð�����
	  1.ÿ�ο۳�hp������
	  2.�۳�hp�������ж�
*/
void Player::hpDecrease()
{
	if (true) {
		healthPoint = healthPoint - 1;
	}
	else {
		healthPoint = healthPoint;
	}
}

/*�����̵깺��װ���������ص�������ö�Ӧװ��*/
void Player::getOneEquip(int equip)
{
	gear.push_back(equip);
}

/*ѡ���Ӧװ���������Ӧ����*/
/*gear�д洢int��Ӧװ����ο�*/
/*ChessPiece��shop��*/
void Player::giveOneEquip(int which,ChessPiece* p1)
{
	p1->giveEquip(1,gear[which]);
}

//��������ѳ���װ������
int Player::howMEquip() { return gear.size(); };

//�������Ѫ��
int Player::getHp() { return  healthPoint; };
