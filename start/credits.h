#ifndef CREDITS_H
#define CREDITS_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class Credits : public SuperScene
{
public:
	Credits();
	virtual ~Credits();

	virtual void update(float deltaTime);

private:
	Timer t;

	//ints
	int buttonwidth;
	int buttonheight;

	//buttons
	BasicEntity* backb;
};

#endif /* CREDITS_H */
