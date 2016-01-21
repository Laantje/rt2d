/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include <time.h>
#include "level1.h"

RGBAColor colors[10] = { WHITE, GRAY, RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PINK, MAGENTA };

Level1::Level1() : SuperScene()
{

	t.start();

	text[0]->message("Tankgame prototype");

	text[4]->message("<Arrow keys> move tank");

	// add player
	player = new BasicEntity();
	player->addSprite("assets/player/tankstand.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	player->scale = Point2(0.4f, 0.4f);
	player->position = Point2(SWIDTH / 4 * 2, SHEIGHT / 3);
	player->halfHeight = 32;
	player->halfWidth = 35;
	

	// add enemies
	std::vector<BasicEntity*> enemies;
	enemy = new BasicEntity();
	enemy->addSprite("assets/enemy/enemystand.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	enemy->scale = Point2(0.4f, 0.4f);
	enemy->position = Point2(SWIDTH / 3 * 2, SHEIGHT / 3 * 2);
	enemy->delay = 400;

	// add bullets
	std::vector<BasicEntity*> bullets;

	// add shotsmokes
	std::vector<BasicEntity*> smokes;
	smoke1 = new BasicEntity();
	smoke2 = new BasicEntity();

	// add explosions
	std::vector<BasicEntity*> explosions;

	// add hearts
	heart1 = new BasicEntity();
	heart1->addSprite("assets/hp/hp1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	heart1->scale = Point2(0.5f, 0.5f);
	heart1->position = Point2(SWIDTH / 30 * 24, SHEIGHT / 12);
	heart1->inUse = true;

	heart2 = new BasicEntity();
	heart2->addSprite("assets/hp/hp1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	heart2->scale = Point2(0.5f, 0.5f);
	heart2->position = Point2(SWIDTH / 30 * 26, SHEIGHT / 12);
	heart2->inUse = true;

	heart3 = new BasicEntity();
	heart3->addSprite("assets/hp/hp1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	heart3->scale = Point2(0.5f, 0.5f);
	heart3->position = Point2(SWIDTH / 30 * 28, SHEIGHT / 12);
	heart3->inUse = true;

	// bullet icon
	bicon = new BasicEntity();
	bicon->addSprite("assets/bullet/bulletsicon.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	bicon->scale = Point2(0.5f, 0.5f);
	bicon->position = Point2(SWIDTH / 30 * 26, SHEIGHT / 11 * 2);


	layers[3]->addChild(player);
	layers[3]->addChild(enemy);
	layers[5]->addChild(smoke1);
	layers[5]->addChild(smoke2);
	layers[7]->addChild(heart1);
	layers[7]->addChild(heart2);
	layers[7]->addChild(heart3);
	layers[7]->addChild(bicon);
}


Level1::~Level1()
{
	layers[3]->removeChild(player);
	layers[3]->removeChild(enemy);
	layers[5]->removeChild(smoke1);
	layers[5]->removeChild(smoke2);
	layers[7]->removeChild(heart1);
	layers[7]->removeChild(heart2);
	layers[7]->removeChild(heart3);
	layers[7]->removeChild(bicon);

	//Delete bullets
	for (int i = 0; i < bullets.size(); i++) {
		delete bullets[i]; // delete Bullet from the heap (a pointer to it is still in the list)
		bullets[i] = NULL; // set Bullet pointer to NULL (don't try to remove it from the list)
	}
	bullets.clear(); // list contains only NULL pointers. Make the list empty with 1 command.

	//Delete enemies
	for (int i = 0; i < enemies.size(); i++) {
		delete enemies[i]; // delete Bullet from the heap (a pointer to it is still in the list)
		enemies[i] = NULL; // set Bullet pointer to NULL (don't try to remove it from the list)
	}
	enemies.clear(); // list contains only NULL pointers. Make the list empty with 1 command.

	//Delete explosions
	for (int i = 0; i < explosions.size(); i++) {
		delete explosions[i]; // delete Bullet from the heap (a pointer to it is still in the list)
		explosions[i] = NULL; // set Bullet pointer to NULL (don't try to remove it from the list)
	}
	explosions.clear(); // list contains only NULL pointers. Make the list empty with 1 command.

	//Delete smokes
	for (int i = 0; i < smokes.size(); i++) {
		delete smokes[i]; // delete Bullet from the heap (a pointer to it is still in the list)
		smokes[i] = NULL; // set Bullet pointer to NULL (don't try to remove it from the list)
	}
	smokes.clear(); // list contains only NULL pointers. Make the list empty with 1 command.

	delete player;
	delete enemy;
	delete smoke1;
	delete smoke2;
	delete heart1;
	delete heart2;
	delete heart3;
	delete bicon;
}

void Level1::update(float deltaTime)
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
	this->updateExplosions(deltaTime);
}

void Level1::updateTank(float deltaTime)
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
	else if (!player->isMoving && !player->isHit) {
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
		smoke1->tankSprite = 210;
		tankShoot();
	}
	else {
		player->isShooting = false;
	}

	//Collisions
	player->eLeft = player->position.x - player->halfWidth;
	player->eRight = player->position.x + player->halfWidth;
	player->eTop = player->position.y - player->halfHeight;
	player->eBottom = player->position.y + player->halfHeight;

	//Hit detection
	if (player->isHit && player->hitDelay > 0 && player->isMoving) {
		player->addSprite("assets/player/tankridehit.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	else if (player->isHit && player->hitDelay > 0 && !player->isMoving) {
		player->addSprite("assets/player/tankhit.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	
	if (player->hitDelay > 0) {
		player->hitDelay--;
	}
	else if (player->hitDelay <= 0) {
		player->isHit = false;
	}

	if (player->position.x < 0) { player->position.x = SWIDTH; }
	if (player->position.x > SWIDTH) { player->position.x = 0; }
	if (player->position.y < 0) { player->position.y = SHEIGHT; }
	if (player->position.y > SHEIGHT) { player->position.y = 0; }
}

void Level1::tankShoot()
{
	player->reloading = true;
	BasicEntity* b = new BasicEntity();
	b->addSprite("assets/bullet/bullet.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	b->scale = Point2(0.06f, 0.06f);
	b->halfHeight = 6;
	b->halfWidth = 6;
	smoke1->addSprite("assets/smoke/smoke1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	smoke1->scale = Point2(0.3f, 0.3f);
	if (player->facingUp) {
		smoke1->position = Point2(player->position.x + 1, player->position.y - 57);
		smoke1->rotation = 0 * DEG_TO_RAD;
		b->position = Point2(player->position.x + 1, player->position.y - 56);
		b->shotUp = true;
		b->shotDown = false;
		b->shotLeft = false;
		b->shotRight = false;
	}
	else if(player->facingDown){
		smoke1->position = Point2(player->position.x - 1, player->position.y + 57);
		smoke1->rotation = 180 * DEG_TO_RAD;
		b->position = Point2(player->position.x - 1, player->position.y + 56);
		b->shotUp = false;
		b->shotDown = true;
		b->shotLeft = false;
		b->shotRight = false;
	}
	else if(player->facingLeft){
		smoke1->position = Point2(player->position.x - 57, player->position.y - 1);
		smoke1->rotation = 270 * DEG_TO_RAD;
		b->position = Point2(player->position.x - 56, player->position.y - 1);
		b->shotUp = false;
		b->shotDown = false;
		b->shotLeft = true;
		b->shotRight = false;
	}
	else if(player->facingRight){
		smoke1->position = Point2(player->position.x + 57, player->position.y + 1);
		smoke1->rotation = 90 * DEG_TO_RAD;
		b->position = Point2(player->position.x + 56, player->position.y + 1);
		b->shotUp = false;
		b->shotDown = false;
		b->shotLeft = false;
		b->shotRight = true;
	}
	layers[4]->addChild(b);
	bullets.push_back(b);
}

void Level1::updateBullet(float deltaTime)
{
	if (player->reloading && player->isMoving && smoke1->tankSprite > 0) {
		if (player->facingUp) {
			smoke1->position = Point2(player->position.x + 1, player->position.y - 60);
			smoke1->rotation = 0 * DEG_TO_RAD;
		}
		else if (player->facingDown) {
			smoke1->position = Point2(player->position.x - 1, player->position.y + 60);
			smoke1->rotation = 180 * DEG_TO_RAD;
		}
		else if (player->facingLeft) {
			smoke1->position = Point2(player->position.x - 60, player->position.y - 1);
			smoke1->rotation = 270 * DEG_TO_RAD;
		}
		else if (player->facingRight) {
			smoke1->position = Point2(player->position.x + 60, player->position.y + 1);
			smoke1->rotation = 90 * DEG_TO_RAD;
		}
	}
	if (smoke1->tankSprite == 175) {
		smoke1->addSprite("assets/smoke/smoke2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke1->tankSprite == 140) {
		smoke1->addSprite("assets/smoke/smoke3.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke1->tankSprite == 105) {
		smoke1->addSprite("assets/smoke/smoke4.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke1->tankSprite == 70) {
		smoke1->addSprite("assets/smoke/smoke5.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)	
	}
	if (smoke1->tankSprite == 35) {
		smoke1->addSprite("assets/smoke/smoke6.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke1->tankSprite <= 0) {
		smoke1->removeSprite();
	}
	if (smoke1->tankSprite > 0) {
		smoke1->tankSprite--;
	}
	if (player->reloading && player->shootDelay > 1150 && !player->isMoving) {
		player->addSprite("assets/player/tankshoot.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	} else if (player->reloading && player->shootDelay > 1150 && player->isMoving) {
		player->addSprite("assets/player/tankshootride.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	else if (!player->isMoving && player->shootDelay < 1150 && player->reloading) {
		player->addSprite("assets/player/tankstand.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (player->shootDelay > 0) {
		player->shootDelay--;
	}
	if (player->reloading && player->shootDelay <= 0) {
		player->reloading = false;
	}
	/*if (player->reloading && bullet->shotUp) {
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
	}*/

	//Bullet iterator
	std::vector<BasicEntity*>::iterator it = bullets.begin(); // get the 'iterator' from the list.
	while (it != bullets.end()) {
		(*it)->eLeft = (*it)->position.x - (*it)->halfWidth;
		(*it)->eRight = (*it)->position.x + (*it)->halfWidth;
		(*it)->eTop = (*it)->position.y - (*it)->halfHeight;
		(*it)->eBottom = (*it)->position.y + (*it)->halfHeight;

		if ((*it)->shotUp) {
			(*it)->position.y -= 1000 * deltaTime;
		}
		else if ((*it)->shotDown) {
			(*it)->position.y += 1000 * deltaTime;
		}
		else if ((*it)->shotLeft) {
			(*it)->position.x -= 1000 * deltaTime;
		}
		else if ((*it)->shotRight) {
			(*it)->position.x += 1000 * deltaTime;
		}

		if ((*it)->position.y < 0 && (*it)->shotUp) {
			layers[4]->removeChild(*it);
			delete (*it); // delete the Bullet
			it = bullets.erase(it); // 'remove' from bullet list
		}
		else if ((*it)->position.y > SHEIGHT && (*it)->shotDown) {
			layers[4]->removeChild(*it);
			delete (*it); // delete the Bullet
			it = bullets.erase(it); // 'remove' from bullet list
		}
		else if ((*it)->position.x < 0 && (*it)->shotLeft) {
			layers[4]->removeChild(*it);
			delete (*it); // delete the Bullet
			it = bullets.erase(it); // 'remove' from bullet list
		}
		else if ((*it)->position.x > SWIDTH && (*it)->shotRight) {
			layers[4]->removeChild(*it);
			delete (*it); // delete the Bullet
			it = bullets.erase(it); // 'remove' from bullet list
		}
		else if ((*it)->eLeft > player->eLeft && (*it)->eRight < player->eRight && (*it)->eTop > player->eTop && (*it)->eBottom < player->eBottom) {
			player->hitDelay = 100;
			player->isHit = true;
			player->hp--;
			BasicEntity* e = new BasicEntity();
			e->position = Point2((*it)->position.x, (*it)->position.y);
			e->scale = Point2(0.3f, 0.3f);
			e->delay = 180;
			layers[6]->addChild(e);
			explosions.push_back(e);
			layers[4]->removeChild(*it);
			delete (*it); // delete the Bullet
			it = bullets.erase(it); // 'remove' from bullet list
		}
		else {
			++it;
		}
	}

	//ENEMY BULLET
	if (enemy->reloading && enemy->isMoving && smoke2->tankSprite > 0) {
		if (enemy->facingUp) {
			smoke2->position = Point2(enemy->position.x + 1, enemy->position.y - 60);
			smoke2->rotation = 0 * DEG_TO_RAD;
		}
		else if (enemy->facingDown) {
			smoke2->position = Point2(enemy->position.x - 1, enemy->position.y + 60);
			smoke2->rotation = 180 * DEG_TO_RAD;
		}
		else if (enemy->facingLeft) {
			smoke2->position = Point2(enemy->position.x - 60, enemy->position.y - 1);
			smoke2->rotation = 270 * DEG_TO_RAD;
		}
		else if (enemy->facingRight) {
			smoke2->position = Point2(enemy->position.x + 60, enemy->position.y + 1);
			smoke2->rotation = 90 * DEG_TO_RAD;
		}
	}
	if (smoke2->tankSprite == 175) {
		smoke2->addSprite("assets/smoke/smoke2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke2->tankSprite == 140) {
		smoke2->addSprite("assets/smoke/smoke3.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke2->tankSprite == 105) {
		smoke2->addSprite("assets/smoke/smoke4.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke2->tankSprite == 70) {
		smoke2->addSprite("assets/smoke/smoke5.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)	
	}
	if (smoke2->tankSprite == 35) {
		smoke2->addSprite("assets/smoke/smoke6.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke2->tankSprite <= 0) {
		smoke2->removeSprite();
	}
	if (smoke2->tankSprite > 0) {
		smoke2->tankSprite--;
	}

	if (enemy->reloading && enemy->shootDelay <= 0) {
		enemy->reloading = false;
	}

	if (enemy->shootDelay > 0) {
		enemy->shootDelay--;
	}

	/*if (enemy->reloading && bullet2->shotUp) {
		bullet2->position.y -= 1000 * deltaTime;
		if (bullet2->position.y < 0) {
			bullet2->removeSprite();
		}
	}
	else if (enemy->reloading && bullet2->shotDown) {
		bullet2->position.y += 1000 * deltaTime;
		if (bullet2->position.y > SHEIGHT) {
			bullet2->removeSprite();
		}
	}
	else if (enemy->reloading && bullet2->shotLeft) {
		bullet2->position.x -= 1000 * deltaTime;
		if (bullet2->position.x < 0) {
			bullet2->removeSprite();
		}
	}
	else if (enemy->reloading && bullet2->shotRight) {
		bullet2->position.x += 1000 * deltaTime;
		if (bullet2->position.x > SWIDTH) {
			bullet2->removeSprite();
		}
	}*/
}

void Level1::updateHearts(float deltaTime)
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

	//GAME OVER WHEN DEAD
	if (player->hp <= 0) {
		SuperScene::activescene = 4;
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

void Level1::updateExplosions(float deltaTime) {
	std::vector<BasicEntity*>::iterator ite = explosions.begin(); // get the 'iterator' from the list.
	while (ite != explosions.end()) {
		std::cout << (*ite)->delay;
		(*ite)->delay--;
		if ((*ite)->delay > 179) {
			(*ite)->addSprite("assets/explosion/expl1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		else if ((*ite)->delay > 149 && (*ite)->delay < 151) {
			(*ite)->addSprite("assets/explosion/expl2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		else if ((*ite)->delay > 119 && (*ite)->delay < 121) {
			(*ite)->addSprite("assets/explosion/expl3.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		else if ((*ite)->delay > 89 && (*ite)->delay < 91) {
			(*ite)->addSprite("assets/explosion/expl4.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		else if ((*ite)->delay > 59 && (*ite)->delay < 61) {
			(*ite)->addSprite("assets/explosion/expl5.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		else if ((*ite)->delay > 29 && (*ite)->delay < 31) {
			(*ite)->addSprite("assets/explosion/expl6.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		}
		else if ((*ite)->delay <= 0) {
			layers[6]->removeChild(*ite);
			delete (*ite); // delete the Bullet
			ite = explosions.erase(ite); // 'remove' from bullet list
		}
		else {
			++ite;
		}
	}
}

void Level1::updateEnemy(float deltaTime)
{
	//Values for player searching
	enemy->UnderY = player->position.y - enemy->position.y;
	enemy->AboveY = enemy->position.y - player->position.y;

	enemy->NextX = player->position.x - enemy->position.x;
	enemy->BeforeX = enemy->position.x - player->position.x;
	
	//Delay controller
	if (enemy->delay > 0) {
		enemy->delay--;
		enemy->cpuLock = true;
	}
	else {
		enemy->cpuLock = false;
	}

	if (enemy->facingPlayer && !enemy->reloading) {
		enemyShoot();
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

	//Check which way is the fastest to the player
	if (enemy->position.x > player->position.x && enemy->position.y > player->position.y) {
		if (enemy->BeforeX < enemy->AboveY) {
			enemy->PreferX = true;
			enemy->PreferY = false;
		}
		else {
			enemy->PreferX = false;
			enemy->PreferY = true;
		}
	}
	else if (enemy->position.x > player->position.x && enemy->position.y < player->position.y) {
		if (enemy->BeforeX < enemy->UnderY) {
			enemy->PreferX = true;
			enemy->PreferY = false;
		}
		else {
			enemy->PreferX = false;
			enemy->PreferY = true;
		}
	}
	else if (enemy->position.x < player->position.x && enemy->position.y > player->position.y) {
		if (enemy->NextX < enemy->AboveY) {
			enemy->PreferX = true;
			enemy->PreferY = false;
		}
		else {
			enemy->PreferX = false;
			enemy->PreferY = true;
		}
	}
	else if (enemy->position.x < player->position.x && enemy->position.y < player->position.y) {
		if (enemy->NextX < enemy->UnderY) {
			enemy->PreferX = true;
			enemy->PreferY = false;
		}
		else {
			enemy->PreferX = false;
			enemy->PreferY = true;
		}
	}


	//If player is not around y position of enemy
	if (enemy->AboveY >= 5 && !enemy->cpuLock) {
		enemy->AroundY = false;
	}
	if (enemy->UnderY >= 5 && !enemy->cpuLock) {
		enemy->AroundY = false;
	}

	//If player is not around x position of enemy
	if (enemy->BeforeX >= 5 && !enemy->cpuLock) {
		enemy->AroundX = false;
	}
	if (enemy->NextX >= 5 && !enemy->cpuLock) {
		enemy->AroundX = false;
	}

	//x-axis player search
	if (!enemy->cpuLock && !enemy->AroundX && player->position.x < enemy->position.x && enemy->PreferX) {
		if (!enemy->AroundX && enemy->BeforeX <= 5) {
			enemy->AroundX = true;
			enemy->isMoving = false;
			enemy->delay = 175;
		}
		enemy->facingDown = false;
		enemy->facingUp = false;
		enemy->facingLeft = true;
		enemy->facingRight = false;
		enemy->facingPlayer = false;
		enemy->position.x -= 100 * deltaTime;
		enemy->isMoving = true;
	}
	else if (!enemy->cpuLock && !enemy->AroundX && player->position.x > enemy->position.x && enemy->PreferX) {
		if (!enemy->AroundX && enemy->NextX <= 5) {
			enemy->AroundX = true;
			enemy->isMoving = false;
			enemy->delay = 175;
		}
		enemy->facingDown = false;
		enemy->facingUp = false;
		enemy->facingLeft = false;
		enemy->facingRight = true;
		enemy->facingPlayer = false;
		enemy->position.x += 100 * deltaTime;
		enemy->isMoving = true;
	}
	else if (!enemy->cpuLock && enemy->AroundX) {
		if (enemy->position.y > player->position.y) {
			enemy->facingDown = false;
			enemy->facingUp = true;
			enemy->facingLeft = false;
			enemy->facingRight = false;
			enemy->isMoving = false;
			enemy->facingPlayer = true;
			enemy->delay = 175;
		}
		else if (enemy->position.y < player->position.y) {
			enemy->facingDown = true;
			enemy->facingUp = false;
			enemy->facingLeft = false;
			enemy->facingRight = false;
			enemy->isMoving = false;
			enemy->facingPlayer = true;
			enemy->delay = 175;
		}
	}

	//y-axis player search
	if (!enemy->cpuLock && !enemy->AroundY && player->position.y < enemy->position.y && enemy->PreferY) {
		if (!enemy->AroundY && enemy->AboveY <= 5) {
			enemy->AroundY = true;
			enemy->isMoving = false;
			enemy->delay = 175;
		}
		enemy->facingDown = false;
		enemy->facingUp = true;
		enemy->facingLeft = false;
		enemy->facingRight = false;
		enemy->facingPlayer = false;
		enemy->position.y -= 100 * deltaTime;
		enemy->isMoving = true;
	}
	else if (!enemy->cpuLock && !enemy->AroundY && player->position.y > enemy->position.y && enemy->PreferY) {
		if (!enemy->AroundY && enemy->UnderY <= 5) {
			enemy->AroundY = true;
			enemy->isMoving = false;
			enemy->delay = 175;
		}
		enemy->facingDown = true;
		enemy->facingUp = false;
		enemy->facingLeft = false;
		enemy->facingRight = false;
		enemy->facingPlayer = false;
		enemy->position.y += 100 * deltaTime;
		enemy->isMoving = true;
	}
	else if (!enemy->cpuLock && enemy->AroundY) {
		if (enemy->position.x > player->position.x) {
			enemy->facingDown = false;
			enemy->facingUp = false;
			enemy->facingLeft = true;
			enemy->facingRight = false;
			enemy->isMoving = false;
			enemy->facingPlayer = true;
			enemy->delay = 175;
		}
		else if (enemy->position.x < player->position.x) {
			enemy->facingDown = false;
			enemy->facingUp = false;
			enemy->facingLeft = false;
			enemy->facingRight = true;
			enemy->isMoving = false;
			enemy->facingPlayer = true;
			enemy->delay = 175;
		}
	}

	//enemy isMoving
	enemy->rideDelay++;

	if (enemy->isMoving && !enemy->AroundY) {
		if (enemy->tankSprite == 0 && enemy->rideDelay >= 50) {
			enemy->addSprite("assets/enemy/enemyride3.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
			enemy->tankSprite++;
			enemy->rideDelay = 0;
		}
		else if (enemy->tankSprite == 1 && enemy->rideDelay >= 50) {
			enemy->addSprite("assets/enemy/enemyride2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
			enemy->tankSprite++;
			enemy->rideDelay = 0;
		}
		else if (enemy->tankSprite == 2 && enemy->rideDelay >= 50) {
			enemy->addSprite("assets/enemy/enemyride1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
			enemy->tankSprite++;
			enemy->rideDelay = 0;
		}
		else if (enemy->tankSprite == 3 && enemy->rideDelay >= 50) {
			enemy->addSprite("assets/enemy/enemyride2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
			enemy->tankSprite = 0;
			enemy->rideDelay = 0;
		}
	}
	else {
		enemy->addSprite("assets/enemy/enemystand.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
}

void Level1::enemyShoot() {
	BasicEntity* b = new BasicEntity();
	if (!enemy->reloading) {
		smoke2->tankSprite = 210;
		enemy->shootDelay = 1250;
	}

	if (!enemy->reloading) {
		b->addSprite("assets/bullet/bullet.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		b->scale = Point2(0.06f, 0.06f);
		b->halfHeight = 6;
		b->halfWidth = 6;
		smoke2->addSprite("assets/smoke/smoke1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
		smoke2->scale = Point2(0.3f, 0.3f);
	}

	if (enemy->facingUp && !enemy->reloading) {
		smoke2->position = Point2(enemy->position.x + 1, enemy->position.y - 57);
		smoke2->rotation = 0 * DEG_TO_RAD;
		b->position = Point2(enemy->position.x + 1, enemy->position.y - 56);
		b->shotUp = true;
		b->shotDown = false;
		b->shotLeft = false;
		b->shotRight = false;
	}
	else if (enemy->facingDown && !enemy->reloading) {
		smoke2->position = Point2(enemy->position.x - 1, enemy->position.y + 57);
		smoke2->rotation = 180 * DEG_TO_RAD;
		b->position = Point2(enemy->position.x - 1, enemy->position.y + 56);
		b->shotUp = false;
		b->shotDown = true;
		b->shotLeft = false;
		b->shotRight = false;
	}
	else if (enemy->facingLeft && !enemy->reloading) {
		smoke2->position = Point2(enemy->position.x - 57, enemy->position.y - 1);
		smoke2->rotation = 270 * DEG_TO_RAD;
		b->position = Point2(enemy->position.x - 56, enemy->position.y - 1);
		b->shotUp = false;
		b->shotDown = false;
		b->shotLeft = true;
		b->shotRight = false;
	}
	else if (enemy->facingRight && !enemy->reloading) {
		smoke2->position = Point2(enemy->position.x + 57, enemy->position.y + 1);
		smoke2->rotation = 90 * DEG_TO_RAD;
		b->position = Point2(enemy->position.x + 56, enemy->position.y + 1);
		b->shotUp = false;
		b->shotDown = false;
		b->shotLeft = false;
		b->shotRight = true;
	}
	if (!enemy->reloading) {
		enemy->reloading = true;
	}
	layers[4]->addChild(b);
	bullets.push_back(b);
}
