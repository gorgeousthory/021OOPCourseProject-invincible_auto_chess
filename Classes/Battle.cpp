#include "Battle.h"

/****************
���ƣ�pieceBattle
���أ�void
������ChessPiece 2��
˵����ģ�⹥�����������ݵĸ���
*/
bool Battle::init()
{
	return true;
}
double Battle::getDistance(PieceCoordinate* start, PieceCoordinate* end)
{
	return sqrt(pow((start->getX() - end->getX()), 2) + pow((start->getY() - end->getY()), 2));
}
void Battle::pieceBattle(ChessPiece &damageMaker, ChessPiece &victim)
{
	//�����˹���
	damageMaker.attackOne(victim);
}

void Battle::findEnemy(ChessPiece* damageMaker,int type)
{
	double distance = 999;
	ChessPiece* enemyPiece = nullptr;
	for (int i = 0; i < 7; i++) {
		if (type == 1) {//ָΪA��Ѱ�ҵ���
			if (battleBoard->getPlayerB_WarZone_Pieces()->at(i) == nullptr) {//û������
				break;
			}
			else {
				double temp = 0;
				temp = getDistance(damageMaker->getPrtCoordinateByType(CoordinateType::logical), battleBoard->getPlayerB_WarZone_Pieces()->at(i)->getPrtCoordinateByType(CoordinateType::logical));
				if (temp < distance) {
					if (battleBoard->getPlayerB_WarZone_Pieces()->at(i)->ifDead()) {
						enemyPiece = battleBoard->getPlayerB_WarZone_Pieces()->at(i);
					}
					//enemyPiece = battleBoard.getPlayerB_WarZone_Pieces().at(i);
				}
			}
		}
		else if (type == 2) {//ΪB��Ѱ�ҵ���
			if (battleBoard->getPlayerA_WarZone_Pieces()->at(i) == nullptr) {
				break;
			}
			else {
				double temp = 0;
				temp = getDistance(damageMaker->getPrtCoordinateByType(CoordinateType::logical), battleBoard->getPlayerA_WarZone_Pieces()->at(i)->getPrtCoordinateByType(CoordinateType::logical));
				if (temp < distance) {
					if (battleBoard->getPlayerA_WarZone_Pieces()->at(i)->ifDead()) {
						enemyPiece = battleBoard->getPlayerA_WarZone_Pieces()->at(i);
					}
					//enemyPiece = battleBoard.getPlayerA_WarZone_Pieces().at(i);
				}
			}
		}
	}
	damageMaker->enemyPtr = enemyPiece;
}

void Battle::findDstPosition()
{
	vector<ChessPiece*>::iterator itA = battleBoard->getPlayerA_WarZone_Pieces()->begin();
	vector<ChessPiece*>::iterator itB = battleDstB.begin();
	for (int i = 0; i < battleDstA.size(); i++) {
		ChessPiece* dst = battleDstA[i];
		PieceCoordinate dstPosition = *(dst->getPrtCoordinateByType(CoordinateType::logical));//A��ս��Ŀ��
		for (int j = 0; j < battleBoard->getPlayerB_WarZone_Pieces()->size(); j++) {
			PieceCoordinate destination = *(battleBoard->getPlayerB_WarZone_Pieces()->at(j)->getPrtCoordinateByType(CoordinateType::logical));

			if (dstPosition.getX() == destination.getX() && dstPosition.getY() == destination.getY()) {//˵���ҵ����Ǹ�Ŀ��

				if (battleDstB[j] == battleBoard->getPlayerA_WarZone_Pieces()->at(i)) {
					//˵�����߻�Ϊ����Ŀ��
					//������ü�������ĺ���
					battleBoard->getPlayerA_WarZone_Pieces()->at(i)->findEnemy = true;
					battleBoard->getPlayerB_WarZone_Pieces()->at(j)->findEnemy = true;
				}
			}
		}
	}
	for (; itA != battleBoard->getPlayerA_WarZone_Pieces()->end(); itA++) {
		ChessPiece* dstPtr = (*itA)->enemyPtr;

		if (dstPtr->enemyPtr == (*itA)) {
			//˵�����߻�Ϊ����Ŀ��,�����������Ƿ����˵�ԭ������findEnemy���Ѿ��������������
			//���ü�������ĺ���
			dstPtr->findEnemy = true;
			(*itA)->findEnemy = true;

		}
	}
	
	//��ʱ������Ϊ��������������Ѿ��ҵ����Լ��Ĺ�������
	//ֻ������������ӵ��յ�����
	//�������ĺ������Ը���findEnemy����������������/2���ǽ���ս����Χ
	//��Ŀ�������Ժ���Ҫ����Ѱ��
	for (itA = battleBoard->getPlayerA_WarZone_Pieces()->begin(); itA != battleBoard->getPlayerA_WarZone_Pieces()->end(); itA++) {
		if (!(*itA)->findEnemy) {
			//�Ѽ������ĺ������������
		}
	}

}

