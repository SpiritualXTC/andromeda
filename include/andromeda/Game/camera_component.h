#ifndef _ANDROMEDA_GAME_CAMERA_COMPONENT_H_
#define _ANDROMEDA_GAME_CAMERA_COMPONENT_H_

#include "component.h"

#include "../Graphics/camera.h"

namespace andromeda
{
	// Forward Declarations
	class TransformComponent;



	/*
	
	*/
	class CameraComponent : public Component<CameraComponent>, public ITarget
	{
	public:
		CameraComponent(std::weak_ptr<TransformComponent> transform);
		virtual ~CameraComponent();

		const inline glm::vec3 & position() const override{ return _position; }

		const inline Float pitch() const override{ return _rotation.x; }
		const inline Float yaw() const override{ return _rotation.y; }
		const inline Float roll() const override{ return _rotation.z; }

		void sync() override;

	private:
		glm::vec3 _position = glm::vec3(0.0f);
		glm::vec3 _rotation = glm::vec3(0.0f);


		std::weak_ptr<TransformComponent> _transform;
	};
}


#endif