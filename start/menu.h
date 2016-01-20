/**
* - Copyright 2015 Your Name <you@yourhost.com>
*     - What you did
*/

#ifndef MENU_H
#define MENU_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class Menu : public SuperScene
{
public:
	Menu();
	virtual ~Menu();

	virtual void update(float deltaTime);

private:
	Timer t;

	//ints
	int buttonwidth;
	int buttonheight;

	//buttons
	BasicEntity* startb;
	BasicEntity* creditsb;
	BasicEntity* quitb;

	//functions
	void updateStart(float deltaTime);
	void updateCredits(float deltaTime);
	void updateQuit(float deltaTime);
};

#endif /* MENU_H */