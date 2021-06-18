#include"Player.h"
#define maxEquip 5

bool Player::init()
{
	money = 5;//��ʼ����5��coin

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

ChessPiece** Player::getPieceBattle()
{
	return pieceBattle;
}

int Player::getExperience()
{
	return experience;
}

void Player::setExperience(int expe)
{
	if (expe > 0 && expe <= 10) {
		experience = expe;
	}
}

int Player::getRank()
{
	return rank;
}

void Player::setRank(int Rank)
{
	rank = Rank;
}

int Player::getMoney()
{
	return money;
}

void Player::setMoney(int coin)
{
	money = coin;
}

int Player::getMaxPieceStorage()
{
	return maxPieceStorage;
}

void Player::setMaxPieceStorage(int maxStorage)
{
	maxPieceStorage = maxStorage;
}

int Player::getMaxPieceBattle()
{
	return maxPieceBattle;
}

void Player::setMaxPieceBAttle(int maxBattle)
{
	maxPieceBattle = maxBattle;
}

int Player::getOwnPieceNum()
{
	int pieceNum = 0;
	for (int i = 0; i < 8; i++) {
		if (piecePossesion[i] != nullptr) {
			pieceNum++;
		}
		else {
			break;
		}
	}
	return pieceNum;
}

/*װ����������Ӧ��*/
/* 1 yataghan ������*/
/*2 bow �����ٶ�*/
/*3 dagger  ��������*/
/*4 ammoue ������*/
/*5 gem ����ֵ*/
bool Player::getOneEquip(int type)
{
	if (type <= 5 && type >= 1 && myEquip.size() < maxEquip)
	{
		myEquip.push_back(type);
		return true;
	}
	else
		return false;
}

//�����Ӧ����һ��װ��
bool Player::giveOneEquip(int which, ChessPiece& object)
{
	if (which <= myEquip.size())
	{
		object.getOneEquip(myEquip[which - 1]);
		myEquip.erase(myEquip.begin() + which - 1, myEquip.begin() + which);
		return true;
	}
	else
		return false;
}

bool Player::getOnePiece(ChessPiece* object)
{ 
	int total = getOwnPieceNum();
	if (total < maxPieceStorage)
	{
		piecePossesion[total] = object;
		return true;
	}
	else
		return false;
}

ChessPiece* Player::saleOnePiece(int which)
{
	if (which <= getOwnPieceNum())
	{
		ChessPiece* result = piecePossesion[which - 1];
		piecePossesion[which - 1] = 0;//c++�п�ָ�������0��ʾ
		int total = getOwnPieceNum();

		//ȥ����Ӧ���Ӻ���������
		for (int i1 = 0; i1 <= total; i1++)
		{
			if (piecePossesion[i1] == NULL)
			{
				ChessPiece* temp;
				temp = piecePossesion[i1 + 1];
				piecePossesion[i1 + 1] = piecePossesion[i1];
				piecePossesion[i1] = temp;
			}
		}
		return result;
	}
	else
	{
		ChessPiece* result = 0;
		return result;
	}
}

bool Player::saleOneEquip(int which)
{
	if (which <= myEquip.size())
	{
		money++;
		myEquip.erase(myEquip.begin() + which, myEquip.begin() + which - 1);
		return true;
	}
	else
		return false;
}