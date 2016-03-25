#include "game.h"

#include <andromeda/Game/camera.h>
#include <andromeda/Game/game_object.h>
#include <andromeda/Game/geometry_component.h>
#include <andromeda/Game/transform_component.h>

#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_generate.h>


#include <andromeda/Renderer/renderer.h>
#include <andromeda/Renderer/scene.h>
#include <andromeda/Renderer/scene_graph_basic.h>
#include <andromeda/Renderer/view.h>

#include <andromeda/Utilities/log.h>


#include "random_path_component.h"





/*

*/
Game::Game(std::shared_ptr<andromeda::Renderer> renderer)
	: _renderer(renderer)
{


	// Do stuff with the renderer

	// Create the Scene
	_scene = std::make_shared<andromeda::Scene>("game_scene", std::make_shared<andromeda::BasicSceneGraph>());

	// Add Scene to Renderer
	renderer->addScene(_scene);


	// Create the Views
	aInt32 players = 2;

	if (players == 1)
		createView(0, 0, 1, 1);
	else if (players == 2)
	{
		createView(0.0f, 0.0f, 0.5f, 1.0f);
		createView(0.5f, 0.0f, 0.5f, 1.0f);
	}
	else
	{
		createView(0.0f, 0.0f, 0.5f, 0.5f);
		createView(0.5f, 0.0f, 0.5f, 0.5f);

		createView(0.0f, 0.5f, 0.5f, 0.5f);
		createView(0.5f, 0.5f, 0.5f, 0.5f);
	}

	// Create Some Objects

	//createEntity("test_1");
	//createEntity("test2");
	//createEntity("test3");


	aInt32 objs = 100;

	for (aInt32 i = 0; i < objs; i++)
	{
		// Create a bunch of entities in a circle with matching sizes and shapes

		std::stringstream name;
		name << "entity_" << i;

		// Create Entity
		std::shared_ptr<andromeda::GameObject> go = createEntity(name.str());

		std::shared_ptr<andromeda::TransformComponent> transform = go->getComponentPtr<andromeda::TransformComponent>();

		aFloat angle = i / (aFloat)objs * glm::pi<aFloat>() * 2.0f;
		aFloat radius = 2.0f;

		transform->position(cosf(angle) * radius, 0.0f, sinf(angle) * radius);
		transform->calculate();
	}



	// Create some cameras..... if it's NOT a single viewport -- this is only cos (lazy)
	if (players > 1)
	{
		aInt32 i = 0;

		//for (aInt32 i = 0; i < _views.size(); ++i)
		for (const auto view : _views)
		{
			std::stringstream name;
			name << "camera_" << i;

			// Create Camera
			std::shared_ptr<andromeda::GameObject> go = createCamera(name.str());

			std::shared_ptr<andromeda::TransformComponent> transform = go->getComponentPtr<andromeda::TransformComponent>();

			aFloat angle = i / (aFloat)_views.size() * glm::pi<aFloat>() * 2.0f;
			aFloat radius = 0.5f;

			transform->position(cosf(angle) * radius, 0.0f, sinf(angle) * radius);
			transform->calculate();


			// Assign the View to the Target
			view->setCameraTarget(name.str());
			view->camera()->distance(5.0f);

			++i;
		}
	}

}


/*

*/
Game::~Game()
{

}


/*

*/
void Game::createView(aFloat x, aFloat y, aFloat w, aFloat h)
{
	// Get Renderer
	std::shared_ptr<andromeda::Renderer> renderer = _renderer.lock();

	// Create 3D Static View
	//std::shared_ptr<andromeda::View> view = std::make_shared<andromeda::View>(_scene->getSceneGraph(), x, y, w, h);

	// Add View to renderer
	std::string name = "view_" + (_views.size() + 1);
	std::shared_ptr<andromeda::View> view = _scene->addScreenView(name, x, y, w, h);

	view->camera()->distance(8.0f);

	// Add View to temp list
	_views.push_back(view);
}


/*

*/
std::shared_ptr<andromeda::GameObject> Game::createEntity(const std::string & name)
{
	// Create Game Object
	std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>(name);

	// Create Standard Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();

	// Add Components
	obj->addComponent<andromeda::TransformComponent>(transform);


	// Create Geometry
	std::shared_ptr<andromeda::Geometry> geometry = andromeda::CreateEllipse(0.5f, 0.5f, 0.5f, 32, 16, 0);;

#if 0
	int shape = rand() % 2;
	
	if (shape == 0)
		geometry = andromeda::CreateEllipse(0.5f, 0.5f, 0.5f, 32, 16, 0);
	else if (shape == 1)
		geometry = andromeda::CreateCube(0.25f, 2.0f, 0.25f, 0);
	else if (shape == 2)
		geometry = andromeda::CreatePlane(4, 4, 0);
#endif


	// Add RenderComponent
	if (geometry)
	{
		std::shared_ptr<andromeda::RenderComponent> render = std::make_shared<andromeda::GeometryRenderComponent>(geometry, transform);
		obj->addComponent<andromeda::RenderComponent>(render);
	}
	else
		return nullptr;

	// Add Game Object to Scene
	_scene->getSceneGraph()->addGameObject(obj);

	return obj;
}


/*

*/
std::shared_ptr<andromeda::GameObject> Game::createCamera(const std::string & name)
{
	// Create Game Object
	std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>(name);
	
	// Create Standard Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();

	// Add Components
	obj->addComponent<andromeda::TransformComponent>(transform);

	// Add/Create Simple Component
	obj->addComponent<RandomPathComponent>(std::make_shared<RandomPathComponent>(transform));




	// Create Geometry
	std::shared_ptr<andromeda::Geometry> geometry = andromeda::CreateCube(0.25f, 0.25f, 0.25f, 0);

	// Add RenderComponent
	if (geometry)
	{
		std::shared_ptr<andromeda::RenderComponent> render = std::make_shared<andromeda::GeometryRenderComponent>(geometry, transform);
		obj->addComponent<andromeda::RenderComponent>(render);
	}
	else
		return nullptr;

	// Add Game Object to Scene
	_scene->getSceneGraph()->addGameObject(obj);

	return obj;
}






/*

*/
void Game::update(aFloat timeStep)
{
#if 0
	aFloat ft2 = timeStep * 0.5f;


	// Physics Update
	for (aInt32 i = 0; i < _entities.size; ++i)
	{
		// No Entity
		if (! _entities.status[i])
			continue;


		_entities.vel[i] += _entities.acc[i] * ft;
		_entities.pos[i] += _entities.acc[i] * ft2 + _entities.vel[i] * ft;
	}
#endif

	// Update the Scene
	_scene->update(timeStep);


	// Collision Detection



	// Entity Update (Entity Specific Updates - animation / scripts / shrugs)


	// Render Sync
}










/*

*/
aBoolean Game::mouseMove(andromeda::MouseMoveEventArgs & e)
{
	aFloat sensitivity = 0.01f;

	if (e.state & andromeda::Mouse::LeftBit)
	{
		// Rotate selected view
		for (const auto & view : _views)
		{
			if (view->getDisplayRegion().contains(glm::vec2(e.x, e.y)))
			{
				std::shared_ptr<andromeda::ICamera> camera = view->camera();

				camera->yaw(camera->yaw() + e.deltaX * sensitivity);
				camera->pitch(camera->pitch() + e.deltaY * sensitivity);
			}
		}
	}

	return true;
}








