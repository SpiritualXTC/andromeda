#include "framework.h"

#include <time.h>

#include <andromeda/Resources/resource_manager.h>
#include <andromeda/Utilities/log.h>

#define GL_GLEXT_PROTOTYPES

// Graphics Libraries
// Windows Definitions
#	include <GL/glew.h>
#	include <SDL2/SDL.h>
#	include <SDL2/SDL_opengl.h>
//#	include <SDL2/SDL_image.h>


// Lazy
#	pragma comment(lib, "SDL2.lib")
#	pragma comment(lib, "SDL2main.lib")
#	pragma comment(lib, "opengl32.lib")
#	pragma comment(lib, "glu32.lib")




/*

*/
Framework::Framework(std::shared_ptr<IFramework> framework)
	: _framework(framework)
{
	assert(_framework);

	_running = false;

	//Timing::getInstance()->_frameRate;

	srand((aUInt32)time(0));



	// Initialise Virtual File System
	andromeda::ResourceManager * fs = andromeda::ResourceManager::instance();

	// Add Search Paths & Filters
	fs->addFilter("shader", "glslfx");

	fs->addFilter("textures", "png");

	// Add Search Locations
	fs->addLocation("../res");

	std::shared_ptr<andromeda::ResourceStream> stream = fs->load("shader.glslfx");
}



/*

*/
Framework::~Framework()
{
	// Delete
	//if (!_game)
	//	delete _game;
	//_game = NULL;


	// Delete Singletons
#if 0
	LineBuffer::destroy();

	FontManager::destroy();
	TextureManager::destroy();
	ShaderManager::destroy();


	EventManager::destroy();
#endif


	// Delete Context
	SDL_GL_DeleteContext(_context);

	// Delete Window
	if (_window)
		SDL_DestroyWindow(_window);
	_window = NULL;
}


/*
initialise():
*/
bool Framework::initialise(int width, int height)
{
	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		log_err("Unable to init SDL:", SDL_GetError());
		return EXIT_SUCCESS;
	}

	// Set double buffering on (must be before window creation)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Setup Backbuffer Properties
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	_width = width;
	_height = height;

	// Create Window
	_window = SDL_CreateWindow("Realtime Rendering: Assignment 3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!_window)
	{
		log_err("Failed to create a window:", SDL_GetError());
		return false;
	}

	// Create Context
	_context = SDL_GL_CreateContext(_window);
	SDL_GL_MakeCurrent(_window, _context);

	// Disable V-Sync (must be after context creation)
	SDL_GL_SetSwapInterval(0);

	// Initialise GLEW (Windows Only)
#ifdef _WIN32
	if (glewInit() != GLEW_OK)
	{
		log_err("Unable to init GLEW (GL Extension Wrangler Library)\n");
		return false;
	}
#endif


	// Set Default OpenGL State Options
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}



/*
loop():
*/
void Framework::loop()
{
	printf("> Entering Loop\n");

	SDL_Event event;

	_running = true;

//	Timing::getInstance()->start();

	while (_running)
	{
//		Timing::getInstance()->update();


		while (SDL_PollEvent(&event))
			handleEvents(event);

		update();
		render();
		postUpdate();
	}

	printf("> Exiting Loop\n");
}




/*
handleWindowEvents():
*/
bool Framework::handleWindowEvents(SDL_WindowEvent & evt)
{
	/* Correct Window? */
	if (evt.windowID != SDL_GetWindowID(_window))
		return true;

	switch (evt.event)
	{
		/* Resize Window */
	case SDL_WINDOWEVENT_RESIZED:
//		_events->dispatchResize(evt.data1, evt.data2);
		break;

		/* Close Window */
	case SDL_WINDOWEVENT_CLOSE:
//		_events->dispatchQuit(true);
		_running = false;
		break;

	default:
		break;
	}

	//Timing::getInstance()->start();


	return true;
}


/*
handleEvents();
*/
bool Framework::handleEvents(SDL_Event & evt)
{
	aBoolean b = true;

	switch (evt.type)
	{
	case SDL_MOUSEMOTION:
//		_events->dispatchMouseMotion(evt.motion);
		break;

	case SDL_MOUSEBUTTONDOWN:
//		_events->dispatchMouseDown(evt.button);
		break;

	case SDL_MOUSEBUTTONUP:
//		_events->dispatchMouseUp(evt.button);
		break;

	case SDL_MOUSEWHEEL:
//		_events->dispatchMouseWheel(evt.wheel);
		break;

	case SDL_KEYDOWN:
//		_events->dispatchKeyDown(evt.key);
		break;

	case SDL_KEYUP:
//		_events->dispatchKeyUp(evt.key);
		break;

	case SDL_WINDOWEVENT:
		b = handleWindowEvents(evt.window);
		break;

	default:
		break;
	}

	return b;
}



/*

*/
void Framework::update()
{
	assert(_framework);

//	_game->update();

}



/*

*/
void Framework::render()
{
	assert(_framework);

	// Clear Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


//	_game->render();

	// Swap Window
	SDL_GL_SwapWindow(_window);



	checkErrors();
}



void Framework::postUpdate()
{
//	_game->postUpdate();
}


/*
checkErrors():

Checks for OpenGL Errors
*/
void Framework::checkErrors()
{
	aInt32 err = 0;

	while ((err = glGetError()) != GL_NO_ERROR)
	{
		log_err("GL Error:", gluErrorString(err));
	}
}



#if 0
/*
onQuit():
*/
Boolean Framework::onQuit(QuitEventData & e)
{
	// Request for quit is being ignored
	/*
	if (e.request)
	{
	// Prompt for Quit ?
	// if Yes. Fire Quit with request set to false
	}
	else
	_running = false;
	*/

	_running = false;

	return true;
}



/*
onKeyUp():
*/
Boolean Framework::onKeyUp(SDL_KeyboardEvent & e)
{
	if (e.keysym.sym == SDLK_ESCAPE)
		_events->dispatchQuit(true);

	return true;
}
#endif