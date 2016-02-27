#include <andromeda/Game/camera_component.h>

#include <andromeda/Game/transform_component.h>

#include <glm/gtc/matrix_inverse.hpp>

using namespace andromeda;

/*

*/
CameraComponent::CameraComponent(std::weak_ptr<TransformComponent> transform)
	:_transform(transform)
{

}


/*

*/
CameraComponent::~CameraComponent()
{

}

/*

*/
void CameraComponent::sync()
{
	std::shared_ptr<TransformComponent> transform = _transform.lock();

	_position = transform->position();
	
	_rotation.x = transform->pitch();
	_rotation.y = transform->yaw();
	_rotation.z = transform->roll();

}



#if 0
/*

*/
const glm::mat4 & CameraComponent::matrix()
{
	//_matrix = glm::inverse(_transform.lock()->matrix());

	glm::mat4 matrix(1.0f);


	std::shared_ptr<TransformComponent> transform = _transform.lock();



	matrix = glm::translate(matrix, -transform->position());




	_matrix = matrix;
	return _matrix;
}
#endif