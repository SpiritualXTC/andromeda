#ifndef _ANDROMEDA_GAME_TRANSFORM_COMPONENT_H_
#define _ANDROMEDA_GAME_TRANSFORM_COMPONENT_H_


#include <andromeda/Game/component.h>
#include <andromeda/Game/transform.h>

#include <glm/glm.hpp>

namespace andromeda
{
	class TransformComponent : public Component < TransformComponent >, public ITransform
	{
	public:
		TransformComponent();
		virtual ~TransformComponent();

		const glm::mat4 & matrix() const { return _matrix; }


		/* Setters */
		inline void position(Float x, Float y, Float z) { _position = glm::vec3(x, y, z); }

		inline void yaw(Float f) { _rotation.y = f; }
		inline void pitch(Float f){ _rotation.x = f; }
		inline void roll(Float f) { _rotation.z = f; }



		/* Getters */
		const inline glm::vec3 & position() const override { return _position; }

		const inline Float x() const override { return _position.x; }
		const inline Float y() const override { return _position.y; }
		const inline Float z() const override { return _position.z; }

		const inline Float pitch() const override { return _rotation.x; }
		const inline Float yaw() const override { return _rotation.y; }
		const inline Float roll() const override { return _rotation.z; }




		/*
			Temporary!
		*/
		void calculate();
		

	private:
	
		glm::vec3 _position = glm::vec3(0.0f);
		glm::vec3 _rotation = glm::vec3(0.0f);

		glm::mat4 _matrix = glm::mat4(1.0f);
	};
}

#endif