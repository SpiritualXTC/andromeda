#include <andromeda/andromeda.h>

#include <Windows.h>

#include <andromeda/Engine/engine.h>
#include <andromeda/Engine/system.h>

#include <andromeda/Graphics/context.h>
#include <andromeda/Graphics/renderer.h>

#include <andromeda/Input/keyboard.h>
#include <andromeda/Input/mouse.h>

#include "Graphics/context_windows.h"
#include "Platform/platform_windows.h"

#include <andromeda/Utilities/log.h>


#include <andromeda/Engine/system.h>

using namespace andromeda;


/*
	Initialise the Engine Under Windows:
	This way the entire creation process is windows-centric, rather than a shit tonne of crappy functions linking everywhere with return values :)
*/
std::unique_ptr<Engine> andromeda::initialise(HINSTANCE hInstance)
{
	// Create Engine:
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	// Get the System Module
	std::weak_ptr<System> system = engine->getModulePtr<System>();


	// Create Platform and Graphics Context
	std::shared_ptr<PlatformWindows> platform = std::make_shared<PlatformWindows>(system, hInstance);
	std::shared_ptr<ContextWindows> context = std::make_shared<ContextWindows>(system, platform);
	
	
	engine->addModule<Platform>(std::static_pointer_cast<Platform>(platform));
	engine->addModule<Context>(std::static_pointer_cast<Context>(context));


	// Create Input Devices!
	engine->addModule<Keyboard>();
	engine->addModule<Mouse>();


	// Assign Platform Dependancies
	engine->setDependancy<Platform, Keyboard>();
	engine->setDependancy<Platform, Mouse>();

	

	return std::move(engine);
}

