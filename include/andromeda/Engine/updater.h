#pragma once

/*
	TODO:
	This does not need to be exposed 
	Deal with hiding laters
*/
#include <memory>

#include "module.h"

namespace andromeda
{
	class SceneManager;

	/*
		This is currently not in use yet.

		Not enough information is available with regards to what will need to be done.
	*/
	class Updater : public Module<Updater>
	{
	public:
		Updater(std::shared_ptr<SceneManager> & sceneManager);

	protected:
		// IModule
		void onPause() override {}
		void onResume() override {}
		void onStop() override {}

		void update() override;

	private:
		std::shared_ptr<SceneManager> _sceneManager;
	};
}