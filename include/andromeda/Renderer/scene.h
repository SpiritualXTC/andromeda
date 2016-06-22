#ifndef _ANDROMEDA_RENDERER_SCENE_H_
#define _ANDROMEDA_RENDERER_SCENE_H_

#include <string>
#include <set>
#include <memory>

#include <andromeda/stddef.h>

#include "view.h"

namespace andromeda
{
	class Effect;
	class SceneGraph;


	/*
		The Scene!

		This .... can actually be extended cleanly: OMG!
	*/
	class Scene
	{
	private:
		struct _LayerGroup
		{
			std::string name;					// Layer Name
			std::shared_ptr<Effect> effect;		// Effect for the Layer
		};




	public:
		Scene(const std::string & name, std::shared_ptr<SceneGraph> sceneGraph);
		virtual ~Scene();


		/*
			TODO:
			Layer Groups
		*/
		Boolean addLayer(const std::string & group, std::shared_ptr<Effect> & effect);


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


		// NOT SUPPORTED YET
		Boolean addTextureView(const std::string & name, const Int32 texWidth, const Int32 texHeight);


		/*
			Gets the Scene Name
		*/
		const std::string & getName() { return _name; }


		/*
			Gets the SceneGraph
		*/
		std::shared_ptr<SceneGraph> getSceneGraph() { return _sceneGraph; }


		/*
			Gets Constant Reference to the SceneGraph
		*/
		const std::shared_ptr<SceneGraph> & getSceneGraph() const { return _sceneGraph; }


		/*
			Update the Scene
		*/
		void update(const Float timeStep);


		/*
			Syncs the Update Data with the Render Data
			SHOULD BE VERY LIGHTWEIGHT.
			Minimal processing needed.
		*/
		void sync();


		/*
			Render the Scene
		*/
		void render();

	private:

		std::string _name;

		
		std::shared_ptr<SceneGraph> _sceneGraph;
		std::multiset<std::shared_ptr<View>> _views;	//Maybe an ordered_map :: Referencing Views by name may be useful

		_LayerGroup _layerGroup;	// TODO: Add LayerGroups
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
