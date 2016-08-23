#include <andromeda/andromeda.h>

#include <andromeda/andromeda_init.h>

#include <andromeda/Engine/application.h>
#include <andromeda/Engine/config.h>
#include <andromeda/Engine/engine.h>
#include <andromeda/Engine/invoker.h>
#include <andromeda/Engine/system.h>

#include <andromeda/Platform/platform.h>

#include <andromeda/Renderer/context.h>
#include <andromeda/Renderer/scene_manager.h>

#include <andromeda/Resources/resource_manager.h>				// REMOVE
#include <andromeda/Resources/resource_location_filesystem.h>	// REMOVE
#include <andromeda/Resources2/resource_factory.h>				// NEW


#include <andromeda/Utilities/log.h>
#include <andromeda/Utilities/timing.h>

#include <andromeda/Events/event_manager.h>


// TEMP
#include <andromeda/Input/input.h>
#include <andromeda/Input/mouse.h>
#include <andromeda/Input/keyboard.h>


using namespace andromeda;




/*

*/



std::shared_ptr<Andromeda> Andromeda::_instance = nullptr;

/*

*/
Boolean Andromeda::initialise(IAndromedaConfig * config)
{
	assert(!_instance);

	log_debugp("Andromeda :: initialise();");

	// Create Instance
	_instance = std::make_shared<Andromeda>(config);


	log_debugp("Andromeda :: initialisation() done;");

	return !!_instance;
}



/*

*/
Boolean Andromeda::destroy()
{
	log_debugp("Andromeda :: destroy();");

	assert(_instance);
	_instance->quit();

	// Lower Reference Count
	_instance.reset();

	return true;
}

















/*

*/
Andromeda::Andromeda(IAndromedaConfig * config)
{
	log_debugp("Andromeda :: <init>()");

	assert(config);

	// Initialise the Resource Manager
	_resources = std::make_shared<ResourceManager>();	// REMOVE

	// Initialise the New Resource Manager
	_resFactory = std::make_shared<ResourceFactory>();




	// Set Loading Methods for KNOWN File Extensions
	// _resources.addType("txt", "conf");				// Generic File resource :: For unknown filetypes
	// _resources.addType("xml");						// XML Files
	// _resources.addType("obj", "x");					// 3D Models :: Asset Importer
	// _resources.addType("png", "dds", "tga", "bmp");	// Textures
	// _resources.addType("glslfx");					// nvFX Shader
	// _resources.addType("vs", "fs", "gs");			// GLSL Shaders







	// Have the Platform Configure Platform-Dependant Resource Management.
	// This will include adding the ability to load from the File System 

	// TODO: Change this to a more general platform config function
	config->init();	



	// Initialise the Configuration Manager
	_config = std::make_shared<Config>();

	// Load Configuration File(s) :: Configuration Files should be stored on the FileSystem (Exception = Android)


	// Add Location to Load Resources From
	// TODO: 
	_resources->addLocation("fs", std::make_shared<ResourceLocationFileSystem>("../res"));



	// Configure the Resource Manager from stored config settings


	

	
	

	// Initialise the System
	log_verbosep("Andromeda :: <init>() :: Create System");
	_system = std::make_shared<System>(config);




	// Initialise the Graphics API
	_graphics = config->initGraphics();

	// Initialise the Engine
	log_verbosep("Andromeda :: <init>() :: Create Engine");
	_engine = std::make_shared<Engine>();

	// Create Invoker
	log_verbosep("Andromeda :: <init>() :: Add Invoker Module");
	_invoker = std::make_shared<Invoker>();
	_engine->addModule<Invoker>(_invoker);
	

	// Create Timing
	log_verbosep("Andromeda :: <init>() :: Add Timing Module");
	_timing = std::make_shared<Timing>();
	_engine->addModule<Timing>(_timing);

	// Add System Modules to Engine
	log_verbosep("Andromeda :: <init>() :: Add System Modules");
	_engine->addModule<Platform>(_system->getPlatform());
	_engine->addModule<Context>(_system->getContext());




	// Create SceneManager
	log_verbosep("Andromeda :: <init>() :: Add Scene Manager");
	_scenes = std::make_shared<SceneManager>();
	_engine->addModule<SceneManager>(_scenes);
	
	// Create Updater for Updating

	// Create Updater for Rendering





	// Add Input Modules
	log_verbosep("Andromeda :: <init>() :: Add Input Modules");

	// TODO: The Platform needs to expose a method for getting a list of Input Devices. For now, this is just a lot of passthroughs
	// The Engine currently will NOT support this action as Template ID's may NOT be correctly inherited (at least from any standpoint that has been tested :S)

	std::shared_ptr<Mouse> mouse = _system->getPlatform()->getMouse();
	std::shared_ptr<Keyboard> keyboard = _system->getPlatform()->getKeyboard();

	if (mouse)
	{
		_engine->addModule<Mouse>(mouse);
		log_verbosep("Andromeda :: <init>() :: Added Mouse Support");
	}
	else
		log_warnp("Andromeda :: <init>() :: No Mouse Detected");

	if (keyboard)
	{
		_engine->addModule<Keyboard>(keyboard);
		log_verbosep("Andromeda :: <init>() :: Added Keyboard Support");
	}
	else
		log_warnp("Andromeda :: <init>() :: No Keyboard Detected");


	log_verbosep("Andromeda :: <init>() :: Done");
}



/*

*/
Andromeda::~Andromeda()
{
	log_verbosep("Andromeda :: <destroy>()");
}


/*

*/
void Andromeda::run(std::shared_ptr<Application> app)
{
	assert(_system);
	assert(_engine);

	log_infop("Andromeda :: run()");

	// Add the Application to the Engine
	_engine->addModule<Application>(app);

	// Start the System
	_system->init();

	// Run the Engine
	_engine->run();
}

/*
	quit():

	Quit Andromeda
*/
void Andromeda::quit()
{
	log_infop("Andromeda :: quit()");

	assert(_engine);

	// Stop the Engine
	_engine->stop();
	
	// Destroy the System
	_system->destroy();
}

/*
	pause():

	Pauses the Engine
*/
void Andromeda::pause()
{
	log_infop("Andromeda :: pause()");

	assert(_engine);

	// Pause the Engine
	_engine->pause(false);



	AppEventArgs e;
	dispatch<AppEventArgs>(System::Pause, e);
}

/*

*/
void Andromeda::resume()
{
	log_infop("Andromeda :: resume()");

	assert(_engine);
	_engine->resume();


	AppEventArgs e;
	dispatch<AppEventArgs>(System::Resume, e);
}