void Battle::calculatePosi(ChessPiece* a,ChessPiece* b)
{
	if (!a->findEnemy && !b->findEnemy) {//���˶���û�ҵ�ս������
		PieceCoordinate* aCoordinate = a->getPrtCoordinateByType(CoordinateType::logical);
		PieceCoordinate* bCoordinate = b->getPrtCoordinateByType(CoordinateType::logical);
		
		double X = 0, Y = 0;
		int xSum = 0, ySum = 0;
		xSum = aCoordinate->getX() + bCoordinate->getX();
		ySum = aCoordinate->getY() + bCoordinate->getY();
		if (xSum % 2 != 0) {//x����
			if (aCoordinate->getX() > bCoordinate->getX()) {
				aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
				bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
			}
			else {
				aCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				bCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
			}
		}
		else {//xż��
			if (aCoordinate->getX() > bCoordinate->getX()) {
				xSum += 1;
				aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
				bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
			}
			else if (aCoordinate->getX() == bCoordinate->getX()) {
				if (aCoordinate->getX() == 7) {//�����ұ�
					xSum -= 1;
					aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
					bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				}
				else {
					xSum += 1;
					aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
					bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				}
			}
			else {//aX<bX
				xSum += 1;
				aCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				bCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
			}
		}
		if (ySum % 2 != 0) {//y����
			if (aCoordinate->getY() > bCoordinate->getY()) {
				aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
				bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
			}
			else {
				aCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				bCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
			}
		}
		else {//yż��
			if (aCoordinate->getY() > bCoordinate->getY()) {
				ySum += 1;
				aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
				bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
			}
			else if (aCoordinate->getY() == bCoordinate->getY()) {
				if (aCoordinate->getY() == 7) {//�����ϱ�
					ySum -= 1;
					aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
					bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				}
				else {
					ySum += 1;
					aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
					bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				}
			}
			else {//aY<bY
				ySum += 1;
				aCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				bCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
			}
		}
	}
	else if (a->findEnemy&&!b->findEnemy) {//a�Ѿ��ҵ��˶���

	}
	else if(!a->findEnemy&&b->findEnemy){//b�ҵ��˶���

	}
}


/*void Battle::normalTraceTrack(ChessPiece* origin, ChessPiece* destination)
{
	PieceCoordinate ori, dst;
	ori = *origin->getPrtCoordinateByType(CoordinateType::logical);
	dst = *destination->getPrtCoordinateByType(CoordinateType::logical);
	int x, y;
	if (ori.getX() < dst.getX()) {
		x = 1;
	}
	else if(ori.getX()>dst.getX()){
		x = -1;
	}
	else {
		x = 0;
	}
	if (ori.getY() < dst.getY()) {
		y = 1;
	}
	else if (ori.getY() > dst.getY()) {
		y = -1;
	}
	else {
		y = 0;
	}
}*/

bool Battle::detect()
{
	int over1 = -1;
	int over2 = -1;
	for (int i = 0; i < 7; i++) {
		if (battleBoard->getPlayerA_WarZone_Pieces()->at(i)==nullptr) {//û������
			break;
		}
		else {
			if (battleBoard->getPlayerA_WarZone_Pieces()->at(i)->ifDead()) {//��������
				if (over1 == -1) {
					over1 = 1;
				}
			}
			else {
				over1 = 0;
			}
		}
	}
	for (int i = 0; i < 7; i++) {
		if (battleBoard->getPlayerB_WarZone_Pieces()->at(i) == nullptr) {//û������
			break;
		}
		else {
			if (battleBoard->getPlayerB_WarZone_Pieces()->at(i)->ifDead()) {//��������
				if (over2 == -1) {
					over2 = 1;
				}
			}
			else {
				over2 = 0;
			}
		}
	}
	if (over1 != 0||over2!=0) {//������
		return true;
	}
	else {
		return false;
	}
}


