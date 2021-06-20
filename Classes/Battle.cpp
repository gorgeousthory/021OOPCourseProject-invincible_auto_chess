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
double Battle::getDistance(PieceCoordinate start, PieceCoordinate end)
{
	return sqrt(pow((start.getX() - end.getX()), 2) + pow((start.getY() - end.getY()), 2));
}
void Battle::pieceBattle(ChessPiece *damageMaker, ChessPiece *victim)
{
	//�����˹���
	damageMaker->attackOne(*victim);
}

void Battle::findEnemy(ChessPiece* damageMaker,int type)
{
	double distance = 999;
	ChessPiece* enemyPiece = nullptr;
	int vectorElement = 0;
	if (type == 1) {
		vectorElement = battleBoard->getPlayerB_WarZone_Pieces()->size();
	}
	else {
		vectorElement = battleBoard->getPlayerA_WarZone_Pieces()->size();
	}
	for (int i = 0; i < vectorElement; i++) {
		if (type == 1) {//ָΪA��Ѱ�ҵ���
			if (battleBoard->getPlayerB_WarZone_Pieces()->size() == 0) {
				//����û����
				break;
			}
			if (battleBoard->getPlayerB_WarZone_Pieces()->at(i) == nullptr) {//û������
				break;
			}
			else {
				double temp = 0;
				temp = getDistance(damageMaker->getPrtCoordinate(), battleBoard->getPlayerB_WarZone_Pieces()->at(i)->getPrtCoordinate());
				if (temp < distance) {
					if (!battleBoard->getPlayerB_WarZone_Pieces()->at(i)->ifDead()) {
						enemyPiece = battleBoard->getPlayerB_WarZone_Pieces()->at(i);
					}
					//enemyPiece = battleBoard.getPlayerB_WarZone_Pieces().at(i);
				}
			}
		}
		else if (type == 2) {//ΪB��Ѱ�ҵ���
			if (battleBoard->getPlayerA_WarZone_Pieces()->size() == 0) {
				//�з�û������
				break;
			}
			if (battleBoard->getPlayerA_WarZone_Pieces()->at(i) == nullptr) {
				break;
			}
			else {
				double temp = 0;
				temp = getDistance(damageMaker->getPrtCoordinate(), battleBoard->getPlayerA_WarZone_Pieces()->at(i)->getPrtCoordinate());
				if (temp < distance) {
					if (!battleBoard->getPlayerA_WarZone_Pieces()->at(i)->ifDead()) {
						enemyPiece = battleBoard->getPlayerA_WarZone_Pieces()->at(i);
					}
					//enemyPiece = battleBoard.getPlayerA_WarZone_Pieces().at(i);
				}
			}
		}
	}
	damageMaker->enemyPtr = enemyPiece;
	
}

void Battle::arrangeEnemy()
{
	//ΪA�����е�������

	for (auto chessPtr : *(battleBoard->getPlayerA_WarZone_Pieces())) {
		findEnemy(chessPtr, 1);
	}
	for (auto chessPtr : *(battleBoard->getPlayerB_WarZone_Pieces())) {
		findEnemy(chessPtr, 2);
	}
}

void Battle::findDstPosition()
{
	vector<ChessPiece*>::iterator itA = battleBoard->getPlayerA_WarZone_Pieces()->begin();
	vector<ChessPiece*>::iterator itB = battleBoard->getPlayerB_WarZone_Pieces()->begin();
	for (; itA != battleBoard->getPlayerA_WarZone_Pieces()->end(); itA++) {
		ChessPiece* dstPtr = (*itA)->enemyPtr;

		if (dstPtr->enemyPtr == (*itA)) {
			//˵�����߻�Ϊ����Ŀ��,�����������Ƿ����˵�ԭ������findEnemy���Ѿ��������������
			//���ü�������ĺ���
			calculatePosi((*itA), dstPtr);
			dstPtr->findEnemy = true;
			(*itA)->findEnemy = true;

		}
	}
	
	//��ʱ������Ϊ��������������Ѿ��ҵ����Լ��Ĺ�������,���Ҽ�������Լ���λ��
	//ֻ������������ӵ��յ�����
	//�������ĺ������Ը���findEnemy����������������/2���ǽ���ս����Χ
	//��Ŀ�������Ժ���Ҫ����Ѱ��
	for (itA = battleBoard->getPlayerA_WarZone_Pieces()->begin(); itA != battleBoard->getPlayerA_WarZone_Pieces()->end(); itA++) {
		if (!(*itA)->findEnemy) {
			//�Ѽ������ĺ������������
			calculatePosi((*itA), (*itA)->enemyPtr);
			(*itA)->findEnemy = true;
		}
	}

	for (; itB != battleBoard->getPlayerB_WarZone_Pieces()->end(); itB++) {
		if (!(*itB)->findEnemy) {
			calculatePosi((*itB), (*itB)->enemyPtr);
			(*itB)->findEnemy = true;
		}
	}

}

