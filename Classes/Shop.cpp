#include "Shop.h"

bool Shop::refresh()
{
	//����Ѿ������ӣ����
	if (!pieceList.empty()) {
		for (auto piece : pieceList) {
			delete piece;
		}
		pieceList.clear();
	}

	srand(time(NULL));
	//��������
	for (int i = 0; i < 4; i++) {
		int figure = rand() % 5;
		switch (figure)
		{
		case 0:
			pieceList.pushBack(new tank);
			break;
		case 1:
			pieceList.pushBack(new mage);
			break;
		case 2:
			pieceList.pushBack(new shooter);
			break;
		case 3:
			pieceList.pushBack(new therapist);
			break;
		case 4:
			pieceList.pushBack(new stalker);
			break;
		}
	}

	gear = rand() % 5;
	return true;
}

bool Shop::init()
{
	refresh();
	return true;
}

bool Shop::qualification(int money, int maxPiece, int pieceNum,int price)
{
	if (money >= price && pieceNum < maxPiece) {
		return true;
	}
	else {
		return false;
	}
}

/*
˵���������ȸ���������Ӹ�����ӵ�еĽ�Ǯ�ж��Ƿ��������ö���ӡ�
      Ȼ�󷵻ز�ͬ�����ӣ����������������������������Ϊ����ʧ��
������A�Ǳ����������
*/
template<class ClassName>
ClassName Shop::pieceIn(ClassName* A)
{
	ClassName entity = *A;
	return entity;
}

int Shop::pieceInEquip()
{
	return gear;
}

Vector<ChessPiece*>* Shop::getPieceList()
{
	return &pieceList;
}

int Shop::pieceOut(ChessPiece* piece)
{
	int price = 0;//���ӵļ۸�
	price = piece->getPiecePerCost()*0.8;

	//������Ӧ����ʵ��
	delete piece;

	return price;
}
