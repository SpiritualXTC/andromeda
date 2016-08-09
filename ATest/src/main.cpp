
#include <fstream>
#include <iostream>

#include <Windows.h>
#include <conio.h>



#include <andromeda/andromeda.h>
#include <andromeda/andromeda_init.h>

#include <andromeda/graphics.h>
#include <andromeda/Resources/resource_manager.h>
#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>


#include "app.h"
#include "console.h"

// Libraries
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")	// glErrorString(...) uses this function
#pragma comment(lib, "glew32.lib")	//glew32s.lib for the static library - which for unknown reasons has decided to stop linking correctly! Go Figure!
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

// Boost Auto Links its libraries?? 




// Debug Console
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
	// Including the fucking logger & console.
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


#include <boost/regex.hpp>



void test(const glm::vec2 & v0, const glm::vec2 & v1, const glm::vec2 & c)
{
	glm::vec2 s0 = v1 - v0;
	glm::vec2 s1 = c - v0;

	aFloat dot = glm::dot(s0, s1);
	aFloat cross = s0.x * s1.y - s0.y * s1.x;

	log_debugp("V0 = (%1%, %2%)", v0.x, v0.y);
	log_debugp("V1 = (%1%, %2%)", v1.x, v1.y);
	log_debugp("C  = (%1%, %2%)", c.x, c.y);
	log_debugp("Dot = %1%", dot);
	log_debugp("Cross = %1%", cross);
}





/*
	TODO:
	This is something that is needed to be handled by the engine,
	and the andromeda configuration file
*/
void configResources(andromeda::ResourceManager * fs)
{
	// Resources
	/*
	TODO
	- Move this to some automated aspect with the engine :: Potentially using the config
	*/
	fs->addResourceType<andromeda::Mesh>("models", andromeda::ResourceManager::Binary);
	fs->addResourceType<andromeda::Effect>("shader");
	fs->addResourceType<andromeda::Texture>("textures", andromeda::ResourceManager::Binary);
	fs->addResourceType<andromeda::CubeTexture>("textures", andromeda::ResourceManager::Binary);
	fs->addResourceType<andromeda::VolumeTexture>("textures", andromeda::ResourceManager::Binary);


	log_warn("main() :: TODO: Rename to Font when Font library is setup fully.");	// This is being logged for a reason :p
	fs->addResourceType<andromeda::FontFace>("fonts", andromeda::ResourceManager::Binary);
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
	

	// Create Engine
	log_debug("main() :: Initialising Engine");

	// Initialise the Engine
	andromeda::initialise(hInstance);


	// Resource management
	configResources(andromeda::Andromeda::Andromeda::instance()->getResourceManager().get());


	// Create Application!
	std::shared_ptr<andromeda::Application> app = std::make_shared<App>();

	// Run Engine
	andromeda::run(app);
	
	log_debug("main() :: Destroying Engine");

	// Destroy the Engine
	andromeda::destroy();

	log_debug("main() :: Fin");

	return 0;
}














