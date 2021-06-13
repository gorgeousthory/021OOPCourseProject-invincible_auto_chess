#include"Player.h"

bool Player::init()
{
	money = 3;//��ʼ����3��coin

	healthPoint = 30;

	experience = 1;

	maxPieceStorage = 5;//��ʼ��ӵ��������Ӹ���

	maxPieceBattle = 3;//��ʼ�ɷ�������Ӹ���

	return true;

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
void Player::hpDecrease(int damage)
{
	healthPoint -= damage;
}

int Player::getHp()
{
	return healthPoint;
}
