#pragma once

#include <andromeda/glm.h>
#include <andromeda/Renderer/renderable.h>


namespace andromeda
{
	class Geometry;
	class ITexture;

	class LightDirectional;



	namespace deferred
	{
		/*
			A Fullscreen quad so all geometry is encapsulated in the lighting phase
		*/
		class DeferredDirectionalLight : public IRenderable
		{
		public:
			DeferredDirectionalLight(const std::shared_ptr<LightDirectional> & directional);



			void render(RenderState & rs) override;



			inline void setLightMatrix(const glm::mat4 & m) { _lightMatrix = m; }

			inline void setLight(const std::shared_ptr<LightDirectional> & directional) { _light = directional; }
			inline void setShadowMap(const std::shared_ptr<ITexture> & texture) { _shadowMap = texture; }



		private:
			// These attributes need to be stored somewhere where the application can gain direct access to them...
			// For Real-time lighting adjustments...
			// This will do for now, however :)
		//	glm::vec3 _lightDirection;
		//	glm::vec3 _lightDiffuse;

			glm::mat4 _lightMatrix;
			
	
			std::shared_ptr<LightDirectional> _light;
			std::shared_ptr<ITexture> _shadowMap;


			 
			std::shared_ptr<Geometry> _geometry;
		};
	}
}