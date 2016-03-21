#include <andromeda/Game/camera.h>

#include <andromeda/Game/transform.h>

using namespace andromeda;


/*

*/
Camera::Camera()
{


}


#if 0
/*

*/
Camera::Camera(std::weak_ptr<ITransform> target)
{
	setTarget(target);
}
#endif


/*

*/
Camera::~Camera()
{


}


/*

*/
const glm::mat4 & Camera::calcMatrix()
{
	glm::mat4 matrix(1.0f);

	// Reset View Matrix
	_view = matrix;





	// Distance camera is from view point
	matrix = glm::translate(matrix, glm::vec3(0, 0, -_distance));
	
#if 1
	// Camera Rotation
	matrix = glm::rotate(matrix, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	// Camera Translation
	matrix = glm::translate(matrix, -_position);
#else
	if (!hasTarget())
	{
		// Camera Rotation
		matrix = glm::rotate(matrix, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::rotate(matrix, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::rotate(matrix, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

		// Camera Translation
		matrix = glm::translate(matrix, -_position);
	}
	else
	{
		// Get Target Matrix
		std::shared_ptr<ITransform> target = _target.lock();

		// Sync the target camera [Temporary]
	//	target->sync();

		// Camera Rotation
		matrix = glm::rotate(matrix, _rotation.x - target->pitch(), glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::rotate(matrix, _rotation.y - target->yaw(), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::rotate(matrix, _rotation.z - target->roll(), glm::vec3(0.0f, 0.0f, 1.0f));

		// Camera Translation
		matrix = glm::translate(matrix, -_position - target->position());
	}
#endif

	// Calculate Final View Matrix
	_view *= matrix;
	
	return _view;
}


/*
	Set Camera Translation
*/
void Camera::translate(Float x, Float y, Float z)
{
	if (isLocked())
		return;

	_position = glm::vec3(x, y, z);
}


/*
	Set Camera Translation
*/
void Camera::translate(const glm::vec3 & position)
{
	if (isLocked())
		return;

	_position = position;
}


void Camera::yaw(Float yaw)
{
	if (isLocked())
		return;

	_rotation.y = yaw;
}


void Camera::roll(Float roll)
{
	if (isLocked())
		return;

	_rotation.z = roll;
}


void Camera::pitch(Float pitch)
{
	if (isLocked())
		return;

	_rotation.x = pitch;
}