#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<sstream>
using namespace sf;
using namespace std;

class Menu {
private:
	Texture menu1Texture[5], menuBgTexture, menu2Texture[3];
	Sprite menu1[5], menuBg, menu2[3];
	bool inclMenu;
public:
	Menu()
	{
		inclMenu = true;
		menuBgTexture.loadFromFile("images/Μενώ/Τξν.jpg"); menuBg.setTexture(menuBgTexture);
		for (int i = 0; i < 5; i++)
		{
			ostringstream temp;
			temp << i;
			menu1Texture[i].loadFromFile("images/Μενώ/" + temp.str() + "1.png");
			menu1[i].setTexture(menu1Texture[i]);
			if (i < 3)
			{
				menu2Texture[i].loadFromFile("images/Μενώ/" + temp.str() + "2.png");
				menu2[i].setTexture(menu2Texture[i]);
			}
		}
		menuBgTexture.loadFromFile("images/Μενώ/Τξν.jpg"); menuBg.setTexture(menuBgTexture);
	}
	void draw1(RenderWindow & window) 
	{ 
		float x = window.getView().getCenter().x;
		float y = window.getView().getCenter().y;
		bool isMenu = true;
		int number = 0;
		menu1[0].setPosition(140,y-195);
		menu1[1].setPosition(x-76,y-55);
		menu1[2].setPosition(x-95, y+25);
		menu1[3].setPosition(x - 73, y + 105);
		menu1[4].setPosition(x - 400, y -225);
		menuBg.setPosition(x-400, y-225);
		while (window.isOpen() && isMenu)
		{	
			Event event;
			while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
				}
			number = 0;
			menu1[1].setColor(Color::White);
			menu1[2].setColor(Color::White);
			menu1[3].setColor(Color::White);
			if (IntRect(324, 170, 152, 52).contains(Mouse::getPosition(window))) { menu1[1].setColor(Color::Blue); number = 1; }
			if (IntRect(305, 250, 191, 52).contains(Mouse::getPosition(window))) { menu1[2].setColor(Color::Blue); number = 2; }
			if (IntRect(327, 330, 155, 51).contains(Mouse::getPosition(window))) { menu1[3].setColor(Color::Blue); number = 3; }
		
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (number == 1) isMenu = false;
				if (number == 2) { window.draw(menu1[4]); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
				if (number == 3) { window.close(); isMenu = false; }
			}
			window.clear();
			window.draw(menuBg);
			for(int i=0; i<4; i++) window.draw(menu1[i]);
			window.display();
		}
		inclMenu = false;
	}
	bool draw2(RenderWindow & window, Text information, string score, string time)
	{	
		float x = window.getView().getCenter().x;
		float y = window.getView().getCenter().y;
		bool isMenu = true;
		int number = 0;
		information.setColor(Color(252,252, 92)); information.setCharacterSize(60); information.setStyle(Text::Bold);
		information.setString("Score:" + score + "  Time:" + time);
		information.setPosition(x-210, y-80);
		menu2[0].setPosition(x-250, y-170);
		menu2[1].setPosition(x-170, y+50);
		menu2[2].setPosition(x+100, y+50);
		menuBg.setPosition(x-400,y-225);

		while (window.isOpen() && isMenu)
		{	
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			number = 0;
			menu2[1].setColor(Color::White);
			menu2[2].setColor(Color::White);
			if (IntRect(230, 275, 64, 64).contains(Mouse::getPosition(window))) { menu2[1].setColor(Color::Blue); number = 1; }
			if (IntRect(500,275, 64, 64).contains(Mouse::getPosition(window))) { menu2[2].setColor(Color::Blue); number = 2; }
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (number == 1) return true;
				if (number == 2) { inclMenu = true; return true; }
			}
			
			window.clear();
			window.draw(menuBg);
			for (int i = 0; i<3; i++) window.draw(menu2[i]);
			window.draw(information);
			window.display();
		}
		return true;
	}
	bool getIncl()
	{
		return inclMenu;
	}
	void setIncl(bool a)
	{
		inclMenu = a;
	}
};