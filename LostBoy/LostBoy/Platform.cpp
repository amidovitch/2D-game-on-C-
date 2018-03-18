#include "Platform.h"
#include"Moving.h"
	Platform::Platform(float X, float Y, float W, float H, String nameObject, String nameFile) :Moving(X, Y, W, H, nameObject, nameFile)
	{
		dx = 0.07;
		dy = 0.07;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void Platform::update(float time)
	{
		if (name == "gorizontPlatform")
		{
			checkCollisionWithMap(dx, 0);
			x += dx*time;
			sprite.setPosition(x + w / 2, y + h / 2);
		}
		if (name == "verticalPlatform")
		{
			checkCollisionWithMap(0, dy);
			y += dy*time;
			sprite.setPosition(x + w / 2, y + h / 2);
		}
	}
	void Platform::checkCollisionWithMap(float DX, float DY)
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (Map::getBlock(i, j) == '|' || (Map::getBlock(i, j) > '0' && Map::getBlock(i, j) <= '9') || Map::getBlock(i, j) == 'h')
				{
					if (DX > 0) { x = j * 32 - w; dx *= -1; }
					if (DX < 0) { x = j * 32 + 32; dx *= -1; }
					if (DY > 0) { y = i * 32 - h; dy *= -1; }
					if (DY < 0) { y = i * 32 + 32; dy *= -1; }
				}
			}
	}
