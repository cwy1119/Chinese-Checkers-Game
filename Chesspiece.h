#ifndef CHESSPIECE_H
#define CHESSPIECE_H
typedef class Chesspiece* piecePoint;
typedef enum {
	EMPTY,
	RED_PLAYER,
	BLUE_PLAYER,
	GREEN_PLAYER
}PLAYER;

class Chesspiece
{
public:
	Chesspiece(PLAYER player = EMPTY);
	~Chesspiece();
	piecePoint makeLeftSon(PLAYER player = EMPTY);
	piecePoint makeRightSon(PLAYER player = EMPTY);
	void linkSons();
	void linkLeftFather();
	void linkRightFather();
	void linkLeftBrother(piecePoint leftBrother);
	piecePoint getLeftFather();
	piecePoint getRightFather();
	piecePoint getLeftBrother();
	piecePoint getRightBrother();
	piecePoint getLeftSon();
	piecePoint getRightSon();
	PLAYER getPlayer();
	void updatePlayer(PLAYER player = EMPTY);
	unsigned getPieceId();
	void updatePieceId(unsigned id);
	
private:
	piecePoint leftFather;
	piecePoint rightFather;
	piecePoint leftBrother;
	piecePoint rightBrother;
	piecePoint leftSon;
	piecePoint rightSon;
	PLAYER player;
	unsigned pieceId;
	
};
#endif

