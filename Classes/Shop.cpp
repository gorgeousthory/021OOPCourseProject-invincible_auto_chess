#include "Shop.h"

bool Shop::refresh()
{
	//����Ѿ������ӣ����
	if (!pieceList.empty()) {
		for (int i = 0; i < 4; i++) {
			delete(pieceList[i]);
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
			pieceList.push_back(new tank);
			break;
		case 1:
			pieceList.push_back(new mage);
			break;
		case 2:
			pieceList.push_back(new shooter);
			break;
		case 3:
			pieceList.push_back(new therapist);
			break;
		case 4:
			pieceList.push_back(new stalker);
			break;
		}
	}

	gear = rand() % 5;
	return true;
}

bool Shop::init()
{
	refresh();
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

template<class ClassName>
int Shop::pieceOut(ClassName piece)
{
	int price = 0;//���ӵļ۸�
	price = static_cast<int>(piece.getPieceLevel());
	return price;
}
