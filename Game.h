#ifndef GAME_H
#define GAME_H
#include"Board.h"
#include"Messager.h"

class Game
{
public:
	Game();
	Game(string ip);
	void startGame();
	~Game();
private:
	Board* board;
	Messager* messager;
	unsigned chosed;
	unsigned target;
	//string serverIP;
	string makeMessage(unsigned chosed, unsigned target);
	void getOrder();
	void display(Board* board);
	void myMove();
	void enemyMove();
};

#endif