#include<SFML\Graphics.hpp>
#include <iostream>
#include"Bullet.h"

using namespace sf;
using namespace std;

	Bullet::Bullet(float X, float Y, float W, float H, String nameObject, String nameFile, int dir) :Moving(X, Y, W, H, nameObject, nameFile)
	{
		direction = dir;
		speed = -0.5;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void Bullet::update(float time)
	{
		switch (direction)
		{
		case 0: dx = speed = -0.5; break;
		case 1:  dx = speed = 0.5; break;
		}
		checkCollisionWithMap();
		x += dx*time;
		sprite.setPosition(x + w / 2, y + h / 2);
		if (x < 0) health = 0;
		if (x > 1600) health = 0;
		if (health <= 0) health = 0;
	}
	void Bullet::checkCollisionWithMap()
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (Map::getBlock(i, j) == '1' || Map::getBlock(i, j) == '2' ||
					Map::getBlock(i, j) == '3' || Map::getBlock(i, j) == '4' ||
					Map::getBlock(i, j) == '5' || Map::getBlock(i, j) == '6' ||
					Map::getBlock(i, j) == '7' || Map::getBlock(i, j) == '8' ||
					Map::getBlock(i, j) == '9' || Map::getBlock(i, j) == 'e')
				{
					health = 0;
				}
			}
	}
