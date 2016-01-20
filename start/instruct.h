#ifndef INSTRUCT_H
#define INSTRUCT_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class Instruct : public SuperScene
{
public:
	Instruct();
	virtual ~Instruct();

	virtual void update(float deltaTime);

private:
	Timer t;

	//ints
	int buttonwidth;
	int buttonheight;

	//buttons
	BasicEntity* nextb;
};

#endif /* INSTRUCT_H */