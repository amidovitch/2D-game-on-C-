#pragma once
#include"Map.h"

class Platform : public Moving {
public:
	Platform(float , float , float , float , String , String );
	void update(float );
	void checkCollisionWithMap(float , float );
};