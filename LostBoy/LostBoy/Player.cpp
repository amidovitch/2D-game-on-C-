#include"Player.h"

Player::Player(int Score,float X, float Y, float W, float H, string nameObject, string nameFile) : Moving(X, Y, W, H, nameObject, nameFile)
	{
		timeForShot = 0;
		direction = r;
		onLadder = isShot = kickR = kickL = kickU = nextLevel = false;
		view.reset(FloatRect(0, 0, 800, 450));
		score = Score;
		if (name == "Player1") sprite.setTextureRect(IntRect(0, 96, w, h));
	}
	void Player::control(float& time)
	{
		if ((Keyboard::isKeyPressed(Keyboard::D)))
		{
			direction = r;
			speed = 0.2;
			state = right;
			currentFrame += 0.007*time;
			if (currentFrame > 4) currentFrame = 0;
			sprite.setTextureRect(IntRect(w * int(currentFrame), 96, w, h));
		}
		else if ((Keyboard::isKeyPressed(Keyboard::S)))
		{
			direction = another;
			if (onLadder)
			{
				speed = 0.1;
				state = down;
				currentFrame += 0.007*time;
				if (currentFrame > 4) currentFrame = 0;
				sprite.setTextureRect(IntRect(32 * int(currentFrame), 144, 32, 48));
			}
			else {
				onLadder = false; state = jump;
			}
		}
		else if ((Keyboard::isKeyPressed(Keyboard::A)))
		{
			direction = l;
			speed = 0.2; state = left;
			currentFrame += 0.007*time;
			if (currentFrame > 4) currentFrame = 0;
			sprite.setTextureRect(IntRect(w * int(currentFrame), 48, w, h));
		}
		if ((Keyboard::isKeyPressed(Keyboard::W)))
		{
			if (onGround &&!onLadder)
			{
				state = jump;
				dy = -0.45;
				onGround = false;
			}
			if (onLadder&& !(Keyboard::isKeyPressed(Keyboard::A)) && !(Keyboard::isKeyPressed(Keyboard::D)))
			{
				direction = another;
				state = up;
				speed = -0.1;
				currentFrame += 0.007*time;
				if (currentFrame > 4) currentFrame = 0;
				sprite.setTextureRect(IntRect(32 * int(currentFrame), 144, 32, 48));
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Space) && timeForShot>1000000 && direction!=2)
		{
			isShot = true;
			timeForShot = 0;
		}
		onLadder = false; onGround = false;
	}
	void Player::update(float time)
	{
		control(time);
		switch (state)
		{
		case right: dx = speed;  break;
		case left:dx = -speed;  break;
		case  up:  dy = speed;  break;
		case down: dy = speed;  break;
		case jump: break;
		case stay:dx = 0; break;
		}
		if (kickU) { dy = -0.3; kickU = false; }
		if (kickR) { dx = 0.3; }if (kickL) { dx = -0.3; }
		if (dy>0) { kickR = 0; kickL = 0; }

		x += dx*time;
		checkCollisionWithMap(dx, 0);

		y += dy*time;
		checkCollisionWithMap(0, dy);
		setPlayerCoordinateForBorder(x, y);
		sprite.setPosition(x + w / 2, y + h / 2);
		if (health <= 0) life = false;
		if (!onLadder) dy = dy + 0.0015*time;
		setPlayerCoordinateForView(x, y);
		speed = 0;

	}
	void Player::checkCollisionWithMap(float DX, float DY)
	{
		int size = 32;
		for (int i = y / size; i < (y + h) / size; i++)
		{
			for (int j = x / size; j < (x + w) / size; j++)
			{
				//cout << "x=" << x << "y=" << y << "DX=" << DX << "DY=" << DY << "state=" << state << "  OnG=" << onGround << "  OnL=" << onLadder << endl;
				if (Map::getBlock(i, j) == '1' || Map::getBlock(i, j) == '2' ||
					Map::getBlock(i, j) == '3' || Map::getBlock(i, j) == '4' ||
					Map::getBlock(i, j) == '5' || Map::getBlock(i, j) == '6' ||
					Map::getBlock(i, j) == '7' || Map::getBlock(i, j) == '8' ||
					Map::getBlock(i, j) == '9')
				{
					if (DY > 0) { y = i * size - h; dy = 0; onGround = true; }
					if (DY < 0) { y = i *size + 32; dy = 0; }
					if (DX > 0) { x = j * size - w; }
					if (DX < 0) { x = j * size + 32; }
				}
				if (Map::getBlock(i, j) == 'l')
				{
					if (DY > 0 || DY < 0)
					{
						dy = 0; dx = 0;
					}
					onLadder = true;
					onGround = true;
				}
				if (Map::getBlock(i, j) == 'i')
				{
					Map::setBlock(i, j, ' ');
					score++;
				}
				if (Map::getBlock(i, j) == 'h')
				{
					dy = -0.5;
					health -= 10;
				}
				if (Map::getBlock(i, j) == 'f')
				{
					nextLevel = true;
				}
			}
		}
	}
	void Player::checkCollisionWithMoving(list<Moving*>& movingList, list<Moving*>::iterator& mIt, float time)
	{
		list<Moving*>::iterator it = movingList.begin();
		for (mIt = movingList.begin(); mIt != movingList.end(); mIt++)
		{
			if ((*mIt)->getRect().intersects(getRect()))
			{
				if ((*mIt)->getName() == "EasyEnemy")
				{
					if ((y + h / 2 - 1 < (*mIt)->getY() - (*mIt)->getH() / 2) && dy>0)//если прыгнул на враза сверху
					{
						(*mIt)->setDX(0);
						dy = -0.2;
						(*mIt)->setHealth(0);
					}
					if ((*mIt)->getDX() > 0)
					{
						Sprite sprt = (*mIt)->getSprite();
						sprt.scale(-1, 1);
						(*mIt)->setSprite(sprt);
						if (!kickL)kickR = true; kickU = true;
						(*mIt)->setDX(-1 * (*mIt)->getDX());
						health -= 5;
					}
					else if ((*mIt)->getDX() < 0)
					{
						Sprite sprt = (*mIt)->getSprite();
						sprt.scale(-1, 1);
						(*mIt)->setSprite(sprt);
						if (!kickR) kickL = true; kickU = true;
						(*mIt)->setDX(-1 * ((*mIt)->getDX()));
						health -= 5;
					}
				}
				if ((*mIt)->getName() == "gorizontPlatform" && (y + h / 2 - 1 < (*mIt)->getY() - (*mIt)->getH() / 2) && dy>0)
				{
					y = (*mIt)->getY() - h;
					x += (*mIt)->getDX()*time;
					speed = 0; dy = 0;
					onGround = true;
				}
				if ((*mIt)->getName() == "verticalPlatform" && (y + h / 2 - 1 < (*mIt)->getY() - (*mIt)->getH() / 2) && dy>0)
				{
					y = (*mIt)->getY() - h + 1;
					//y += (*mIt)->getDY()*time;
					speed = 0; dy = 0;
					onGround = true;
				}

			}
			if ((*mIt)->getName() == "EasyEnemy")
			{
				it = mIt;
				for (it; it != movingList.end(); it++)
				{
					if ((*mIt)->getRect().intersects((*it)->getRect()) && (*it)->getName() == "Bullet")
					{
						(*mIt)->setHealth(0);
						(*it)->setHealth(0);
					}
				}
			}
		}
	}
	void Player::setPlayerCoordinateForBorder(float X, float Y)
	{
		if (X < 32) { x = 32; dx = 0; onGround = true; }
		if (Y < 1) y = 1;
		if (Y > 1215) y = 1215;
		if (X > 1576) { x = 1576; dx = 0; }
	}
	void Player::setPlayerCoordinateForView(float x, float y)
	{
		float tempX = x; float tempY = y;
		if (x <432) tempX = 432;
		if (y < 223) tempY = 223;
		if (y > 980) tempY = 980;
		if (x > 1200) tempX = 1200;
		view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты. 
	}
	bool Player::getIsShot()
	{
		return isShot;
	}
	void Player::setIsShot(bool a)
	{
		isShot = a;
	}
	int Player::getDiraction()
	{
		return direction;
	}
	View Player::getView()
	{
		return view;
	}
	bool Player::getNextLevel()
	{
		return nextLevel;
	}
	void Player::setTimeForShot(float time)
	{
		timeForShot = time;
	}
	float Player::getTimeForShot()
	{
		return timeForShot;
	}
	int Player::getScore()
	{
		return score;
	}
