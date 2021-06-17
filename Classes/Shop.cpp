#include "Shop.h"

bool Shop::refresh()
{
	//����Ѿ������ӣ����
	if (!pieceList.empty()) {
		for (int i = 0; i < pieceList.size(); i++) {
			pieceList.pop_back();
		}
		pieceList.clear();
	}

	srand(time(NULL));
	//��������
	for (int i = 0; i < 4; i++) {
		int figure = rand() % 5;
		ChessPiece piece0, piece1, piece2, piece3, piece4;
		switch (figure)
		{
		case 0:
			piece0.initPieceInfo(figure);
			pieceList.push_back(piece0);
			break;
		case 1:
			piece1.initPieceInfo(figure);
			pieceList.push_back(piece1);
			break;
		case 2:
			piece2.initPieceInfo(figure);
			pieceList.push_back(piece2);
			break;
		case 3:
			piece3.initPieceInfo(figure);
			pieceList.push_back(piece3);
			break;
		case 4:
			piece4.initPieceInfo(figure);
			pieceList.push_back(piece4);
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

template<class ClassName, typename price>
bool Shop::qualification(int money, int maxPiece, int pieceNum, ClassName* A, typename price)
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

vector<ChessPiece>* Shop::getPieceList()
{
	return &pieceList;
}

int Shop::getgear()
{
	return gear;
}

template<class ClassName>
int Shop::pieceOut(ClassName piece)
{
	int price = 0;//���ӵļ۸�
	price = static_cast<int>(piece.getPieceLevel());
	return price;
}
