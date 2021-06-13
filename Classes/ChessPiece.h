/********************************************
 * ���ܣ�����ģ��
 * ���ߣ�����Դ,���γ�
 * �汾��1.2.1
 * λ�ã�Classes/model(ɸѡ��)
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * �������ݣ��ϲ���ljc�ϴ���һЩ���ݣ�������storageNum�������
 ********************************************/
#pragma once
#ifndef _CHESSPIECE_H_
#define _CHESSPIECE_H_
#include "ConfigController.h"
#include"Equipment.h"
#include"Condition.h"

struct PieceInfo // ���������࣬�����ŵ��ǻ���ս�����ж��ı������
{
	double healthPoint; // ����
	double healthPointM;//�������ֵ
	
	double magicPoint; // ����
	double magicPointM; // �����

	double attack; // ������
	double equipAttack;//װ��+��ʼ
	
	double defence; // ������
	double equpiDefence;//װ��+��ʼ

	double attackSpeed; // �����ٶ�
	double equipAttackSpeed; //װ�� + ��ʼ

	double attackScope; // ��������

	double criticalChance; // ��������

	double criticalDamage; // �����˺�

	Condition myCondition;//��ǰ״̬
};

enum class CoordinateType{ real, logical }; // ��������

class PieceCoordinate // ��������
{
public:
	// ��ȡ���Ӻ�����
	int getX() const;

	// ��ȡ����������
	int getY() const;

	// �������Ӻ�����
	void setX(const int x);

	// ��������������
	void setY(const int y);

private:
	int _x; // ������

	int _y; // ������

	CoordinateType _type; // ��������
};

// ����ֻ�������Ǽ�������ö�ٿ���
enum class Level { level1, level2, level3 };

class ChessPiece : public Ref
{
public:
	// ��ʼ������״̬
	virtual bool init(int id);
	virtual bool init();

	// ��ʼ������״̬
	void initPieceIfo(int id);

	// ��������״̬
	bool updatePieceInfo(const double damage, PieceCoordinate* newRealCoordinate);

	// ��ȡ��������
	const string getPieceName();

	// ��ȡ��ǰ������ֵ
	const PieceInfo* getCrtPieceCondition();

	// ��ȡ��ǰ�����Ǽ�
	const Level getPieceLevel();

	// ��ȡ��ǰ����λ��
	const PieceCoordinate* getPrtCoordinateByType(CoordinateType type);

	// ���õ�ǰ�����Ǽ�
	void setPieceLevel(const Level newLevel);

	//��ȡ��������
	virtual string getTag() = 0;

	//CREATE_FUNC(ChessPiece);   ����ChessPiece�ǳ����಻��create

	//���ܺ������̳�
	virtual void skill() = 0;
	
	//� �̳�
	virtual void familyBuff() = 0;

	//�����Ǽ�,����Ϊһ������������������ӵ�ָ���vector
	//�����ĵ��û᷵��һ�������˶�Ӧ���ӵ�vector��
	virtual vector<ChessPiece*> promoteRank(vector<ChessPiece*> piece) = 0;
	//ֻ������������ִ�г�ȥ���ӵĲ���
	virtual void promoteRank() = 0;

	//�ṩװ��
	//virtual void giveEquip(int equipNum, int equipType);

	//����buff���޸���������
	virtual void readCondition();

	virtual void setCondition(double s,int Condition);

	//���ع�������
	int myAttack();

	//��������Ѫ����
	int attackBack(int blood);

	//����������������,�����˺����۳������hp
	int beenAttack(int attack);

	//���湥��������package��������������ã�����A��Ϊ�������Ķ���(����Ϊ�麯������Ϊ����ǣ�����������࣬���ڵ��������ǳ�����û�취��������)
	void attackOne(ChessPiece &A);

	//�ж������Ƿ�����
	bool ifDead();

	int storageNum = 0;//�Ϸ�����Ϊ�������·�����Ϊ����
private:
	string _pieceName; // ����
	
	string _piecePicPath; // ģ��ͼƬ���·��
	
	string _pieceDataPath; // ���������ڿ��е�key
	
