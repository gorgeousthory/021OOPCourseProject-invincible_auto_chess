#include "ChessPiece.h"
#define AdvancedM		0//һ��������Ӧ�У�����
#define Linear			3//һ���ߴ���Ӧ�У�����
#define Physics			6//һ�������Ӧ�У��̿�
#define History			9 //һ�����ٶ�Ӧ�У���ʦ
#define C_				12//һ��c++��Ӧ�У�̹��
#define nameL			2//�������ֶ�Ӧ��
#define pathL			3//ͼƬ·����Ӧ��
#define costL			4//������Ӧ��
#define hpL				6//����ֵ��Ӧ��
#define mpL				7//ħ��ֵ��Ӧ��
#define attackL			9//��������Ӧ��
#define defenceL		11//��������Ӧ��
#define attackspeedL	12//���ٶ�Ӧ��
#define attackscopeL	13//���������Ӧ��
#define criticalchanceL 14//�������ʶ�Ӧ��
#define criticaldamageL	15//�����˺���Ӧ��

bool ChessPiece::init()
{
	return true;
}

PieceCoordinate ChessPiece::getPrtCoordinate()
{
	return _logCoordinate;
}

PieceCoordinate ChessPiece::getOriginCoordin()
{
	return _originCoordinate;
}

void ChessPiece::setOriginCoordinate(int x, int y)
{
	_originCoordinate.setX(x);
	_originCoordinate.setY(y);
}

void ChessPiece::setPrtCoordinate(int x, int y)
{
	_logCoordinate.setX(x);
	_logCoordinate.setY(y);
}

void ChessPiece::setPieceLevel(const Level newLevel)
{
	_pieceLevel = newLevel;
}

const string ChessPiece::getPieceName()
{
	return _pieceName;
}

const string ChessPiece::getPicPath()
{
	return _piecePicPath;
}

const PieceInfo* ChessPiece::getCrtPieceCondition()
{
	return &_pieceCrtCondition;
}

const Level ChessPiece::getPieceLevel()
{
	return _pieceLevel;
}

bool ChessPiece::ifDead()
{
	return _pieceCrtCondition.healthPoint > 0 ? false : true;
}

Sprite* ChessPiece::getChessPice()
{
	return imagePiece;
}


void ChessPiece::setVec2(Vec2 position)
{
	_realCoordinate.setX(position.x);
	_realCoordinate.setY(position.y);
}

Vec2 ChessPiece::getVec2()
{
	Vec2 position;
	position.x = _realCoordinate.getX();
	position.y = _realCoordinate.getY();
	return position;
}

int ChessPiece::getPiecePerCost()
{
	return _piecePerCost;
}


void ChessPiece::readCondition()
{
	//ʵ��ս���У�һ�����ӵ���ʵ���Ծ���equipXX�д��棬Attack/defence��Щ���ݾ���һ���������ݣ�����������
	//�й����ӳ�buff�Ĺ�����
	_pieceCrtCondition.attack = _pieceCrtCondition.equipAttack * (1 + _pieceCrtCondition.myCondition.getInspireAttack());

	//�з����ӳ�
	_pieceCrtCondition.defence = _pieceCrtCondition.equpiDefence * (1 + _pieceCrtCondition.myCondition.getInspireDefence());

	//���ټӳ�
	_pieceCrtCondition.attackSpeed = _pieceCrtCondition.equipAttackSpeed * (1 + _pieceCrtCondition.myCondition.getInspireSpeed());
}

void ChessPiece::setCondition(double s, int Condition)
{
	switch (Condition)
	{
	case 1:
		_pieceCrtCondition.myCondition.controlSleep(s);
		break;
	case 2:
		_pieceCrtCondition.myCondition.controlFragile(s);
		break;
	case 3:
		_pieceCrtCondition.myCondition.controlInspireAttack(s);
		break;
	case 4:
		_pieceCrtCondition.myCondition.controlInspireSpeed(s);
		break;
	case 5:
		_pieceCrtCondition.myCondition.controlInspireDefence(s);
		break;
	case 6:
		_pieceCrtCondition.myCondition.controlSuck(s);
		break;
	case 7:
		_pieceCrtCondition.myCondition.controlGetHp(s);
		break;
	}
}

