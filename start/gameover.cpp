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

#include "gameover.h"

GameOver::GameOver() : SuperScene()
{
	// Button width & Height
	buttonwidth = 256;
	buttonheight = 102;

	// Text
	deadtxt = new BasicEntity();
	deadtxt->addSprite("assets/menu/dead1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	deadtxt->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	deadtxt->scale = Point2(1, 1);
	deadtxt->tankSprite = 0;
	deadtxt->delay = 80;

	// start button
	backb = new BasicEntity();
	backb->position = Point2(SWIDTH / 12 * 2, SHEIGHT / 12 * 10);
	backb->addSprite("assets/buttons/back.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	backb->scale = Point2(1, 1);

	layers[4]->addChild(deadtxt);
	layers[5]->addChild(backb);
}

GameOver::~GameOver()
{
	layers[4]->removeChild(deadtxt);
	layers[5]->removeChild(backb);

	delete deadtxt;
	delete backb;
}

void GameOver::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	//Button delay
	if (deadtxt->delay <= 0 && deadtxt->tankSprite == 0) {
		deadtxt->delay = 80;
		deadtxt->tankSprite++;
	}
	else if (deadtxt->delay <= 0 && deadtxt->tankSprite == 1) {
		deadtxt->delay = 80;
		deadtxt->tankSprite--;
	}

	if (deadtxt->delay > 0) {
		deadtxt->delay--;
	}

	//Sprite changer
	if (deadtxt->tankSprite == 0) {
		deadtxt->addSprite("assets/menu/dead1.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	else if (deadtxt->tankSprite == 1) {
		deadtxt->addSprite("assets/menu/dead2.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	}
	
	//Mouse registration
	int mousex = input()->getMouseX() + camera()->position.x - SWIDTH / 2;
	int mousey = input()->getMouseY() + camera()->position.y - SHEIGHT / 2;

	//Button handler
	int halfwidth = buttonwidth / 2;
	int halfheight = buttonheight / 2;

	//Back button
	int sleft = backb->position.x - halfwidth;
	int sright = backb->position.x + halfwidth;
	int stop = backb->position.y - halfheight;
	int sbottom = backb->position.y + halfheight;


	//If mouse is on back button
	if (mousex > sleft && mousex < sright && mousey > stop && mousey < sbottom) {
		backb->sprite()->color.a = 127;
		if (input()->getMouseUp(0)) {
			backb->sprite()->color = RGBAColor(192, 192, 192, 255);
			SuperScene::activescene = 0;
		}
	}
	else {
		backb->sprite()->color.a = 255;
	}
}
