/*
���ܣ����ģ��
���ߣ�����Դ
λ�ã�Class/model��ɸѡ����
��Ϸ���棺Cocos2d-x 4.0
*/
#pragma once


#ifndef _PLAYER_H
#define _PLAYER_H_
#include"ChessPiece.h"

class Player : public Ref
{
public:
	virtual bool init();

	CREATE_FUNC(Player);

	//���ý�ҹ���ȼ� ����Ϊ����ĵ�ǰ��������͵�ǰ�ȼ� ����ֵ�����Ƿ������ɹ�
	bool buyLevel(int coin, int level);

	//�޸ĵȼ�
	void promote();

	//afterbattle��ʧ�ܿ�Ѫ
	void hpDecrease(int damage);

	//���hp
	int getHp();

	// ChessPiece** getPieceBattle();//����ָ�������ָ�룬����ַ

	//��ȡ���趨privated������
	int getExperience();
	void setExperience(int expe);

	int getRank();
	void setRank(int Rank);
	
	int getMoney();
	void setMoney(int coin);

	int getMaxPieceStorage();
	void setMaxPieceStorage(int maxStorage);

	int getMaxPieceBattle();
	void setMaxPieceBAttle(int maxBattle);

	int getOwnPieceNum();

	Vector<ChessPiece*>* getPlayerPiecePossesion() { return &piecePossesion; }

	void addToPiecePossesion(ChessPiece* piece);

	void deleteFromPossesionByID(int id);

	Vector<ChessPiece*>* getPlayerPieceBattle() { return & pieceBattle; }

	void addToPieceBattle(ChessPiece* piece);

	void deleteFromBattleByID(int id);

	//���ݸ���������ʹ��һ��һ��װ��
	//����ֵ��ʾ��ȡ�Ƿ�ɹ�
	//ʧ�ܱ�ʾ��Ч�����򳬳�����
	bool getOneEquip(int type);

	//���ݸ��������־�������װ��������һ��
	//����ֵ��ʾ��������װ���Ƿ�ɹ�
	//�������Ӧ��λû��װ��ʱ������ʧ��
	bool giveOneEquip(int which, ChessPiece* object);

	//����һ��װ��
	//����ֵ��ʾ��Ϊ�Ƿ�ɹ�
	//��λ��1��ʼ
	bool saleOneEquip(int which);

	//����һö����
	//����ʧ��ʱ���ؿ�ָ��
	//�����̵꺯������ʹ��,Ϊ�̵��������Ӻ����ṩ����
	//�̵��Ӧ�����ķ���ֵ���������Ǯ��
	ChessPiece* saleOnePiece(int which);

private:
	//���ﾭ��ȼ������Ϊ10��
	int experience = 1;

	//���ﵱǰ����
	int rank;

	//���ﵱǰ��������������������������ӵȣ�
	int money;

	//���ﵱǰ��ӵ�����Ӹ�����������ͨ��public�����޸���ֵ��
	int maxPieceStorage;

	//���ﵱǰ���ϳ�ս���������ֵ���޸ķ�ʽͬ�ϣ�
	int maxPieceBattle;

	//����Ѫ��
	int healthPoint;

	//������ӵ������(ÿ�����ͬʱ����8ö����),��ʼ���ֵΪ5
	Vector<ChessPiece*> piecePossesion{};

	//��ǰ�ϳ�ս������(ÿ������������ϳ�7������)����ʼ���ֵΪ3
	Vector<ChessPiece*> pieceBattle{};

	//�������װ��
	vector<int> myEquip;
};

#endif // !_PLAYER_H
