#include "app.h"

#include "test.h"

#include <common/log.h>
#include <core/Engine/engine.h>
#include <core/Input/generic_keyboard.h>	// TODO: Should only need to include "keyboard.h, generic_keyboard.h should be hidden away :)"
#include <core/Input/generic_mouse.h>		// TODO: Should only need to include "keyboard.h, generic_keyboard.h should be hidden away :)"
#include <core/Graphics/graphics.h>

void threadRun(App* app)
{
	for (int i = 0; i < 5; ++i)
	{
		std::this_thread::sleep_for(std::chrono::seconds{ 1 });

		log_debug("Waiting");
	}
//	app->quit();
}





App::App(std::shared_ptr<ITest> testRunner)
{
	// Initialise
	log_debug("Creating Application");
	//_thread = std::thread(threadRun, this);

	// Install Keyboard Listener
	std::shared_ptr<andromeda::Keyboard> _keyboard = getEngine()->find<andromeda::Keyboard>();
	std::shared_ptr<andromeda::Mouse> _mouse = getEngine()->find<andromeda::Mouse>();

	if (_keyboard)
	{
		log_debug("App :: Keyboard Installed");
		_keyboard->addObserver(this);
	}

	if (_mouse)
	{
		log_debug("App :: Mouse Installed");
		_mouse->addObserver(this);
	}
	
	std::shared_ptr<andromeda::Graphics> _graphics = getEngine()->find<andromeda::Graphics>();

	_graphics->setClearColor(1.0f, 0.0f, 1.0f);
}

App::~App()
{
	// This be crashing when it's supposed to automatically remove ... during it's attempt to remove ...
	// NOTE: The Crash occurs during app.reset(), which kills andromeda (and consequently; the keyboard) and the application as they all automatically go out of scope
	std::shared_ptr<andromeda::Keyboard> keyboard = getEngine()->find<andromeda::Keyboard>();
	std::shared_ptr<andromeda::Mouse> mouse = getEngine()->find<andromeda::Mouse>();

	if (keyboard)
		keyboard->removeObserver(this);
	if (mouse)
		mouse->removeObserver(this);

	log_debug("Closing Application");
}


aBoolean App::keyDown(const andromeda::KeyEventArgs & e)
{
	return true;
}

aBoolean App::keyUp(const andromeda::KeyEventArgs & e)
{
	log_debugp("App :: KeyUp = %d", e.key);
	if (e.key == 27)
		quit();
	return true;
}

aBoolean App::keyRepeat(const andromeda::KeyEventArgs & e)
{
	return true;
}

aBoolean App::mouseDown(const andromeda::MouseButtonEventArgs& e)
{
	log_debugp("App :: MouseDown = %d", e.button);
	return true;
}

aBoolean App::mouseUp(const andromeda::MouseButtonEventArgs& e)
{
	log_debugp("App :: MouseUp = %d", e.button);
	return true;
}

aBoolean App::mouseMove(const andromeda::MouseMoveEventArgs& e)
{
	return true;
}

aBoolean App::mouseWheel(const andromeda::MouseWheelEventArgs& e)
{
	return true;
}