int ChessPiece::myAttack()
{
	srand(time(NULL));
	int rate = rand() % 100 + 1;
	if (rate >= _pieceCrtCondition.criticalChance) {//������
		return 2 * _pieceCrtCondition.attack;
	}
	else {//û����
		return _pieceCrtCondition.attack;
	}
}

//bloodָһ�ι����������˺���hp�ǹ����Ժ��Ѫ��
int ChessPiece::attackBack(int blood)
{
	int hp = 0;//ָ�����ظ���hp
	hp = _pieceCrtCondition.healthPoint + blood * _pieceCrtCondition.myCondition.getSuck();
	if (hp >= _pieceCrtCondition.healthPointM) {
		_pieceCrtCondition.healthPoint = _pieceCrtCondition.healthPointM;
		return  _pieceCrtCondition.healthPointM;
	}
	else {
		_pieceCrtCondition.healthPoint = hp;
		return hp;
	}
}

//�����ܵ����˺�,���ҿ۳���ӦѪ��
int ChessPiece::beenAttack(int attack)
{
	double defenceRate = _pieceCrtCondition.defence / (1 + _pieceCrtCondition.defence);
	int damage = attack * defenceRate * _pieceCrtCondition.myCondition.getFragile();//�ܹ��˺�
	_pieceCrtCondition.healthPoint -= damage;
	return damage;
}

void ChessPiece::attackOne(ChessPiece& A)
{
	//��Ѫ&&������A���˺�
	attackBack(A.beenAttack(myAttack()));
}

int PieceCoordinate::getX() const
{
	return _x;
}

int PieceCoordinate::getY() const
{
	return _y;
}

void PieceCoordinate::setX(const int x)
{
	_x = x;
}

void PieceCoordinate::setY(const int y)
{
	_y = y;
}

