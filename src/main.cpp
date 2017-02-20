//
//  main.cpp
//  
//
//  Created by Bret Jackson on 1/29/17.
//
//

#include <stdio.h>
#include <iostream>

#include "ExampleApp.h"
//include "App.h"


using namespace basicgraphics;

int main(int argc, char** argv)
{
	// Initialize freeimage library
	//FreeImage_Initialise();

	//ExampleApp *app = new ExampleApp(argc, argv, "Basic Graphics Example", 1280, 720);
	ExampleApp *app = new ExampleApp(argc, argv, "Basic Graphics Example", 1920, 1080);
    //App *app = new App(argc, argv, "Ping Pong 3D", 1280, 720);
	app->run();
	delete app;

	//FreeImage_DeInitialise();

	return 0;

}
