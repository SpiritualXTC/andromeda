#pragma once

#include <memory>
#include <string>
#include <list>
#include <unordered_map>


#include <andromeda/glm.h>

#include <andromeda/stddef.h>

#include "camera.h"

#include "renderable.h"


namespace andromeda
{
	class Camera;

	class Effect;
	class ITechnique;
	class IPass;


	class IRenderable;
	class IProjection;

	

	class RenderableGroup;


	// Layer Extension :: This ended up not being needed, but leaving it here anyway. Something might need it eventually.
	class ILayerExtension
	{
	public:
		virtual void begin(const std::shared_ptr<IShader> & shader) = 0;
		virtual void end(const std::shared_ptr<IShader> & shader) = 0;
	};

	// Customise numerous options that need to be applied to many layers :: This is a temporary setup
	// May Change it to be a list of uniforms
	// The Environment incorporates such things as Light Settings, Environment Mapping options - but ONLY when it applies to ALL objects being drawn
	class ILayerEnvironment
	{
	public:
		virtual void begin(const IShader * shader) = 0;
		virtual void end(const IShader * shader) = 0;
	};



	// Abstract Layer
	class ILayer
	{
	public:
		virtual Boolean setActiveTechnique(const std::string & techniqueName) = 0;

		virtual Boolean render(ILayerEnvironment * environment) = 0;

		virtual Boolean addExtension(const std::shared_ptr<ILayerExtension> & extension) = 0;
	};



	/*
		A layer consists of a single effect, an "active" technique that renderes multiple passes
	*/
	class Layer : virtual public ILayer
	{
	public:
		Layer(const std::shared_ptr<Camera> & camera, const std::shared_ptr<Effect> & effect, const std::shared_ptr<RenderableGroup> rg);
		virtual ~Layer();
		

		Boolean setActiveTechnique(const std::string & techniqueName);

		Boolean render(ILayerEnvironment * environment) override;							


		Boolean addExtension(const std::shared_ptr<ILayerExtension> & extension) override;

	protected:
		inline std::shared_ptr<Camera> getCamera() { return _camera; }
		inline std::shared_ptr<RenderableGroup> getRenderGroup() { return _renderGroup; }

	private:
		std::shared_ptr<Effect> _effect;
		std::weak_ptr<ITechnique> _technique;

		std::shared_ptr<Camera> _camera;
		std::shared_ptr<RenderableGroup> _renderGroup;


		std::list<std::shared_ptr<ILayerExtension>> _extensions;
	};













}

