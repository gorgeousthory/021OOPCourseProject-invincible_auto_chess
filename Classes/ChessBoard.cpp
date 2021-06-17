#include "ChessBoard.h"

bool ChessBoard::init()
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (vector<Sprite*>::iterator it = board[i].begin(); it != board[i].end(); it++) {
			*it = nullptr;
		}
	}
	return true;
}

/*
* ��һ������Ϊrealʱ��ʾ���߼�ת��Ϊ��ʵ
* ���һ������Ӧ���̶���������ս��������
* �½�һС��
*/

PieceCoordinate* ChessBoard::coordinateConvert(CoordinateType type, PieceCoordinate* oldPos, PieceCoordinate* newPos, Sprite* sprite)
{
	//��ȡ��ʼ����߼��ߴ�
	Size oneP = sprite->getContentSize();
	int halfBoardWidth = oneP.width / 2;
	int halfBoardHeight = oneP.height / 2;

	//���С�����½�λ��(Ĭ���޸�С��ê��λ�����½�)
	//С��ê��Ķ���������޸ļ���
	Vec2 XY = sprite->getPosition();
	XY.x = XY.x - 2 * halfBoardWidth;

	if (type == CoordinateType::logical)
	{
		newPos->setX(static_cast<int>(oldPos->getX() - XY.x) % (halfBoardWidth * 2) + 1);
		newPos->setY(static_cast<int>(oldPos->getY() - XY.y) % (halfBoardHeight * 2) + 1);
		return newPos;
	}
	else
	{
		//������߼��ߴ������Ƕ�Ӧ����λ��С���������
		newPos->setX(oldPos->getX() * 2 * halfBoardWidth - halfBoardWidth);
		newPos->setY(oldPos->getY() * 2 * halfBoardHeight - halfBoardHeight);
		return newPos;
	}
}

vector<ChessPiece*>* ChessBoard::getPlayerA_WarZone_Pieces()
{
	return &_prtPlayerA_WarZone_Pieces;
}

vector<ChessPiece*>* ChessBoard::getPlayerA_PreZone_Pieces()
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

/*
bool ChessBoard::setBoard(ChessPiece &piece)
{
	//�������̶�Ӧλ���Ƿ�Ϊ�գ��Ƿ��ܻ�λ��
	if ('.' == board[piece.getPrtCoordinateByType(CoordinateType::real)->getX()][piece.getPrtCoordinateByType(CoordinateType::real)->getY()]) {
        board[piece.getPrtCoordinateByType(CoordinateType::real)->getX()][piece.getPrtCoordinateByType(CoordinateType::real)->getY()] = '@';
		return true;
	}
	else {
		return false;
	}
}*/

bool ChessBoard::isInBoard(Vec2 posi)
{
	if (posi.x > 500 && posi.y > 500) {
		return true;
	}
	else {
		return false;
	}
}

int turn = 1;//�ڼ���

