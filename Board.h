#ifndef BOARD_H
#define BOARD_H
#include"Chesspiece.h"
#include<vector>
class Board
{
public:
	Board();
	Board(unsigned boardSize = 4, unsigned numberOfPlayers = 2);
	~Board();
	void setPieces();
	piecePoint getHead(unsigned index);
	piecePoint findPiece(unsigned pieceId);
	void setReachables(unsigned pieceId);
	bool hasReachables(unsigned pieceId);
	bool movePiece(unsigned pieceId);
	bool setChoice(unsigned pieceId,bool flag=false);
private:
	piecePoint top;
	piecePoint tempHead;
	unsigned boardSize;
	unsigned numberOfPlayers;
	piecePoint makeNextLineMore(PLAYER player = EMPTY);
	piecePoint makeNextLineLess(PLAYER player = EMPTY);
	piecePoint makeNextLineLess(int limit, PLAYER player = EMPTY);
	static void returnHead(piecePoint& head);
	std::vector<unsigned> reachables;
	piecePoint pieceChosed;
};
#endif
