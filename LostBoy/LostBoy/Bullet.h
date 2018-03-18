#pragma once
#include"map.h"
#include"Moving.h"
class Bullet : public Moving
{
private:
	int direction;
public:
	Bullet(float, float, float, float, String, String, int);
	void update(float );
	void checkCollisionWithMap();
};