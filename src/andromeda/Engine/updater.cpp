#include <andromeda/Engine/updater.h>

#include <andromeda/andromeda.h>
#include <andromeda/Renderer/scene_manager.h>
#include <andromeda/Utilities/timing.h>

using namespace andromeda;

/*

*/
Updater::Updater(std::shared_ptr<SceneManager> & sceneManager)
	: Module(Module::Update)
	, _sceneManager(sceneManager)
{

}


/*

*/
void Updater::update()
{
	assert(_sceneManager);

	std::shared_ptr<Timing> & timing = Andromeda::instance()->getTiming();

	assert(timing);

	// Get Timing
	Float ft = (Float)timing->frametime();

	// Update Scenes
	_sceneManager->update(ft);
}