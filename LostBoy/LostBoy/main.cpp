#include"Game.h"
#include <SFML/Graphics.hpp>
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 450), "Lost Boy");
	Menu menu;
	menu.draw1(window);
	int level = 1, score = 0, gameTime = 0;
	gameRunning(level, window, menu, gameTime, score);	
	return 0;
}