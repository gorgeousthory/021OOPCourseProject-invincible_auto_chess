/*
���ܣ����ģ��
���ߣ�����Դ,���γ�
λ�ã�Class/model��ɸѡ����
��Ϸ���棺Cocos2d-x 4.0
*/
#pragma once

#include <cocos2d.h>
USING_NS_CC;

#include <string>
using std::string;

#include"Chesspiece.h"

class Player : public Ref
{
public:
	virtual bool init();

	CREATE_FUNC(Player);

	//�����̵�
	void shop();

	//���ý�ҹ���ȼ� ����Ϊ����ĵ�ǰ��������͵�ǰ�ȼ� ����ֵ�����Ƿ������ɹ�
	bool buyLevel(int coin, int level);

	//�޸ĵȼ�
	void promote();

	//afterbattle��ʧ�ܿ�Ѫ
	void hpDecrease();

	//���һ��װ��,�����̵깺��װ������ʹ��
	void getOneEquip(int equip);

	//����һ��װ��,which��ʾ�ڼ������ӵ�װ��
	void giveOneEquip(int which, ChessPiece* p1);

	//��������ѳ���װ������
	int howMEquip();

	//�������Ѫ��
	int getHp();
	
private:
	//���ﾭ��ȼ������Ϊ10��
	int experience;

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

	//����װ��,
	vector<int> gear;

    //������ӵ������(ÿ�����ͬʱ����8ö����),��ʼ���ֵΪ5
	vector<ChessPiece&> piecePossesion[8]{};

	//��ǰ�ϳ�ս������(ÿ������������ϳ�7������)����ʼ���ֵΪ3
	vector<ChessPiece&> pieceBattle[7]{};
};