#ifndef _ANDROMEDA_GAME_GEOMETRY_COPMONENT_H_
#define _ANDROMEDA_GAME_GEOMETRY_COPMONENT_H_

#include "render_component.h"

namespace andromeda
{
	class Geometry;
	class ITransform;
	


	class GeometryRenderComponent : public RenderComponent
	{
	public:
		GeometryRenderComponent(std::shared_ptr<Geometry> geometry, std::shared_ptr<ITransform> transform);
		virtual ~GeometryRenderComponent();

		void render(const std::shared_ptr<andromeda::IEffect> effect, andromeda::MatrixStack & ms) override;

	private:
		std::shared_ptr<Geometry> _geometry;
		std::shared_ptr<ITransform> _transform;
	};
}

#endif
