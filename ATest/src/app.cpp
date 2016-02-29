#include "app.h"

#include <cassert>

#include <andromeda/Engine/engine.h>
#include <andromeda/Events/event_manager.h>
#include <andromeda/Events/resize.h>

#include <andromeda/Engine/system.h>
#include <andromeda/Platform/platform.h>


#include <andromeda/Game/camera.h>
#include <andromeda/Game/entity.h>
#include <andromeda/Game/transform_component.h>
#include <andromeda/Game/render_component.h>

#include <andromeda/Geometry/geometry_generate.h>
#include <andromeda/Geometry/geometry_surface.h>

#include <andromeda/Graphics/particle_system.h>
#include <andromeda/Graphics/render_target.h>
#include <andromeda/Graphics/shader.h>
#include <andromeda/Graphics/texture.h>


#include <andromeda/Renderer/renderer.h>


#include <andromeda/Utilities/log.h>



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



	// Create the Renderer : This should be done by the engine :)
	//std::shared_ptr<andromeda::Renderer> renderer = _engine->getModulePtr<andromeda::Renderer>();
	std::shared_ptr<andromeda::Renderer> renderer = getDependancyPtr<andromeda::Renderer>();


	// Load textures
	_texture = andromeda::LoadTexture("../res/textures/test.png");


	// Create the Standard View
	_view = std::make_shared<andromeda::View>();
	renderer->addView(_view);


	// Create a Renderable View
	_target = std::make_shared<andromeda::RenderTarget2>(512, 512, 4);
	_dynView = std::make_shared<andromeda::View>(_target);

	// Add the Renderable View
	renderer->addView(_dynView);


	// Create a Cube
	GeometryRenderable * geomRend = new GeometryRenderable(andromeda::CreateCube(1.0f, 1.0f, 1.0f, andromeda::GEN_TEXTURE | andromeda::GEN_NORMALS), _target);
	std::shared_ptr<andromeda::IRenderable> cube = std::shared_ptr<andromeda::IRenderable>(geomRend);

	
	// Create Ground Surface
	std::shared_ptr<andromeda::IRenderable> surface = std::shared_ptr<andromeda::IRenderable>(new GeometryRenderable(andromeda::CreateSurface(-5.0f, -5.0f, 5.0f, 5.0f, 100, 100, andromeda::GEN_TEXTURE | andromeda::GEN_NORMALS, [](aFloat x, aFloat y, const void*){return glm::vec3(x, cosf(x) * 0.25f - 1.0f, y); }, nullptr), _texture));
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

//	renderer->addRenderable(1, _particles);
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
	// Get System Module
	std::shared_ptr<aSystem> system = getDependancyPtr<andromeda::System>();

	assert(system);

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

		camera = _dynView->camera();

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

	// Get Transformation Component
	std::weak_ptr<andromeda::TransformComponent> transform = entity->getComponentPtr<andromeda::TransformComponent>();


	// Create Render Component
	aBoolean render = true;

	if (render)
	{
		//std::shared_ptr<andromeda::Geometry> geometry = andromeda::CreateEllipse(0.5f, 0.5f, 0.5f, 8, 8, 0);
		//std::shared_ptr<andromeda::Geometry> geometry = andromeda::CreateCube(0.25f, 0.25f, 0.25f, andromeda::GEN_TEXTURE);
		std::shared_ptr<andromeda::Geometry> geometry = andromeda::CreateSphere(0.2f, 8, 4, andromeda::GEN_NORMALS | andromeda::GEN_TEXTURE);
		std::shared_ptr<andromeda::RenderComponent> renderable = std::make_shared<andromeda::RenderComponent>(geometry, transform);
		
		renderable->setTexture(_texture)
			.setAmbient(glm::vec4(1, 0, 0, 1))
			.setDiffuse(glm::vec4(0, 1, 0, 1))
			.setSpecular(glm::vec4(0, 0, 1, 1));

		entity->addComponent(renderable);

		// Add Renderable
		getDependancyPtr<andromeda::Renderer>()->addRenderable(0, renderable);
	}


	// Setup Camera Tracking
	if (_entities.size() == 0)
	{
		

		// Set View Camera's Target
		_view->camera()->setTarget(transform);
		_dynView->camera()->setTarget(transform);
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
