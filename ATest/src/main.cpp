
#include <fstream>
#include <iostream>

#include <Windows.h>
#include <conio.h>


#include <andromeda/andromeda.h>
#include <andromeda/Engine/engine.h>

#include <andromeda/Utilities/log.h>


#include "app.h"
#include "console.h"
#include "test_event.h"
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
	std::ifstream file("../res/andromeda.txt");

	if (!file.is_open())
		return;


	std::string line;
	while (std::getline(file, line))
	{
		std::cout << line << "\n";
	}
	

	file.close();
}






/*

*/
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Set Exit Handler
	atexit(exit);

	// Create Log
	andromeda::Log::instance();

#if defined(_DEBUG)
	// Create the Console Output
	std::shared_ptr<Console> console = std::make_shared<Console>();
#endif

	// Print the Header to Console
	printHeader();

	testBounds();


	/* If this isn't a pointer... it don't wanna compile. so it's unqiue ptr! */

	// Create Engine
	std::unique_ptr<App> app = std::make_unique<App>(std::move(andromeda::initialise(hInstance)));

	// Run the Engine!
	app->run();

	return 0;
}