void Battle::findPerDstPosition(ChessPiece* a)
{
	ChessPiece* dstPtr = a->enemyPtr;

	//�˴˻�Ϊ����Ŀ��
	if (a == dstPtr->enemyPtr) {
		calculatePosi(a, dstPtr);
		a->findEnemy = true;
		dstPtr->findEnemy = true;
	}
	//���a�Ĺ���Ŀ�겻����a
	else if (a != dstPtr->enemyPtr) {
		calculatePosi(a, dstPtr);
		a->findEnemy = true;
	}

}

void Battle::calculatePosi(ChessPiece* a,ChessPiece* b)
{
	double X = 0, Y = 0;
	int xSum = 0, ySum = 0;
	int ax = 0, ay = 0, bx = 0, by = 0;
	bool unFinish = true;
	PieceCoordinate* aCoordinate = nullptr;
	PieceCoordinate* bCoordinate = nullptr;
	if (a->findEnemy) {
		aCoordinate = &(a->getNextCoordinate());
	}
	else {
		aCoordinate = &(a->getPrtCoordinate());
	}
	if (b->findEnemy) {
		bCoordinate = &(b->getNextCoordinate());
	}
	else {
		bCoordinate = &(b->getPrtCoordinate());
	}
	if (!a->findEnemy && !b->findEnemy) {//���˶���û�ҵ�ս������
		xSum = aCoordinate->getX() + bCoordinate->getX();
		ySum = aCoordinate->getY() + bCoordinate->getY();
		if (xSum % 2 != 0) {//x����
			if (aCoordinate->getX() > bCoordinate->getX()) {
				ax = static_cast<int>(ceilf(static_cast<double>(xSum) / 2));
				bx = static_cast<int>(floor(static_cast<double>(xSum) / 2));
				//aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
				//bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
			}
			else {
				ax = static_cast<int>(floor(static_cast<double>(xSum) / 2));
				bx = static_cast<int>(ceilf(static_cast<double>(xSum) / 2));
				//aCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				//bCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
			}
		}
		else {//xż��
			if (aCoordinate->getX() > bCoordinate->getX()) {
				xSum += 1;
				ax = static_cast<int>(ceilf(static_cast<double>(xSum) / 2));
				bx = static_cast<int>(floor(static_cast<double>(xSum) / 2));
				//aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
				//bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
			}
			else if (aCoordinate->getX() == bCoordinate->getX()) {
				if (aCoordinate->getX() == 7) {//�����ұ�
					xSum -= 1;
					ax = static_cast<int>(ceilf(static_cast<double>(xSum) / 2));
					bx = static_cast<int>(floor(static_cast<double>(xSum) / 2));
					//aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
					//bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				}
				else {
					xSum += 1;
					ax = static_cast<int>(ceilf(static_cast<double>(xSum) / 2));
					bx = static_cast<int>(floor(static_cast<double>(xSum) / 2));
					//aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
					//bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				}
			}
			else {//aX<bX
				xSum += 1;
				ax = static_cast<int>(floor(static_cast<double>(xSum) / 2));
				bx = static_cast<int>(ceilf(static_cast<double>(xSum) / 2));
				//aCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				//bCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
			}
		}
		if (ySum % 2 != 0) {//y����
			if (aCoordinate->getY() > bCoordinate->getY()) {
				ay = static_cast<int>(ceilf(static_cast<double>(ySum) / 2));
				by = static_cast<int>(floor(static_cast<double>(ySum) / 2));
				//aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
				//bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
			}
			else {
				ay = static_cast<int>(floor(static_cast<double>(ySum) / 2));
				by = static_cast<int>(ceilf(static_cast<double>(ySum) / 2));
				//aCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				//bCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
			}
		}
		else {//yż��
			if (aCoordinate->getY() > bCoordinate->getY()) {
				ySum += 1;
				ay = static_cast<int>(ceilf(static_cast<double>(ySum) / 2));
				by = static_cast<int>(floor(static_cast<double>(ySum) / 2));
				//aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
				//bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
			}
			else if (aCoordinate->getY() == bCoordinate->getY()) {
				if (aCoordinate->getY() == 7) {//�����ϱ�
					ySum -= 1;
					ay = static_cast<int>(ceilf(static_cast<double>(ySum) / 2));
					by = static_cast<int>(floor(static_cast<double>(ySum) / 2));
					//aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
					//bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				}
				else {
					ySum += 1;
					ay = static_cast<int>(ceilf(static_cast<double>(ySum) / 2));
					by = static_cast<int>(floor(static_cast<double>(ySum) / 2));
					//aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
					//bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				}
			}
			else {//aY<bY
				ySum += 1;
				ay = static_cast<int>(floor(static_cast<double>(ySum) / 2));
				by = static_cast<int>(ceilf(static_cast<double>(ySum) / 2));
				//aCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				//bCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
			}
		}
	}
	else if (a->findEnemy&&!b->findEnemy) {//a�Ѿ��ҵ��˶���,bû�У�Ϊbȷ��λ��
		if (aCoordinate->getX() > bCoordinate->getX()) {//a��b���ұ�
			bx = aCoordinate->getX() - 1;
			ax = aCoordinate->getX();
		}
		else if (aCoordinate->getX() == bCoordinate->getX()) {//a��b��xһ��
			if (aCoordinate->getX() == 0) {
				bx = 1;
				ax = aCoordinate->getX();
			}
			else {
				bx = aCoordinate->getX() - 1;
				ax = aCoordinate->getX();
			}
		}
		else {//a��b�����
			bx = aCoordinate->getX() + 1;
			ax = aCoordinate->getX();
		}

		//Y
		if (aCoordinate->getY() > bCoordinate->getY()) {//a��b���ϱ�
			by = aCoordinate->getY() - 1;
			ay = aCoordinate->getY();
		}
		else if (aCoordinate->getY() == bCoordinate->getY()) {//a��b��Yһ��
			if (aCoordinate->getY() == 0) {
				by = 1;
				ay = aCoordinate->getY();
			}
			else {
				by = aCoordinate->getY() - 1;
				ay = aCoordinate->getY();
			}
		}
		else {//a��b���±�
			by = aCoordinate->getY() + 1;
			ay = aCoordinate->getY();
		}
	}
	else if(!a->findEnemy&&b->findEnemy){//b�ҵ��˶���,aû��,Ϊaȷ��λ��
		if (bCoordinate->getX() > aCoordinate->getX()) {//b��a���ұ�
			ax = bCoordinate->getX() - 1;
			bx = bCoordinate->getX();
		}
		else if (bCoordinate->getX() == aCoordinate->getX()) {//b��a��xһ��
			if (bCoordinate->getX() == 0) {
				ax = 1;
				bx = bCoordinate->getX();
			}
			else {
				ax = bCoordinate->getX() - 1;
				bx = bCoordinate->getX();
			}
		}
		else {//b��a�����
			ax = bCoordinate->getX() + 1;
			bx = bCoordinate->getX();
		}

		//Y
		if (bCoordinate->getY() > aCoordinate->getY()) {//b��a���ϱ�
			ay = bCoordinate->getY() - 1;
			by = bCoordinate->getY();
		}
		else if (bCoordinate->getY() == aCoordinate->getY()) {//b��a��Yһ��
			if (bCoordinate->getY() == 0) {
				ay = 1;
				by = bCoordinate->getY();
			}
			else {
				ay = bCoordinate->getY() - 1;
				by = bCoordinate->getY();
			}
		}
		else {//b��a���±�
			ay = bCoordinate->getY() + 1;
			by = bCoordinate->getY();
		}
	}

	//���������Ѿ�֪�����������ӵ����۵�ַ����Ҫ��������Ƿ�Ϊ�գ����Ϊ�վͷ��£������Ϊ�վ�����Χ8�����ӱ���Ѱ���·�λ��

	//����a���Է�
	if (battleBoard->getWarZonePieces(ay)->at(ax) == nullptr&&unFinish) {
		//Ŀ��ص��a��ָ�룬ԭ��ַ�����ɿ�ָ��
		if (!a->findEnemy) {
			a->retain();
			changeWarZonePtr(ax, ay, a);
		}
		//����bǡ��Ҳ���Է�
		if (battleBoard->getWarZonePieces(by)->at(bx) == nullptr) {
			if (!b->findEnemy) {
				b->retain();
				changeWarZonePtr(bx, by, b);
			}
		}
		//����b���ܷ��ˣ���Ҫ����a�Աߵ�һȦ
		else {
			if (!b->findEnemy) {
				b->retain();
				enumerate(ax, ay, b);
			}
		}
		unFinish = false;
	}
	//�������b���Է�����a���ܷ�(��дelse��ԭ�����Ű�������)
	if (battleBoard->getWarZonePieces(by)->at(bx) == nullptr && battleBoard->getWarZonePieces(ay)->at(ax) != nullptr&&unFinish) {
		if (!b->findEnemy) {
			b->retain();
			changeWarZonePtr(bx, by, b);
		}
		//������Ҫ����b����
		if (!a->findEnemy) {
			a->retain();
			enumerate(bx, by, a);
		}
		unFinish = false;
	}
	//�������Ӷ������Է�
	if (battleBoard->getWarZonePieces(by)->at(bx) != nullptr && battleBoard->getWarZonePieces(ay)->at(ax) != nullptr&&unFinish) {
		//�ȱ���a��Χ�����a
		if (!a->findEnemy) {
			//b��ȷ����
			if (b->findEnemy) {
				a->retain();
				//enumerate ���ǰ���changeWarZonePtr��
				enumerate(bx, by, a);
			}
			else {
				a->retain();
				//enumerate ���ǰ���changeWarZonePtr��
				enumerate(ax, ay, a);
			}
			
		}
		//a�ͱ��ź���
		ax = a->getNextCoordinate().getX();
		ay = a->getNextCoordinate().getY();
		if (!b->findEnemy) {
			b->retain();
			enumerate(ax, ay, b);
		}
		unFinish = false;
	}

}


void Battle::changeWarZonePtr(int x, int y, ChessPiece* a)
{
	//Ŀ��ص��a��ָ�룬ԭ��ַ�����ɿ�ָ��
	PieceCoordinate* aCoordinate = &(a->getPrtCoordinate());
	battleBoard->getWarZonePieces(y)->at(x) = a;
	battleBoard->getWarZonePieces(aCoordinate->getY())->at(aCoordinate->getX()) = nullptr;
	//�޸���a���߼����꣬������ʵ����Ŀǰû���޸�
	a->setNextCoordinate(x,y);
}

void Battle::enumerate(int x, int y, ChessPiece* a)
{
	bool finish = false;
	//�������
	if (x == 0) {
		for (int i = x; i <= (x + 1); i++) {
			
			//��������±�
			if (y == 0) {
				for (int j = y; j <= (y + 1); j++) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
			//��������ϱ�
			else if (y == 7) {
				for (int j = y; j >= (y - 1); j--) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
			//�������������
			else {
				for (int j = y - 1; j <= (y + 1); j++) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
		}
	}
	//�����ұ�
	else if (x == 7) {
		for (int i = x; i >= (x - 1); i--) {

			//��������±�
			if (y == 0) {
				for (int j = y; j <= (y + 1); j++) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
			//��������ϱ�
			else if (y == 7) {
				for (int j = y; j >= (y - 1); j--) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
			//�������������
			else {
				for (int j = y - 1; j <= (y + 1); j++) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
		}
	}
	//���м�
	else {
		for (int i = x-1; i <= (x + 1); i++) {

			//��������±�
			if (y == 0) {
				for (int j = y; j <= (y + 1); j++) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
			//��������ϱ�
			else if (y == 7) {
				for (int j = y; j >= (y - 1); j--) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
			//�������������
			else {
				for (int j = y - 1; j <= (y + 1); j++) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
		}
	}
}

int Battle::battleChoice(ChessPiece* A,int type)
{
	//�Ȼ��A��λ��
	PieceCoordinate aCoordinate = A->getPrtCoordinate();

	//����
	if (A->ifDead()) {
		//warZone���Ƴ����chesspieceָ�룬ʹ����ָ������ߵ����λ��
		//��Ӧ��ͼ�λ�������Ҫ��playscene�в���
		if (battleBoard->getWarZonePieces(aCoordinate.getY())->at(aCoordinate.getX()) == A) {
			battleBoard->getWarZonePieces(aCoordinate.getY())->at(aCoordinate.getX()) = nullptr;
		}
		return 0;
	}
	//û��
	else {
		//�жϵ�ǰ����Ŀ������û

		//��ǰ����Ŀ������
		if (A->enemyPtr->ifDead()) {
			//�ȸ����Լ���״̬������û�е���
			A->findEnemy = false;
			findEnemy(A, type);
		}

		//�ж��Ƿ��ڹ�����Χ��
		PieceCoordinate aCoordinate = A->getPrtCoordinate();
		PieceCoordinate dstCoordinate = A->enemyPtr->getPrtCoordinate();

		double length = getDistance(aCoordinate, dstCoordinate);

		//�ڷ�Χ�ڣ�����ΧһȦ
		if (length <= 1.5) {
			return 2;
		}
		else {
			return 1;
		}
	}
}

void Battle::moveAction(ChessPiece* A)
{
	PieceCoordinate aCoordinate = A->getPrtCoordinate();

	if (battleBoard->getWarZonePieces(aCoordinate.getY())->at(aCoordinate.getX()) == A) {
		battleBoard->getWarZonePieces(aCoordinate.getY())->at(aCoordinate.getX()) = nullptr;
	}
	else {
		CCLOG("moveAction error ");
	}
	

	//���ˣ�A��Ŀ�ĵ��Ѿ����ˣ������ƶ���
	aCoordinate = A->getNextCoordinate();
	//������,����֮ǰ��Ŀ�ĵ�ʱ�Ѿ�ȷ������ѡ����ָ��ĵط�������ok�������������
	battleBoard->getWarZonePieces(aCoordinate.getY())->at(aCoordinate.getX()) = A;

	//�����ݣ�ԭ���ĵط��ĳ�nullptr
	aCoordinate = A->getPrtCoordinate();
	battleBoard->getWarZonePieces(aCoordinate.getY())->at(aCoordinate.getX()) = nullptr;

}

void Battle::attackAction(ChessPiece* A)
{
	A->retain();
	pieceBattle(A, A->enemyPtr);
	CCLOG("attack");
}

int Battle::ifEnd()
{
	int over1 = -1;
	int over2 = -1;
	for (int i = 0; i < static_cast<int>(battleBoard->getPlayerA_WarZone_Pieces()->size()); i++) {
		//�յ�
		if (battleBoard->getPlayerA_WarZone_Pieces()->size() == 0) {
			break;
		}
		if (battleBoard->getPlayerA_WarZone_Pieces()->at(i) == nullptr) {//û������
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
	for (int i = 0; i < static_cast<int>(battleBoard->getPlayerB_WarZone_Pieces()->size()); i++) {
		//�յ�
		if (battleBoard->getPlayerB_WarZone_Pieces()->size() == 0) {
			break;
		}
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
	//������,���п�����ƽ��
	if (over1 != 0 || over2 != 0) {
		if (over1 != 0 && over2 != 0) {
			return 1;
		}
		//���Aʤ��
		else if (over1 == 0 && over2 != 0) {
			return 2;
		}
		//���Bʤ��
		else {
			return 3;
		}
	}
	else {
		return 0;
	}
	
}

void Battle::setBoard(ChessBoard* a)
{
	battleBoard = a;
}

ChessBoard* Battle::getChessBoard()
{
	return battleBoard;
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