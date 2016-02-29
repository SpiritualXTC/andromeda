#ifndef _ANDROMEDA_GRAPHICS_PARTICLE_SYSTEM_H_
#define _ANDROMEDA_GRAPHICS_PARTICLE_SYSTEM_H_

#include "../stddef.h"

#include <glm/glm.hpp>

#include <andromeda/opengl.h>
#include <andromeda/Renderer/renderable.h>

namespace andromeda
{
	/*
	
	*/
	class ParticleSystem : public IRenderable
	{
	private:
		struct _Particle
		{
			glm::vec3 position;
			glm::vec3 velocity;
			Float lifetime;
		};

	public:
		ParticleSystem();
		virtual ~ParticleSystem();


		void update(Float ft);
		void render(const Shader * const shader, const glm::mat4 & modelView);

	private:
		Boolean _process = false;

		GLuint _buffer[2];
		GLuint _transform[2];

		Int32 _activeBuffer = 0;
		Int32 _activeTransform = 1;

	};
}

#endif