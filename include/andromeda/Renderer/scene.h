#ifndef _ANDROMEDA_RENDERER_SCENE_H_
#define _ANDROMEDA_RENDERER_SCENE_H_

#include <string>
#include <set>
#include <memory>

#include <andromeda/stddef.h>

#include "view.h"

namespace andromeda
{
	class ISceneGraph;


	/*
		The Scene!

		This .... can actually be extended cleanly: OMG!
	*/
	class Scene
	{
	public:
		Scene(const std::string & name, std::shared_ptr<ISceneGraph> sceneGraph);
		virtual ~Scene();


		/*
			Adds a Precreated View
		*/
		Boolean addView(std::shared_ptr<View> view);

		/*
			Remove a View
		*/
		Boolean removeView(std::shared_ptr<View> view);

		/*
			Clear all Views
		*/
		Boolean clearViews();



		// Currently only Static Views as they are the only type of view that exists
		inline std::shared_ptr<View> addScreenView(const std::string & name)
		{
			return addScreenView(name, 0.0f, 0.0f, 1.0f, 1.0f, View::Normal);
		}
		std::shared_ptr<View> addScreenView(const std::string & name, Float x, Float y, Float width, Float height, Int32 order = View::Normal);



		Boolean addTextureView(const std::string & name, const Int32 texWidth, const Int32 texHeight);


		/*
			Gets the Scene Name
		*/
		const std::string & getName() { return _name; }

		/*
			Gets the SceneGraph
		*/
		std::shared_ptr<ISceneGraph> getSceneGraph() { return _sceneGraph; }

		/*
			Gets Constant Reference to the SceneGraph
		*/
		const std::shared_ptr<ISceneGraph> & getSceneGraph() const { return _sceneGraph; }



		/*
			Render the Scene
		*/
		void render();

	private:

		std::string _name;

		
		std::shared_ptr<ISceneGraph> _sceneGraph;
		std::multiset<std::shared_ptr<View>> _views;	//Maybe an ordered_map :: Referencing Views by name may be useful
	};



	/*
		Builds a scene

		INPUT. Numerous Options. Could even be XML File
		OUTPUT. A Scene Object
	*/
	class SceneBuilder
	{
	public:
		SceneBuilder(){}
		virtual ~SceneBuilder() {}

	};

}

#endif
