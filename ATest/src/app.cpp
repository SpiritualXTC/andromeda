#include "app.h"

#include <cassert>

#include <andromeda/Engine/engine.h>
#include <andromeda/Events/event_manager.h>

#include <andromeda/Engine/system.h>
#include <andromeda/Platform/platform.h>

#include <andromeda/Input/keyboard.h>



#include <andromeda/Utilities/log.h>







/*

*/
App::App(std::unique_ptr<andromeda::Engine> engine) : _engine(std::move(engine))
{

	// Bind Close Event!
	andromeda::bind<andromeda::CloseEventArgs>(andromeda::System::Close, std::bind(&App::close, this, std::placeholders::_1));
	andromeda::bind<andromeda::ResizeEventArgs>(andromeda::System::Resize, std::bind(&App::resize, this, std::placeholders::_1));

	// Bind Keyboard Events
	andromeda::bind<andromeda::KeyEventArgs>(andromeda::Keyboard::KeyDown, std::bind(&App::keyDown, this, std::placeholders::_1));
	andromeda::bind<andromeda::KeyEventArgs>(andromeda::Keyboard::KeyUp, std::bind(&App::keyUp, this, std::placeholders::_1));
	andromeda::bind<andromeda::KeyEventArgs>(andromeda::Keyboard::KeyRepeat, std::bind(&App::keyRepeat, this, std::placeholders::_1));

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
}


/*

*/
App::~App()
{

}


/*

*/
void App::run()
{
	assert(_engine);

	_engine->run();
}


/*

*/
aBoolean App::close(andromeda::CloseEventArgs & e)
{
	// This should be an automatically called internally
	// Unless e.cancel, is set to true!
	//_engine->quit();

	log_debug("Allowing Engine to Quit Automatically");

	return true;
}

/*

*/
aBoolean App::resize(andromeda::ResizeEventArgs & e)
{
	log_debug("Resize:", e.displayWidth, e.displayHeight);

	return true;
}


/*

*/
aBoolean App::keyUp(andromeda::KeyEventArgs & e)
{
	if (e.key == 27)
		_engine->quit();
	else if (e.key == 'F')
	{
		std::shared_ptr<aSystem> system = _engine->getModulePtr<aSystem>();

		andromeda::DisplayMode mode;

		if (system->displayMode() == andromeda::DisplayMode::Windowed)
			mode = andromeda::DisplayMode::Borderless;
		else
			mode = andromeda::DisplayMode::Windowed;

		system->changeDisplaySettings(mode);
	}
	else if (e.key >= '1' && e.key <= '9')
	{
		std::shared_ptr<aSystem> system = _engine->getModulePtr<aSystem>();



		// Seriously this is a bad idea! (at least, for anything that isn't windowed!)
		if (system->displayMode() == andromeda::DisplayMode::Windowed)
		{
			aInt32 size = e.key - '1' + 1;
			system->changeDisplaySettings(size * 100, size * 75);
		}
		else
		{
			aInt32 i = 0;
			aInt32 index = e.key - '1';
			
			std::set<andromeda::DisplayFormat> displays;
		
			system->enumerateDisplaySettings(displays);

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

	//		format = it;
			if (i == index)
				system->changeDisplaySettings(format.width, format.height);
		}
	}

	//log_event("KeyUp:", e.key);

	return true;
}


/*

*/
aBoolean App::keyDown(andromeda::KeyEventArgs & e)
{
	//log_event("KeyDown:", e.key);

	return true;
}

/*

*/
aBoolean App::keyRepeat(andromeda::KeyEventArgs & e)
{
	//log_event("KeyRepeat:", e.key);

	return true;
}