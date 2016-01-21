#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class GameOver : public SuperScene
{
public:
	GameOver();
	virtual ~GameOver();

	virtual void update(float deltaTime);

private:
	Timer t;

	//ints
	int buttonwidth;
	int buttonheight;

	//txt
	BasicEntity* deadtxt;

	//buttons
	BasicEntity* backb;
};

#endif /* GAMEOVER_H */