#ifndef _ANDROMEDA_GRAPHICS_VIEW_H_
#define _ANDROMEDA_GRAPHICS_VIEW_H_

/*
	view.h:

	The class has been trimmed down pretty damn heavily.

	Render Target Capabilities have been removed for now.
*/

#include <memory>
#include <unordered_map>

#include <andromeda/stddef.h>

#include <andromeda/Events/resize.h>
#include <andromeda/Math/region.h>


namespace andromeda
{
	// Forward Declarations
	class Camera;
	class IProjection;

	class Layer;
	//class Scene;	// Remove
	class IRenderable;
	class ISceneGraph;
	class SceneGraphCache;

	/*

	*/
	class View //: public ResizeListener
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
		View(const std::shared_ptr<ISceneGraph> sceneGraph, Int32 order = View::Normal)
			: View(sceneGraph, 0.0f, 0.0f, 1.0f, 1.0f, order)
		{

		}

		View(const std::shared_ptr<ISceneGraph> sceneGraph, Float x, Float y, Float width, Float height, Int32 order = View::Normal)
			: View(sceneGraph, nullptr, x, y, width, height, order)
		{

		}

		View(const std::shared_ptr<ISceneGraph> sceneGraph, std::shared_ptr<IProjection> projection, Float x, Float y, Float width, Float height, Int32 order = View::Normal);

		virtual ~View();

		/*
			Gets the Z-Order
		*/
		const inline Int32 zOrder() const { return _zOrder; }

		/*
			Gets the Views Camera
		*/
		const inline std::shared_ptr<Camera> camera() const { return _camera; }

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
			Renderables
		*/
		Boolean addRenderable(const std::string & layer, IRenderable * renderable);
		Boolean removeRenderable(const std::string & layer, IRenderable * renderable);


	private:
		// ResizeListener Event
		/*Boolean onResize(ResizeEventArgs & e) override;*/


		Int32 _zOrder = 0;								// View Order

		Region2f _view;									// Weighted View Region
		Region2i _display;								// View Display Region
		Region2i _screen;								// Screen Region


		std::shared_ptr<IProjection> _projection;		// Projection Matrix
		

		std::shared_ptr<ISceneGraph> _sceneGraph;			// Reference to the SceneGraph for this View :: May Remove This. and Pass Through Render()
		std::shared_ptr<SceneGraphCache> _sceneGraphCache;	// Reference to the "visible" scene


		// Camera Implementations May be up for as massive flexibility change....
		std::shared_ptr<Camera> _camera;				// Camera for the View



		std::unordered_map<std::string, std::unique_ptr<Layer>> _layers;		// Visual Style Layers
																				// Create Default Layer using default shader
																				// Special Systems will need to auto create their own layers (such as particle effects)
																				// Might be possible to override the Layer class ?
	};


	/*
	
	*/
	class ScreenView : public View, public ResizeListener
	{
	public:
		ScreenView(const std::shared_ptr<ISceneGraph> sceneGraph, Int32 order = View::Normal)
			: ScreenView(sceneGraph, 0.0f, 0.0f, 1.0f, 1.0f, order)
		{

		}

		ScreenView(const std::shared_ptr<ISceneGraph> sceneGraph, Float x, Float y, Float width, Float height, Int32 order = View::Normal)
			: ScreenView(sceneGraph, nullptr, x, y, width, height, order)
		{

		}



		ScreenView(const std::shared_ptr<ISceneGraph> sceneGraph, std::shared_ptr<IProjection> projection, Float x, Float y, Float width, Float height, Int32 order = View::Normal);
		virtual ~ScreenView();

	private:

		// ResizeListener Event
		Boolean onResize(ResizeEventArgs & e) override;
	};




	/*
	
	*/
	class TextureView : public View
	{
	public:
		TextureView(const std::shared_ptr<ISceneGraph> sceneGraph)
			: View(sceneGraph, 0.0f, 0.0f, 1.0f, 1.0f, View::Target)
		{	

		}

	};

}

#endif