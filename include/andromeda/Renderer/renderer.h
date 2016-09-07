#pragma once

#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

#include <boost/multi_index_container.hpp>

#include <andromeda/stddef.h>


namespace andromeda
{

	class IPass;
	class Effect;

	class SceneGraph;

	class Camera;
	class ILayer;
	class ILayerEnvironment;
	

	class RenderableGroup;
	class RenderCache;
	class RenderStage;

	class GraphicsState;

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
		virtual void render(GraphicsState & gs) = 0;




		// TEMP
		virtual std::shared_ptr<Camera> & getCamera() = 0;
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
		Boolean addMethod(const std::string & methodName, const std::shared_ptr<RenderStage> & method);


		// Adds a Layer
		Boolean addLayer(const std::string & method, const std::string & renderGroup,
			const std::shared_ptr<Effect> & effect, const std::string & technique = "") override;
	

		// TEMPORARY
		std::shared_ptr<Camera> & getCamera() { return _camera; }
		const std::shared_ptr<Camera> & getCamera() const { return _camera; }



		// Clears... Stuff
		void clear() override;

		// Updates the Camera
		void update() override;

		// Renders all the methods!
		void render(GraphicsState & gs) override;

		// Resize : Doesn't require any action for the basic renderer
		void resize(Float width, Float height) override;



	protected:
		virtual void onResize(Float width, Float height) {}
	//	virtual void onBegin(){}
	//	virtual void onEnd() {}




		Boolean hasRenderMethod(const std::string & methodName);

		std::shared_ptr<RenderStage> getRenderMethod(const std::string & methodName);

	private:
		std::shared_ptr<SceneGraph> _sceneGraph;



		std::shared_ptr<Camera> _camera;		// Shared Camera :: Could this be a group?

	
	

	//	boost::multi_index_container<std::shared_ptr<RenderStage>> _stages;

		/*
			RenderStates need to be sorted by a priority value
			They also need to be accessed by key (string:name)
		*/
		std::unordered_map<std::string, std::shared_ptr<RenderStage>> _methods;
	};















}