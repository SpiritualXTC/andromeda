#ifndef _ANDROMEDA_GRAPHICS_RENDERER_H_
#define _ANDROMEDA_GRAPHICS_RENDERER_H_

#include <memory>
#include <set>
#include <unordered_map>

#include <andromeda/stddef.h>

#include <andromeda/Engine/module.h>





namespace andromeda
{
	// Forward-Declarations
	class Scene;
	

	/*
		TODO:
		Currently the SceneManager is doing:

		view->render();		// View Manager
		graphics->clear();

		There is no process where the SceneManager actually UPDATES the scene... only renders it.

		update() ... cannot do both

		This should not be a module
	*/
	
	class SceneManager : public Module<SceneManager>
	{
	public:
		SceneManager();
		virtual ~SceneManager();

		/*
			Add Scene
		*/
		Boolean addScene(std::shared_ptr<Scene> scene);

		/*
			Remove Scene
		*/
		Boolean removeScene(const std::string & name);
		Boolean removeScene(std::shared_ptr<Scene> scene);

		/*
			Has Scene
		*/
		Boolean hasScene(const std::string & name);
		std::shared_ptr<Scene> getScene(const std::string & name);


		
		void update(Float ft);
		void render();


	protected:
		// IModule
		void onPause() override {}
		void onResume() override {}
		void onStop() override {}

		void update() override { render(); }	// TEMP :: Renders the Scene
	private:



		void errorCheck();


		// Scenes (Should really be ordered)
		std::unordered_map<std::string, std::shared_ptr<Scene>> _scenes;
	};



}

#endif