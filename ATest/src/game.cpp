#include "game.h"

// dont really wanna include this everywhere ...
#include <andromeda/andromeda.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Game/game_object.h>
#include <andromeda/Game/geometry_component.h>
#include <andromeda/Game/mesh_component.h>
#include <andromeda/Game/transform_component.h>

#include <andromeda/geometry.h>

#include <andromeda/graphics.h>

#include <andromeda/Renderer/renderer.h>
#include <andromeda/Renderer/scene.h>
#include <andromeda/Renderer/scene_graph_basic.h>
#include <andromeda/Renderer/view.h>
#include <andromeda/Renderer/view_builder.h>

#include <andromeda/Utilities/log.h>


#include <xeffect/xeffect.h>

#include "random_path_component.h"
#include "circular_path_component.h"
#include "plane_test_component.h"

#include "player.h"



/*

*/
Game::Game(std::shared_ptr<andromeda::Renderer> renderer)
	: _renderer(renderer)
{


	// Do stuff with the renderer

	// Load a Font
	_font = std::make_shared<andromeda::Font>("../res/fonts/unispace rg.ttf", 96);


	// Create the Scene
	_scene = std::make_shared<andromeda::Scene>("game_scene", std::make_shared<andromeda::BasicSceneGraph>());

	// Add Scene to Renderer
	renderer->addScene(_scene);



	// Effect Test
	std::shared_ptr<andromeda::Effect> effect = andromeda::LoadResource<andromeda::Effect>("shader.xml");

	// Add Layers
	andromeda::Boolean addLayers = true;

	if (addLayers)
	{
		if (!effect)
			log_err("Game :: <init>() :: Invalid Effect");
//		else
//			_scene->addLayerGroup(effect);
	}


	// Create the Views
	aInt32 players = 4;

	if (players == 1)
		createPlayer(0, 0, 1, 1);
	else if (players == 2)
	{
		createPlayer(0.0f, 0.0f, 0.5f, 1.0f);
		createPlayer(0.5f, 0.0f, 0.5f, 1.0f);
	}
	else
	{
		createPlayer(0.0f, 0.0f, 0.5f, 0.5f);
		createPlayer(0.5f, 0.0f, 0.5f, 0.5f);

		createPlayer(0.0f, 0.5f, 0.5f, 0.5f);
		createPlayer(0.5f, 0.5f, 0.5f, 0.5f);
	}




	// Create Some Objects
	createGround();

	createMesh("mesh_0");


	aInt32 objs = 50;

	for (aInt32 i = 0; i < objs; i++)
	{
		// Create a bunch of entities in a circle with matching sizes and shapes

		std::stringstream name;
		name << "entity_" << i;

		// Create Entity
		std::shared_ptr<andromeda::GameObject> go = createEntity(name.str());

		// Set Initial Transform
		std::shared_ptr<andromeda::TransformComponent> transform = go->getComponentPtr<andromeda::TransformComponent>();

		aFloat angle = i / (aFloat)objs * glm::pi<aFloat>() * 2.0f;
		//aFloat radius = 2.0f;

		//transform->position(cosf(angle) * radius, 0.0f, sinf(angle) * radius);
		//transform->calculate();


		// Setup Pathing
		std::shared_ptr<CircularPathComponent> circle = std::make_shared<CircularPathComponent>(transform, angle);
		go->addComponent<CircularPathComponent>(circle);
	}



	// Create some cameras..... if it's NOT a single viewport -- this is only cos (lazy)

	aInt32 i = 0;

	for (const auto view : _views)
	{
		std::stringstream name;
		name << "camera_" << i;

		// Create Camera
		std::shared_ptr<andromeda::GameObject> go = createCamera(name.str());

			
		if (players > 1)
		{
			std::shared_ptr<andromeda::TransformComponent> transform = go->getComponentPtr<andromeda::TransformComponent>();

			aFloat angle = i / (aFloat)_views.size() * glm::pi<aFloat>() * 2.0f;
			aFloat radius = 0.5f;

			transform->position(cosf(angle) * radius, 0.0f, sinf(angle) * radius);
			transform->calculate();

			// Add/Create Simple Component
			go->addComponent<RandomPathComponent>(std::make_shared<RandomPathComponent>(transform));
		}

		// Assign the View to the Target
//		view->setCameraTarget(name.str());
//		view->camera()->distance(15.0f);

		++i;
	}



	


}


