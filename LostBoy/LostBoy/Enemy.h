#pragma once
#include"map.h"
#include"Moving.h"

class Enemy : public Moving
{
public:
	Enemy(float , float , float , float , string , string);
	void update(float );
	void checkCollisionWithMap(float , float);
};