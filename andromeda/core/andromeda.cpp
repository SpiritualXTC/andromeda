#include "andromeda.h"

#include <boost/shared_ptr.hpp>

#include <common/log.h>
#include <shared/platform.h>

#include "Engine/config.h"
#include "Engine/engine.h"
#include "Engine/timing.h"
#include "Engine/invoke.h"
#include "Graphics/graphics.h"

using namespace andromeda;

Andromeda::Andromeda() :
	_running(false)
{
	// Create Engine
	_engine = std::make_shared<Engine>();

	// Load Config
	_config = std::make_shared<Config>();

	// Create Timer
	_timing = std::make_shared<Timing>();

	// TEMP: Timing should be the first module to be added
	_engine->insert<Timing>(_timing);

	// Create Platform Loader
	_platform = std::make_shared<Platform>(_engine);
	
	// Add Platform Modules
	_graphics = std::make_shared<Graphics>(_platform->getContext(),  _platform->getGraphics());

	// Add Modules
	_engine->insert<Graphics>(_graphics);

	// Add Invoker
	_engine->insert<Invoke>(std::make_shared<Invoke>());
}

Andromeda::~Andromeda()
{


}

Boolean Andromeda::run()
{
	return _engine->run();
}

Boolean Andromeda::quit()
{
	return _engine->quit();
}