#pragma once 

#include <string>
#include <set>
#include <memory>
#include <unordered_map>

#include <andromeda/stddef.h>
//#include <andromeda/Renderer/view.h>


namespace andromeda
{
	class SceneGraph;
	class View;


	/*
		The Scene!

		This .... can actually be extended cleanly: OMG!
	*/
	class Scene
	{
	private:


	public:
		Scene(const std::string & name, const std::shared_ptr<SceneGraph> & sceneGraph);
		virtual ~Scene();

		/*
			Gets the Scene Name
		*/
		inline const std::string & getName() const { return _name; }

		/*
			Is the scene enabled :: This can come in handy when displaying multiple scenes, and one scene is completely invisible
		*/
		inline Boolean isEnabled() const { return _enabled; }






		/*
			Adds a Precreated View
		*/
		std::shared_ptr<View> addView(std::shared_ptr<View> view);

		/*
			Remove a View
		*/
		Boolean removeView(std::shared_ptr<View> view);

		/*
			Clear all Views
		*/
		Boolean clearViews();


#if 0
		// Currently only Static Views as they are the only type of view that exists
		inline std::shared_ptr<View> addScreenView(const std::string & name)
		{
			return addScreenView(name, 0.0f, 0.0f, 1.0f, 1.0f, View::Normal);
		}
		std::shared_ptr<View> addScreenView(const std::string & name, Float x, Float y, Float width, Float height, Int32 order = View::Normal);
#endif










		/*
			Adds a SceneGraph
		*/
		Boolean addSceneGraph(const std::shared_ptr<SceneGraph> & sg, const std::string & groupName = "");


		/*
			Gets the SceneGraph
		*/
		inline std::shared_ptr<SceneGraph> getSceneGraph(const std::string & groupName = "") 
		{ 
			const auto & it = _graphs.find(groupName);
			return it == _graphs.end() ? nullptr : it->second; 
		}



		/*
			Gets Constant Reference to the SceneGraph
		*/
		const inline std::shared_ptr<SceneGraph> getSceneGraph(const std::string & groupName = "") const 
		{ 
			const auto & it = _graphs.find(groupName);
			return it == _graphs.end() ? nullptr : it->second;
		}




		/*
			Update the Scene
		*/
		void update(const Float timeStep);


		/*
			Syncs the Update Data with the Render Data
			MUST BE VERY LIGHTWEIGHT.
			Minimal processing needed.
		*/
	//	void sync();


		/*
			Render the Scene
		*/
		void render();

	private:

		std::string _name;

		Boolean _enabled = true;
		Boolean _paused = false;
		

		// Map of Scene Graphs used by this scene
		// Why does a Scene need multiple Graphs???? -- This is can be achieved by multiple scenes... and would make more sense that way :)
		std::unordered_map<std::string, std::shared_ptr<SceneGraph>> _graphs;


		std::multiset<std::shared_ptr<View>> _views;	//Maybe an ordered_map :: Referencing Views by name may be useful
	};



	/*
		Builds a scene

		INPUT. Numerous Options. Could be an XML File
		OUTPUT. A Scene Object
	*/
	class SceneBuilder
	{
	public:
		SceneBuilder(){}
		virtual ~SceneBuilder() {}

	};

}

