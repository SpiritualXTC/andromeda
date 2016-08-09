#include "game.h"

// dont really wanna include this everywhere ...
#include <andromeda/andromeda.h>
#include <andromeda/resources.h>


#include <andromeda/Game/game_object.h>
#include <andromeda/Game/geometry_component.h>
#include <andromeda/Game/mesh_component.h>
#include <andromeda/Game/text_component.h>
#include <andromeda/Game/transform_component.h>

#include <andromeda/geometry.h>

#include <andromeda/graphics.h>
#include <andromeda/Graphics/frame_buffer.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/renderer.h>
#include <andromeda/Renderer/renderer_deferred.h>
#include <andromeda/Renderer/scene.h>
#include <andromeda/Renderer/scene_graph_basic.h>
#include <andromeda/Renderer/scene_manager.h>
#include <andromeda/Renderer/view.h>
#include <andromeda/Renderer/view_builder.h>

#include <andromeda/Resources/font_resource.h>

#include <andromeda/Utilities/log.h>


#include <xeffect/xeffect.h>

#include "random_path_component.h"
#include "circular_path_component.h"
#include "plane_test_component.h"

#include "player.h"
#include "factory.h"


/*

*/
Game::Game()
{
	// Load a Font
	_font = std::make_shared<andromeda::Font>("../res/fonts/arial.ttf", 192);


	// Initialise States
	andromeda::graphics()->setDepthEnable(true);




	// Create the Scene
	_scene = std::make_shared<andromeda::Scene>("game_scene", std::make_shared<andromeda::BasicSceneGraph>());

	// Add Scene to Scene Manager
	andromeda::scenes()->addScene(_scene);



	// Effect Test
	std::shared_ptr<andromeda::Effect> effect = andromeda::LoadEffect("shader.xml");


	// Create Skybox
	std::shared_ptr<andromeda::GameObject> skybox = Factory::createSkybox();

	// Create Some Objects
	createGround();



	// Create the Views
	// TODO: There is a bug since moving to the deferred renderer when it comes to split/multi screen, 
	// as the viewport is altered when rendering to the offscreen targets but not restored when 
	// doing the lighting pass
	aInt32 players = 1;

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




	// Add Game Object to Scene
	_scene->getSceneGraph()->addGameObject(skybox);






	//createMesh("mesh_0");


	// Create Spheres
	aInt32 objs = 5;// 50;

	for (aInt32 i = 0; i < objs; i++)
	{
		aFloat angle = i / (aFloat)objs * glm::pi<aFloat>() * 2.0f;

		std::shared_ptr<andromeda::GameObject> obj = Factory::createSphere(angle);

		// Add Game Object to Scene
		_scene->getSceneGraph()->addGameObject(obj);
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

		++i;
	}


	// Creates Text
	createText();
}


/*

*/
Game::~Game()
{

}





void Game::createText()
{

	// Load a Font via the ResourceManager
	// TODO: Needs to be Font
	std::shared_ptr<andromeda::FontFace> f = std::make_shared<andromeda::FontFace>("../res/fonts/arial.ttf");
	//std::shared_ptr<andromeda::FontFace> f = std::make_shared<andromeda::FontFace>("../res/fonts/CODE2000.ttf");


	// Create Font Atlas
	std::shared_ptr<andromeda::FontAtlas> fa = std::make_shared<andromeda::FontAtlas>(f, 128);




	// Create Object
	std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>("text");

	// Create Standard Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();

	// Add Components
	obj->addComponent<andromeda::TransformComponent>(transform);

	transform->x(-0.0f);
	transform->y( 0.0f);	//2.0f
	transform->z(-1.0f);





	// Add RenderComponent
	if (f)
	{
		std::shared_ptr<andromeda::FontRenderComponent> render = std::make_shared<andromeda::FontRenderComponent>(fa, transform);

		render->getMaterial().setDiffuse(1.0f, 0.0f, 1.0f);
		render->getMaterial().setDiffuseTexture(andromeda::LoadTexture("pattern0.png"));

		obj->addComponent(render);
	}

	// Add Game Object to Scene
	_scene->getSceneGraph()->addGameObject(obj);
}











