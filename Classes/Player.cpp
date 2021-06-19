#include"Player.h"

bool Player::init()
{
	money = 5000000;//��ʼ����5��coin

	healthPoint = 30;

	experience = 1;

	maxPieceStorage = 8;//��ʼ��ӵ��������Ӹ���

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

//ChessPiece** Player::getPieceBattle()
//{
//	return pieceBattle;
//}

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
	money += coin;
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
		if (piecePossesion.at(i) != nullptr) {
			pieceNum++;
		}
		else {
			break;
		}
	}
	return pieceNum;
}

void Player::addToPiecePossesion(ChessPiece* piece)
{
	if (piecePossesion.size() < maxPieceStorage)
	{
		piecePossesion.pushBack(piece);
	}
}

void Player::deleteFromPossesionByID(int id)
{
	if (piecePossesion.size() >= id)
	{
		piecePossesion.erase(piecePossesion.begin() + id);
	}
}

void Player::addToPieceBattle(ChessPiece* piece)
{
	if (pieceBattle.size() < maxPieceBattle)
	{
		pieceBattle.pushBack(piece);
	}
}

void Player::deleteFromBattleByID(int id)
{
	if (pieceBattle.size() >= id)
	{
		pieceBattle.erase(pieceBattle.begin() + id);
	}
}
