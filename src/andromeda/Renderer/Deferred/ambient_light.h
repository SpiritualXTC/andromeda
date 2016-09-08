#pragma once

#include <andromeda/stddef.h>
#include <andromeda/glm.h>

#include <andromeda/Math/view_matrix.h>

namespace andromeda
{
	// Forward Declarations
	class LightDirectional;
	class Camera;

	class ITexture;


	namespace deferred
	{
		class DeferredDirectionalLight;

		/*
			The Ambient Light View Matrix requirements:

			1. Track the POSITION ONLY of the world matrix :: IE what the "player" or primary viewport sees.
				- There is another piece of information related to the view matrix that is required to correctly construct the final light matrix ... however it is related to the perspective not the view
			2. Construct a matrix (LookAt will do) that looks down in the direction of the light, and offset by the world view position

			This is a primitive implementation -- will do for now, make a bit smart later on. :)
		*/
		class AmbientLightViewMatrix : public IViewMatrix
		{
		public:

			// Get Matrix
			const inline glm::mat4 & matrix() const override { return _view; }

			// Sets the Light Direction
			inline void setLightDirection(const glm::vec3 & direction) { _eye = -direction; }

			/*
				Sets the Position in the World for the Main View Camera
				This allows the ambient light to "move" alongside the world for shadow mapping
			*/
			inline void setWorldPosition(const glm::vec3 & position) { _position = position; }


			// Calculate the View Matrix
			void calculate() override
			{
				// Distance camera is from view point
				_view = glm::lookAt(_eye + _position, _target + _position, _up);
			}

		private:
			glm::mat4 _view;
			
			glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);

			glm::vec3 _eye = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 _target = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
		};


		/*
			Manages the Ambient Light Properties


			This needs to "observe" the light. It will then be require to update changes on everything that is relevant :)

			Might be possible to abstract this class out once the shadowing is working -- as point lights and spot lights MAY be able to cast lights and besides the values -- they will have similiaraties


			The Shadow Map assignment and the Renderable, need to be adjusted once the it working bring it all together and not be such a clusterfuck
		*/
		class DeferredAmbientLight
		{
		public:
			DeferredAmbientLight();
			virtual ~DeferredAmbientLight();

			// Sets the Ambient Light
			void setAmbientLight(const std::shared_ptr<LightDirectional> & ambient);// { _light = ambient; }

			// Sets the Shadow Map
			void setShadowMap(const std::shared_ptr<ITexture> & texture);


			//inline std::shared_ptr<IViewMatrix> getLightViewMatrix()
			inline const std::shared_ptr<Camera> & getLightCamera() const { return _camera; }

			inline const std::shared_ptr<deferred::DeferredDirectionalLight> getRenderable() const { return _renderable; }	// TEMP


			void sync();

		private:
			std::shared_ptr<LightDirectional> _light;

			std::shared_ptr<Camera> _camera;
			std::shared_ptr<AmbientLightViewMatrix> _viewMatrix;	// This is used when rendering the Shadow Map


			std::shared_ptr<deferred::DeferredDirectionalLight> _renderable;

		};
	}
}