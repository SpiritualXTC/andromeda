#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <andromeda/stddef.h>

namespace andromeda
{

	class IPass;
	class Effect;

	class SceneGraph;

	class Camera;
	class Layer;
	
	class RenderableGroup;
	class RenderCache;


	/*
		This will end up replacing BOTH, Layers & LayerGroups.

		LayerGroups will be completely removed
		ViewGroups are now being completely removed

		This interface may not be needed, however keeping it could allow for a little more flexibility with Renderer Options.
	*/
	class IRenderer
	{
	public:
		IRenderer() {}


		virtual Boolean addLayer(const std::string & method, const std::string & renderGroup,
			const std::shared_ptr<Effect> & effect, const std::string & technique = "") = 0;

		virtual void resize(Float width, Float height) = 0;

		virtual void clear() = 0;
		virtual void update() = 0;
		virtual void render() = 0;




		// TEMP
		virtual std::shared_ptr<Camera> & getCamera() = 0;
	};











	/*
		Better name pl0x
	*/
	class RendererMethod
	{
	public:
		RendererMethod();
		virtual ~RendererMethod();

		// THIS SECTION NEEDS TO DO CLASS SPECIFIC STUFF...
		// FOR NOW ... NOTHING IS OK :)
		virtual void begin();	// Begin Technique Setup
		virtual void end();		// End Technique Setup

		void render();	// Render all the layers

		void addLayer(const std::shared_ptr<Camera> & camera, const std::shared_ptr<RenderableGroup> & rg,
			const std::shared_ptr<Effect> & effect, const std::string & technique = "");

	private:
		std::vector<std::shared_ptr<Layer>> _layers;
	};




	/*
		This is the Abstract Renderer.

		Most renderers should be able to extend this class
	*/
	class Renderer : public IRenderer
	{
	public:
		Renderer(const std::shared_ptr<SceneGraph> & sg);
		virtual ~Renderer();


		// Adds a Method
		Boolean addMethod(const std::string & methodName, const std::shared_ptr<RendererMethod> & method);


		// Adds a Layer
		Boolean addLayer(const std::string & method, const std::string & renderGroup,
			const std::shared_ptr<Effect> & effect, const std::string & technique = "") override;
	


		std::shared_ptr<Camera> & getCamera() { return _camera; }
		const std::shared_ptr<Camera> & getCamera() const { return _camera; }



		// Clears... Stuff
		void clear() override;

		// Updates the Camera
		void update() override;

		// Renders all the methods!
		void render() override;

		// Resize : Doesn't require any action for the basic renderer
		void resize(Float width, Float height) override;



	protected:
		virtual void onResize(Float width, Float height) {}
		virtual void onBegin(){}
		virtual void onEnd() {}

	private:
		
		std::shared_ptr<Camera> _camera;
		std::shared_ptr<SceneGraph> _sceneGraph;

		std::shared_ptr<RenderCache> _cache;	// Unique_Ptr<> ??

		

		// Make it an unordered map while working out how all this crap gets jammed together

		std::unordered_map<std::string, std::shared_ptr<RendererMethod>> _methods;
	};















}