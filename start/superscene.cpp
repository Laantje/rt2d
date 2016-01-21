/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include "superscene.h"

int SuperScene::activescene = 0;

SuperScene::SuperScene() : Scene()
{
	fpstimer.start();

	player = NULL;
	top_layer = 7; // 8 layers (0-7)

	for (unsigned int i = 0; i <= top_layer; i++) {
		BasicEntity* layer = new BasicEntity();
		layers.push_back(layer);
		this->addChild(layer);
	}

	for (unsigned int i = 0; i < 16; i++) {
		Text* line = new Text();
		line->scale = Point2(0.5f, 0.5f);

		text.push_back(line);
		layers[top_layer]->addChild(line);
	}

	// Create a logo entity on the top layer

	text[1]->message("");
	text[2]->message("<[/]> previous/next scene");
	text[3]->message("<ESC> quit demo");
}


SuperScene::~SuperScene()
{

	int ls = layers.size();
	for (int i=0; i<ls; i++) {
		this->removeChild(layers[i]);
		delete layers[i];
		layers[i] = NULL;
	}
	layers.clear();

	int ts = text.size();
	for (int i=0; i<ts; i++) {
		this->removeChild(text[i]);
		delete text[i];
		text[i] = NULL;
	}
	text.clear();

}

// must be explicitly called from subclass
void SuperScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}

	// ###############################################################
	// Enter key goes to the menu
	// ###############################################################
	if (input()->getKeyUp(GLFW_KEY_ENTER) && activescene != 0) {
		activescene = 0;
	}

	// ###############################################################
	// '[' and ']' switch scenes
	// ###############################################################
	if (input()->getKeyUp(GLFW_KEY_LEFT_BRACKET)) {
		activescene--;
	}
	if (input()->getKeyUp(GLFW_KEY_RIGHT_BRACKET)) {
		activescene++;
	}

	// ###############################################################
	// logo and text follow camera
	// ###############################################################
	Point2 cam_pos = Point2(camera()->position.x, camera()->position.y);

	Point2 logo_pos = Point2(cam_pos.x, cam_pos.y - 50 + SHEIGHT/2);

	unsigned int s = text.size();
	for (unsigned int i = 0; i < s; i++) {
		text[i]->position = Point2(cam_pos.x + 50 - SWIDTH/2, cam_pos.y + 50 + (30*i) - SHEIGHT/2);
	}

	// ###############################################################
	// show FPS
	// ###############################################################
	static int framecounter = 0;
	if (fpstimer.seconds() > 1.0f) {
		std::string fpstxt = "SuperScene FPS: ";
		fpstxt.append(std::to_string(framecounter));
		text[1]->message(fpstxt);
		framecounter = 0;
		fpstimer.start();
	}
	framecounter++;
}

void SuperScene::moveCamera(float deltaTime)
{
	// ###############################################################
	// Move Camera (Arrow up, down, left, right)
	// ###############################################################
	float speed = 600.0f; // 600 units / second

	// Right and Down vector
	Point2 right = Point2(1, 0);
	Point2 up = Point2(0, 1);
	// Direction
	Vector2 direction = Vector2(0,0);

	if (input()->getKey( GLFW_KEY_UP )) {
		direction -= up;
	}
	if (input()->getKey( GLFW_KEY_DOWN )) {
		direction += up;
	}
	if (input()->getKey( GLFW_KEY_RIGHT )) {
		direction += right;
	}
	if (input()->getKey( GLFW_KEY_LEFT )) {
		direction -= right;
	}
	direction.normalize();
	direction *= deltaTime * speed;
	camera()->position += direction;
}
