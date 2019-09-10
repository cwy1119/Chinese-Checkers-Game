#include "Game.h"
#include<iomanip>
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
using std::setw;
using std::left;

Game::Game()
{
}

Game::Game(string ip)
{
	this->board = new Board(4, 2);
	this->messager = new Messager(ip);
}

void Game::startGame()
{
	messager->connectServer();
	string data = messager->receiveMessage();
	cout << data << endl;
	if (data._Equal("接入成功! 正在匹配玩家二.."))
	{
		cout << messager->receiveMessage() << endl;
		board->setPieces();
		display(board);
		myMove();
	}
	else
	{
		board->setPieces();
		display(board);

	}
	while (true)
	{
		enemyMove();
		myMove();
	}

}


Game::~Game()
{
}

string Game::makeMessage(unsigned chosed, unsigned target)
{
	static char message[225];
	sprintf_s(message, 255, "%d#%d\0", chosed, target);
	string result;
	result.append(message);
	return result;

}

void Game::getOrder()
{
	cout << " Please choose the piece that you want to move:" << endl;
	cin >> chosed;
	while (!board->setChoice(chosed)) {
		cout << "Incorrect choice! Please choose another:" << endl;
		cin >> chosed;
	}
	board->setReachables(chosed);
	cout << " Please choose the place that you want to move to:" << endl;
	cin >> target;
}



void Game::myMove()
{

	this->getOrder();
	//board->setChoice(chosed);
	//board->setReachables(chosed);
	while (!board->movePiece(target))
	{
		cout << "You cann't reach this place! Please choose again:" << endl;
		this->getOrder();
	}
	display(board);
	messager->sendMessage(this->makeMessage(chosed, target));
}

void Game::enemyMove()
{
	cout << "Waiting for another player.." << endl;
	string data = messager->receiveMessage();
	sscanf_s(data.c_str(), "%u#%u", &chosed, &target);
	board->setChoice(chosed, false);
	board->setReachables(chosed);
	board->movePiece(target);
	display(board);
}


void Game::display(Board *board) {
	piecePoint temp;
	for (int i = 1; i <= 4; i++)
	{
		temp = board->getHead(i);
		for (int j = 0; j < 13 - i; j++)
			cout << "   ";
		while (temp != nullptr) {
			if (temp->getPlayer() == BLUE_PLAYER) cout << "▅ " << "   ";
			else if (temp->getPlayer() == RED_PLAYER) cout << "▼ " << "   ";
			else cout << "[] " << "   ";
			temp = temp->getRightBrother();
		}
		cout << endl;
		temp = board->getHead(i);
		for (int j = 0; j < 13 - i; j++)
			cout << "   ";
		while (temp != nullptr) {
			cout << left << setw(3) << temp->getPieceId() << "   ";
			temp = temp->getRightBrother();
		}
		cout << endl;

	}
	for (int i = 5; i <= 9; i++)
	{
		temp = board->getHead(i);
		for (int j = 0; j < i - 5; j++)
			cout << "   ";
		while (temp != nullptr) {
			if (temp->getPlayer() == BLUE_PLAYER) cout << "▅ " << "   ";
			else if (temp->getPlayer() == RED_PLAYER) cout << "▼ " << "   ";
			else cout << "[] " << "   ";
			temp = temp->getRightBrother();
		}
		cout << endl;
		temp = board->getHead(i);
		for (int j = 0; j < i - 5; j++)
			cout << "   ";
		while (temp != nullptr) {
			cout << left << setw(3) << temp->getPieceId() << "   ";
			temp = temp->getRightBrother();
		}
		cout << endl;

	}
	for (int i = 10; i <= 13; i++)
	{
		temp = board->getHead(i);
		for (int j = 0; j < 13 - i; j++)
			cout << "   ";
		while (temp != nullptr) {
			if (temp->getPlayer() == BLUE_PLAYER) cout << "▅ " << "   ";
			else if (temp->getPlayer() == RED_PLAYER) cout << "▼ " << "   ";
			else cout << "[] " << "   ";
			temp = temp->getRightBrother();
		}
		cout << endl;

		temp = board->getHead(i);
		for (int j = 0; j < 13 - i; j++)
			cout << "   ";
		while (temp != nullptr) {
			cout << left << setw(3) << temp->getPieceId() << "   ";
			temp = temp->getRightBrother();
		}
		cout << endl;
	}
	for (int i = 14; i <= 17; i++)
	{
		temp = board->getHead(i);
		for (int j = 0; j < i - 5; j++)
			cout << "   ";
		while (temp != nullptr) {
			if (temp->getPlayer() == BLUE_PLAYER) cout << "▅ " << "   ";
			else if (temp->getPlayer() == RED_PLAYER) cout << "▼ " << "   ";
			else cout << "[] " << "   ";
			temp = temp->getRightBrother();
		}
		cout << endl;
		temp = board->getHead(i);
		for (int j = 0; j < i - 5; j++)
			cout << "   ";
		while (temp != nullptr) {
			cout << left << setw(3) << temp->getPieceId() << "   ";
			temp = temp->getRightBrother();
		}
		cout << endl;
	}
}
