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

void Shop::reFresh()
{
	//����Ѿ������ӣ��ͷŶ�Ӧ�ڴ棬���vector
	if (!pieceList.empty())
	{
		for (int i1 = 0; i1 < 4; i1++)
			delete (pieceList[i1]);
		pieceList.clear();
	}

	srand(time(NULL));
	//Ϊ����vector�����ö����
	for (int i1 = 0; i1 < 4; i1++)
	{
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
			pieceList.push_back(new shotter);
			break;
		case 3:
			pieceList.push_back(new therapist);
			break;
		case 4:
			pieceList.push_back(new stalker);
		}
	}
	//ˢ��װ����Ӧ����
	gear = rand() % 5;
};
/*
˵���������ȸ���������Ӹ�����ӵ�еĽ�Ǯ�ж��Ƿ��������ö���ӡ�
      Ȼ�󷵻ز�ͬ�����ӣ����������������������������Ϊ����ʧ��
������A�Ǳ����������
*/
template<class ClassName, typename price>
ClassName Shop::pieceIn(int money,int maxPiece, int pieceNum, ClassName A,typename price,int which)
{
	if (money >= price && pieceNum < maxPiece) {//����ɹ�   
		A = *(pieceList[which - 1]);
		judge = 1;
		return A;
		//����ֱ�ӷ���һ�����󣬶�����ָ�룬ע��
		//��Ϊ����ָ��ˢ�µ�ʱ�����ӻ�û��
	}
	else {
		judge = 0;
		return ;//���ʧ�ܣ��򷵻�NULL
	}
}
//����1��5Ϊ�����Ӧλ�õ����ӡ�
//�����뼴Ϊ����װ��


template<class ClassName>
int Shop::pieceOut(ClassName piece)
{
	int price = 0;//���ӵļ۸�
	price = static_cast<int>(piece.getPieceLevel());
	return price;
}

/*piecenum��ʾ�ѳ���װ������*/
/*ͨ��player��howMEquip()���*/
int Shop::pieceInEquip(int money,int pieceNum, int price, int which)
{
	if (money >= price && pieceNum < maxEquip) {//����ɹ�   
		judge = 1;
		gear = 0;//��ʾ��װ����
		return gear;
	}
	else {
		judge = 0;
		return;//���ʧ�ܣ��򷵻�NULL
	}
}