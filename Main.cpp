#include"Game.h"
#include<iostream>
using namespace std;
int main()
{
	char IP[255];
	cout << "Please enter the ip of the server:";
	cin >> IP;
	Game* game = new Game(string(IP));
	game->startGame();
}