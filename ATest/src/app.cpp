#include "app.h"

#include <cassert>

#include <andromeda/Engine/engine.h>
#include <andromeda/Events/event_manager.h>
#include <andromeda/Events/resize.h>

#include <andromeda/Engine/system.h>
#include <andromeda/Platform/platform.h>


#include <andromeda/Graphics/camera.h>
#include <andromeda/Graphics/geometry_builder.h>
#include <andromeda/Graphics/renderer.h>
#include <andromeda/Graphics/shader.h>


#include <andromeda/Utilities/log.h>

#include <andromeda/Game/entity.h>
#include <andromeda/Game/dummy_component.h>


#include "test_renderable.h"

/*

*/
App::App()
{
	log_verbose("App: Create");
}

/*

*/
App::~App()
{
	log_verbose("App: Destroy");
}



/*

*/
//App::App(std::unique_ptr<andromeda::Engine> engine) 
//	: _engine(std::move(engine))
void App::initialise()
{

	// Create Instance of Game... ?
//	std::shared_ptr<Game> game = std::make_shared<Game>(_engine.get());

	// Add Game Dependancies
	// Timing
	// Config
	// System
	// Renderer
	// ResourceManager
	

	// add game to engine


	// Bind Close Event!
	andromeda::bind<andromeda::CloseEventArgs>(andromeda::System::Close, std::bind(&App::close, this, std::placeholders::_1));
	andromeda::bind<andromeda::ResizeEventArgs>(andromeda::System::Resize, std::bind(&App::resize, this, std::placeholders::_1));


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




	//std::shared_ptr<andromeda::Renderer> renderer = _engine->getModulePtr<andromeda::Renderer>();
	std::shared_ptr<andromeda::Renderer> renderer = getDependancyPtr<andromeda::Renderer>();

	// Create a View
	_view = std::make_shared<andromeda::View>();

	renderer->addView(_view);




	std::shared_ptr<andromeda::IRenderable> cube = std::shared_ptr<andromeda::IRenderable>(new GeometryRenderable(andromeda::CreateCube(1.0f, 1.0f, 1.0f, 0)));
	std::shared_ptr<andromeda::IRenderable> plane = std::shared_ptr<andromeda::IRenderable>(new GeometryRenderable(andromeda::CreatePlane(5.0f, 5.0f, 0)));


	renderer->addRenderable(cube);
	renderer->addRenderable(plane);




	// Create entity
	aEntity entity;


	log_debug("Has Dummy Component:", entity.hasComponent<andromeda::DummyComponent>());
	log_debug("Add Dummy Component:", entity.addComponent<andromeda::DummyComponent>());
	log_debug("Has Dummy Component:", entity.hasComponent<andromeda::DummyComponent>());



}


/*

*/
void App::update(aDouble ft)
{

}




#if 0
/*

*/
void App::run()
{
	assert(_engine);

	// Create Instance of Game!
	_engine->run();
}
#endif


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
	log_debug("Resize:", e.displayWidth, e.displayHeight);

	return true;
}


/*

*/
aBoolean App::keyUp(andromeda::KeyEventArgs & e)
{
	std::shared_ptr<aSystem> system = getDependancyPtr<andromeda::System>();

	if (!system)
		return false;

	if (e.key == 27)
	{
	//	_engine->quit();
		system->quit();
	}
	else if (e.key == 'F')
	{
		//std::shared_ptr<aSystem> system = _engine->getModulePtr<aSystem>();

		andromeda::DisplayMode mode;

		if (system->displayMode() == andromeda::DisplayMode::Windowed)
			mode = andromeda::DisplayMode::Borderless;
		else
			mode = andromeda::DisplayMode::Windowed;

		system->changeDisplaySettings(mode);
	}
	else if (e.key >= '1' && e.key <= '9')
	{
		//std::shared_ptr<aSystem> system = _engine->getModulePtr<aSystem>();


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



/*

*/
aBoolean App::mouseDown(andromeda::MouseButtonEventArgs & e)
{
	log_event("MouseDown:", e.button, e.x, e.y);

	return true;
}


/*

*/
aBoolean App::mouseUp(andromeda::MouseButtonEventArgs & e)
{
	log_event("MouseUp:", e.button, e.x, e.y);

	return true;
}

/*

*/
aBoolean App::mouseMove(andromeda::MouseMoveEventArgs & e)
{
	//log_event("MouseMove:", e.x, e.y, e.deltaX, e.deltaY, "Buttons:", e.state);

	if (e.state & andromeda::Mouse::LeftBit)
	{
		std::shared_ptr<andromeda::Camera> camera = _view->camera();

		camera->yaw(camera->yaw()  + e.deltaX * 0.005f);
		camera->pitch(camera->pitch() +e.deltaY * 0.005f);
	}

	return true;
}

/*

*/
aBoolean App::mouseWheel(andromeda::MouseWheelEventArgs & e)
{
	log_event("MouseWheel:", e.delta);
	return true;
}
