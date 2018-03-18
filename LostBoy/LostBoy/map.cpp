#include "Enemy.h"
#include "Platform.h"
	String* Map::MapOfBlocks;
	Map::~Map()
	{
		delete[] MapOfBlocks;
	}
	Map::Map() {};
	Map::Map(list<Moving*>& moving, int level)
	{
		MapOfBlocks = new String[WIDTH_MAP];
		char temp[51]; float x; float y; int amount;
		
		itoa(level, temp, 10); numberLevel = temp;
		ifstream in(numberLevel+".txt");
		if (!in) exit(1);
		int i = 0;
		while (i < HEIGHT_MAP) {//загрузка карты
			in.getline(temp, WIDTH_MAP + 2);
			MapOfBlocks[i] = temp;
			i++;
		}

		in >> temp;  amount= atoi(temp);//загрузка врагов 
		for (int i = 0; i < amount; i++)
		{
			in >> temp; x = atof(temp);
			in >> temp; y = atof(temp);
			moving.push_back((new Enemy(x, y, 32, 32, "EasyEnemy", "enemy.png")));
		}

		in >> temp; amount = atoi(temp);//загрузка горизонтальных платформ 
		for (int i = 0; i < amount; i++)
		{
			in >> temp; x = atof(temp);
			in >> temp; y = atof(temp);
			moving.push_back((new Platform(x, y, 96, 23, "gorizontPlatform", "platform" + numberLevel + ".png")));
		}

		in >> temp; amount = atoi(temp);//загрузка вертикальных платформ платформ 
		for (int i = 0; i < amount; i++)
		{
			in >> temp; x = atof(temp);
			in >> temp; y = atof(temp);
			moving.push_back((new Platform(x, y, 96, 23, "verticalPlatform", "platform" + numberLevel + ".png")));
		}
		in >> temp;
		in.close();
		size = 32;
		image_map.loadFromFile(temp);
		texture_map.loadFromImage(image_map);
		sprite_map.setTexture(texture_map);

		image_background.loadFromFile("images/Карты/BG"+numberLevel+".png");
		texture_background.loadFromImage(image_background);
		sprite_background.setTexture(texture_background);
	}
	void Map::createMap(RenderWindow & window)
	{
		window.draw(sprite_background);
		bool draw;
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				draw = false;
				if (MapOfBlocks[i][j] == '1') { sprite_map.setTextureRect(IntRect(0, 0, size, size)); draw = true; }
				if (MapOfBlocks[i][j] == '2') { sprite_map.setTextureRect(IntRect(size, 0, size, size)); draw = true; }
				if (MapOfBlocks[i][j] == '3') { sprite_map.setTextureRect(IntRect(size * 2, 0, size, size));  draw = true; }
				if (MapOfBlocks[i][j] == '4') { sprite_map.setTextureRect(IntRect(size * 3, 0, size, size));  draw = true; }
				if (MapOfBlocks[i][j] == '5') { sprite_map.setTextureRect(IntRect(size * 4, 0, size, size));  draw = true; }
				if (MapOfBlocks[i][j] == '6') { sprite_map.setTextureRect(IntRect(size * 5, 0, size, size));  draw = true; }
				if (MapOfBlocks[i][j] == '7') { sprite_map.setTextureRect(IntRect(size * 6, 0, size, size));  draw = true; }
				if (MapOfBlocks[i][j] == '8') { sprite_map.setTextureRect(IntRect(size * 7, 0, size, size));  draw = true; }
				if (MapOfBlocks[i][j] == '9') { sprite_map.setTextureRect(IntRect(size * 8, 0, size, size));  draw = true; }
				if (MapOfBlocks[i][j] == 'w') { sprite_map.setTextureRect(IntRect(size * 9, 0, size, size));  draw = true; }
				if (MapOfBlocks[i][j] == 'h') { sprite_map.setTextureRect(IntRect(size * 10, 0, size, size));  draw = true; }
				if (MapOfBlocks[i][j] == 'f') { sprite_map.setTextureRect(IntRect(size * 11, 0, size, size));  draw = true; }
				if (MapOfBlocks[i][j] == 's') { sprite_map.setTextureRect(IntRect(size * 12, 0, size, size));  draw = true; }
				if (MapOfBlocks[i][j] == 'l') { sprite_map.setTextureRect(IntRect(size * 13, 0, size, size));  draw = true; }
				if (MapOfBlocks[i][j] == 'i') { sprite_map.setTextureRect(IntRect(size * 14, 0, size, size));  draw = true; }
				sprite_map.setPosition(j * size, i * size);
				if (draw == true) window.draw(sprite_map);
			}
		return;
	}
	int Map::getSize()
	{
		return size;
	}
	char Map:: getBlock(int i, int j)
	{
		return  MapOfBlocks[i][j];
	}
	void Map:: setBlock(int i, int j, char a)
	{
		MapOfBlocks[i][j] = a;
	}

