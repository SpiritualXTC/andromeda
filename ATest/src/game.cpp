#include "game.h"

// dont really wanna include this everywhere ...
#include <andromeda/andromeda.h>
#include <andromeda/resources.h>


#include <andromeda/Game/game_object.h>
#include <andromeda/Game/geometry_component.h>
#include <andromeda/Game/mesh_component.h>
#include <andromeda/Game/text_component.h>
#include <andromeda/Game/transform_component.h>
#include <andromeda/Game/light_component.h>

#include <andromeda/geometry.h>
#include <andromeda/resources.h>

#include <andromeda/graphics.h>
#include <andromeda/Graphics/frame_buffer.h>
#include <andromeda/Graphics/font_atlas.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/renderer.h>
#include <andromeda/Renderer/renderer_deferred.h>
#include <andromeda/Renderer/scene.h>
//#include <andromeda/Renderer/scene_graph_basic.h>
#include <andromeda/Renderer/scene_graph.h>
#include <andromeda/Renderer/scene_manager.h>
#include <andromeda/Renderer/view.h>
#include <andromeda/Renderer/view_builder.h>

#include <andromeda/Utilities/font.h>
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
	//_font = std::make_shared<andromeda::Font>("../res/fonts/arial.ttf", 192);


	// Initialise States
	andromeda::graphics()->setDepthEnable(true);




	// Create the Scene
	//_scene = std::make_shared<andromeda::Scene>("game_scene", std::make_shared<andromeda::BasicSceneGraph>());
	_scene = std::make_shared<andromeda::Scene>("game_scene", std::make_shared<andromeda::SceneGraph>());

	// Add Scene to Scene Manager
	andromeda::scenes()->addScene(_scene);



	// Effect Test
	std::shared_ptr<andromeda::Effect> effect = andromeda::LoadEffect("shader");


	// Create Objects
	std::shared_ptr<andromeda::GameObject> skybox = Factory::createSkybox();
	std::shared_ptr<andromeda::GameObject> ground = Factory::createGround();
	std::shared_ptr<andromeda::GameObject> directionalLight = Factory::createLight();

	// Add Game Object to Scene
	_scene->getSceneGraph()->addGameObject(skybox);
	_scene->getSceneGraph()->addGameObject(ground);
	_scene->getSceneGraph()->addGameObject(directionalLight);


	// Get Handle to Light
	_light = directionalLight->getComponentPtr<andromeda::LightDirectionalComponent>();
	_light->setSpecular(1.0f, 1.0f, 1.0f);



	// Create the Views
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
	std::shared_ptr<andromeda::Font> f = andromeda::LoadFont("arial");

	// Create Font Atlas
	std::shared_ptr<andromeda::FontAtlas> fa = std::make_shared<andromeda::FontAtlas>(f, 128);




	// Create Object
	std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>("text");

	// Create Standard Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();

	// Add Components
	obj->addComponent<andromeda::TransformComponent>(transform);

	transform->x(0.0f);
	transform->y(5.0f);	//2.0f
	transform->z(1.0f);





	// Add RenderComponent
	if (f)
	{
		std::shared_ptr<andromeda::TextRenderComponent> render = std::make_shared<andromeda::TextRenderComponent>(fa, transform);

		render->getMaterial().setDiffuse(1.0f, 0.0f, 1.0f);
		render->getMaterial().setDiffuseTexture(andromeda::LoadTexture("pattern"));

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
	std::shared_ptr<andromeda::Effect> effect = andromeda::LoadEffect("shader");
	std::shared_ptr<andromeda::Effect> defEffect = andromeda::LoadEffect("deferred");




	andromeda::ViewBuilder vb;

	// Add ViewGroup
	vb.addGroup("", _scene->getSceneGraph());
	vb.setRegion(x, y, w, h);


	// Create a View
	std::string name = "view_" + (_views.size() + 1);
	std::shared_ptr<andromeda::View> view = _scene->addView(vb.build());




	// Get the Main SceneGraph
	std::shared_ptr<andromeda::SceneGraph> sg = _scene->getSceneGraph();

	// Load the Cube Texture
	//std::shared_ptr<andromeda::CubeTexture> cubeTex = andromeda::resourceFactory()->getResource<andromeda::CubeTexture>("skybox");
	std::shared_ptr<andromeda::CubeTexture> cubeTex = andromeda::LoadCubeTexture("skybox");

	// Create Deferred Renderer
	std::shared_ptr<andromeda::DeferredRenderer> deferred = std::make_shared<andromeda::DeferredRenderer>(sg, defEffect, "lightDirectional");
	deferred->getCamera()->setPerspectiveFov(glm::pi<aFloat>() / 3.0f * 2.0f, 0.01f, 1000.0f);
	deferred->getCamera()->setView(28.0f);
	deferred->setEnvironmentReflectionMap(cubeTex);



	deferred->addLayer("background", "background", defEffect, "skybox");	//addBackgroundLayer'
	deferred->addLayer("geometry", "terrain", defEffect, "objects");
	deferred->addLayer("geometry", "", defEffect, "objects");				//addDeferredLayer
	deferred->addLayer("geometry", "text", defEffect, "objects");			//addDeferredLayer


	// TODO: Use a different shader - and this layer shouldn't need to be manually added.
	// GameObjects should be flagged as "cast shadow" and the renderable is automatically added to the shadow layer
	deferred->addLayer("shadow", "", defEffect, "shadow");	
	deferred->addLayer("shadow", "text", defEffect, "shadow");

	// Add Directional Light
	deferred->setAmbientLight(_light);



	// Add Debug Stage :: Wireframes
#if 0
	deferred->addLayer("debug", "", effect, "wireframe");
	deferred->addLayer("debug", "terrain", effect, "wireframe");
#endif



	// Add the Renderer
	view->addRenderer("deferred", deferred);


	// Create Local SceneGraph :: This graph doesn't get updated :: It should but it currently doesn't. lol
	std::shared_ptr<andromeda::SceneGraph> dsg = std::make_shared<andromeda::SceneGraph>();
	

	// Create Debug Renderer :: This needs a different SceneGraph
	std::shared_ptr<andromeda::IRenderer> debug = std::make_shared<andromeda::Renderer>(dsg);
	debug->getCamera()->setOrthogonal(1.0f, -1.0f, 1.0f);
	
	debug->addLayer("", "debug", effect, "debug");

	view->addRenderer("debug", debug);



	// Add Debug Render Buffer Streams
	for (aInt32 i = 0; i < 3; ++i)
	{
		std::stringstream name("debug");
		name << i;

		// Create a Debug Game Object to Display
		std::shared_ptr<andromeda::GameObject> obj = Factory::createRenderBufferDebug(name.str(), 1.0f, i * 0.5f - 0.5f, deferred->getGBuffer()->getTexture(i));

		// Add to debug scene graph
		dsg->addGameObject(obj);
	}

	// Add Debug Depth Buffer Stream
	std::shared_ptr<andromeda::GameObject> dobj = Factory::createRenderBufferDebug("debugdepth", -1.0f, 0.5f, deferred->getGBuffer()->getDepthTexture());

	dsg->addGameObject(dobj);


	// Show the Test Shadow Depth Stream :: TEMP
	std::shared_ptr<andromeda::GameObject> sobj = Factory::createRenderBufferDebug("debugshadow", -1.0f, 0.0f, deferred->getShadowMap());

	dsg->addGameObject(sobj);



	return view;
}



/*

*/
std::shared_ptr<Player> Game::createPlayer(aFloat x, aFloat y, aFloat w, aFloat h)
{
	// Create View for Player
	std::shared_ptr<andromeda::View> view = createView(x, y, w, h);

	// Add View to temp list
	_views.push_back(view);

	// Create "Player" Object
	std::shared_ptr<andromeda::GameObject> obj = Factory::createCube();
	
	// Add Game Object to Scene
	_scene->getSceneGraph()->addGameObject(obj);

	// Add to Players Array
	_players.push_back(std::make_shared<Player>(view, view->getRenderer("deferred")->getCamera(), obj));

	return nullptr;
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
		for (const auto & player : _players)
		{
			std::shared_ptr<andromeda::View> view = player->getView();

			if (view->getDisplayRegion().contains(glm::vec2(e.x, e.y)))
			{
				player->alterCameraDistance(e.deltaY * zoom_sensitivity);
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






