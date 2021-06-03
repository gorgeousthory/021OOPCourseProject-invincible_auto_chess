#include "ChessPiece.h"

bool ChessPiece::init(int id)
{
	if (!ChessPiece::init(id))
		return false;

	// ��ʼ����������
	_pieceName = ConfigController::getDataByID(id).asString();
	_piecePicPath = "Resources/Sprite/";
	_piecePicPath += _pieceName;

	// �������ݵĳ�ʼ�����ļ��ṹ���ƺ�������ӣ�Ԥ����1.4.0�汾֮ǰ���


	return true;
}

bool ChessPiece::init()
{
	if (!ChessPiece::init()) {
		return false;
	}
	else {
		return true;
	}
}

void ChessPiece::initPieceIfo(int id)
{
	//// ��ʼ����������
	//_pieceName = ConfigController::getDataByID(id).asString();
	//_piecePicPath = "Resources/Sprite/";
	//_piecePicPath += _pieceName;

	// �������ݵĳ�ʼ�����ļ��ṹ���ƺ�������ӣ�Ԥ����1.4.0�汾֮ǰ���
}

const PieceCoordinate* ChessPiece::getPrtCoordinateByType(CoordinateType type)
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
	auto distance = ChessBoard::getDistance(&_realCoordinate, newRealCoordinate);
	auto time = static_cast<float>(distance / MOVESPEED);

	// ����Ӧ����PlayScene�д����������ȷ�������汾1.1.1��
	auto updatePiecePos = MoveTo::create(time, Vec2(newRealCoordinate->getX(), newRealCoordinate->getY()));
}

bool ChessPiece::ifDead()
{
	return _pieceCrtCondition.healthPoint > 0 ? true : false;
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

//�����ܵ����˺�
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
