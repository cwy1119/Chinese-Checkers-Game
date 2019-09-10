#include "Board.h"

Board::Board()
{
	this->boardSize = 4;
	this->numberOfPlayers = 2;
	this->top = nullptr;
}

Board::Board(unsigned boardSize, unsigned numberOfPlayers)
{
	this->boardSize = boardSize;
	this->numberOfPlayers = numberOfPlayers;
	this->top = nullptr;
}


Board::~Board()
{
}

void Board::setPieces()
{
	tempHead = new Chesspiece(BLUE_PLAYER);
	this->top = tempHead;
	for (unsigned i = 0; i < 4; i++)
	{
		tempHead = this->makeNextLineMore(i < boardSize - 1 ? BLUE_PLAYER : EMPTY);
	}
	piecePoint tempTail = tempHead;
	while (tempTail->getRightBrother() != nullptr) {
		tempTail = tempTail->getRightBrother();
	}
	piecePoint temp;
	for (unsigned i = 0; i < 4; i++) {
		temp = new Chesspiece(EMPTY);
		tempHead->linkLeftBrother(temp);
		tempHead = temp;
		temp = new Chesspiece(EMPTY);
		temp->linkLeftBrother(tempTail);
		tempTail = temp;
	}
	temp = tempHead;
	for (unsigned i = (1 + boardSize)*boardSize / 2+1; temp != nullptr; i++)
	{
		temp->updatePieceId(i);
		temp = temp->getRightBrother();
	}
	for (unsigned i = 0; i < 4; i++)
	{
		tempHead = this->makeNextLineLess(EMPTY);
	}
	for (unsigned i = 0; i < 4; i++)
	{
		tempHead = this->makeNextLineMore(EMPTY);
	}
	for (unsigned i = 0; i < boardSize; i++) {
		tempHead = tempHead->getRightBrother();
	}
	for (unsigned i = 0; i < 4; i++)
	{
		tempHead = this->makeNextLineLess(boardSize,RED_PLAYER);
	}
	tempHead = this->top;
	
}

piecePoint Board::getHead(unsigned index)
{
	piecePoint head = this->top;
	for (unsigned i = 1; i < index; i++)
	{
		if (i == 3 * this->boardSize + 1) {
			for (unsigned j = 0; j < this->boardSize; j++)
			{
				head = head->getRightBrother();
			}
			head = head->getRightSon();
		}
		else if (head->getLeftSon() == nullptr) {
			head = head->getRightSon();
		}
		else if (i == this->boardSize) {
			head = head->getRightSon();
			returnHead(head);
		}
		else {
			head = head->getLeftSon();
		}
	}
	return head;
}

piecePoint Board::findPiece(unsigned pieceId)
{
	if (pieceId > (2 * boardSize + 1)*(2 * boardSize + 1) + 2 * boardSize*(boardSize + 1)) return false;
	piecePoint temp;
	for (int i = 1; i <= 4*boardSize+1; i++)
	{
		if (this->getHead(i + 1)->getPieceId() < pieceId) continue;
		temp = this->getHead(i);
		while (temp != nullptr&&temp->getPieceId()!=pieceId) {
			
			temp = temp->getRightBrother();
		}
		if (temp!=nullptr) return temp;
	}
	
	return nullptr;
}