/*

*/
Game::~Game()
{

}


/*

*/
std::shared_ptr<Player> Game::createPlayer(aFloat x, aFloat y, aFloat w, aFloat h)
{
	// Get Renderer
	std::shared_ptr<andromeda::Renderer> renderer = _renderer.lock();


	

	andromeda::ViewBuilder vb;

	// TODO: This needs to be adjusted. As it shouldn't be needed :)
	// Add default layergroup
	vb.addLayerGroup("", _scene->getSceneGraph());

	vb.addLayer(andromeda::LayerBuilder("layer2").setEffect("shader.xml"));
	vb.setRegion(x, y, w, h);

	// Create a View
	std::string name = "view_" + (_views.size() + 1);
//	std::shared_ptr<andromeda::View> view = _scene->addScreenView(name, x, y, w, h);
	std::shared_ptr<andromeda::View> view = _scene->addView(vb.build());


	// Add View to temp list
	_views.push_back(view);

	// Create Object
	std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>(name);

	// Create Standard Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();

	// Add Components
	obj->addComponent<andromeda::TransformComponent>(transform);

	// Create Geometry
	andromeda::geometry::Cube geom(4.0f, 0.5f, 0.1f);

	std::shared_ptr<andromeda::Geometry> geometry = geom.build(andromeda::geometry::GeometryGenerate::Texture | andromeda::geometry::GeometryGenerate::Normals);

	// Add RenderComponent
	if (geometry)
	{
		std::shared_ptr<andromeda::RenderComponent> render = std::make_shared<andromeda::GeometryRenderComponent>(geometry, transform);
		obj->addComponent<andromeda::RenderComponent>(render);
	}

	// Add Game Object to Scene
	_scene->getSceneGraph()->addGameObject(obj);





	// Add to Players Array
	_players.push_back(std::make_shared<Player>(view, obj));


	return nullptr;
}


