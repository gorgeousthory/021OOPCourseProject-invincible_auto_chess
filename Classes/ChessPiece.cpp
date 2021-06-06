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
//----------------------------------------------------------------------------------------------------------------------------------
int ChessPiece::myAttack()
{
	srand(time(NULL));
	int rate = rand() % 100 + 1;
	return rate <= _pieceCrtCondition.criticalChance ? 2 * _pieceCrtCondition.attack : _pieceCrtCondition.attack;
}//����ģ��ı�������ֻ���ر�ӽ���������ȫ׼ȷ(̫����)

int ChessPiece::attackBack(int blood)
{
	_pieceCrtCondition.healthPoint = (_pieceCrtCondition.healthPoint + blood * _pieceCondition.getSuck()) <= _pieceCrtCondition.healthPointM? _pieceCrtCondition.healthPoint + blood * _pieceCondition.getSuck() : _pieceCrtCondition.healthPointM;
}//������ɵ��˺���Ѫ

int ChessPiece::beenAttack(int attack)
{
	double d_rate = _pieceCrtCondition.defence / (100.0 + _pieceCrtCondition.defence);//���˱���
	int blood = (attack * d_rate) * (_pieceCondition.getFragile() + 1);
	_pieceCrtCondition.healthPoint = _pieceCrtCondition.healthPoint - blood;
}

void ChessPiece::attackOne(ChessPiece& who_been_a)
{
	attackBack(who_been_a.beenAttack(myAttack()));
}//����������package 
//----------------------------------------------------------------------------------------------------------------------------------
bool ChessPiece::ifDead() { return _pieceCrtCondition.healthPoint <= 0 ? true : false; };
//----------------------------------------------------------------------------------------------------------------------------------
void ChessPiece::chessMoveLogicalJump(Vector<ChessPiece*>* Oc)
{
	int Dx = 0;//����x����
	int Dy = 0;//����y����
	int TargetX = 0;
	int TargetY = 0;
	PieceCoordinate* XY;//��������һ�����ӵ�����
	int MinDistance=9999;//�߼��ϣ���Ϊ����Ծ�ƶ������Ծ���Ӧ���Ǻ��������������
	for (unsigned i1 = 0; i1 < Oc->size(); i1++)
	{
		XY = (((*Oc)[i1])->getPrtCoordinateByType(1));
		Dx = XY->getX()- _logCoordinate.getX();
		Dy = XY->getY() - _logCoordinate.getY();
		if (MinDistance <= pow(Dy + Dx,0.5))
			;
		else
		{
			TargetX = XY->getX();
			TargetY = XY->getY();
			MinDistance = pow(Dy + Dx, 0.5);
		}

		if (_logCoordinate.getX() != TargetX)
			_logCoordinate.setX(TargetX);
		else
			;

		if (_logCoordinate.getY() !=TargetY)
			_logCoordinate.setY(_logCoordinate.getY() - 1);
		else
			;
	}
}

void ChessPiece::chessMoveLogicalOne(Vector<ChessPiece*>* Oc)
{
	int Dx = 0;//����x����
	int Dy = 0;//����y����
	int TargetX = 0;
	int TargetY = 0;
	PieceCoordinate* XY;//��������һ�����ӵ�����
	int MinDistance = 9999;//�߼��ϣ���Ϊ��һ���ƶ������Ծ���Ӧ����ƽ���Ϳ���
	for (unsigned i1 = 0; i1 <Oc->size(); i1++)
	{
		XY = (((*Oc)[i1])->getPrtCoordinateByType(1));
		Dx = XY->getX() - _logCoordinate.getX();
		Dy = XY->getY() - _logCoordinate.getY();
		if (MinDistance <= Dy + Dx)
			;
		else
		{
			TargetX = XY->getX();
			TargetY = XY->getY();
			MinDistance = Dy + Dx;
		}

		if (_logCoordinate.getX() > TargetX&&Dx+Dy>=2)
			_logCoordinate.setX(_logCoordinate.getX() - 1);
		else if (_logCoordinate.getX() < TargetX && Dx + Dy >= 2)
			_logCoordinate.setX(_logCoordinate.getX() + 1);
		else
			;

		if (_logCoordinate.getY() > TargetY && Dx + Dy >= 2)
			_logCoordinate.setY(_logCoordinate.getY() - 1);
		else if (_logCoordinate.getY() < TargetY && Dx + Dy >= 2)
			_logCoordinate.setY(_logCoordinate.getY() + 1);
		else
			;
	}
}
//----------------------------------------------------------------------------------------------------------------------------------
//����buff���޸���������
void ChessPiece::readCondition()
{
	_pieceCrtCondition.attack= _pieceCrtCondition.equipAttack * (1 + _pieceCondition.getInsAtk());
	_pieceCrtCondition.defence = _pieceCrtCondition.equpiDefence * (1 + _pieceCondition.getInspireDefence());
	_pieceCrtCondition.attackSpeed = _pieceCrtCondition.equipAttackSpeed * (1 + _pieceCondition.getInspireSpeed());
}//����buff�ӳɲ��һ����Ӧ����

