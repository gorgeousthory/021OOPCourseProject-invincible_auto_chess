#include "ChessPiece.h"

bool ChessPiece::init(int id)
{

	// ��ʼ����������
	//_pieceName = ConfigController::getDataByID(id).asString();
	_piecePicPath = "Resources/Sprite/";
	_piecePicPath += _pieceName;

	// �������ݵĳ�ʼ�����ļ��ṹ���ƺ�������ӣ�Ԥ����1.4.0�汾֮ǰ���


	return true;
}

bool ChessPiece::init()
{
	return true;
}

void ChessPiece::initPieceIfo(int id)
{
	//// ��ʼ����������
	//_pieceName = ConfigController::getDataByID(id).asString();
	//_piecePicPath = "Resources/Sprite/";
	//_piecePicPath += _pieceName;

	// �������ݵĳ�ʼ�����ļ��ṹ���ƺ�������ӣ�Ԥ����1.4.0�汾֮ǰ���
}

PieceCoordinate* ChessPiece::getPrtCoordinateByType(CoordinateType type)
{
	if (type == CoordinateType::logical)
	{
		return &_logCoordinate;
	}
	else
	{
		return &_realCoordinate;
	}
}

void ChessPiece::setPieceLevel(const Level newLevel)
{
	_pieceLevel = newLevel;
}






bool ChessPiece::updatePieceInfo(const double damage, PieceCoordinate* newRealCoordinate)
{
	/***********************************************
	* �������ӵ�ǰ��ֵʱ��Ҫ���ǵ�ǰװ��Ч����ʱ����
	* 1.ÿ���Ծ��״δ���������ʱ���ڳ�ʼ��ʱ���ǣ�
	* 2.Ϊ���������װ��������Ϊ�ⲿ�ַ���װ���ǿ鿼�ǣ���
	* ע�⣺ÿ���յ��˺��������Ϣ������װ��Ч��
	************************************************/

	// ��������ֵ
	_pieceCrtCondition.healthPoint -= (damage - _pieceCrtCondition.defence);
	if (_pieceCrtCondition.healthPoint < 0)
	{
		return false; // ����ʧ�ܣ���������ֱ���˳�
	}

	// ��������λ��
	const int MOVESPEED = 3; // �ƶ��ٶȣ���λ����ÿ��λ����
	//auto distance = ChessBoard::getDistance(&_realCoordinate, newRealCoordinate);
	//auto time = static_cast<float>(distance / MOVESPEED);

	// ����Ӧ����PlayScene�д����������ȷ�������汾1.1.1��
	//auto updatePiecePos = MoveTo::create(time, Vec2(newRealCoordinate->getX(), newRealCoordinate->getY()));
}

