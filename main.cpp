#include "Header.h"

int main()
{
	Ping_Pong game(40, 20); // instanciating game
	Menu(game);
	game.lets_ping_pong(::language); // playing
	return 0; // leaving
}