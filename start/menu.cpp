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
	buttonwidth = 250;
	buttonheight = 100;

	// start button
	startb = new BasicEntity();
	startb->position = Point2(SWIDTH / 2, SHEIGHT / 12 * 5);

	// credits button
	creditsb = new BasicEntity();
	creditsb->position = Point2(SWIDTH / 2, SHEIGHT / 12 * 7);

	// quit button
	quitb = new BasicEntity();
	quitb->position = Point2(SWIDTH / 2, SHEIGHT / 12 * 9);

	layers[5]->addChild(startb);
	layers[5]->addChild(creditsb);
	layers[5]->addChild(quitb);
}

Menu::~Menu()
{
	layers[5]->removeChild(startb);
	layers[5]->removeChild(creditsb);
	layers[5]->removeChild(quitb);

	delete startb;
	delete creditsb;
	delete quitb;
}

void Menu::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

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
	}

	//If mouse is on creditsbutton
	if (mousex > cleft && mousex < cright && mousey > ctop && mousey < cbottom) {
		creditsb->sprite()->color.a = 127;
		if (input()->getMouseDown(0)) {
			creditsb->sprite()->color = RGBAColor(192, 192, 192, 255);
		}
		if (input()->getMouseDown(1)) {
			creditsb->sprite()->color = RGBAColor(64, 64, 64, 255);
		}
		if (input()->getMouseDown(2)) {
			creditsb->sprite()->color = GRAY;
		}
	}
	else {
		creditsb->sprite()->color.a = 255;
	}

	//If mouse is on quitbutton
	if (mousex > qleft && mousex < qright && mousey > qtop && mousey < qbottom) {
		quitb->sprite()->color.a = 127;
		if (input()->getMouseDown(0)) {
			quitb->sprite()->color = RGBAColor(192, 192, 192, 255);
		}
		if (input()->getMouseDown(1)) {
			quitb->sprite()->color = RGBAColor(64, 64, 64, 255);
		}
		if (input()->getMouseDown(2)) {
			quitb->sprite()->color = GRAY;
		}
	}
	else {
		quitb->sprite()->color.a = 255;
	}

	this->updateStart(deltaTime);
	this->updateCredits(deltaTime);
	this->updateQuit(deltaTime);
}

void Menu::updateStart(float deltaTime)
{
	
}

void Menu::updateCredits(float deltaTime)
{

}

void Menu::updateQuit(float deltaTime)
{

}