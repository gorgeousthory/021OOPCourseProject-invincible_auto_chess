#include "Shop.h"


bool Shop::init()
{
	return false;
}

bool Shop::init(int random)
{
	if (!Shop::init()) {
		return false;
	}
	else {
		//��������������������Ӻ�װ��
		//Ȼ�����private������
	}
	return false;
}

/*
˵���������ȸ���������Ӹ�����ӵ�еĽ�Ǯ�ж��Ƿ��������ö���ӡ�
      Ȼ�󷵻ز�ͬ�����ӣ����������������������������Ϊ����ʧ��
������A�Ǳ����������
*/
template<class ClassName, typename price>
ClassName Shop::pieceIn(int money,int maxPiece, int pieceNum, ClassName A,typename price)
{
	if (money >= price && pieceNum < maxPiece) {//����ɹ�   

		return A;//����һ�����ӣ�������Ҫϸ��
	}
	else {//����ʧ�ܣ������ض�����

	}
	return ChessPiece();
}

template<class ClassName>
int Shop::pieceOut(ClassName piece)
{
	int price = 0;//���ӵļ۸�
	price = static_cast<int>(piece.getPieceLevel());
	return price;
}
