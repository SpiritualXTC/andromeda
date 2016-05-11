#ifndef _ANDROMEDA_GRAPHICS_VIEW_H_
#define _ANDROMEDA_GRAPHICS_VIEW_H_

/*
	view.h:

	The class has been trimmed down pretty damn heavily.

	Render Target Capabilities have been removed for now.


	TODO:
	Visibility Check and the SceneGraphCache could be tied together a bit better
*/

#include <memory>
#include <unordered_map>

#include <andromeda/stddef.h>

#include <andromeda/Events/resize.h>
#include <andromeda/Math/region.h>


namespace andromeda
{
	// Forward Declarations
	class ICamera;
	class IProjection;
	class IVisibility;

	class Layer;
	class IRenderable;
	class SceneGraph;
	class SceneGraphCache;

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

		// TODO
		/*
		enum _Order
		{
			Default,
			Interface,
			Debug,
		};

		enum _Target
		{
			Texture,
			Screen,
		};
		
		*/


		// View Order Sorting!
		friend Boolean operator <(const std::shared_ptr<View> & lhs, const std::shared_ptr<View> & rhs)
		{
			return lhs->zOrder() < rhs->zOrder();
		}

	public:
		View(const std::shared_ptr<SceneGraph> sceneGraph, Int32 order = View::Normal)
			: View(sceneGraph, 0.0f, 0.0f, 1.0f, 1.0f, order)
		{

		}

		View(const std::shared_ptr<SceneGraph> sceneGraph, Float x, Float y, Float width, Float height, Int32 order = View::Normal)
			: View(sceneGraph, nullptr, nullptr, x, y, width, height, order)
		{

		}

		View(const std::shared_ptr<SceneGraph> sceneGraph, std::shared_ptr<IProjection> projection, std::shared_ptr<IVisibility> visibility,
			Float x, Float y, Float width, Float height, Int32 order = View::Normal);

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
			Renderables
		*/
		Boolean addRenderable(const std::string & layer, IRenderable * renderable);
		Boolean removeRenderable(const std::string & layer, IRenderable * renderable);




		/*
			Set Camera Target using a default Camera
		*/
		Boolean setCameraTarget();

		/*
			Set Camera Target using a GameObject. GameObject must be in the SceneGraph
		*/
		Boolean setCameraTarget(const std::string & name);

		/*
			Set Camera Target using a Custom Camera
		*/
		Boolean setCameraTarget(std::shared_ptr<ICamera> & camera);




		/*
			Gets the Views Camera
		*/
		const inline std::shared_ptr<ICamera> camera() const { return _camera; }

	private:

		Int32 _zOrder = 0;									// View Order

		Region2f _view;										// Weighted View Region
		Region2i _display;									// View Display Region
		Region2i _screen;									// Screen Region



		// Camera Related
		std::shared_ptr<IProjection> _projection;			// Projection Matrix
		std::shared_ptr<ICamera> _camera;					// Camera for the View :: Make this a weak pointer :: Add another Camera for a default camera (Maybe)
		std::shared_ptr<IVisibility> _visibility;			// Visibility Check :: Checks whether a GameObject is visible from this view


		// Scene Reltated
		std::shared_ptr<SceneGraph> _sceneGraph;			// Reference to the SceneGraph for this View
		std::shared_ptr<SceneGraphCache> _sceneGraphCache;	// Lookup table of objects in the "visible" space of the scene from this view




		// View Related
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
		ScreenView(const std::shared_ptr<SceneGraph> sceneGraph, Int32 order = View::Normal)
			: ScreenView(sceneGraph, 0.0f, 0.0f, 1.0f, 1.0f, order)
		{

		}

		ScreenView(const std::shared_ptr<SceneGraph> sceneGraph, Float x, Float y, Float width, Float height, Int32 order = View::Normal)
			: ScreenView(sceneGraph, nullptr, nullptr, x, y, width, height, order)
		{

		}



		ScreenView(const std::shared_ptr<SceneGraph> sceneGraph, std::shared_ptr<IProjection> projection, std::shared_ptr<IVisibility> visibility, 
			Float x, Float y, Float width, Float height, Int32 order = View::Normal);
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
		TextureView(const std::shared_ptr<SceneGraph> sceneGraph)
			: View(sceneGraph, 0.0f, 0.0f, 1.0f, 1.0f, View::Target)
		{	

		}

	};
}

#endif