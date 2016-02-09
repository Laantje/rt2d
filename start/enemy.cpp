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

Enemy::Enemy(): Entity()
{
	//Add iterator enemy smokes
	std::vector<BasicEntity*> enemysmokes;
}


Enemy::~Enemy()
{

}

void Enemy::update(float deltaTime)
{

	//Updates
	this->updateEnemy(deltaTime);
	this->updateSmokes(deltaTime);
}

void Enemy::updateEnemy(float deltaTime)
{
	
}

void Enemy::updateSmokes(float deltaTime)
{

}

void Enemy::enemyShoot()
{
	BasicEntity* b = new BasicEntity();
	BasicEntity* s = new BasicEntity();
	if (!this->reloading) {
		b->addSprite("assets/bullet/bullet.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		b->scale = Point2(0.06f, 0.06f);
		b->halfHeight = 6;
		b->halfWidth = 6;
		this->shootDelay = 1250;
		s->tankSprite = 210;
		s->addSprite("assets/smoke/smoke1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		s->scale = Point2(0.3f, 0.3f);
	}

	if (this->facingUp && !this->reloading) {
		s->position = Point2(this->position.x + 1, this->position.y - 57);
		s->rotation = 0 * DEG_TO_RAD;
		b->position = Point2(this->position.x + 1, this->position.y - 56);
		b->shotUp = true;
		b->shotDown = false;
		b->shotLeft = false;
		b->shotRight = false;
	}
	else if (this->facingDown && !this->reloading) {
		s->position = Point2(this->position.x - 1, this->position.y + 57);
		s->rotation = 180 * DEG_TO_RAD;
		b->position = Point2(this->position.x - 1, this->position.y + 56);
		b->shotUp = false;
		b->shotDown = true;
		b->shotLeft = false;
		b->shotRight = false;
	}
	else if (this->facingLeft && !this->reloading) {
		s->position = Point2(this->position.x - 57, this->position.y - 1);
		s->rotation = 270 * DEG_TO_RAD;
		b->position = Point2(this->position.x - 56, this->position.y - 1);
		b->shotUp = false;
		b->shotDown = false;
		b->shotLeft = true;
		b->shotRight = false;
	}
	else if (this->facingRight && !this->reloading) {
		s->position = Point2(this->position.x + 57, this->position.y + 1);
		s->rotation = 90 * DEG_TO_RAD;
		b->position = Point2(this->position.x + 56, this->position.y + 1);
		b->shotUp = false;
		b->shotDown = false;
		b->shotLeft = false;
		b->shotRight = true;
	}
	if (!this->reloading) {
		this->reloading = true;
	}
	Level1::layers[5]->addChild(s);
	Level1::layers[4]->addChild(b);
	Level1::bullets.push_back(b);
	enemysmokes.push_back(s);
}
