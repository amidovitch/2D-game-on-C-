#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<sstream>
#include"menu.h"
#include"map.h"
#include"Player.h"
#include<list>
#include"Enemy.h"
#include"Bullet.h"

using namespace sf;
using namespace std;

bool startGame(int& level, RenderWindow& window, Menu& menu, int& gameTime, int& score)
{	
	Font font; font.loadFromFile("font/fable.ttf");
	Text information("", font, 25); information.setColor(Color::Black);
	list<Moving*>  moving;//создаю список движущися объектов
	list<Moving*>::iterator it;//итератор чтобы проходить по эл-там списка
	Map map(moving, level);//создаем карту
	Player p(score, 60, 1100, 22, 48, "Player1", "boy.png");//создаем игрока
	Clock clock, gameTimeClock; int tempGameTime = 0;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		if(p.getHealth()>0) tempGameTime = gameTimeClock.getElapsedTime().asSeconds();
		p.setTimeForShot(p.getTimeForShot() + time);
		clock.restart();
		time = time / 800; 

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (p.getIsShot() == true)//создаем пули
			{
				moving.push_back(new Bullet(p.getX() + 8, p.getY() + 20, 16, 16, "Bullet", "bullet1.png", p.getDiraction()));
				p.setIsShot(false);
			}
		}
		p.checkCollisionWithMoving(moving, it, time);
		if(p.getHealth()>0) p.update(time);//обновляем игрока
		if (p.getNextLevel()) 
		{ 
			gameTime = tempGameTime;
			score += p.getScore();
			level++; 
			return true; 
		}
		for (it = moving.begin(); it != moving.end();)//обновляем движущиеся объекты
		{
			(*it)->update(time);
			if ((*it)->getHealth() <= 0)  it = moving.erase(it);
			else it++;
		}
		window.setView(p.getView());
		window.clear();

		ostringstream playerScoreString, playerHealthString, playerTimeString;
		playerScoreString << p.getScore(); playerHealthString << p.getHealth(); playerTimeString << (gameTime+tempGameTime);
		information.setString("Score:" + playerScoreString.str() + " Health:" + playerHealthString.str() + 
			" Time:" + playerTimeString.str());
		information.setPosition(p.getView().getCenter().x-400, p.getView().getCenter().y-230);
		
		if (p.getHealth() <= 0)
		{
			level = 1; score = 0; gameTime = 0;
			return menu.draw2(window, information, playerScoreString.str(), playerTimeString.str());
		}
		map.createMap(window);
		for (it = moving.begin(); it != moving.end(); it++) window.draw((*it)->getSprite());
		window.draw(information);
		window.draw(p.getSprite());
		window.display();	
	}
}


void gameRunning(int level, RenderWindow& window, Menu& menu, int& gameTime, int&score) 
{
	if (startGame(level, window, menu, gameTime, score)) 
	{ 
		window.setView(window.getDefaultView());
		if (menu.getIncl()) menu.draw1(window);
		gameRunning(level, window, menu, gameTime, score); 
	} 
}