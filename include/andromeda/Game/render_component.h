#ifndef _ANDROMEDA_GAME_RENDER_COMPONENT_H_
#define _ANDROMEDA_GAME_RENDER_COMPONENT_H_



#include "component.h"
#include "../Graphics/renderable.h"

namespace andromeda
{
	// Forward Declarations
	class Geometry;
	class Shader;
	class TransformComponent;




	/*
	
	*/
	class RenderComponent : public Component<RenderComponent>, public IRenderable
	{
	public:
		RenderComponent(std::shared_ptr<andromeda::Geometry> geometry, std::weak_ptr<TransformComponent> transform);
		virtual ~RenderComponent();

		void render(const andromeda::Shader * const shader, const glm::mat4 & modelView) override;

	private:
		std::shared_ptr<Geometry> _geometry;
		std::weak_ptr<TransformComponent> _transform;
	};
}


#endif