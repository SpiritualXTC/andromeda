#include "app.h"

#include <cassert>

#include <andromeda/Engine/engine.h>
#include <andromeda/Events/event_manager.h>
#include <andromeda/Events/resize.h>

#include <andromeda/Engine/system.h>
#include <andromeda/Platform/platform.h>


#include <andromeda/Graphics/camera.h>
#include <andromeda/Graphics/geometry_generate.h>
#include <andromeda/Graphics/geometry_surface.h>
#include <andromeda/Graphics/particle_system.h>
#include <andromeda/Graphics/renderer.h>
#include <andromeda/Graphics/render_target.h>
#include <andromeda/Graphics/shader.h>
#include <andromeda/Graphics/texture.h>


#include <andromeda/Utilities/log.h>

#include <andromeda/Game/entity.h>
#include <andromeda/Game/camera_component.h>
#include <andromeda/Game/transform_component.h>
#include <andromeda/Game/render_component.h>

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

	// Test Render Target
	_target = std::make_shared<andromeda::RenderTarget>(128, 128);
	_dynView = std::make_shared<andromeda::View>(_target);


	renderer->addView(_dynView);


	std::shared_ptr<aTexture> tex = andromeda::LoadTexture("../res/textures/test.png");

	std::shared_ptr<andromeda::IRenderable> cube = std::shared_ptr<andromeda::IRenderable>(new GeometryRenderable(andromeda::CreateCube(1.0f, 1.0f, 1.0f, andromeda::GEN_TEXTURE | andromeda::GEN_NORMALS), _target));

	


	std::shared_ptr<andromeda::IRenderable> surface = std::shared_ptr<andromeda::IRenderable>(new GeometryRenderable(andromeda::CreateSurface(-5.0f, -5.0f, 5.0f, 5.0f, 100, 100, andromeda::GEN_TEXTURE | andromeda::GEN_NORMALS, [](aFloat x, aFloat y, const void*){return glm::vec3(x, cosf(x) * 0.25f - 1.0f, y); }, nullptr), tex));
	//std::shared_ptr<andromeda::IRenderable> grid = std::shared_ptr<andromeda::IRenderable>(new GeometryRenderable(andromeda::CreateSurface(-5.0f, -5.0f, 5.0f, 5.0f, 100, 100, 0, nullptr)));




	// Create a sphere at the camera position
	std::shared_ptr<GeometryRenderable> sphere = std::make_shared<GeometryRenderable>(andromeda::CreateEllipse(0.25f, 0.25f, 0.25f, 8, 8, 0));
	sphere->posiiton(_view->camera()->position());

	renderer->addRenderable(0, cube);
	renderer->addRenderable(0, surface);
	//renderer->addRenderable(0, grid);

	//renderer->addRenderable(0, sphere);




	// Create Entities!
	createEntity();


	
	// Create Particle System
	_particles = std::make_shared<andromeda::ParticleSystem>();

	renderer->addRenderable(1, _particles);
}


/*

*/





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

	aFloat sensitivity = 0.01f;	// Pull this from engine<Config>

	if (e.state & andromeda::Mouse::LeftBit)
	{
		std::shared_ptr<andromeda::Camera> camera = _view->camera();

		camera->yaw(camera->yaw() + e.deltaX * sensitivity);
		camera->pitch(camera->pitch() + e.deltaY * sensitivity);
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












/*

*/
void App::createEntity()
{
	/*
		This can be pulled from an XML / Pre-Parsed XML
	*/

	// Create Entity
	std::shared_ptr<aEntity> entity = std::make_shared<aEntity>();

	// Create Transform Component
	entity->addComponent<andromeda::TransformComponent>();


	// Create Render Component
	aBoolean render = true;

	if (render)
	{
		//std::shared_ptr<andromeda::Geometry> geometry = andromeda::CreateEllipse(0.5f, 0.5f, 0.5f, 8, 8, 0);
		std::shared_ptr<andromeda::Geometry> geometry = andromeda::CreateCube(0.25f, 0.25f, 0.25f, 0);
		std::shared_ptr<andromeda::RenderComponent> renderable = std::make_shared<andromeda::RenderComponent>(geometry, entity->getComponentPtr<andromeda::TransformComponent>());

		entity->addComponent(renderable);

		// Add Renderable
		getDependancyPtr<andromeda::Renderer>()->addRenderable(0, renderable);
	}


	// Add Camera Module (ONLY TO THE FIRST ENTITY! LOL)
	if (_entities.size() == 0)
	{
		// Create Component
		std::shared_ptr<andromeda::CameraComponent> camera = std::make_shared<andromeda::CameraComponent>(entity->getComponentPtr<andromeda::TransformComponent>());

		entity->addComponent<andromeda::CameraComponent>(camera);

		// Set Camera to View
		_view->camera()->setTarget(entity->getComponentPtr<andromeda::CameraComponent>());

		_dynView->camera()->setTarget(entity->getComponentPtr<andromeda::CameraComponent>());
	}


	// Add Entity
	_entities.push_back(entity);


	glEnable(GL_DEPTH_TEST);
}




/*

*/
void App::update(aDouble ft)
{
	static aFloat angle = 0.0f;
	static aFloat speed = 0.25f;

	// Crappy Game Logic!
	for (auto entity : _entities)
	{
		std::shared_ptr<andromeda::TransformComponent> transform = entity->getComponentPtr<andromeda::TransformComponent>();

		if (transform)
		{
			transform->position(cosf(angle), 0.0f, sinf(angle));
			transform->yaw(-angle);
			
			transform->calculate();
		}
	}


	angle += (aFloat)ft * glm::pi<aFloat>() * speed;


	// Update the Game... that doesn't do anything!
	_game.update((aFloat)ft);
}
