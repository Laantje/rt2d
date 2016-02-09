/**
* This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
*
* - Copyright 2015 Rik Teerling <rik@onandoffables.com>
*     - Initial commit
* - Copyright 2015 Your Name <you@yourhost.com>
*     - What you did
*/

#include <time.h>
#include "enemy.h"
#include "level1.h"
#include "superscene.h"

Enemy::Enemy()
	: Entity()
{

}


Enemy::~Enemy()
{

}

void Enemy::update(float deltaTime)
{

	//Updates
	this->updateEnemy(deltaTime);
}

void Enemy::updateEnemy(float deltaTime)
{
	
}

void Enemy::enemyShoot()
{
	BasicEntity* b = new BasicEntity();
	if (!this->reloading) {
		smoke2->tankSprite = 210;
		this->shootDelay = 1250;
	}

	if (!this->reloading) {
		b->addSprite("assets/bullet/bullet.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		b->scale = Point2(0.06f, 0.06f);
		b->halfHeight = 6;
		b->halfWidth = 6;
		smoke2->addSprite("assets/smoke/smoke1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		smoke2->scale = Point2(0.3f, 0.3f);
	}

	if (this->facingUp && !this->reloading) {
		smoke2->position = Point2(this->position.x + 1, this->position.y - 57);
		smoke2->rotation = 0 * DEG_TO_RAD;
		b->position = Point2(this->position.x + 1, this->position.y - 56);
		b->shotUp = true;
		b->shotDown = false;
		b->shotLeft = false;
		b->shotRight = false;
	}
	else if (this->facingDown && !this->reloading) {
		smoke2->position = Point2(this->position.x - 1, this->position.y + 57);
		smoke2->rotation = 180 * DEG_TO_RAD;
		b->position = Point2(this->position.x - 1, this->position.y + 56);
		b->shotUp = false;
		b->shotDown = true;
		b->shotLeft = false;
		b->shotRight = false;
	}
	else if (this->facingLeft && !this->reloading) {
		smoke2->position = Point2(this->position.x - 57, this->position.y - 1);
		smoke2->rotation = 270 * DEG_TO_RAD;
		b->position = Point2(this->position.x - 56, this->position.y - 1);
		b->shotUp = false;
		b->shotDown = false;
		b->shotLeft = true;
		b->shotRight = false;
	}
	else if (this->facingRight && !this->reloading) {
		smoke2->position = Point2(this->position.x + 57, this->position.y + 1);
		smoke2->rotation = 90 * DEG_TO_RAD;
		b->position = Point2(this->position.x + 56, this->position.y + 1);
		b->shotUp = false;
		b->shotDown = false;
		b->shotLeft = false;
		b->shotRight = true;
	}
	if (!this->reloading) {
		this->reloading = true;
	}
	Level1::layers[]->addChild(s);
	Level1::layers[4]->addChild(b);
	Level1::bullets.push_back(b);
	enemysmoke.push_back->(s);
}
