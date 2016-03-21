#pragma once

#include <memory>



// Graphics Libraries
// Windows Definitions
#	include <GL/glew.h>
#	include <SDL2/SDL.h>
#	include <SDL2/SDL_opengl.h>

/*
	The Framework here is a common initialisation base seperated from the core engine.
*/


class IFramework
{
public:
	IFramework() {}
	virtual ~IFramework() {}
};




class Framework
{
public:
	Framework(std::shared_ptr<IFramework> framework);
	virtual ~Framework();

	bool initialise(int width, int height);
	void loop();



	inline int getWidth() { return _width; }
	inline int getHeight() { return _height; }

private:
	// Event Callbacks
	//Boolean onQuit(QuitEventData & e);
	//Boolean onKeyDown(SDL_KeyboardEvent & e) { return true; }
	//Boolean onKeyUp(SDL_KeyboardEvent & e);



	bool handleEvents(SDL_Event & evt);
	bool handleWindowEvents(SDL_WindowEvent & evt);

	void update();
	void render();
	void postUpdate();

	void checkErrors();

	int _width;
	int _height;
	bool _running;

	SDL_Window * _window;
	SDL_GLContext _context;



	std::shared_ptr<IFramework> _framework;

	//EventManager * _events;	//Rudimentary for now
};



void framework(std::shared_ptr<IFramework> ptr);





