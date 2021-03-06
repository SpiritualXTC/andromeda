#pragma once

#include <andromeda/Graphics/material.h>

#include "render_component.h"

namespace andromeda
{
	class Geometry;
	class Texture;
	class ITransform;
	
	class GraphicsState;

	class GeometryRenderComponent : public RenderComponent
	{
	public:
		GeometryRenderComponent(std::shared_ptr<Geometry> geometry, std::shared_ptr<ITransform> transform);
		GeometryRenderComponent(std::shared_ptr<Geometry> geometry, const Material & material, std::shared_ptr<ITransform> transform);
		virtual ~GeometryRenderComponent();


		void render(GraphicsState & state) override;


		Material & getMaterial() { return _material; }

		const Material & getMaterial() const { return _material; }

	private:
		Material _material;

		std::shared_ptr<Geometry> _geometry;

		std::shared_ptr<ITransform> _transform;
		
	};
}

