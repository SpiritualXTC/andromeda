#pragma once

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

#include <andromeda/Utilities/observable.h>
#include <andromeda/Utilities/observer.h>

namespace andromeda
{
	// Forward Declarations
	class IRenderer;
	class Effect;



	class IViewTarget : public Observable<IViewTarget>
	{
	public:
		IViewTarget() {}
		virtual ~IViewTarget() {}

		virtual Int32 width() const = 0;
		virtual Int32 height() const = 0;
	};


	/*
		The View is Drawn to the Screen
	*/
	class ViewScreen : public IViewTarget, public ResizeListener
	{
	public:
		ViewScreen();
		virtual ~ViewScreen();

		Int32 width() const override { return _width; }
		Int32 height() const override { return _height; }


	protected:
		// ResizeListener Event
		Boolean onResize(ResizeEventArgs & e) override;

	private:
		Int32 _width = 0;
		Int32 _height = 0;
	};



	/*
		The View is Drawn to a Texture... worry about semantics, options - and how it's done, later :)

		This probably needs a lot more ... stuff
	*/
	class ViewTexture : public IViewTarget
	{
	public:

	};










	/*

	*/
	class View : public IObserver<IViewTarget>
	{
	public:
		enum _ZOrder		// Make this an Enum Class :: Is this required ??? [I assume it should be, view's using something other than the BackBuffer for drawing will need to be rendered before anything else]
		{
			Target,		// Render Target :: is this needed anymore ?? [not sure]
			Normal,		// Typical Game Layer
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
			Getters
		*/

		// Gets the Z-Order
		const inline Int32 zOrder() const { return _zOrder; }

		inline const Region2f getViewRegion() const { return _view; }
		inline const Region2i getDisplayRegion() const { return _display; }
		inline const Region2i getScreenRegion() const { return _screen; }


		// Gets the Renderer
		std::shared_ptr<IRenderer> getRenderer(const std::string & rendererName);




		// Adds a Renderer to the View
		Boolean addRenderer(const std::string & rendererName, const std::shared_ptr<IRenderer> & renderer);


		// Adds a Layer to a Renderer
//		Boolean addRendererLayer(const std::string & rendererName, const std::string & renderGroup, const std::string & renderMethod,
//			const std::shared_ptr<Effect> effect, const std::string & technique);

		// Render the View
		void render();



		// Clear
		void clear();


		// This will be the final -- I Hope... lololol :)
		// The Cache is now handled by the renderer itself
		// RenderGroups are handled by the cache
		std::unordered_map<std::string, std::shared_ptr<IRenderer>> _renderer;

		/*
			Renderer Examples:
				deferred	- 3D geometry to a GBuffer, then draws the Gbuffer and processes lighting calculations
				basic		- Renders directly to the screen

			From the RenderGroup examples:
				A single deferred renderer would render terrain/objects/lights
				Multiple basic renderers would be used to render the hud, interface, 3D debug layer, 2D debug layer
		*/


	protected:


		// Resize the View :: The public facing resize() should only be able to resize the weighted values
		void resize(const Int32 width, const Int32 height);

		// IObserver<IViewTarget>
		void notify(const IViewTarget * const vt) override;


	private:
		Int32 _zOrder = 0;									// View Order

		Region2f _view;										// Weighted View Region
		Region2i _display;									// View Display Region
		Region2i _screen;									// Screen Region


		std::shared_ptr<ObserverHelper<IViewTarget>> _helper;
		std::shared_ptr<IViewTarget> _target;

			/*
				RenderGroup Examples:
						
					terrain		
						- 3D world camera : Camera 1
						- Shader to render geometry : Shader 1
							- Technique 1, Pass 1
							
						- SceneGraph = 'world'
						- Renderer = Deferred, Method = Terrain

					objects
						- 3D world camera : Camera 1
						- Shader to render geometry : Shader 2
							(Objects and Terrain could share the same shader, but terrain may need be doing tesselation in the shader)
							- Technique 1, Pass 2
							
						- SceneGraph = 'world'
						- Renderer = Deferred, Method = Objects

					text
						- 3D world camera : Camera 1
						- Shader to render text : Shader 6 (Could also be shader 2)
							(depending on special color options)
						- This is for 3D text that could be used for "Augmented Reality". So, is "present" in the world
						
						- SceneGraph = 'world'
						- Renderer = Deferred, Method = Text/Objects

					lights		
						- 3D world camera : Camera 1
						- Shader to render lights and process GBuffer : Shader 3 
							(Deferred Rendering Only - Renders lights to screen by processing values stored in the GBuffer)
							- Technique 2, Pass 1
						- It may be required to use multiple light layers. One for directional and one for bounded lights (point/spotlight)

						- SceneGraph = 'world'
						- Renderer = Deferred, Method = Deferred

					hud	/ interface		
						- 2D ortho Camera : Camera 2
						- Shader to render direct to screen : Shader 4
						- Hud & Interface are logically separate however are very similiar in the way they work
							(Should use separate cameras, however would probably use the same shader)

						- SceneGraph = 'hud' or 'Interface'
						- Renderer = Simple2D
							
					debug3d		
						- 3D world camera : Camera 1
						- Shader to render direct to screen : Shader 5
						- Shows debug information on objects (Normals, etc)
						- SceneGraph = 'world'
						- Renderer = Simple3D

					debug2d		
						- 2D world camera : Camera 3
						- Shows text information to the screen (Console, kinda thing)
						- SceneGraph = 'debug'
						- Renderer = Simple 2D
			*/
	};
}

