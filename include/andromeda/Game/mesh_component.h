#ifndef _ANDROMEDA_GAME_MESH_COMPONENT_
#define _ANDROMEDA_GAME_MESH_COMPONENT_

#include "render_component.h"

namespace andromeda
{
	class Mesh;
	class ITransform;

	class RenderState;

	class MeshRenderComponent : public RenderComponent
	{
	public:
		MeshRenderComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<ITransform> transform);
		virtual ~MeshRenderComponent();

		void render(const std::shared_ptr<andromeda::IShader> shader, andromeda::MatrixStack & ms) override;
		void render(RenderState & rs) override;

	private:
		std::shared_ptr<Mesh> _mesh;
		std::shared_ptr<ITransform> _transform;
	};
}

#endif