	Level _pieceLevel; // �Ǽ�

	int _piecePerCost; // һֻһ������������

	PieceInfo _pieceCrtCondition; // ��ǰ������ֵ
	
	PieceInfo _buffEffect; // ��ǰװ��(���)Ч���ӳ�

	PieceCoordinate _logCoordinate; // ���ӵ��߼�λ��

	PieceCoordinate _realCoordinate; // ���ӵ�ʵ��λ��
};

//----------------------------------------------------------------------------------------------------------------------------------
//�ָ��ߣ����������ӻ���������������Ǹ��־������ӵ�����
//----------------------------------------------------------------------------------------------------------------------------------
/*tank*/
class tank : public ChessPiece
{
public:
	static int oRankTank;//��¼һ��tank������
	static int twRankTank;//��¼����tank����
	string tag = "tank";//���������������
	//����������
	string getTag();
	//��ʼ������
	virtual bool init();
	tank();
	//��������
	~tank();
	//������¼�����캯���漰���ĵط��϶�,���ÿ��ƣ��ɴ��Լ����Ƽ�1��
	void IncreaseOne();
	void DecreaseOne();
	void IncreaseTwo();
	void DecreaseTwo();
	//���ܺ���
	void skill();
	//����buff �ճ�����
	void familyBuff();
	//��������
	vector<ChessPiece*> promoteRank(vector<ChessPiece*> piece);
	void promoteRank();
};

/*mage*/
class mage : public ChessPiece
{
public:
	static int oRankMage;//��¼һ��Mage������
	static int twRankMage;//��¼����Mage����
	string tag = "mage";
	//����������
	string getTag();
	mage();
	~mage();
	//������һ�����캯���漰���ĵط��϶࣬�ɴ��Լ����Ƽ�1��
	void Increase();
	void Decrease();
	void IncreaseTwo();
	void DecreaseTwo();
	//���ܺ���
	void skill();
	//����buff �ճ�����
	void familyBuff();
	//��������
	vector<ChessPiece*> promoteRank(vector<ChessPiece*> piece);
	void promoteRank();
};

/*stalker*/
class stalker : public ChessPiece
{
public:
	static int oRankStalker;//��¼һ��stalker������
	static int twRankStalker;//��¼����stalker����
	string tag = "stalker";
	//����������
	string getTag();
	stalker();
	~stalker();
	//������һ�����캯���漰���ĵط��϶࣬�ɴ��Լ����Ƽ�1��
	void Increase();
	void Decrease();
	void IncreaseTwo();
	void DecreaseTwo();
	//���ܺ���
	void skill();
	//����buff �ճ�����
	void familyBuff();
	//��������
	vector<ChessPiece*> promoteRank(vector<ChessPiece*> piece);
	void promoteRank();
};

/*therapist*/
class therapist : public ChessPiece
{
public:
	static int oRankTherapist;//��¼һ��therapist������
	static int twRankTherapist;//��¼����therapist����
	string tag = "therapist";
	//����������
	string getTag();
	therapist();
	~therapist();
	//������һ�����캯���漰���ĵط��϶࣬�ɴ��Լ����Ƽ�1��
	void Increase();
	void Decrease();
	void IncreaseTwo();
	void DecreaseTwo();
	//���ܺ���
	void skill();
	//����buff �ճ�����
	void familyBuff();
	//��������
	vector<ChessPiece*> promoteRank(vector<ChessPiece*> piece);
    void promoteRank();
};

/*shooter*/
class shooter : public ChessPiece
{
public:
	static int oRankShooter;//��¼һ��shotter������
	static int twRankShooter;//��¼����shotter����
	string tag = "shooter";
	//����������
	string getTag();
	shooter();
	~shooter();
	//������һ�����캯���漰���ĵط��϶࣬�ɴ��Լ����Ƽ�1��
	void Increase();
	void Decrease();
	void IncreaseTwo();
	void DecreaseTwo();
	//���ܺ���
	void skill();
	//����buff �ճ�����
	void familyBuff();
	//��������
	vector<ChessPiece*> promoteRank(vector<ChessPiece*> piece);
	void promoteRank();
};
#endif