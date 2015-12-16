/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#ifndef BASICENTITY_H
#define BASICENTITY_H

#include <rt2d/entity.h>

class BasicEntity: public Entity
{
	public:
		BasicEntity();
		virtual ~BasicEntity();

		virtual void update(float deltaTime);

		bool isMoving = false;
		bool cpuLock = false;
		bool inUse = false;
		bool facingUp = true;
		bool facingDown = false;
		bool facingLeft = false;
		bool facingRight = false;
		bool shotUp = false;
		bool shotDown = false;
		bool shotLeft = false;
		bool shotRight = false;
		bool isShooting = false;
		bool reloading = false;
		int delay = 0;
		int shotDelay = 0;
		int tankSprite = 0;
		int shootDelay = 0;

	private:
};

#endif /* BASICENTITY_H */
