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
	// start button
	startb = new BasicEntity();

	// credits button
	creditsb = new BasicEntity();

	// quit button
	quitb = new BasicEntity();

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