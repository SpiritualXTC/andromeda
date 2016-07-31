#ifndef _ANDROMEDA_RENDERER_VIEW_BUILDER_H_
#define _ANDROMEDA_RENDERER_VIEW_BUILDER_H_

#include <memory>
#include <string>

#include <set>

#include <andromeda/stddef.h>
#include <andromeda/Math/region.h>

namespace andromeda
{
	class IProjectionMatrix;
	class IViewMatrix;

	class View;
	class SceneGraph;



	/*
		Creates a Layer
	*/
	class LayerBuilder
	{
	public:
		LayerBuilder(const std::string & name);

		LayerBuilder & setGroup(const std::string & groupName);
		LayerBuilder & setRenderGroup(const std::string & groupName);

		LayerBuilder & setEffect(const std::string & effectName);
		LayerBuilder & setEffect(const std::string & effectName, const std::string & techniqueName);




		inline const std::string & getName() const { return _name; }
		inline const std::string & getGroup() const { return _group; }


		inline const std::string & getEffectName() const { return _effectName; }
		inline const std::string & getTechniqueName() const { return _techniqueName; }



		inline const std::string & getRenderGroup() const { return _renderGroup; }

	private:
		// Layer
		std::string _name;				// Name of the Layer
		std::string _effectName;		// Name of the Effect to Load
		std::string _techniqueName;		// Name of the Technique to use

										// View Group
		std::string _group;				// Name of the Layer Group

										// RenderGroup
		std::string _renderGroup;		// Name of the RenderGroup used by the layer
	};



	/*
		Creates a View
	*/
	class ViewBuilder
	{
	private:
		struct _Group
		{
			std::string groupName;
			std::shared_ptr<SceneGraph> sceneGraph;
		};

	public:
		ViewBuilder() {}
		virtual ~ViewBuilder() {}


		/*
			Projection Matrices
		*/
		ViewBuilder & setProjectionOrth();
		ViewBuilder & setProjectionPerspective();

		/*
			View Matrices / Camera
		*/

		/*
			Region
		*/
		ViewBuilder & setRegion(Float x, Float y, Float width, Float height);


		/*
			Add Layers
		*/
		ViewBuilder & addLayer(LayerBuilder & lb);

		/*
			Add View Group
		*/
		ViewBuilder & addGroup(const std::string & name, const std::shared_ptr<SceneGraph> sceneGraph);


		/* Creates the View */
		std::shared_ptr<View> build();

		/* Recreates the View */
		std::shared_ptr<View> & rebuild(std::shared_ptr<View> & view);

	private:
		Region2f _screen{ {0, 0}, {1, 1} };

		Int32 _zOrder = 0;

		std::shared_ptr<IProjectionMatrix> _projection;



		std::vector<_Group> _groups;
		std::vector<LayerBuilder> _layers;
	};

}

#endif
