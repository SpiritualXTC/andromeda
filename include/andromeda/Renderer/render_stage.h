#pragma once

#include <memory>
#include <vector>


#include "render_cache.h"	// where renderablemanager is currently defined


namespace andromeda
{
	class ILayer;
	class ILayerEnvironment;

	class Camera;
	class Effect;


	class SceneGraph;
	class RenderCache;
	class RenderableGroup;

	class RenderState;


	/*
		TODO:
		Reconstruct the RenderManager into multiple parts.

		The RenderStage should act as a facade to the Manager
	*/



	/*

	*/
	class RenderStage : public IRenderableManager
	{
	private:
		typedef std::unordered_map<std::string, std::unique_ptr<RenderableGroup>> RenderGroupMap;

	public:
		RenderStage(const std::shared_ptr<Camera> & camera = nullptr, const std::shared_ptr<ILayerEnvironment> & enviroment = nullptr);
		virtual ~RenderStage();

		// Begin the State
		virtual void begin(RenderState & gs);		

		// End Stage Setup
		virtual void end(RenderState & gs);			

		// Update all the layers
		void update(SceneGraph * sg);			

		// Render all the layers
		void render(RenderState & state);

		// Adds a Layer
		std::shared_ptr<ILayer> addLayer(const std::string & renderGroup,
			const std::shared_ptr<Effect> & effect, const std::string & technique = "");



		std::shared_ptr<Camera> & getCamera() { return _camera; }
		const std::shared_ptr<Camera> & getCamera() const { return _camera; }




		// Facade Passthroughs :: Currently has the implementation <,<
		Boolean RenderStage::addRenderable(IRenderable * renderable, const std::string & group) override;
		Boolean RenderStage::removeRenderable(IRenderable * renderable, const std::string & group) override;


	protected:
		//std::shared_ptr<RenderCache> & getCache() { return _cache; }
		RenderableGroup * getRenderGroup(const std::string & group);
		
	private:
		



		std::shared_ptr<Camera> _camera;
		std::shared_ptr<RenderCache> _cache;



		std::shared_ptr<ILayerEnvironment> _environment;
		std::vector<std::shared_ptr<ILayer>> _layers;		// Unique Ptr?



		RenderGroupMap _renderGroups;
	};

}
