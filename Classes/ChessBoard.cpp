#include "ChessBoard.h"


bool ChessBoard::init()
{
	if (!ChessBoard::init()) {
		return false;
	}
	else {
		for (auto n : board) {
			*n = '.';//代表棋盘这里为空
		}
	}
}

/*
* 第一个参数为real时表示从逻辑转换为真实
* 最后一个参数应当固定传入棋盘战斗区最左
* 下角一小格
*/
PieceCoordinate* coordinateConvert(CoordinateType type, PieceCoordinate* oldPos, PieceCoordinate* newPos, Sprite* sprite)
{
	//获取起始块的逻辑尺寸
	Size oneP=sprite->getContentSize();
	int halfBoardWidth = static_cast<int>(oneP.width/2);
	int halfBoardHeight = static_cast<int>(oneP.height/2);

	//获得小格左下角位置(默认修改小格锚点位于右下角)
	//小格锚点改动，这里简单修改即可
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
		//给予的逻辑尺寸坐标是对应坐标位置小方块的中心
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
	//检验棋盘对应位置是否为空，是否能换位置
	if ('.' == board[piece.getPrtCoordinateByType(CoordinateType::real)->getX()][piece.getPrtCoordinateByType(CoordinateType::real)->getY()]) {
        board[piece.getPrtCoordinateByType(CoordinateType::real)->getX()][piece.getPrtCoordinateByType(CoordinateType::real)->getY()] = '@';
		return true;
	}
	else {
		return false;
	}
}