const string ChessPiece::getPieceName()
{
	return _pieceName;
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

Sprite* ChessPiece::createChessPiece(string pieceName, string piecePicPath, Vec2 position)
{
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");

	auto piece = Sprite::createWithTexture(texture->getTextureForKey(piecePicPath));
	auto hpBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/HpBar.png"));//������
	auto mpBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//����
	/*auto hpDecreaseBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//����
	auto mpDecreaseBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//����

	hpDecreaseBar->setColor(Color3B::BLACK);
	mpDecreaseBar->setColor(Color3B::BLACK);

	ProgressTimer* hp, mp;
	hp = ProgressTimer::create(hpDecreaseBar);*/
	Vec2 originSize1 = piece->getContentSize();
	Vec2 originSize2 = hpBar->getContentSize();
	Vec2 originSize3 = mpBar->getContentSize();
	float scale1 = 4 * config->getPx()->x / originSize1.x;
	float scale2 = 2;
	float scale3 = 2;

	piece->setScale(scale1);
	hpBar->setScale(scale2);
	mpBar->setScale(scale3);

	hpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	mpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);

	hpBar->setScale(0.7, 2);
	mpBar->setScale(0.7, 3);

	piece->setPosition(position);
	hpBar->setPosition(position.x + 300, position.y + 1700);
	mpBar->setPosition(position.x + 300, position.y + 2000);

	piece->addChild(hpBar);
	piece->addChild(mpBar);

	return piece;
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


void ChessPiece::readCondition()
{
	//ʵ��ս���У�һ�����ӵ���ʵ���Ծ���equipXX�д��棬Attack/defence��Щ���ݾ���һ���������ݣ�����������
	//�й����ӳ�buff�Ĺ�����
	_pieceCrtCondition.equipAttack = _pieceCrtCondition.equipAttack * (1 + _pieceCrtCondition.myCondition.getInspireAttack());

	//�з����ӳ�
	_pieceCrtCondition.equpiDefence = _pieceCrtCondition.equpiDefence * (1 + _pieceCrtCondition.myCondition.getInspireDefence());

	//���ټӳ�
	_pieceCrtCondition.equipAttackSpeed = _pieceCrtCondition.equipAttackSpeed * (1 + _pieceCrtCondition.myCondition.getInspireSpeed());
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
		return 2 * _pieceCrtCondition.equipAttack;
	}
	else {//û����
		return _pieceCrtCondition.equipAttack;
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
			a = Value(csv[13][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[13][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[13][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[13][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[13][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[13][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[13][11].c_str());	
				_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[13][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[12][3].c_str());
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
			a = Value(csv[14][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[14][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[14][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[14][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[14][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[14][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[14][11].c_str());	
				_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[14][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[14][3].c_str());
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
			a = Value(csv[13][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[13][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[13][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[13][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[13][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[13][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[13][11].c_str());	
				_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[13][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[13][3].c_str());
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
			a = Value(csv[14][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[14][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[14][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[14][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[14][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[14][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[14][11].c_str());	
				_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[14][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[14][3].c_str());
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
			a = Value(csv[10][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[10][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[10][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[10][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[10][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[10][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[10][11].c_str());	
				_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[10][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[10][3].c_str());
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
			a = Value(csv[11][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[11][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[11][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[11][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[11][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[11][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[11][11].c_str());	
				_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[11][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[11][3].c_str());
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
			a = Value(csv[10][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[10][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[10][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[10][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[10][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[10][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[10][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[10][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[10][3].c_str());
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
			a = Value(csv[11][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[11][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[11][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[11][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[11][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[11][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[11][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[11][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[11][3].c_str());
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
			a = Value(csv[7][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[7][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[7][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[7][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[7][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[7][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[7][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[7][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[7][3].c_str());
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
			a = Value(csv[8][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[8][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[8][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[8][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[8][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[8][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[8][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[8][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[8][3].c_str());
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
			a = Value(csv[7][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[7][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[7][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[7][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[7][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[7][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[7][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[7][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[7][3].c_str());
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
			a = Value(csv[8][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[8][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[8][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[8][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[8][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[8][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[8][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[8][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[8][3].c_str());
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
			a = Value(csv[4][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[4][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[4][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[4][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[4][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[4][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[4][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[4][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[4][3].c_str());
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
			a = Value(csv[5][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[5][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[5][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[5][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[5][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[5][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[5][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[5][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[5][3].c_str());
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
			a = Value(csv[4][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[4][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[4][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[4][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[4][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[4][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[4][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[4][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[4][3].c_str());
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
			a = Value(csv[5][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[5][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[5][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[5][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[5][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[5][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[5][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[5][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[5][3].c_str());
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
			a = Value(csv[1][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[1][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[1][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[1][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[1][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[1][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[1][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[1][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[1][3].c_str());
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
			a = Value(csv[2][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[2][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[2][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[2][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[2][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[2][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[2][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[2][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[2][3].c_str());
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
			a = Value(csv[1][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[1][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[1][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[1][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[1][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[1][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[1][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[1][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[1][3].c_str());
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
			a = Value(csv[2][5].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[2][6].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[2][7].c_str());
			_pieceCrtCondition.equipAttack = a.asDouble();
			a = Value(csv[2][8].c_str());
			_pieceCrtCondition.equpiDefence = a.asDouble();
			a = Value(csv[2][9].c_str());
			_pieceCrtCondition.equipAttackSpeed = a.asDouble();
			a = Value(csv[2][10].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[2][11].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[2][12].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[2][3].c_str());
			_piecePicPath = a.asString();
		}
	}
	return result;
}

/**********************************����Ϊ�����������ݳ�ʼ������***************************************/
tank::tank()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[12][2].c_str());
	_pieceName = a.asString();
	a = Value(csv[12][3].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[12][4].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//������������ֵ��ʼ��
	a = Value(csv[12][5].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[12][6].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[12][7].c_str());
	_pieceCrtCondition.equipAttack = a.asDouble();
	a = Value(csv[12][8].c_str());
	_pieceCrtCondition.equpiDefence = a.asDouble();
	a = Value(csv[12][9].c_str());
	_pieceCrtCondition.equipAttackSpeed = a.asDouble();
	a = Value(csv[12][10].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[12][11].c_str());	
	_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[12][12].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

mage::mage()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[9][2].c_str());
	_pieceName = a.asString();
	a = Value(csv[9][3].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[9][4].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//������������ֵ��ʼ��
	a = Value(csv[9][5].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[9][6].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[9][7].c_str());
	_pieceCrtCondition.equipAttack = a.asDouble();
	a = Value(csv[9][8].c_str());
	_pieceCrtCondition.equpiDefence = a.asDouble();
	a = Value(csv[9][9].c_str());
	_pieceCrtCondition.equipAttackSpeed = a.asDouble();
	a = Value(csv[9][10].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[9][11].c_str());	
		_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[9][12].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

shooter::shooter()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[0][2].c_str());
	_pieceName = a.asString();
	a = Value(csv[0][3].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[0][4].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//������������ֵ��ʼ��
	a = Value(csv[0][5].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[0][6].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[0][7].c_str());
	_pieceCrtCondition.equipAttack = a.asDouble();
	a = Value(csv[0][8].c_str());
	_pieceCrtCondition.equpiDefence = a.asDouble();
	a = Value(csv[0][9].c_str());
	_pieceCrtCondition.equipAttackSpeed = a.asDouble();
	a = Value(csv[0][10].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[0][11].c_str());	
		_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[0][12].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

therapist::therapist()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[3][2].c_str());
	_pieceName = a.asString();
	a = Value(csv[3][3].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[3][4].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//������������ֵ��ʼ��
	a = Value(csv[3][5].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[3][6].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[3][7].c_str());
	_pieceCrtCondition.equipAttack = a.asDouble();
	a = Value(csv[3][8].c_str());
	_pieceCrtCondition.equpiDefence = a.asDouble();
	a = Value(csv[3][9].c_str());
	_pieceCrtCondition.equipAttackSpeed = a.asDouble();
	a = Value(csv[3][10].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[3][11].c_str());	
		_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[3][12].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

stalker::stalker()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[6][2].c_str());
	_pieceName = a.asString();
	a = Value(csv[6][3].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[6][4].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//������������ֵ��ʼ��
	a = Value(csv[6][5].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[6][6].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[6][7].c_str());
	_pieceCrtCondition.equipAttack = a.asDouble();
	a = Value(csv[6][8].c_str());
	_pieceCrtCondition.equpiDefence = a.asDouble();
	a = Value(csv[6][9].c_str());
	_pieceCrtCondition.equipAttackSpeed = a.asDouble();
	a = Value(csv[6][10].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[6][11].c_str());	
		_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[6][12].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}


