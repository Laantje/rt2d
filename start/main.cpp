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

#include "level1.h"
#include "menu.h"

/// @brief main entry point
int main( void )
{
	// Core instance
	Core core;

	// Create all scenes on the heap and keep a list
	std::vector<SuperScene*> scenes;
	scenes.push_back(new Menu());
	scenes.push_back(new Level1());
	int s = scenes.size();


	SuperScene* scene = scenes[0];
	int scenecounter = 0;
	int running = 1;
	while (running) {
		scenecounter = scene->activescene;
		if (scenecounter > s - 1) { scenecounter = 0; scene->activescene = 0; }
		if (scenecounter < 0) { scenecounter = s - 1; scene->activescene = s - 1; }
		scene = scenes[scenecounter];
		core.run(scene); // update and render the current scene
		core.showFrameRate(5); // show framerate in output every n seconds
		if (!scene->isRunning()) { running = 0; } // check status of Scene every frame
	}
	//core.cleanup(); // cleanup ResourceManager (Textures + Meshes, but not Shaders)



	// delete all scenes
	for (int i = 0; i < s; i++) {
		delete scenes[i];
		scenes[i] = NULL;
	}
	scenes.clear();

	// No need to explicitly clean up the core.
	// As a local var, core will go out of scope and destroy Renderer->ResourceManager.
	// ResourceManager destructor also deletes Shaders.

	return 0;
}
