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

#include "menu.h"
Menu::Menu() : SuperScene()
{
	// Button width & Height
	buttonwidth = 256;
	buttonheight = 102;

	// Logo game
	size = 1.4f;
	logo = new BasicEntity();
	logo->position = Point2(SWIDTH / 2, SHEIGHT / 12 * 2);
	logo->addSprite("assets/logo/logo.tga", 0.5f, 0.5f, 3, 0); // custom pivot point, filter, wrap (0=repeat, 1=mirror, 2=clamp)
	logo->scale.x = size;
	logo->scale.y = size;
	logo->tankSprite = 0;

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

	//string
	char CopyrightChar = '\xa9';
	std::string copyright = "David Laan, Rik Teerling - 2015";
	text[15]->message(copyright);

	layers[5]->addChild(startb);
	layers[5]->addChild(creditsb);
	layers[5]->addChild(quitb);
	layers[4]->addChild(logo);
}

Menu::~Menu()
{
	layers[5]->removeChild(startb);
	layers[5]->removeChild(creditsb);
	layers[5]->removeChild(quitb);
	layers[4]->removeChild(logo);

	delete startb;
	delete creditsb;
	delete quitb;
	delete logo;
}

void Menu::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	// Logo scale
	if (logo->scale.x >= 1.8f) {
		logo->tankSprite = 1;
	}
	else if (logo->scale.x < 1.4f) {
		logo->tankSprite = 0;
	}

	if (logo->tankSprite == 0) {
		size += 0.2f * deltaTime;
	}
	else if (logo->tankSprite == 1) {
		size -= 0.2f * deltaTime;
	}
	
	logo->scale.x = size;
	logo->scale.y = size;

	//Mouse registration
	int mousex = input()->getMouseX() + camera()->position.x - SWIDTH / 2;
	int mousey = input()->getMouseY() + camera()->position.y - SHEIGHT / 2;

	//Button handler
	int halfwidth = buttonwidth / 2;
	int halfheight = buttonheight / 2;

	//Start button
	int sleft = startb->position.x - halfwidth;
	int sright = startb->position.x + halfwidth;
	int stop = startb->position.y - halfheight;
	int sbottom = startb->position.y + halfheight;

	//Credits button
	int cleft = creditsb->position.x - halfwidth;
	int cright = creditsb->position.x + halfwidth;
	int ctop = creditsb->position.y - halfheight;
	int cbottom = creditsb->position.y + halfheight;

	//Quit button
	int qleft = quitb->position.x - halfwidth;
	int qright = quitb->position.x + halfwidth;
	int qtop = quitb->position.y - halfheight;
	int qbottom = quitb->position.y + halfheight;


	//If mouse is on startbutton
	if (mousex > sleft && mousex < sright && mousey > stop && mousey < sbottom) {
		startb->sprite()->color.a = 127;
		if (input()->getMouseUp(0)) {
			startb->sprite()->color = RGBAColor(192, 192, 192, 255);
			SuperScene::activescene = 3;
		}
	}
	else {
		startb->sprite()->color.a = 255;
	}

	//If mouse is on creditsbutton
	if (mousex > cleft && mousex < cright && mousey > ctop && mousey < cbottom) {
		creditsb->sprite()->color.a = 127;
		if (input()->getMouseUp(0)) {
			creditsb->sprite()->color = RGBAColor(192, 192, 192, 255);
			SuperScene::activescene = 1;
		}
	}
	else {
		creditsb->sprite()->color.a = 255;
	}

	//If mouse is on quitbutton
	if (mousex > qleft && mousex < qright && mousey > qtop && mousey < qbottom) {
		quitb->sprite()->color.a = 127;
		if (input()->getMouseUp(0)) {
			quitb->sprite()->color = RGBAColor(192, 192, 192, 255);
			SuperScene::stop();
		}
	}
	else {
		quitb->sprite()->color.a = 255;
	}
}
