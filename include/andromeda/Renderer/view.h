#ifndef _ANDROMEDA_GRAPHICS_VIEW_H_
#define _ANDROMEDA_GRAPHICS_VIEW_H_

/*
	view.h:

	The class has been trimmed down pretty damn heavily.

	Render Target Capabilities have been removed for now.


	TODO:
	Visibility Check and the SceneGraphViewCache could be tied together a bit better
*/

#include <memory>
#include <unordered_map>

#include <andromeda/stddef.h>

#include <andromeda/Events/resize.h>
#include <andromeda/Math/region.h>



#include "camera.h"

namespace andromeda
{
	// Forward Declarations
	class ICamera;
	class IProjection;
	class IRenderable;

	class Layer;
	class LayerGroup;
	class RenderGroup;
	class SceneGraph;
	class SceneGraphViewCache;

	class Effect;

#if 0
	enum class ViewOrder
	{
		Target,
		Screen,
	};
#endif

	/*

	*/
	class View
	{
	public:
		enum _ZOrder		// Make this an Enum Class
		{
			Target,		// Render Target :: is this needed anymore ?? [not sure]
			Normal,		// Typical Game Layer
			Interface,	// Interface/HUD Layer :: Not needed
		};

		// View Order Sorting!
		friend Boolean operator <(const std::shared_ptr<View> & lhs, const std::shared_ptr<View> & rhs)
		{
			return lhs->zOrder() < rhs->zOrder();
		}

	public:
		View(Int32 order = View::Normal)
			: View(0.0f, 0.0f, 1.0f, 1.0f, order)
		{

		}

		View(Float x, Float y, Float width, Float height, Int32 order = View::Normal);


		virtual ~View();

		/*
			Gets the Z-Order
		*/
		const inline Int32 zOrder() const { return _zOrder; }

		/*
		
		*/
		void render();

		/*
		
		*/
		void resize(const Int32 width, const Int32 height);


		inline const Region2f getViewRegion() const { return _view; }
		inline const Region2i getDisplayRegion() const { return _display; }
		inline const Region2i getScreenRegion() const { return _screen; }




		/*
			Render Group
		*/
	//	Boolean addRenderGroup(const std::string & group);

		/*
			Layer Group
		*/
		Boolean addLayerGroup(const std::string & group, const std::shared_ptr<SceneGraph> & sg);


		Boolean addLayer(const std::string & layerName, std::shared_ptr<Effect> effect, const std::string & technique, const std::string & layerGroup, const std::string & renderGroup);

		/*
			Clear Layers, LayerGroups, RenderGroups
		*/
		void clear();


		/*
			Renderables
		*/
		Boolean addRenderable(IRenderable * renderable, const std::string & group = "");
		Boolean removeRenderable(IRenderable * renderable, const std::string & group = "");

		/*
			Gets the Views Camera
		*/
		std::shared_ptr<Camera> & getCamera(const std::string & layerGroup = "");

	private:

		// Add and/or Retrieve the RenderGroup
		std::shared_ptr<RenderGroup> getRenderGroup(const std::string & group);

		// Add and/or Retrieve the LayerGroup
		std::shared_ptr<LayerGroup> getLayerGroup(const std::string & group);



		Int32 _zOrder = 0;									// View Order

		Region2f _view;										// Weighted View Region
		Region2i _display;									// View Display Region
		Region2i _screen;									// Screen Region



		std::unordered_map<std::string, std::unique_ptr<Layer>> _layers;		// Visual Style Layers
																				// Create Default Layer using default shader
																				// Special Systems will need to auto create their own layers (such as particle effects)
																				// Might be possible to override the Layer class ?

		std::unordered_map<std::string, std::shared_ptr<RenderGroup>> _renderGroups;

		std::unordered_map<std::string, std::shared_ptr<LayerGroup>> _layerGroups;
	};










	/*
		TODO:
		Remove this.
		Re-add the functionality as a a component to a View
	*/
	class ScreenView : public View, public ResizeListener
	{
	public:
		ScreenView(Int32 order = View::Normal)
			: ScreenView(0.0f, 0.0f, 1.0f, 1.0f, order)
		{

		}

		ScreenView(Float x, Float y, Float width, Float height, Int32 order = View::Normal)
			: View(x, y, width, height, order)
		{

		}

		virtual ~ScreenView() {}

	private:

		// ResizeListener Event
		Boolean onResize(ResizeEventArgs & e) override;
	};



}

#endif