bool PieceCoordinate::operator==(PieceCoordinate& coordinate)
{
	if (this->getX() == coordinate.getX() && this->getY() == coordinate.getY())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int tank::oRankTank = 0;
int tank::twRankTank = 0;
void tank::IncreaseOne()
{
	oRankTank++;
}

void tank::DecreaseOne()
{
	oRankTank--;
}

void tank::IncreaseTwo()
{
	twRankTank++;
}

void tank::DecreaseTwo()
{
	twRankTank--;
}

void tank::skill()
{
	_pieceCrtCondition.defence *= 1.1;
}

int mage::oRankMage = 0;
int mage::twRankMage = 0;

void mage::Increase()
{
	oRankMage++;
}

void mage::Decrease()
{
	oRankMage--;
}

void mage::IncreaseTwo()
{
	twRankMage++;
}

void mage::DecreaseTwo()
{
	twRankMage--;
}

void mage::skill()
{
	_pieceCrtCondition.equipAttack *= 1.1;
}

int stalker::oRankStalker = 0;
int stalker::twRankStalker = 0;

void stalker::Increase()
{
	oRankStalker++;
}

void stalker::Decrease()
{
	oRankStalker--;
}

void stalker::IncreaseTwo()
{
	twRankStalker++;
}

void stalker::DecreaseTwo()
{
	twRankStalker--;
}

void stalker::skill()
{
	_pieceCrtCondition.criticalChance *= 1.1;
}

int therapist::oRankTherapist = 0;
int therapist::twRankTherapist = 0;
void therapist::Increase()
{
	oRankTherapist++;
}

void therapist::Decrease()
{
	oRankTherapist--;
}

void therapist::IncreaseTwo()
{
	twRankTherapist++;
}

void therapist::DecreaseTwo()
{
	twRankTherapist--;
}

void therapist::skill()
{
	_pieceCrtCondition.healthPoint += 10;
}

int shooter::oRankShooter = 0;
int shooter::twRankShooter = 0;

void shooter::Increase()
{
	oRankShooter++;
}

void shooter::Decrease()
{
	oRankShooter--;
}

void shooter::IncreaseTwo()
{
	twRankShooter++;
}

void shooter::DecreaseTwo()
{
	twRankShooter--;
}

void shooter::skill()
{
	_pieceCrtCondition.attackScope *= 1.1;
}

string tank::getTag() { return tag; };
string mage::getTag() { return tag; };
string shooter::getTag() { return tag; };
string therapist::getTag() { return tag; };
string stalker::getTag() { return tag; };

void tank::promoteRank()
{
	if (Level::level1 == getPieceLevel())
	{
		if (oRankTank >= 3)
		{
			setPieceLevel(Level::level2);
			oRankTank = oRankTank - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[C_ + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[C_ + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[C_ + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[C_ + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[C_ + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[C_ + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[C_ + 1][criticalchanceL].c_str());
				_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[C_ + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[C_ + 1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankTank >= 3)
		{
			setPieceLevel(Level::level3);
			twRankTank = twRankTank - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[C_ + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[C_ + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[C_ + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[C_ + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[C_ + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[C_ + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[C_ + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[C_ + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[C_ + 2][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
}

vector<ChessPiece*>  tank::promoteRank(vector<ChessPiece*> piece)
{
	vector<ChessPiece*> result;
	if (Level::level1 == getPieceLevel())
	{
		if (oRankTank >= 3)
		{
			setPieceLevel(Level::level2);
			oRankTank = oRankTank - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("tank" == getTag() && m1 < 3 && Level::level1 == i1->getPieceLevel()) {
					m1++;
				}
				else
					result.push_back(i1);
			}

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[C_ + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[C_ + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[C_ + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[C_ + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[C_ + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[C_ + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[C_ + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[C_ + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[C_ + 1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankTank >= 3)
		{
			setPieceLevel(Level::level3);
			twRankTank = twRankTank - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("tank" == getTag() && m1 < 3 && Level::level2 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[C_ + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[C_ + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[C_ + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[C_ + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[C_ + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[C_ + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[C_ + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[C_ + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[C_ + 2][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	return result;
}

void mage::promoteRank()
{
	if (Level::level1 == getPieceLevel())
	{
		if (oRankMage >= 3)
		{
			setPieceLevel(Level::level2);
			oRankMage = oRankMage - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[History + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[History + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[History + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[History + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[History + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[History + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[History + 1][criticalchanceL].c_str());
				_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[History + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[History+1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankMage >= 3)
		{
			setPieceLevel(Level::level3);
			twRankMage = twRankMage - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[History + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[History + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[History + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[History + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[History + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[History + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[History + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[History + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[History + 2][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
}

vector<ChessPiece*>  mage::promoteRank(vector<ChessPiece*> piece)
{
	vector<ChessPiece*> result;
	if (Level::level1 == getPieceLevel())
	{
		if (oRankMage >= 3)
		{
			setPieceLevel(Level::level2);
			oRankMage = oRankMage - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("mage" == getTag() && m1 < 3 && Level::level1 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[History + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[History + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[History + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[History + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[History + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[History + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[History + 1][criticalchanceL].c_str());
				_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[History + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[History+1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankMage >= 3)
		{
			setPieceLevel(Level::level3);
			twRankMage = twRankMage - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("mage" == getTag() && m1 < 3 && Level::level2 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[History + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[History + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[History + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[History + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[History + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[History + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[History + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[History + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[History + 2][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	return result;
}

void stalker::promoteRank()
{
	if (Level::level1 == getPieceLevel())
	{
		if (oRankStalker >= 3)
		{
			setPieceLevel(Level::level2);
			oRankStalker = oRankStalker - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[Physics + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Physics + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Physics + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Physics + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Physics + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Physics + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Physics + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Physics + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Physics + 1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankStalker >= 3)
		{
			setPieceLevel(Level::level3);
			twRankStalker = twRankStalker - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[Physics + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Physics + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Physics + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Physics + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Physics + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Physics + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Physics + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Physics + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Physics + 2][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
}

vector<ChessPiece*>  stalker::promoteRank(vector<ChessPiece*> piece)
{
	vector<ChessPiece*> result;
	if (Level::level1 == getPieceLevel())
	{
		if (oRankStalker >= 3)
		{
			setPieceLevel(Level::level2);
			oRankStalker = oRankStalker - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("stalker" == getTag() && m1 < 3 && Level::level1 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}
			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[Physics + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Physics + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Physics + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Physics + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Physics + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Physics + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Physics + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Physics + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Physics + 1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankStalker >= 3)
		{
			setPieceLevel(Level::level3);
			twRankStalker = twRankStalker - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("stalker" == getTag() && m1 < 3 && Level::level2 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[Physics + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Physics + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Physics + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Physics + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Physics + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Physics + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Physics + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Physics + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Physics + 2][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	return result;
}

void therapist::promoteRank()
{
	if (Level::level1 == getPieceLevel())
	{
		if (oRankTherapist >= 3)
		{
			setPieceLevel(Level::level2);
			oRankTherapist = oRankTherapist - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[Linear + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Linear + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Linear + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Linear + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Linear + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Linear + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Linear + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Linear + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Linear + 1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankTherapist >= 3)
		{
			setPieceLevel(Level::level3);
			twRankTherapist = twRankTherapist - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[Linear + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Linear + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Linear + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Linear + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Linear + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Linear + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Linear + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Linear + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Linear + 2][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
}

vector<ChessPiece*>  therapist::promoteRank(vector<ChessPiece*> piece)
{
	vector<ChessPiece*> result;
	if (Level::level1 == getPieceLevel())
	{
		if (oRankTherapist >= 3)
		{
			setPieceLevel(Level::level2);
			oRankTherapist = oRankTherapist - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("therapist" == getTag() && m1 < 3 && Level::level1 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[Linear + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Linear + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Linear + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Linear + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Linear + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Linear + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Linear + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Linear + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Linear + 1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankTherapist >= 3)
		{
			setPieceLevel(Level::level3);
			twRankTherapist = twRankTherapist - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("therapist" == getTag() && m1 < 3 && Level::level2 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[Linear + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Linear + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Linear + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Linear + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Linear + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Linear + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Linear + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Linear + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Linear + 2][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	return result;
}

void shooter::promoteRank()
{
	if (Level::level1 == getPieceLevel())
	{
		if (oRankShooter >= 3)
		{
			setPieceLevel(Level::level2);
			oRankShooter = oRankShooter - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[AdvancedM + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[AdvancedM + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[AdvancedM + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[AdvancedM + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[AdvancedM + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[AdvancedM + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[AdvancedM + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[AdvancedM + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[AdvancedM + 1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankShooter >= 3)
		{
			setPieceLevel(Level::level3);
			twRankShooter = twRankShooter - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[AdvancedM + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[AdvancedM + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[AdvancedM + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[AdvancedM + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[AdvancedM + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[AdvancedM + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[AdvancedM + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[AdvancedM + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[AdvancedM + 2][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
}

vector<ChessPiece*>  shooter::promoteRank(vector<ChessPiece*> piece)
{
	vector<ChessPiece*> result;
	if (Level::level1 == getPieceLevel())
	{
		if (oRankShooter >= 3)
		{
			setPieceLevel(Level::level2);
			oRankShooter = oRankShooter - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("shooter" == getTag() && m1 < 3 && Level::level1 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[AdvancedM + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[AdvancedM + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[AdvancedM + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[AdvancedM + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[AdvancedM + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[AdvancedM + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[AdvancedM + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[AdvancedM + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[AdvancedM + 1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankShooter >= 3)
		{
			setPieceLevel(Level::level3);
			twRankShooter = twRankShooter - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("shooter" == getTag() && m1 < 3 && Level::level2 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//��������������Ϣ
			a = Value(csv[AdvancedM + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[AdvancedM + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[AdvancedM + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[AdvancedM + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[AdvancedM + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[AdvancedM + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[AdvancedM + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[AdvancedM + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[AdvancedM + 2][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	return result;
}

bool tank::init()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[C_][nameL].c_str());
	_pieceName = a.asString();
	a = Value(csv[C_][pathL].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[C_][costL].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//������������ֵ��ʼ��
	a = Value(csv[C_][hpL].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[C_][mpL].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[C_][attackL].c_str());
	_pieceCrtCondition.bAttack = a.asDouble();
	a = Value(csv[C_][defenceL].c_str());
	_pieceCrtCondition.bDefence = a.asDouble();
	a = Value(csv[C_][attackspeedL].c_str());
	_pieceCrtCondition.bAttackSpeed = a.asDouble();
	a = Value(csv[C_][attackscopeL].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[C_][criticalchanceL].c_str());
	_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[C_][criticaldamageL].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
	return true;
}

/**********************************����Ϊ�����������ݳ�ʼ������***************************************/
tank::tank()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[C_][nameL].c_str());
	_pieceName = a.asString();
	a = Value(csv[C_][pathL].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[C_][costL].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//������������ֵ��ʼ��
	a = Value(csv[C_][hpL].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[C_][mpL].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[C_][attackL].c_str());
	_pieceCrtCondition.bAttack = a.asDouble();
	a = Value(csv[C_][defenceL].c_str());
	_pieceCrtCondition.bDefence = a.asDouble();
	a = Value(csv[C_][attackspeedL].c_str());
	_pieceCrtCondition.bAttackSpeed = a.asDouble();
	a = Value(csv[C_][attackscopeL].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[C_][criticalchanceL].c_str());
	_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[C_][criticaldamageL].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

mage::mage()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[History][nameL].c_str());
	_pieceName = a.asString();
	a = Value(csv[History][pathL].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[History][costL].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//������������ֵ��ʼ��
	a = Value(csv[History][hpL].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[History][mpL].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[History][attackL].c_str());
	_pieceCrtCondition.bAttack = a.asDouble();
	a = Value(csv[History][defenceL].c_str());
	_pieceCrtCondition.bDefence = a.asDouble();
	a = Value(csv[History][attackspeedL].c_str());
	_pieceCrtCondition.bAttackSpeed = a.asDouble();
	a = Value(csv[History][attackscopeL].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[History][criticalchanceL].c_str());
		_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[History][criticaldamageL].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

shooter::shooter()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[AdvancedM][nameL].c_str());
	_pieceName = a.asString();
	a = Value(csv[AdvancedM][pathL].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[AdvancedM][costL].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//������������ֵ��ʼ��
	a = Value(csv[AdvancedM][hpL].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[AdvancedM][mpL].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[AdvancedM][attackL].c_str());
	_pieceCrtCondition.bAttack = a.asDouble();
	a = Value(csv[AdvancedM][defenceL].c_str());
	_pieceCrtCondition.bDefence = a.asDouble();
	a = Value(csv[AdvancedM][attackspeedL].c_str());
	_pieceCrtCondition.bAttackSpeed = a.asDouble();
	a = Value(csv[AdvancedM][attackscopeL].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[AdvancedM][criticalchanceL].c_str());
		_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[AdvancedM][criticaldamageL].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

therapist::therapist()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[Linear][nameL].c_str());
	_pieceName = a.asString();
	a = Value(csv[Linear][pathL].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[Linear][costL].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//������������ֵ��ʼ��
	a = Value(csv[Linear][hpL].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[Linear][mpL].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[Linear][attackL].c_str());
	_pieceCrtCondition.bAttack = a.asDouble();
	a = Value(csv[Linear][defenceL].c_str());
	_pieceCrtCondition.bDefence = a.asDouble();
	a = Value(csv[Linear][attackspeedL].c_str());
	_pieceCrtCondition.bAttackSpeed = a.asDouble();
	a = Value(csv[Linear][attackscopeL].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[Linear][criticalchanceL].c_str());
		_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[Linear][criticaldamageL].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

stalker::stalker()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[Physics][nameL].c_str());
	_pieceName = a.asString();
	a = Value(csv[Physics][pathL].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[Physics][costL].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//������������ֵ��ʼ��
	a = Value(csv[Physics][hpL].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[Physics][mpL].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[Physics][attackL].c_str());
	_pieceCrtCondition.bAttack = a.asDouble();
	a = Value(csv[Physics][defenceL].c_str());
	_pieceCrtCondition.bDefence = a.asDouble();
	a = Value(csv[Physics][attackspeedL].c_str());
	_pieceCrtCondition.bAttackSpeed = a.asDouble();
	a = Value(csv[Physics][attackscopeL].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[Physics][criticalchanceL].c_str());
		_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[Physics][criticaldamageL].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}
