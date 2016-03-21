#ifndef _ANDROMEDA_GAME_RENDER_COMPONENT_H_
#define _ANDROMEDA_GAME_RENDER_COMPONENT_H_


#include <andromeda/Graphics/material.h>

#include <andromeda/Renderer/renderable.h>

#include "../component.h"


namespace andromeda
{
	// Forward Declarations
	
	class Geometry;
	class Shader;
	class Texture;
	class TransformComponent;




	/*
		RenderComponent:

		Flexible Renderer.
		No Animation.

		TEMPORARY:
		Currently the geometry object is placed directly into core component.
		This may be better being done another way
	*/
	class RenderComponent : public Component<RenderComponent>, public IRenderable
	{
	public:
		RenderComponent(std::shared_ptr<andromeda::Geometry> geometry, std::weak_ptr<TransformComponent> transform);
		//RenderComponent(std::weak_ptr<TransformComponent> transform);
		virtual ~RenderComponent();

		void render(const andromeda::Shader * const shader, const glm::mat4 & modelView) override;



		/*
			THE SETTERS HERE ARE ALL TEMPORARY		
		*/

		/* Assign Texture */
		inline RenderComponent & setTexture(std::weak_ptr<Texture> texture) { _texture = texture; return *this; }
		/* Assign Material */
		inline RenderComponent & setAmbient(const glm::vec4 & ambient) { _material.ambient = ambient; return *this; }
		inline RenderComponent & setDiffuse(const glm::vec4 & diffuse) { _material.diffuse = diffuse; return *this; }
		inline RenderComponent & setSpecular(const glm::vec4 & specular) { _material.specular = specular; return *this; }

	private:
		std::shared_ptr<Geometry> _geometry;	// TEMPORARY
		std::weak_ptr<Texture> _texture;		// TEMPORARY
		Material _material;						// TEMPORARY

		std::weak_ptr<TransformComponent> _transform;


		
	};
}


#endif