
#include <fstream>
#include <iostream>

#include <Windows.h>
#include <conio.h>




#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>



#include "console.h"
#include "framework.h"
#include "test_bounds.h"
#include "test_effect.h"
#include "test_engine.h"
#include "test_fs.h"
#include "test_xml.h"

// Libraries
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "soil.lib")

#pragma comment(lib, "assimp-vc130-mtd.lib")
#pragma comment(lib, "freetype240MT_D.lib")

#pragma comment(lib, "andromeda.lib")



// nvFX Library
#if defined(_DEBUG) 
#pragma comment(lib, "fxLibD.lib")
#pragma comment(lib, "fxLibGLD.lib")
#pragma comment(lib, "fxParserD.lib")
#pragma comment(lib, "nvFxcc.lib")
#else
#pragma comment(lib, "fxLib.lib")
#pragma comment(lib, "fxLibGL.lib")
#pragma comment(lib, "fxParser.lib")
#pragma comment(lib, "nvFxcc.lib")
#endif


// Boost may Auto Link ?? 


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
	//std::cout << "\n\nPress any Key to Continue:";
	_getch();
#endif
}



/*
	Prints a Header
*/
void printHeader(std::shared_ptr<Console> console)
{
	std::string contents = andromeda::LoadFile("../res/andromeda.txt");

	console->print(contents);
}


/*

*/
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Set Exit Handler
	atexit(exit);

	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);


	// Create Log
	andromeda::Log::instance();

#if defined(_DEBUG) && defined(_WIN32)
	// Create the Console Output
	std::shared_ptr<Console> console = std::make_shared<Console>();

	// Print the Header to Console
	printHeader(console);
#endif

	// Create Framework Pointer

//#define FRAMEWORK

#if defined(FRAMEWORK)
	std::shared_ptr<IFramework> framework = std::make_shared<IFramework>();
#else
	std::shared_ptr<IFramework> framework = nullptr;
#endif


	


	// Test the Engine
	if (!framework)
		testEngine(hInstance);
	else
	{
		std::shared_ptr<Framework> fw = std::make_shared<Framework>(framework);
		if (fw->initialise(1650, 900))
			fw->loop();
	}

	return 0;
}