void Board::setReachables(unsigned pieceId)
{
	//this->reachables.clear();
	piecePoint chose = findPiece(pieceId);
	piecePoint temp = chose;
	unsigned i = 0;
	while (temp->getLeftBrother() != nullptr&&temp->getLeftBrother()->getPlayer() == EMPTY) {
		temp = temp->getLeftBrother();
		i++;
	}
	if (temp->getLeftBrother() != nullptr) {
		temp = temp->getLeftBrother();
		while (temp->getLeftBrother() != nullptr&&temp->getLeftBrother()->getPlayer() == EMPTY&&i>0) {
			temp = temp->getLeftBrother();
			i--;
		}
		if (i == 0&& temp->getLeftBrother() != nullptr&&temp->getLeftBrother()->getPlayer() == EMPTY) {
			temp = temp->getLeftBrother();
			if (!this->hasReachables(temp->getPieceId())) {
				reachables.push_back(temp->getPieceId());
				setReachables(temp->getPieceId());
			}
		}
	}

	temp = chose;
	i = 0;
	while (temp->getRightBrother() != nullptr&&temp->getRightBrother()->getPlayer() == EMPTY) {
		temp = temp->getRightBrother();
		i++;
	}
	if (temp->getRightBrother() != nullptr) {
		temp = temp->getRightBrother();
		while (temp->getRightBrother() != nullptr&&temp->getRightBrother()->getPlayer() == EMPTY&&i>0) {
			temp = temp->getRightBrother();
			i--;
		}
		if (i == 0&& temp->getRightBrother() != nullptr&&temp->getRightBrother()->getPlayer() == EMPTY) {
			temp = temp->getRightBrother();
			if (!this->hasReachables(temp->getPieceId())) {
				reachables.push_back(temp->getPieceId());
				setReachables(temp->getPieceId());
			}
		}
	}

	temp = chose;
	i = 0;
	while (temp->getRightFather() != nullptr&&temp->getRightFather()->getPlayer() == EMPTY) {
		temp = temp->getRightFather();
		i++;
	}
	if (temp->getRightFather() != nullptr) {
		temp = temp->getRightFather();
		while (temp->getRightFather() != nullptr&&temp->getRightFather()->getPlayer() == EMPTY&&i>0) {
			temp = temp->getRightFather();
			i--;
		}
		if (i == 0&& temp->getRightFather() != nullptr&&temp->getRightFather()->getPlayer() == EMPTY) {
			temp = temp->getRightFather();
			if (!this->hasReachables(temp->getPieceId())) {
				reachables.push_back(temp->getPieceId());
				setReachables(temp->getPieceId());
			}
		}
	}

	temp = chose;
	i = 0;
	while (temp->getLeftFather() != nullptr&&temp->getLeftFather()->getPlayer() == EMPTY) {
		temp = temp->getLeftFather();
		i++;
	}
	if (temp->getLeftFather() != nullptr) {
		temp = temp->getLeftFather();
		while (temp->getLeftFather() != nullptr&&temp->getLeftFather()->getPlayer() == EMPTY&&i>0) {
			temp = temp->getLeftFather();
			i--;
		}
		if (i == 0&& temp->getLeftFather() != nullptr&&temp->getLeftFather()->getPlayer() == EMPTY) {
			temp = temp->getLeftFather();
			if (!this->hasReachables(temp->getPieceId())) {
				reachables.push_back(temp->getPieceId());
				setReachables(temp->getPieceId());
			}
		}
	}

	temp = chose;
	i = 0;
	while (temp->getLeftSon() != nullptr&&temp->getLeftSon()->getPlayer() == EMPTY) {
		temp = temp->getLeftSon();
		i++;
	}
	if (temp->getLeftSon() != nullptr) {
		temp = temp->getLeftSon();
		while (temp->getLeftSon() != nullptr&&temp->getLeftSon()->getPlayer() == EMPTY&&i>0) {
			temp = temp->getLeftSon();
			i--;
		}
		if (i == 0&& temp->getLeftSon() != nullptr&&temp->getLeftSon()->getPlayer() == EMPTY) {
			temp = temp->getLeftSon();
			if (!this->hasReachables(temp->getPieceId())) {
				reachables.push_back(temp->getPieceId());
				setReachables(temp->getPieceId());
			}
		}
	}

	temp = chose;
	i = 0;
	while (temp->getRightSon() != nullptr&&temp->getRightSon()->getPlayer() == EMPTY) {
		temp = temp->getRightSon();
		i++;
	}
	if (temp->getRightSon() != nullptr) {
		temp = temp->getRightSon();
		while (temp->getRightSon() != nullptr&&temp->getRightSon()->getPlayer() == EMPTY&&i>0) {
			temp = temp->getRightSon();
			i--;
		}
		if (i == 0 && temp->getRightSon() != nullptr&&temp->getRightSon()->getPlayer() == EMPTY) {
			temp = temp->getRightSon();
			if (!this->hasReachables(temp->getPieceId())) {
				reachables.push_back(temp->getPieceId());
				setReachables(temp->getPieceId());
			}
		}
	}

}

bool Board::hasReachables(unsigned pieceId)
{
	unsigned n = reachables.size();
	for (unsigned i = 0; i < n; i++) {
		if (pieceId == reachables[i]) return true;
	}
	return false;
}

bool Board::movePiece(unsigned pieceId)
{
	if (pieceChosed == nullptr||!hasReachables(pieceId)) return false;
	findPiece(pieceId)->updatePlayer(pieceChosed->getPlayer());
	pieceChosed->updatePlayer(EMPTY);
	return true;
}

bool Board::setChoice(unsigned pieceId,bool flag )
{
	piecePoint temp = findPiece(pieceId);
	if (temp == nullptr || (!flag&&temp->getPlayer()==EMPTY)||(flag&&temp->getPlayer() != RED_PLAYER)) return false;
	pieceChosed = temp;
	reachables.clear();
	return true;
}

piecePoint Board::makeNextLineMore(PLAYER player )
{
	tempHead->makeLeftSon(player);
	while (tempHead->getRightBrother() != nullptr) {
		tempHead->makeRightSon(player);
		tempHead->getRightSon()->linkRightFather();
		tempHead = tempHead->getRightBrother();
	 }
	tempHead->makeRightSon(player);
	
	while (tempHead->getLeftBrother() != nullptr) {
		tempHead->linkSons();
		tempHead = tempHead->getLeftBrother();
	}
	tempHead->linkSons();
	return tempHead->getLeftSon();
}

piecePoint Board::makeNextLineLess(PLAYER player)
{
	piecePoint topOfNextline;
	while (tempHead->getRightBrother() != nullptr) {
		tempHead->makeRightSon(player);
		tempHead->getRightSon()->linkRightFather();
		tempHead = tempHead->getRightBrother();
	}
	
	while (tempHead->getLeftBrother() != nullptr) {
		tempHead->linkSons();
		tempHead = tempHead->getLeftBrother();
	}
	tempHead->linkSons();
	return tempHead->getRightSon();
}

piecePoint Board::makeNextLineLess(int limit, PLAYER player)
{
	int i = 0;
	piecePoint topOfNextline;
	while (tempHead->getRightBrother() != nullptr&&i<limit) {
		tempHead->makeRightSon(player);
		tempHead->getRightSon()->linkRightFather();
		tempHead = tempHead->getRightBrother();
		i++;
	}
//	tempHead->linkSons();
	i = 0;
	while (tempHead->getLeftBrother() != nullptr&&i<limit) {
		tempHead->linkSons();
		tempHead = tempHead->getLeftBrother();
		i++;
	}

	return tempHead->getRightSon();
}

void Board::returnHead(piecePoint& head)
{
	while (head->getLeftBrother() != nullptr) {
		head = head->getLeftBrother();
	}
	
}
