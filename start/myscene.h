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

private:
	Timer t;

	BasicEntity* player;
	BasicEntity* bullet;
	BasicEntity* smoke;

	void updateTank(float deltaTime);
	void updateBullet(float deltaTime);
	void tankShoot();
};

#endif /* SCENE03_H */
