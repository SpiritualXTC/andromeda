#include "app.h"

#include <cassert>

#include <andromeda/Engine/engine.h>
#include <andromeda/Events/event_manager.h>
#include <andromeda/Events/resize.h>

#include <andromeda/Engine/system.h>
#include <andromeda/Platform/platform.h>

#include <andromeda/Utilities/log.h>


/*
	TODO:
	This isn't needed. It could just be forward declared
*/
#include <andromeda/Renderer/scene_manager.h>





/*

*/
App::App()
{
	log_verbose("App :: <init>()");

	// Bind Events!
	andromeda::bind<andromeda::CloseEventArgs>(andromeda::System::Close, std::bind(&App::close, this, std::placeholders::_1));
	andromeda::bind<andromeda::ResizeEventArgs>(andromeda::Display::Resize, std::bind(&App::resize, this, std::placeholders::_1));


#if 0
	// Output Informations!
	aInt32 scrWidth = 0;
	aInt32 scrHeight = 0;
	aInt32 cliWidth = 0;
	aInt32 cliHeight = 0;



	std::shared_ptr<aPlatform> platform = _engine->getModulePtr<aPlatform>();

	platform->getScreenResolution(scrWidth, scrHeight);
	platform->getClientResolution(cliWidth, cliHeight);

	log_info("Screen Resolution:", scrWidth, scrHeight);
	log_info("Client Resolution:", cliWidth, cliHeight);





	// Retrieve list of supported displays
	std::set<andromeda::DisplayFormat> displays;

	platform->enumerateDisplaySettings(displays);

	for (auto display : displays)
	{
		log_verbose("Display: ", display.width, display.height);
	}
#endif



	// Create Game Instance
#if 1
	_game = std::make_shared<Game>();
#else
	log_warnp("===========================");
	log_errp("====== Game Disabled ======");
	log_warnp("===========================");
#endif
}

/*

*/
App::~App()
{
	log_verbose("App: Destroy");
}


/*

*/
aBoolean App::close(andromeda::CloseEventArgs & e)
{
	log_debug("Allowing Engine to Quit Automatically");

	return true;
}


/*

*/
aBoolean App::resize(andromeda::ResizeEventArgs & e)
{
	log_debugp("Resize: %1%x%2%", e.displayWidth, e.displayHeight);

	return true;
}


/*

*/
aBoolean App::keyUp(andromeda::KeyEventArgs & e)
{
	// Get System Module
	std::shared_ptr<aSystem> system = andromeda::Andromeda::instance()->getSystem();

	assert(system);

	if (!system)
		return false;

	if (e.key == 27)
	{
		andromeda::Andromeda::instance()->quit();
	}
	else if (e.key == 'F')
	{
		log_eventp("Changing Display Mode");

		andromeda::DisplayParameters params = system->getDisplay()->getDisplayParameters();

		if (params.mode == andromeda::DisplayMode::Windowed)
		{
			params.mode = andromeda::DisplayMode::Borderless;
			params.resolution.width = 0;
			params.resolution.height = 0;
		}
		else
		{
			params.resolution.width = 800;
			params.resolution.height = 600;
			params.mode = andromeda::DisplayMode::Windowed;
		}

		system->changeDisplaySettings(params);
	}
	else if (e.key >= '1' && e.key <= '9')
	{

		log_eventp("Changing Screen Resolution");

		andromeda::DisplayParameters params = system->getDisplay()->getDisplayParameters();


		// Seriously this is a bad idea! (at least, for anything that isn't windowed!)
		if (params.mode == andromeda::DisplayMode::Windowed)
		{
			aInt32 size = e.key - '1' + 1;

			params.resolution.width = size * 100;
			params.resolution.height = size * 100;

			system->changeDisplaySettings(params);
		}
		else if (params.mode == andromeda::DisplayMode::Borderless)
		{
#if 0
			// This is for exclusive fullscreen
			aInt32 i = 0;
			aInt32 index = e.key - '1';

			std::set<andromeda::DisplayFormat> displays = system->getDisplay()->enumDisplaySettings();

			andromeda::DisplayFormat format;

			for (auto & it : displays)
			{
				if (i == index)
				{
					format = it;
					break;
				}
				i++;
			}

			if (i == index)
			{
				andromeda::DisplayParameters params = system->getDisplay()->getDisplayParameters();

				params.resolution = format;
				params.mode = andromeda::DisplayMode::Borderless;

				system->changeDisplaySettings(params);
			}
#endif
		}
	}

//	log_eventp("KeyUp: %1%", e.key);

	return true;
}


/*

*/
aBoolean App::keyDown(andromeda::KeyEventArgs & e)
{
//	log_eventp("KeyDown: %1%", e.key);

	return true;
}

/*

*/
aBoolean App::keyRepeat(andromeda::KeyEventArgs & e)
{
//	log_eventp("KeyRepeat: %1%", e.key);

	return true;
}



/*

*/
aBoolean App::mouseDown(andromeda::MouseButtonEventArgs & e)
{
	log_eventp("MouseDown: %1%, %2%x%3%", e.button, e.x, e.y);

	return true;
}


/*

*/
aBoolean App::mouseUp(andromeda::MouseButtonEventArgs & e)
{
	log_eventp("MouseUp: %1%, %2%x%3%", e.button, e.x, e.y);

	return true;
}

/*

*/
aBoolean App::mouseMove(andromeda::MouseMoveEventArgs & e)
{
	//log_event("MouseMove:", e.x, e.y, e.deltaX, e.deltaY, "Buttons:", e.state);

	return true;
}

/*

*/
aBoolean App::mouseWheel(andromeda::MouseWheelEventArgs & e)
{
	log_eventp("MouseWheel: %1%", e.delta);
	return true;
}












/*

*/
void App::update(aDouble ft)
{
	if (_game)
		_game->update((aFloat)ft);
}
