#include "test_engine.h"



#include <andromeda/andromeda.h>
#include <andromeda/Engine/engine.h>
#include <andromeda/Engine/system.h>

#include <andromeda/Graphics/mesh.h>
#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/texture.h>

#include <andromeda/Renderer/renderer.h>
#include <andromeda/Resources/resource_manager.h>
#include <andromeda/Utilities/timing.h>
#include <andromeda/Utilities/log.h>

#include "app.h"


#include <andromeda/Platform/file.h>



void testEngine(HINSTANCE hInstance)
{
	// Create Engine
	//std::unique_ptr<andromeda::Engine> engine = andromeda::initialise(hInstance);

	log_debugp("TEST: Initialising Engine");

	andromeda::initialise(hInstance);


	log_debugp("TEST: Engine Initialised");




	// Resource management
	//andromeda::ResourceManager * fs = andromeda::ResourceManager::instance();
	andromeda::ResourceManager * fs = andromeda::Andromeda::Andromeda::instance()->getResourceManager().get();


#if 0
	// Register Resource Types :: This is technically not needed -- should happen as soon as any of these are called inline :D
	andromeda::ResourceType<andromeda::Effect>;
	andromeda::ResourceType<andromeda::Mesh>;
	andromeda::ResourceType<andromeda::Texture>;

	log_debugp("Effect Resource ID = %1%", andromeda::ResourceType<andromeda::Effect>::getResourceId());
	log_debugp("Mesh Resource ID = %1%", andromeda::ResourceType<andromeda::Mesh>::getResourceId());
	log_debugp("Texture Resource ID = %1%", andromeda::ResourceType<andromeda::Texture>::getResourceId());
#endif

	
	// Resources
	fs->addResourceType<andromeda::Mesh>("models");
	fs->addResourceType<andromeda::Effect>("shader");
	fs->addResourceType<andromeda::Texture>("textures");

	// Test Loading a Mesh
	//std::shared_ptr<andromeda::Mesh> mesh = fs->loadResource<andromeda::Mesh>("box.dae");
	


	// DONE BY CONFIG
	// Add Search Paths & Filters
	//fs->addFilter("shader", "glslfx");
	//fs->addFilter("textures", "png");

	// Add Search Locations
	//fs->addLocation("../res");


	// Get Engine Reference
	andromeda::IAndromeda * a = andromeda::Andromeda::instance();
	std::shared_ptr<andromeda::Engine> engine = a->getEngine();

	// Create Application!
	std::shared_ptr<App> app = std::make_shared<App>();

	// Initialise Application
	app->initialise();




	// Run Engine
	a->run(app);


	// Destroy the Engine
	andromeda::Andromeda::destroy();
}