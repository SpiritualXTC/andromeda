#pragma once

#include <memory>
#include <vector>

namespace andromeda
{
	class ILayer;
	class ILayerEnvironment;

	class Camera;
	class Effect;


	class SceneGraph;
	class RenderCache;
	class RenderableGroup;

	class GraphicsState;

	/*

	*/
	class RenderStage
	{
	public:
		RenderStage(const std::shared_ptr<Camera> & camera = nullptr, const std::shared_ptr<ILayerEnvironment> & enviroment = nullptr);
		virtual ~RenderStage();

		// THIS SECTION NEEDS TO DO CLASS SPECIFIC STUFF...
		// FOR NOW ... NOTHING IS OK :)
		virtual void begin(GraphicsState & gs);		// Begin Stage Setup
		virtual void end(GraphicsState & gs);		// End Stage Setup

		void update(SceneGraph * sg);			// Update all the layers
		void render(GraphicsState & gs);		// Render all the layers

//		std::shared_ptr<ILayer> addLayer(const std::shared_ptr<Camera> & camera, const std::shared_ptr<RenderableGroup> & rg,
//			const std::shared_ptr<Effect> & effect, const std::string & technique = "");

		std::shared_ptr<ILayer> addLayer(/*const std::shared_ptr<Camera> & camera, */const std::string & renderGroup,
			const std::shared_ptr<Effect> & effect, const std::string & technique = "");



		std::shared_ptr<Camera> & getCamera() { return _camera; }
		const std::shared_ptr<Camera> & getCamera() const { return _camera; }

	protected:
		std::shared_ptr<RenderCache> & getCache() { return _cache; }

	private:


		std::shared_ptr<Camera> _camera;
		std::shared_ptr<RenderCache> _cache;



		std::shared_ptr<ILayerEnvironment> _environment;
		std::vector<std::shared_ptr<ILayer>> _layers;
	};

}