/*

*/
std::shared_ptr<andromeda::View> Game::createView(aFloat x, aFloat y, aFloat w, aFloat h)
{
	// Load/Get Effects
	std::shared_ptr<andromeda::Effect> effect = andromeda::LoadEffect("shader.xml");
	std::shared_ptr<andromeda::Effect> defEffect = andromeda::LoadEffect("deferred.xml");




	andromeda::ViewBuilder vb;

	// Add ViewGroup
	vb.addGroup("", _scene->getSceneGraph());
	vb.setRegion(x, y, w, h);


	// Create a View
	std::string name = "view_" + (_views.size() + 1);
	std::shared_ptr<andromeda::View> view = _scene->addView(vb.build());




	// Get the Main SceneGraph
	std::shared_ptr<andromeda::SceneGraph> sg = _scene->getSceneGraph();


	// Create Renderer
	std::shared_ptr<andromeda::IRenderer> renderer = std::make_shared<andromeda::Renderer>(sg);
	renderer->getCamera()->setPerspectiveFov(glm::pi<aFloat>() / 3.0f, 0.01f, 1000.0f);
	renderer->getCamera()->setView(28.0f);
//	view->addRenderer("default", renderer);
//	view->addRendererLayer("default", "", "", effect, "");
//	view->addRendererLayer("default", "text", "", effect, "");

	// Create Deferred Renderer
	std::shared_ptr<andromeda::DeferredRenderer> deferred = std::make_shared<andromeda::DeferredRenderer>(sg, defEffect, "lightDirectional");
	deferred->getCamera()->setPerspectiveFov(glm::pi<aFloat>() / 3.0f, 0.01f, 1000.0f);
	deferred->getCamera()->setView(28.0f);
	deferred->setEnvironmentReflectionmap(andromeda::LoadCubeTexture("skybox", nullptr));

	view->addRenderer("deferred", deferred);
	view->addRendererLayer("deferred", "", "geometry", defEffect, "objects");
	view->addRendererLayer("deferred", "text", "geometry", defEffect, "objects");

	deferred->addDirectionalLight();




	// Create Local SceneGraph :: No Idea where this graph gets updated :O (LOLOLOLOLOLOLOLOL) doesn't matter for now though... none of the components would get updated.
	std::shared_ptr<andromeda::SceneGraph> dsg = std::make_shared<andromeda::BasicSceneGraph>();

	// Create Debug Renderer :: This needs a different SceneGraph :O
	std::shared_ptr<andromeda::IRenderer> debug = std::make_shared<andromeda::Renderer>(dsg);
	debug->getCamera()->setOrthogonal(1.0f, -1.0f, 1.0f);
	view->addRenderer("debug", debug);
	view->addRendererLayer("debug", "debug", "", effect, "debug");




	for (aInt32 i = 0; i < 3; ++i)
	{
		std::stringstream name("debug");
		name << i;

		// Create a Debug Game Object to Display
		std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>(name.str());

		// Add Transform Components
		std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();
		obj->addComponent<andromeda::TransformComponent>(transform);
		transform->position(1.0f, i * 0.5f - 0.5f, 0.0f);
		transform->update(0.0f);

		// Create Geometry
		andromeda::geometry::Cube geom(0.5f);

		std::shared_ptr<andromeda::Geometry> geometry = geom.build(andromeda::geometry::GeometryGenerate::Texture | andromeda::geometry::GeometryGenerate::Normals);


		std::shared_ptr<andromeda::GeometryRenderComponent> render =
			std::make_shared<andromeda::GeometryRenderComponent>(geometry, transform);

		render->setRenderGroup("debug");

		obj->addComponent<andromeda::GeometryRenderComponent>(render);

		render->getMaterial().setDiffuseTexture(deferred->getGBuffer()->getTexture(i));

		// Add to debug scene graph
		dsg->addGameObject(obj);
	}

	return view;
}



/*

*/
std::shared_ptr<Player> Game::createPlayer(aFloat x, aFloat y, aFloat w, aFloat h)
{





	std::shared_ptr<andromeda::View> view = createView(x, y, w, h);

	// Add View to temp list
	_views.push_back(view);

	std::shared_ptr<andromeda::GameObject> obj = Factory::createCube();
	
#if 0
	// Add RenderComponent
	if (_font)
	{
	//	std::shared_ptr<andromeda::RenderComponent> render = std::make_shared<andromeda::GeometryRenderComponent>(geometry, material, transform);

		std::shared_ptr<andromeda::RenderComponent> render = std::make_shared<andromeda::TextRenderComponent>(_font, transform);

		obj->addComponent<andromeda::RenderComponent>(render);
	}
#endif




	// Add Game Object to Scene
	_scene->getSceneGraph()->addGameObject(obj);

	// Add to Players Array
	_players.push_back(std::make_shared<Player>(view, view->getRenderer("deferred")->getCamera(), obj));


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
	std::shared_ptr<andromeda::Texture> tex = andromeda::LoadTexture("pattern0.png");
	andromeda::Material material;

	material.setDiffuse(1, 1, 1)
		.setDiffuseTexture(tex);


	aInt32 divisions = 100;

	// Create Geometry
	andromeda::geometry::Surface surface;
	surface.setDivisions(divisions, divisions)
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
std::shared_ptr<andromeda::GameObject> Game::createCamera(const std::string & name)
{
	// Create Game Object
	std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>(name);
	
	// Create Standard Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();

	//transform->z(2.0f);

	// Add Components
	obj->addComponent<andromeda::TransformComponent>(transform);




	// Create Material

	// Create Geometry
	andromeda::geometry::Ellipse geom(1.0f);
	geom.setSlices(32).setStacks(16);
	
	//andromeda::geometry::Cube geom(16.0f, 0.5f, 0.25f);




	std::shared_ptr<andromeda::Geometry> geometry = nullptr;// geom.build(andromeda::geometry::GeometryGenerate::Texture | andromeda::geometry::GeometryGenerate::Normals);

	// Add RenderComponent
	if (geometry)
	{
		std::shared_ptr<andromeda::RenderComponent> render = std::make_shared<andromeda::GeometryRenderComponent>(geometry, transform);
		obj->addComponent<andromeda::RenderComponent>(render);
	}
//	else
//		return nullptr;


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
	This shouldn't be here :)
*/
void Game::update(aFloat timeStep)
{


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


/*

*/
aBoolean Game::keyUp(andromeda::KeyEventArgs & e)
{
	if (_players.size() == 0)
		return true;

	// Get First Player Only
	std::shared_ptr<Player> & p = _players.front();


	if (e.key == 'q' || e.key == 'Q')
	{
		p->zoomIn();
	}
	else if (e.key == 'e' || e.key == 'E')
	{
		p->zoomOut();
	}

	return true;
}






