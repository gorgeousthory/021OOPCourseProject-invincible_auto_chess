#include "ChessBoard.h"


bool ChessBoard::init()
{
	if (!ChessBoard::init()) {
		return false;
	}
	else {
		for (auto n : board) {
			*n = '.';//������������Ϊ��
		}
	}
}

/*
* ��һ������Ϊrealʱ��ʾ���߼�ת��Ϊ��ʵ
* ���һ������Ӧ���̶���������ս��������
* �½�һС��
*/
PieceCoordinate* coordinateConvert(CoordinateType type, PieceCoordinate* oldPos, PieceCoordinate* newPos, Sprite* sprite)
{
	//��ȡ��ʼ����߼��ߴ�
	Size oneP=sprite->getContentSize();
	int halfBoardWidth = static_cast<int>(oneP.width/2);
	int halfBoardHeight = static_cast<int>(oneP.height/2);

	//���С�����½�λ��(Ĭ���޸�С��ê��λ�����½�)
	//С��ê��Ķ���������޸ļ���
	Vec2 XY = sprite->getPosition();
	XY.x = XY.x - 2*halfBoardWidth;

	if (type == CoordinateType::logical)
	{
		newPos->setX(int(oldPos->getX()-XY.x) % (halfBoardWidth * 2)+1);
		newPos->setY(int(oldPos->getY() - XY.y) % (halfBoardHeight * 2) + 1);
		return newPos;
	}
	else
	{
		//������߼��ߴ������Ƕ�Ӧ����λ��С���������
		newPos->setX(oldPos->getX()*2* halfBoardWidth - halfBoardWidth);
		newPos->setY(oldPos->getY()*2*halfBoardHeight-halfBoardHeight);
		return newPos;
	}
}

double ChessBoard::getDistance(PieceCoordinate* start, PieceCoordinate* end)
{
	return sqrt(pow((start->getX() - end->getX()), 2) + pow((start->getY() - end->getY()), 2));
}

vector<ChessPiece*>* ChessBoard::getPlayerA_WarZone_Pieces()
{
	return &_prtPlayerA_WarZone_Pieces;
}

vector<ChessPiece*>* ChessBoard::getPlayerA_PreZone_Pieces()v
{
	return &_prtPlayerA_PreZone_Pieces;
}

vector<ChessPiece*>* ChessBoard::getPlayerB_WarZone_Pieces()
{
	return &_prtPlayerB_WarZone_Pieces;
}

vector<ChessPiece*>* ChessBoard::getPlayerB_PreZone_Pieces()
{
	return &_prtPlayerB_PreZone_Pieces;
}

bool ChessBoard::setBoard(ChessPiece& piece)
{
	//�������̶�Ӧλ���Ƿ�Ϊ�գ��Ƿ��ܻ�λ��
	if ('.' == board[piece.getPrtCoordinateByType(CoordinateType::real)->getX()][piece.getPrtCoordinateByType(CoordinateType::real)->getY()]) {
        board[piece.getPrtCoordinateByType(CoordinateType::real)->getX()][piece.getPrtCoordinateByType(CoordinateType::real)->getY()] = '@';
		return true;
	}
	else {
		return false;
	}
}
