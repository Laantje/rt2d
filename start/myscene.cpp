/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include <time.h>
#include "myscene.h"

RGBAColor colors[10] = { WHITE, GRAY, RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PINK, MAGENTA };

MyScene::MyScene() : SuperScene()
{
	t.start();

	text[0]->message("Tankgame prototype");

	text[4]->message("<Arrow keys> move tank");

	// add player
	player = new BasicEntity();
	player->addSprite("assets/player/tankstand.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	player->scale = Point2(0.5f, 0.5f);
	player->position = Point2(SWIDTH / 3, SHEIGHT / 2);

	// add enemy
	enemy = new BasicEntity();
	enemy->addSprite("assets/enemy/enemystand.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	enemy->scale = Point2(0.5f, 0.5f);
	enemy->position = Point2(SWIDTH / 3 * 2, SHEIGHT / 3 * 2);
	enemy->delay = 400;

	// add bullet
	bullet = new BasicEntity();

	// add shotsmoke
	smoke = new BasicEntity();

	// add explosion1
	explosion1 = new BasicEntity();

	// add explosion2
	explosion2 = new BasicEntity();

	// add explosion3
	explosion3 = new BasicEntity();

	// add hearts
	heart1 = new BasicEntity();
	heart1->addSprite("assets/hp/hp1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	heart1->scale = Point2(0.5f, 0.5f);
	heart1->position = Point2(SWIDTH / 25 * 20, SHEIGHT / 12);
	heart1->inUse = true;

	heart2 = new BasicEntity();
	heart2->addSprite("assets/hp/hp1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	heart2->scale = Point2(0.5f, 0.5f);
	heart2->position = Point2(SWIDTH / 25 * 22, SHEIGHT / 12);
	heart2->inUse = true;

	heart3 = new BasicEntity();
	heart3->addSprite("assets/hp/hp1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	heart3->scale = Point2(0.5f, 0.5f);
	heart3->position = Point2(SWIDTH / 25 * 24, SHEIGHT / 12);
	heart3->inUse = true;

	// bullet icon
	bicon = new BasicEntity();


	layers[3]->addChild(player);
	layers[4]->addChild(bullet);
	layers[3]->addChild(enemy);
	layers[5]->addChild(smoke);
	layers[6]->addChild(explosion1);
	layers[6]->addChild(explosion2);
	layers[6]->addChild(explosion3);
	layers[7]->addChild(heart1);
	layers[7]->addChild(heart2);
	layers[7]->addChild(heart3);
	layers[7]->addChild(bicon);
}


MyScene::~MyScene()
{
	layers[3]->removeChild(player);
	layers[4]->removeChild(bullet);
	layers[3]->removeChild(enemy);
	layers[5]->removeChild(smoke);
	layers[6]->removeChild(explosion1);
	layers[6]->removeChild(explosion2);
	layers[6]->removeChild(explosion3);
	layers[7]->removeChild(heart1);
	layers[7]->removeChild(heart2);
	layers[7]->removeChild(heart3);
	layers[7]->removeChild(bicon);

	delete player;
	delete bullet;
	delete enemy;
	delete smoke;
	delete explosion1;
	delete explosion2;
	delete explosion3;
	delete heart1;
	delete heart2;
	delete heart3;
	delete bicon;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	// ###############################################################
	// dynamic_line
	// ###############################################################
	/*if (t.seconds() >= 0.1f) {
		Line* line = dynamic_line->line();
		unsigned int s = line->points().size();
		for (unsigned int i = 1; i < s-1; i++) {
			float x = line->points()[i].x;
			line->editPoint(i, x, (rand()%100)-50);
		}
		t.start();
	}

	// ###############################################################
	// rt2d_line
	// ###############################################################
	rt2d_line->rotation += 90 * DEG_TO_RAD * deltaTime;
	if (rt2d_line->rotation > TWO_PI) { rt2d_line->rotation -= TWO_PI; }
	rt2d_line->scale.x = sin(rt2d_line->rotation);
	rt2d_line->scale.y = cos(rt2d_line->rotation);
	rt2d_line->line()->color = Color::rotate(rt2d_line->line()->color, deltaTime*2);

	// ###############################################################
	// default_line
	// ###############################################################
	static float s = 0.0f;
	s += 2 * deltaTime;
	if (s > TWO_PI) { s -= TWO_PI; }
	default_line->scale.x = sin(s);
	default_line->scale.y = cos(s);
	default_line->line()->color = Color::rotate(default_line->line()->color, deltaTime);

	// ###############################################################
	// spaceship
	// ###############################################################
	//this->updateSpaceShip(deltaTime);*/
	this->updateTank(deltaTime);
	this->updateBullet(deltaTime);
	this->updateHearts(deltaTime);
	this->updateEnemy(deltaTime);
}

void MyScene::updateTank(float deltaTime)
{
	player->delay++;

	if (player->isMoving) {
		if (player->tankSprite == 0 && player->delay >= 50) {
			player->addSprite("assets/player/tankride3.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
			player->tankSprite++;
			player->delay = 0;
		}
		else if (player->tankSprite == 1 && player->delay >= 50) {
			player->addSprite("assets/player/tankride2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
			player->tankSprite++;
			player->delay = 0;
		}
		else if (player->tankSprite == 2 && player->delay >= 50) {
			player->addSprite("assets/player/tankride1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
			player->tankSprite++;
			player->delay = 0;
		}
		else if (player->tankSprite == 3 && player->delay >= 50) {
			player->addSprite("assets/player/tankride2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
			player->tankSprite = 0;
			player->delay = 0;
		}
	}
	else {
		player->addSprite("assets/player/tankstand.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}

	if (input()->getKey( GLFW_KEY_UP )) {
		player->isMoving = true;
		player->rotation = 0 * DEG_TO_RAD;
		player->position.y -= 125 * deltaTime;
		player->facingUp = true;
		player->facingDown = false;
		player->facingLeft = false;
		player->facingRight = false;
	}
	else if (input()->getKey( GLFW_KEY_RIGHT )) {
		player->isMoving = true;
		player->rotation = 90 * DEG_TO_RAD;
		player->position.x += 125 * deltaTime;
		player->facingUp = false;
		player->facingDown = false;
		player->facingLeft = false;
		player->facingRight = true;
	}
	else if (input()->getKey( GLFW_KEY_LEFT )) {
		player->isMoving = true;
		player->rotation = 270 * DEG_TO_RAD;
		player->position.x -= 125 * deltaTime;
		player->facingUp = false;
		player->facingDown = false;
		player->facingLeft = true;
		player->facingRight = false;
	}
	else if (input()->getKey(GLFW_KEY_DOWN)) {
		player->isMoving = true;
		player->rotation = 180 * DEG_TO_RAD;
		player->position.y += 125 * deltaTime;
		player->facingUp = false;
		player->facingDown = true;
		player->facingLeft = false;
		player->facingRight = false;
	}
	else {
		player->isMoving = false;
	}

	if (input()->getKeyDown(GLFW_KEY_SPACE) && !player->reloading) {
		player->isShooting = true;
		player->shootDelay = 1250;
		smoke->tankSprite = 210;
		tankShoot();
	}
	else {
		player->isShooting = false;
	}

	if (player->position.x < 0) { player->position.x = SWIDTH; }
	if (player->position.x > SWIDTH) { player->position.x = 0; }
	if (player->position.y < 0) { player->position.y = SHEIGHT; }
	if (player->position.y > SHEIGHT) { player->position.y = 0; }
}

void MyScene::tankShoot()
{
	player->reloading = true;
	bullet->addSprite("assets/bullet/bullet.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	bullet->scale = Point2(0.06f, 0.06f);
	smoke->addSprite("assets/smoke/smoke1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	smoke->scale = Point2(0.3f, 0.3f);
	if (player->facingUp) {
		smoke->position = Point2(player->position.x + 1, player->position.y - 60);
		smoke->rotation = 0 * DEG_TO_RAD;
		bullet->position = Point2(player->position.x + 1, player->position.y - 56);
		bullet->shotUp = true;
		bullet->shotDown = false;
		bullet->shotLeft = false;
		bullet->shotRight = false;
	}
	else if(player->facingDown){
		smoke->position = Point2(player->position.x - 1, player->position.y + 60);
		smoke->rotation = 180 * DEG_TO_RAD;
		bullet->position = Point2(player->position.x - 1, player->position.y + 56);
		bullet->shotUp = false;
		bullet->shotDown = true;
		bullet->shotLeft = false;
		bullet->shotRight = false;
	}
	else if(player->facingLeft){
		smoke->position = Point2(player->position.x - 60, player->position.y - 1);
		smoke->rotation = 270 * DEG_TO_RAD;
		bullet->position = Point2(player->position.x - 56, player->position.y - 1);
		bullet->shotUp = false;
		bullet->shotDown = false;
		bullet->shotLeft = true;
		bullet->shotRight = false;
	}
	else if(player->facingRight){
		smoke->position = Point2(player->position.x + 60, player->position.y + 1);
		smoke->rotation = 90 * DEG_TO_RAD;
		bullet->position = Point2(player->position.x + 56, player->position.y + 1);
		bullet->shotUp = false;
		bullet->shotDown = false;
		bullet->shotLeft = false;
		bullet->shotRight = true;
	}
	
}
void MyScene::updateBullet(float deltaTime)
{
	if (player->reloading && player->isMoving && smoke->tankSprite > 0) {
		if (player->facingUp) {
			smoke->position = Point2(player->position.x + 1, player->position.y - 60);
			smoke->rotation = 0 * DEG_TO_RAD;
		}
		else if (player->facingDown) {
			smoke->position = Point2(player->position.x - 1, player->position.y + 60);
			smoke->rotation = 180 * DEG_TO_RAD;
		}
		else if (player->facingLeft) {
			smoke->position = Point2(player->position.x - 60, player->position.y - 1);
			smoke->rotation = 270 * DEG_TO_RAD;
		}
		else if (player->facingRight) {
			smoke->position = Point2(player->position.x + 60, player->position.y + 1);
			smoke->rotation = 90 * DEG_TO_RAD;
		}
	}
	if (smoke->tankSprite == 175) {
		smoke->addSprite("assets/smoke/smoke2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke->tankSprite == 140) {
		smoke->addSprite("assets/smoke/smoke3.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke->tankSprite == 105) {
		smoke->addSprite("assets/smoke/smoke4.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke->tankSprite == 70) {
		smoke->addSprite("assets/smoke/smoke5.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)	
	}
	if (smoke->tankSprite == 35) {
		smoke->addSprite("assets/smoke/smoke6.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke->tankSprite <= 0) {
		smoke->removeSprite();
	}
	if (smoke->tankSprite > 0) {
		smoke->tankSprite--;
	}
	if (player->reloading && player->shootDelay > 1150 && !player->isMoving) {
		player->addSprite("assets/player/tankshoot.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	} else if (player->reloading && player->shootDelay > 1150 && player->isMoving) {
		player->addSprite("assets/player/tankshootride.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	else if (!player->isMoving && player->shootDelay < 1150) {
		player->addSprite("assets/player/tankstand.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (player->shootDelay > 0) {
		player->shootDelay--;
	}
	if (player->reloading && player->shootDelay <= 0) {
		player->reloading = false;
	}
	if (player->reloading && bullet->shotUp) {
		bullet->position.y -= 1000 * deltaTime;
		if (bullet->position.y < 0) {
			bullet->removeSprite();
		}
	}
	else if (player->reloading && bullet->shotDown) {
		bullet->position.y += 1000 * deltaTime;
		if (bullet->position.y > SHEIGHT) {
			bullet->removeSprite();
		}
	}
	else if (player->reloading && bullet->shotLeft) {
		bullet->position.x -= 1000 * deltaTime;
		if (bullet->position.x < 0) {
			bullet->removeSprite();
		}
	}
	else if (player->reloading && bullet->shotRight) {
		bullet->position.x += 1000 * deltaTime;
		if (bullet->position.x > SWIDTH) {
			bullet->removeSprite();
		}
	}
}

void MyScene::updateHearts(float deltaTime)
{
	//IN USE SWITCH
	if (player->hp == 3) {
		heart1->inUse = true;
		heart2->inUse = true;
		heart3->inUse = true;
	}
	else if (player->hp == 2) {
		heart1->inUse = false;
		heart2->inUse = true;
		heart3->inUse = true;
	}
	else if (player->hp == 1) {
		heart1->inUse = false;
		heart2->inUse = false;
		heart3->inUse = true;
	}
	else if (player->hp == 0) {
		heart1->inUse = false;
		heart2->inUse = false;
		heart3->inUse = false;
	}

	//HPDELAY
	if (hpDelay > 0) {
		hpDelay--;
	}
	else if (hpDelay <= 0) {
		hpDelay = 815;
	}

	//MAKE HEART GREY WHEN HIT
	if (!heart1->inUse) {
		heart1->addSprite("assets/hp/hpDead.tga", 0.5f, 0.5f, 3, 0);
	}
	if (!heart2->inUse) {
		heart2->addSprite("assets/hp/hpDead.tga", 0.5f, 0.5f, 3, 0);
	}
	if (!heart3->inUse) {
		heart3->addSprite("assets/hp/hpDead.tga", 0.5f, 0.5f, 3, 0);
	}

	//ANIMATOR HEARTS
	if (hpDelay == 460) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 440) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 420) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp3.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp3.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp3.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 400) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp4.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp4.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp4.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 380) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp5.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp5.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp5.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 360) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp6.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp6.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp6.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 340) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp7.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp7.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp7.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 320) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp8.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp8.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp8.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 300) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp9.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp9.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp9.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 280) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp10.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp10.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp10.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 260) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp11.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp11.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp11.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 240) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp12.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp12.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp12.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 220) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp13.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp13.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp13.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 200) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp14.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp14.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp14.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 180) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp15.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp15.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp15.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 160) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp16.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp16.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp16.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 140) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp17.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp17.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp17.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 120) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp18.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp18.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp18.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 100) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp19.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp19.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp19.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 80) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp20.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp20.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp20.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 60) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp21.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp21.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp21.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 40) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp22.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp22.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp22.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
	if (hpDelay == 20) {
		if (heart1->inUse) {
			heart1->addSprite("assets/hp/hp23.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart2->inUse) {
			heart2->addSprite("assets/hp/hp23.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		if (heart3->inUse) {
			heart3->addSprite("assets/hp/hp23.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
	}
}

void MyScene::updateEnemy(float deltaTime)
{
	//Values for player searching
	enemy->UnderY = player->position.y - enemy->position.y;
	enemy->AboveY = enemy->position.y - player->position.y;
	
	//Delay controller
	if (enemy->delay > 0) {
		enemy->delay--;
		enemy->cpuLock = true;
	}
	else {
		enemy->cpuLock = false;
	}

	//Rotation Controller
	if (enemy->facingDown) {
		enemy->rotation = 180 * DEG_TO_RAD;
	}
	else if (enemy->facingUp) {
		enemy->rotation = 0 * DEG_TO_RAD;
	}
	else if (enemy->facingRight) {
		enemy->rotation = 90 * DEG_TO_RAD;
	}
	else if (enemy->facingLeft) {
		enemy->rotation = 270 * DEG_TO_RAD;
	}

	//y-axis player search
	if (!enemy->cpuLock && player->position.y < enemy->position.y) {
		if (enemy->AboveY <= 5) {
			enemy->delay = 150;
		}
		enemy->facingDown = false;
		enemy->facingUp = true;
		enemy->facingLeft = false;
		enemy->facingRight = false;
		enemy->position.y -= 100 * deltaTime;
	}
	else if (!enemy->cpuLock && player->position.y > enemy->position.y) {
		if (enemy->UnderY <= 5) {
			enemy->delay = 150;
		}
		enemy->facingDown = true;
		enemy->facingUp = false;
		enemy->facingLeft = false;
		enemy->facingRight = false;
		enemy->position.y += 100 * deltaTime;
	}
	else if (!enemy->cpuLock && enemy->UnderY <= 5 || !enemy->cpuLock && enemy->AboveY <= 5) {
		if (enemy->position.x > player->position.x) {
			enemy->facingDown = false;
			enemy->facingUp = false;
			enemy->facingLeft = true;
			enemy->facingRight = false;
			enemy->delay = 150;
		}
		else if (enemy->position.x < player->position.x) {
			enemy->facingDown = false;
			enemy->facingUp = false;
			enemy->facingLeft = false;
			enemy->facingRight = true;
			enemy->delay = 150;
		}
	}
}
