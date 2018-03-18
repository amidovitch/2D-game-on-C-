#include<SFML\Graphics.hpp>
#include"Enemy.h"
#include <iostream>
using namespace sf;
using namespace std;

	Enemy::Enemy(float X, float Y, float W, float H, string nameObject, string nameFile) :Moving(X, Y, W, H, nameObject, nameFile)
	{
		state = stay;
		if (name == "EasyEnemy")
		{
			sprite.setTextureRect(IntRect(0, 64, w, h));
			dx = 0.08;
		}
	}
	void Enemy::update(float time)
	{
		if (name == "EasyEnemy")
		{
			checkCollisionWithMap(dx, 0);
			x += dx*time;

			currentFrame += 0.005*time;
			if (currentFrame > 3) currentFrame = 0;
			sprite.setTextureRect(IntRect(32 * int(currentFrame), 64, 32, 32));
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) life = false;
		}
	}
	void Enemy::checkCollisionWithMap(float DX, float DY)
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (Map::getBlock(i, j) == '|' || Map::getBlock(i, j) == '5')
				{
					if (DX > 0) { x = j * 32 - w; dx = -0.1; sprite.scale(-1, 1); }
					if (DX < 0) { x = j * 32 + 32; dx = 0.1; sprite.scale(-1, 1); }
				}
			}
	}
