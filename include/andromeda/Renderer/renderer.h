#ifndef _ANDROMEDA_GRAPHICS_RENDERER_H_
#define _ANDROMEDA_GRAPHICS_RENDERER_H_

#include <memory>
#include <set>
#include <unordered_map>

#include <andromeda/stddef.h>

#include <andromeda/Engine/module.h>
#include <andromeda/Engine/system.h>





namespace andromeda
{
	// Forward-Declarations
	class Scene;
	
	

	/*

	*/
	class Renderer : public Module < Renderer >
	{
	public:
		Renderer();
		virtual ~Renderer();

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



		// IModule
		void onPause(){}
		void onResume(){}

		void update();
	private:



		void errorCheck();


		// Scenes
		std::unordered_map<std::string, std::shared_ptr<Scene>> _scenes;
	};



}

typedef andromeda::Renderer aRenderer;

#endif