/*

*/
std::shared_ptr<andromeda::GameObject> Game::createGround()
{

	andromeda::geometry::SurfaceFunctionLambda<> lamb(
		[&](aFloat x, aFloat z)
	{
		aFloat fx = 100.0f * x;
		aFloat fy = -8.0f;
		aFloat fz = 100.0f * z;

		fy += sinf(x * glm::pi<aFloat>() * 8.0f) * 2.0f;
		fy += sinf(z * glm::pi<aFloat>() * 8.0f) * 2.0f;

		return glm::vec3(fx, fy, fz);
	});




	// Create Game Object
	std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>("ground");

	// Create Standard Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();
	obj->addComponent(transform);

	// Create Material
	std::shared_ptr<andromeda::Texture> tex = andromeda::LoadResource<andromeda::Texture>("pattern0.png");
	andromeda::Material material;

	material.setDiffuse(1, 1, 1)
		.setDiffuseTexture(tex);

	// Create Geometry
	andromeda::geometry::Surface surface;
	surface.setDivisions(1000, 1000)
		.setPositionFunction(&lamb);

	std::shared_ptr<andromeda::Geometry> geometry = surface.build(andromeda::geometry::GeometryGenerate::Texture | andromeda::geometry::GeometryGenerate::Normals);
	

	std::shared_ptr<andromeda::RenderComponent> render = std::make_shared<andromeda::GeometryRenderComponent>(geometry, material, transform);
	obj->addComponent<andromeda::RenderComponent>(render);

	// Add Game Object to Scene
	_scene->getSceneGraph()->addGameObject(obj);

	return obj;
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
	//andromeda::geometry::Cube geom(0.25f, 2.0f, 0.125f);
	andromeda::geometry::Ellipse geom(0.5f);

	std::shared_ptr<andromeda::Geometry> geometry = geom.build(andromeda::geometry::GeometryGenerate::Texture | andromeda::geometry::GeometryGenerate::Normals);

	// Add RenderComponent
	if (geometry)
	{
		std::shared_ptr<andromeda::GeometryRenderComponent> render = std::make_shared<andromeda::GeometryRenderComponent>(geometry, transform);
		obj->addComponent<andromeda::GeometryRenderComponent>(render);

		// Add Plane Test Component
		std::shared_ptr<PlaneTestComponent> planeTest = std::make_shared<PlaneTestComponent>(render, transform);
		obj->addComponent<PlaneTestComponent>(planeTest);
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

	//transform->z(2.0f);

	// Add Components
	obj->addComponent<andromeda::TransformComponent>(transform);






#if 0
	// Load Mesh
	std::shared_ptr<andromeda::Mesh> mesh = andromeda::LoadResource<andromeda::Mesh>("test.dae");

	// Add RenderComponent
	if (mesh)
	{
		std::shared_ptr<andromeda::RenderComponent> render = std::make_shared<andromeda::MeshRenderComponent>(mesh, transform);
		obj->addComponent<andromeda::RenderComponent>(render);
	}
//	else
//		return nullptr;
#else
	// Create Geometry
	andromeda::geometry::Ellipse geom(1.0f);
	geom.setSlices(32).setStacks(16);
	//andromeda::geometry::Cube geom(16.0f, 0.5f, 0.25f);

	std::shared_ptr<andromeda::Geometry> geometry = geom.build(andromeda::geometry::GeometryGenerate::Texture | andromeda::geometry::GeometryGenerate::Normals);

	// Add RenderComponent
	if (geometry)
	{
		std::shared_ptr<andromeda::RenderComponent> render = std::make_shared<andromeda::GeometryRenderComponent>(geometry, transform);
		obj->addComponent<andromeda::RenderComponent>(render);
	}
	else
		return nullptr;
#endif

	// Add Game Object to Scene
	_scene->getSceneGraph()->addGameObject(obj);

	return obj;
}


/*

*/
std::shared_ptr<andromeda::GameObject> Game::createMesh(const std::string & name)
{
	// Create Game Object
	std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>(name);

	// Create Standard Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();

	// Add Components
	obj->addComponent<andromeda::TransformComponent>(transform);

	// Load Mesh
	std::shared_ptr<andromeda::Mesh> mesh;// = andromeda::LoadResource<andromeda::Mesh>("Missile AGM-65.dae");
	
	// Add RenderComponent
	if (mesh)
	{
		std::shared_ptr<andromeda::RenderComponent> render = std::make_shared<andromeda::MeshRenderComponent>(mesh, transform);
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
	// Much of this will happen when the sceneGraph is updated


	// Render Sync
}










/*

*/
aBoolean Game::mouseMove(andromeda::MouseMoveEventArgs & e)
{
	aFloat rotate_sensitivity = 0.01f;
	aFloat zoom_sensitivity = 0.1f;

	if (e.state & andromeda::Mouse::LeftBit)
	{
		// Rotate selected view
		for (const auto & view : _views)
		{
			if (view->getDisplayRegion().contains(glm::vec2(e.x, e.y)))
			{
		//		const std::shared_ptr<andromeda::ICamera> & camera = view->camera();

		//		camera->yaw(camera->yaw() - e.deltaX * rotate_sensitivity);
		//		camera->pitch(camera->pitch() - e.deltaY * rotate_sensitivity);
			}
		}

		// Rotate Selected View
		for (const auto & player : _players)
		{
			std::shared_ptr<andromeda::View> view = player->getView();

			if (view->getDisplayRegion().contains(glm::vec2(e.x, e.y)))
			{

				aFloat yaw = e.deltaX * rotate_sensitivity;
				aFloat pitch = e.deltaY * rotate_sensitivity;

				player->alterCameraRotation(-yaw, -pitch);
			}
		}

	}

	if (e.state & andromeda::Mouse::RightBit)
	{
		// Zoom Selected View
		for (const auto & view : _views)
		{
			if (view->getDisplayRegion().contains(glm::vec2(e.x, e.y)))
			{
//				const std::shared_ptr<andromeda::ICamera> & camera = view->camera();

			//	andromeda::Float distance = camera->distance();

		//		distance += e.deltaY * zoom_sensitivity;

		//		camera->distance(distance);
			}
		}


		// Zoom Selected View
		for (const auto & player : _players)
		{
			std::shared_ptr<andromeda::View> view = player->getView();

			if (view->getDisplayRegion().contains(glm::vec2(e.x, e.y)))
			{
				player->alterCameraDistance(e.deltaY * zoom_sensitivity);

				/*
					TODO:
					This recreates memory :: A listener or observer will be able to solve this issue :)

					Both the View/Projection matrix needs to be "observed" by the Camera.
					Any changes sets a flag -- 
					The flag is polled in the update() function to check for changes
					Any changes resets the flag and updates the matrices
				*/
		

				//vm->setDistance(distance);
				//vm->calculate();
			}
		}
	}


	return true;
}