void ChessPiece::setCondition(double s, int Condition)
{
	switch (Condition)
	{
	case 1:
		_pieceCondition.controlSleep(s);
		break;
	case 2:
		_pieceCondition.controlFragile(s);
		break;
	case 3:
		_pieceCondition.controlInspireAtk(s);
		break;
	case 4:
		_pieceCondition.controlInspireSpeed(s);
		break;
	case 5:
		_pieceCondition.controlInspireDefence(s);
		break;
	case 6:
		_pieceCondition.controlSuck(s);
		break;
	case 7:
		_pieceCondition.controlGetHp(s);
		break;
	default:
		break;
	}
}
/*����1 ���ڿ������ ��0Ϊ��0Ϊ��*/
/*���ڱ������,��ʾ�����������ٷ�֮40����д0.4*/
/*������ֵ���,��ʾ��ָ��ÿ���Ѫ800����д800*/
/*����2��ʾĳһ״̬:1,���� 2,���� 3,�������� 4,�������� 5,�������� 6,������Ѫ 7,��Ѫ״̬*/
//----------------------------------------------------------------------------------------------------------------------------------
void ChessPiece::giveEquip(int qua, int e_class)
{
	switch (e_class)
	{
	case 1:
		_pieceEquipment.give_yataghan(qua);
		break;
	case 2:
		_pieceEquipment.give_gem(qua);
		break;
	case 3:
		_pieceEquipment.give_dagger(qua);
		break;
	case 4:
		_pieceEquipment.give_ammoue(qua);
		break;
	case 5:
		_pieceEquipment.give_bow(qua);
		break;
	default:
		break;
	}
	readEquipment();
	equipCombine();
}//����װ��ʱ�ͻ����װ���ϳɺ�������������������˵���Ǹ�package

void ChessPiece::readEquipment()
{
	_pieceCrtCondition.healthPointM += _pieceEquipment.get_t_gem() * 150;
	_pieceCrtCondition.equipAttackSpeed += _pieceEquipment.get_t_bow() * 0.1;
	_pieceCrtCondition.equpiDefence += _pieceEquipment.get_t_ammoue() * 10;
	_pieceCrtCondition.equipAttack += _pieceEquipment.get_t_yataghan() * 10;
	_pieceCrtCondition.criticalChance += 10 * _pieceEquipment.get_t_dagger();
}//���������ʱ������ģ����������ӵ��ֵ���Ҫ�����޸�

void ChessPiece::equipCombine()
{

}
//----------------------------------------------------------------------------------------------------------------------------------
//�ָ��ߣ����������ӻ����ʵ�֣������Ǹ��־������ӵ�ʵ��
//----------------------------------------------------------------------------------------------------------------------------------

/*tank*/
//����Ĺ��캯����Ҫ����ʼ�����ֵܲ���
tank::tank()
{

}

void tank::skill()
{

}

void tank::familyBuff()
{

}
//ע�⣬�ú��������ý�Ϊ���������������
//ɾȥ��ʹ�����ӵķ�ʽҪ���������־����д��ʽ�����̶�
void tank::promoteRank() 
{
	if (oRankTank >= 3)
		setPieceLevel(Level::level2);
	if(twRankTank>=3)
		setPieceLevel(Level::level3);
}

/*mage*/
mage::mage()
{

}

void mage::skill()
{

}

void mage::familyBuff()
{

}

void mage::promoteRank() 
{
	if (oRankMage >= 3)
		setPieceLevel(Level::level2);
	if (twRankMage >= 3)
		setPieceLevel(Level::level3);
}

/*stalker*/
stalker::stalker()
{

}

void stalker::skill()
{

}

void stalker::familyBuff()
{

}

void stalker::promoteRank()
{
	if (oRankStalker >= 3)
		setPieceLevel(Level::level2);
	if (twRankStalker >= 3)
		setPieceLevel(Level::level3);
}

/*therapist*/
therapist::therapist()
{

}

void therapist::skill()
{

}

void therapist::familyBuff()
{

}

void therapist::promoteRank()
{
	if (oRankTherapist >= 3)
		setPieceLevel(Level::level2);
	if (twRankTherapist >= 3)
		setPieceLevel(Level::level3);
}

/*shotter*/
shotter::shotter()
{

}

void shotter::skill()
{

}

void shotter::familyBuff()
{

}

void shotter::promoteRank()
{
	if (oRankShotter >= 3)
		setPieceLevel(Level::level2);
	if (twRankShotter >= 3)
		setPieceLevel(Level::level3);
}
