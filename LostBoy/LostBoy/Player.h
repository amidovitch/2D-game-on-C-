#pragma once
#include<SFML\Graphics.hpp>
#include <iostream>
#include"map.h"
#include"Moving.h"
using namespace sf;
using namespace std;

class Player : public Moving
{
private:
	bool onLadder, isShot, kickR, kickL, kickU, nextLevel;
	enum Dir {l, r, another} direction;
	int score;
	View view;
	float timeForShot;
public:
	Player(int, float , float , float , float , string, string );
	void control(float& );
	void update(float );
	void checkCollisionWithMap(float , float );
	void checkCollisionWithMoving(list<Moving*>&, list<Moving*>::iterator& , float );
	void setPlayerCoordinateForBorder(float , float );
	void setPlayerCoordinateForView(float , float );
	bool getIsShot();
	void setIsShot(bool );
	int getDiraction();
	View getView();
	bool getNextLevel();
	void setTimeForShot(float );
	float getTimeForShot();
	int getScore();
};
