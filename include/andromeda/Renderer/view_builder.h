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

		LayerBuilder & setLayerGroup(const std::string & groupName);

		LayerBuilder & setEffect(const std::string & effectName);
		LayerBuilder & setEffect(const std::string & effectName, const std::string & techniqueName);

		LayerBuilder & setRenderGroup(const std::string & groupName);


		inline const std::string & getName() const { return _name; }

		inline const std::string & getEffectName() const { return _effectName; }
		inline const std::string & getTechniqueName() const { return _techniqueName; }

		inline const std::string & getLayerGroup() const { return _layerGroup; }

		inline const std::string & getRenderGroup() const { return _renderGroup; }

	private:
		// Layer
		std::string _name;				// Name of the Layer
		std::string _effectName;		// Name of the Effect to Load
		std::string _techniqueName;		// Name of the Technique to use

		// LayerGroup
		std::string _layerGroup;		// Name of the Layer Group

		// RenderGroup
		std::string _renderGroup;		// Name of the RenderGroup used by the layer
	};





	/*
		Creates a View
	*/
	class ViewBuilder
	{
	private:
		struct _LayerGroup
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
			Add Layer Group
		*/
		ViewBuilder & addLayerGroup(const std::string & name, const std::shared_ptr<SceneGraph> sceneGraph);


		/* Creates the View */
		std::shared_ptr<View> build();

		/* Recreates the View */
		std::shared_ptr<View> & rebuild(std::shared_ptr<View> & view);

	private:
		Region2f _screen{ {0, 0}, {1, 1} };

		Int32 _zOrder = 0;

		std::shared_ptr<IProjectionMatrix> _projection;



		std::vector<_LayerGroup> _layerGroups;
		std::vector<LayerBuilder> _layers;
	};

}

#endif
