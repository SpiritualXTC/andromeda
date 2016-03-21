#include "test_engine.h"



#include <andromeda/andromeda.h>
#include <andromeda/Engine/engine.h>
#include <andromeda/Engine/system.h>
#include <andromeda/Renderer/renderer.h>
#include <andromeda/Resources/resource_manager.h>
#include <andromeda/Utilities/timing.h>

#include "app.h"

void testEngine(HINSTANCE hInstance)
{
	// Create Engine
	std::unique_ptr<andromeda::Engine> engine = andromeda::initialise(hInstance);



	// Resource management
	andromeda::ResourceManager * fs = andromeda::ResourceManager::instance();


	// Add Search Paths & Filters
	fs->addFilter("shader", "glslfx");
	fs->addFilter("textures", "png");

	// Add Search Locations
	fs->addLocation("../res");




	// Create Application!
	std::shared_ptr<App> app = std::make_shared<App>();

	engine->addModule<App>(app);

	engine->setDependancy<App, andromeda::Timing>();
	engine->setDependancy<App, andromeda::System>();
	engine->setDependancy<App, andromeda::Renderer>();

	// Initialise Application
	app->initialise();

	// Run Engine
	engine->run();
}