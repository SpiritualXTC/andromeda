
#include <fstream>
#include <iostream>

#include <Windows.h>
#include <conio.h>


#include <andromeda/andromeda.h>
#include <andromeda/Engine/engine.h>
#include <andromeda/Engine/system.h>
#include <andromeda/Graphics/renderer.h>
#include <andromeda/Utilities/timing.h>


#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>


#include "app.h"
#include "console.h"
#include "test_bounds.h"


// Libraries
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib, "glew32.lib")

#pragma comment(lib, "andromeda.lib")


#if defined(_DEBUG)
#define LOCK_CONSOLE
// Uncomment this to immediately quit on exit :)
//#undef LOCK_CONSOLE
#endif


/*
	Quit Handler
*/
void exit()
{
#if defined(LOCK_CONSOLE)
	// Everything else will be out of scope by now :P
	std::cout << "\n\nPress any Key to Continue:";
	_getch();
#endif
}



/*
	Prints a Header
*/
void printHeader()
{
	std::string contents = andromeda::LoadFile("../res/andromeda.txt");

	std::cout << contents;
}






/*

*/
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Set Exit Handler
	atexit(exit);

	// Create Log
	andromeda::Log::instance();

#if defined(_DEBUG) && defined(_WIN32)
	// Create the Console Output
	std::shared_ptr<Console> console = std::make_shared<Console>();
#endif

	// Print the Header to Console
	printHeader();

	//testBounds();









	// Create Engine
	std::unique_ptr<andromeda::Engine> engine = andromeda::initialise(hInstance);

	// Create Application!
	std::shared_ptr<App> app = std::make_shared<App>();

	engine->addModule<App>(app);

	engine->setDependancy<App, andromeda::Timing>();
	engine->setDependancy<App, andromeda::System>();
	engine->setDependancy<App, andromeda::Renderer>();

	// Initialise Application
	app->initialise();


	// Run Engine
	engine->run();

	return 0;
}














