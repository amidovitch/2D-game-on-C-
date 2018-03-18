#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include<list>
#include "Enemy.h"
#include "Moving.h"
using namespace std;
using namespace sf;

class Map{
private:
	static String* MapOfBlocks;
	Image image_map, image_background;
	Texture texture_map, texture_background;
	Sprite sprite_map, sprite_background;
	string numberLevel;
	int size;
public:	
	~Map();
	Map();
	Map(list<Moving*>&, int );
	void createMap(RenderWindow & window);
	int getSize();
	static char getBlock(int , int );
	static void setBlock(int , int , char );
};	

