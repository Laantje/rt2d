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

	/*// Load Line from file (rt2d logo)
	// This is the preferred method.
	rt2d_line = new BasicEntity();
	rt2d_line->addLine("assets/rt2d.line");
	rt2d_line->line()->color = RED;
	rt2d_line->position = Point2(SWIDTH/3, SHEIGHT/3);

	// and another one (default 128x128 square)
	default_line = new BasicEntity();
	default_line->addLine("assets/default.line");
	default_line->line()->color = GREEN;
	default_line->position = Point2((SWIDTH/3)*2, SHEIGHT/3);*/

	// add player
	player = new BasicEntity();
	player->addSprite("assets/tankstand.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	player->scale = Point2(0.5f, 0.5f);
	player->position = Point2(SWIDTH / 3, SHEIGHT / 2);

	// add bullet
	bullet = new BasicEntity();

	// add shotsmoke
	smoke = new BasicEntity();

	/*// Or create a new Line and add it to an Entity later.
	// It will be unique once you added it to an Entity.
	// You must delete it yourself after you've added it to all the Entities you want.
	Line* tmp = new Line();
	tmp->addPoint(-10.0f, -10.0f);
	tmp->addPoint(20.0f, 0.0f);
	tmp->addPoint(-10.0f, 10.0f);
	tmp->addPoint(-10.0f, -10.0f);

	//Create a BasicEntity as our spaceship.
	//spaceship = new BasicEntity();
	//spaceship->addLine(tmp);
	//spaceship->position = Point2(SWIDTH/2, SHEIGHT/2);
	//delete tmp; // delete when you're done with it.

	// Shapes!!
	shape_container = new BasicEntity();
	shape_container->position = Point2(SWIDTH/2, (SHEIGHT/3)*2);
	int numshapes = 12;
	// fill shapes vector with variants of a circle
	for (int i = 3; i <= numshapes; i++) {
		Line* circle = new Line();
		circle->createCircle(30, i);
		circle->color = colors[(i-3)%10];

		BasicEntity* b = new BasicEntity();
		int spacing = 80;
		// shape_container acts as pivot point (center of the shapes).
		b->position.x = ((i-3)*spacing) - ((numshapes*spacing)/2) + (1.5f*spacing);
		b->addLine(circle);
		shapes.push_back(b);
		shape_container->addChild(b);
		delete circle;
	}

	// Dynamic Line
	Line* dynamic = new Line();
	dynamic->dynamic(true);
	//dynamic->closed(true);
	dynamic->color = GREEN;
	int spacing = 25;
	int amount = SWIDTH/spacing;
	int i=0;
	for (i = 1; i < amount; i++) {
		dynamic->addPoint(i*spacing, 0);
	}

	dynamic_line = new BasicEntity();
	dynamic_line->position.y = SHEIGHT-60;
	dynamic_line->addLine(dynamic);
	delete dynamic;*/

	// Create Tree
	//layers[0]->addChild(dynamic_line);
	//layers[0]->addChild(rt2d_line);
	//layers[0]->addChild(default_line);
	layers[0]->addChild(player);
	layers[0]->addChild(bullet);
	layers[0]->addChild(smoke);
	//layers[0]->addChild(spaceship);
	//layers[0]->addChild(shape_container);
}


MyScene::~MyScene()
{
	//layers[0]->removeChild(shape_container);
	//layers[0]->removeChild(spaceship);
	layers[0]->removeChild(player);
	layers[0]->removeChild(bullet);
	layers[0]->removeChild(smoke);
	//layers[0]->removeChild(default_line);
	//layers[0]->removeChild(rt2d_line);
	//layers[0]->removeChild(dynamic_line);

	//delete dynamic_line;
	//delete rt2d_line;
	//delete default_line;
	delete player;
	delete bullet;
	delete smoke;
	//delete spaceship;

	/*int s = shapes.size();
	for (int i=0; i<s; i++) {
		shape_container->removeChild(shapes[i]);
		delete shapes[i];
		shapes[i] = NULL;
	}
	shapes.clear();

	delete shape_container;*/
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
}

void MyScene::updateTank(float deltaTime)
{
	player->delay++;

	if (player->isMoving) {
		if (player->tankSprite == 0 && player->delay >= 50) {
			player->addSprite("assets/tankride3.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
			player->tankSprite++;
			player->delay = 0;
		}
		else if (player->tankSprite == 1 && player->delay >= 50) {
			player->addSprite("assets/tankride2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
			player->tankSprite++;
			player->delay = 0;
		}
		else if (player->tankSprite == 2 && player->delay >= 50) {
			player->addSprite("assets/tankride1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
			player->tankSprite++;
			player->delay = 0;
		}
		else if (player->tankSprite == 3 && player->delay >= 50) {
			player->addSprite("assets/tankride2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
			player->tankSprite = 0;
			player->delay = 0;
		}
	}
	else {
		player->addSprite("assets/tankstand.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
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
	bullet->addSprite("assets/bullet.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	bullet->scale = Point2(0.06f, 0.06f);
	smoke->addSprite("assets/smoke1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
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
		smoke->addSprite("assets/smoke2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke->tankSprite == 140) {
		smoke->addSprite("assets/smoke3.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke->tankSprite == 105) {
		smoke->addSprite("assets/smoke4.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke->tankSprite == 70) {
		smoke->addSprite("assets/smoke5.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)	
	}
	if (smoke->tankSprite == 35) {
		smoke->addSprite("assets/smoke6.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	if (smoke->tankSprite <= 0) {
		smoke->removeSprite();
	}
	if (smoke->tankSprite > 0) {
		smoke->tankSprite--;
	}
	if (player->reloading && player->shootDelay > 1150 && !player->isMoving) {
		player->addSprite("assets/tankshoot.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	} else if (player->reloading && player->shootDelay > 1150 && player->isMoving) {
		player->addSprite("assets/tankshootride.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	else if (!player->isMoving && player->shootDelay < 1150) {
		player->addSprite("assets/tankstand.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
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
