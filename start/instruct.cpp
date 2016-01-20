/**
* Copyright 2015 Your Name <you@yourhost.com>
*
* @brief Description of My Awesome Game.
*
* @file main.cpp
*
* @mainpage My Awesome Game
*
* @section intro Introduction
*
* Detailed description of My Awesome Game.
*
* There's even a second paragraph.
*/
#include <rt2d/core.h>

#include "instruct.h"
Instruct::Instruct() : SuperScene()
{
	/*
	// Button width & Height
	buttonwidth = 256;
	buttonheight = 102;

	// start button
	startb = new BasicEntity();
	startb->position = Point2(SWIDTH / 2, SHEIGHT / 12 * 5);
	startb->addSprite("assets/buttons/start.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	startb->scale = Point2(1, 1);

	// credits button
	creditsb = new BasicEntity();
	creditsb->position = Point2(SWIDTH / 2, SHEIGHT / 12 * 7);
	creditsb->addSprite("assets/buttons/credits.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	creditsb->scale = Point2(1, 1);

	// quit button
	quitb = new BasicEntity();
	quitb->position = Point2(SWIDTH / 2, SHEIGHT / 12 * 9);
	quitb->addSprite("assets/buttons/quit.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	quitb->scale = Point2(1, 1);

	layers[5]->addChild(startb);
	layers[5]->addChild(creditsb);
	layers[5]->addChild(quitb);
	*/
}

Instruct::~Instruct()
{
	/*
	layers[5]->removeChild(startb);
	layers[5]->removeChild(creditsb);
	layers[5]->removeChild(quitb);

	delete startb;
	delete creditsb;
	delete quitb;
	*/
}

void Instruct::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	/*
	//Mouse registration
	int mousex = input()->getMouseX() + camera()->position.x - SWIDTH / 2;
	int mousey = input()->getMouseY() + camera()->position.y - SHEIGHT / 2;

	//Button handler
	int halfwidth = buttonwidth / 2;
	int halfheight = buttonheight / 2;

	//Back button
	int sleft = startb->position.x - halfwidth;
	int sright = startb->position.x + halfwidth;
	int stop = startb->position.y - halfheight;
	int sbottom = startb->position.y + halfheight;
	*/


	//If mouse is on back button
	/*if (mousex > sleft && mousex < sright && mousey > stop && mousey < sbottom) {
	startb->sprite()->color.a = 127;
	if (input()->getMouseDown(0)) {
	startb->sprite()->color = RGBAColor(192, 192, 192, 255);
	}
	if (input()->getMouseDown(1)) {
	startb->sprite()->color = RGBAColor(64, 64, 64, 255);
	}
	if (input()->getMouseDown(2)) {
	startb->sprite()->color = GRAY;
	}
	}
	else {
	startb->sprite()->color.a = 255;
	}*/
}
