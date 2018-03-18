#pragma once
#include<SFML\Graphics.hpp>
#include <iostream>
#include"map.h"
const int WIDTH_MAP = 50;
const int HEIGHT_MAP = 38;
using namespace sf;
using namespace std;

class Moving
{
protected:
	float x, y, w, h, dx, dy, speed, currentFrame;//координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	bool life, onGround;
	enum { left, right, up, down, jump, stay } state; // состояния объекта
	int health;
	string name; 
	Image image;
	Texture texture;
	Sprite sprite;
public:
	Moving(float X, float Y, float W, float H, string nameObject, string nameFile)
	{
		x = X; y = Y;
		dx = 0; dy = 0; speed = 0; health = 100; w = W, h = H; currentFrame = 0;
		life = true; onGround = false; state = stay;
		name = nameObject;
		image.loadFromFile("images/" + nameFile);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
	void virtual update(float time) = 0 ;
	Sprite getSprite()
	{
		return sprite;
	}
	void setSprite(Sprite spr)
	{
		sprite = spr;
	}
	
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
	String getName()
	{
		return name;
	}
	float getDY()
	{
		return dy;
	}
	float getDX()
	{
		return dx;
	}
	void setDX(float a)
	{
		dx=a;
	}
	void setHealth(int a)
	{
		health = a;
	}
	int getHealth()
	{
		return health;
	}
	float getH()
	{
		return h;
	}
	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}
};
