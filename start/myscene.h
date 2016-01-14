/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#ifndef SCENE03_H
#define SCENE03_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class MyScene: public SuperScene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltaTime);

	int hpDelay = 815;

private:
	Timer t;
	
	//player
	BasicEntity* player;

	//items
	BasicEntity* bullet;
	BasicEntity* bullet2;
	BasicEntity* bicon;
	BasicEntity* heart1;
	BasicEntity* heart2;
	BasicEntity* heart3;
	
	//enemies
	BasicEntity* enemy;
	
	//particles
	BasicEntity* smoke1;
	BasicEntity* smoke2;
	BasicEntity* explosion1;
	BasicEntity* explosion2;
	BasicEntity* explosion3;

	//vector
	std::vector<BasicEntity*> bullets;

	//functions
	void updateTank(float deltaTime);
	void updateBullet(float deltaTime);
	void updateEnemy(float deltaTime);
	void updateExplosions(float deltaTime);
	void updateHearts(float deltaTime);
	void tankShoot();
	void enemyShoot();
};

#endif /* SCENE03_H */
