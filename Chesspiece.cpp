#include "Chesspiece.h"



Chesspiece::Chesspiece(PLAYER player)
{
	static unsigned numberOfPieces = 0;
	this->leftFather = nullptr;
	this->rightFather = nullptr;
	this->leftBrother = nullptr;
	this->rightBrother = nullptr;
	this->leftSon = nullptr;
	this->rightSon = nullptr;
	this->player = player;
	this->pieceId = ++numberOfPieces;
}


Chesspiece::~Chesspiece()
{
	
}

piecePoint Chesspiece::makeLeftSon(PLAYER player)
{
	piecePoint leftSon = new Chesspiece(player);
	leftSon->rightFather = this;
	this->leftSon = leftSon;
	return leftSon;
}

piecePoint Chesspiece::makeRightSon(PLAYER player)
{
	piecePoint rightSon = new Chesspiece(player);
	rightSon->leftFather = this;
	this->rightSon = rightSon;
	return rightSon;
}

void Chesspiece::linkSons()
{
	if (this->leftSon == nullptr || this->rightSon == nullptr) return;
	this->leftSon->rightBrother = this->rightSon;
	this->rightSon->leftBrother = this->leftSon;
}

void Chesspiece::linkLeftFather()
{
	if (this->rightFather == nullptr || this->rightFather->leftBrother == nullptr) return;
	this->leftFather = this->rightFather->leftBrother;
	this->leftFather->rightSon = this;
}

void Chesspiece::linkRightFather()
{
	if (this->leftFather == nullptr || this->leftFather->rightBrother == nullptr) return;
	this->rightFather = this->leftFather->rightBrother;
	this->rightFather->leftSon = this;
}

void Chesspiece::linkLeftBrother(piecePoint leftBrother)
{
	this->leftBrother = leftBrother;
	leftBrother->rightBrother = this;
}

piecePoint Chesspiece::getLeftFather()
{
	return this->leftFather;
}

piecePoint Chesspiece::getRightFather()
{
	return this->rightFather;
}

piecePoint Chesspiece::getLeftBrother()
{
	return this->leftBrother;
}

piecePoint Chesspiece::getRightBrother()
{
	return this->rightBrother;
}

piecePoint Chesspiece::getLeftSon()
{
	return this->leftSon;
}

piecePoint Chesspiece::getRightSon()
{
	return this->rightSon;
}

PLAYER Chesspiece::getPlayer()
{
	return this->player;
}

void Chesspiece::updatePlayer(PLAYER player)
{
	this->player = player;
}

unsigned Chesspiece::getPieceId()
{
	return this->pieceId;
}

void Chesspiece::updatePieceId(unsigned id)
{
	this->pieceId = id;
}
