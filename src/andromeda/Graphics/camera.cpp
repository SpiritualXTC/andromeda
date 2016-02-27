#include <andromeda/Graphics/camera.h>

using namespace andromeda;


/*

*/
Camera::Camera()
{


}

/*

*/
Camera::Camera(std::weak_ptr<ITarget> target)
{
	setTarget(target);
}



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

	// Calculate Free Form Matrix
	matrix = glm::translate(matrix, _position);
	
	matrix = glm::rotate(matrix, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::rotate(matrix, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

	// Track Target
	if (hasTarget())
	{
		// Get Target Matrix
		std::shared_ptr<ITarget> target = _target.lock();
	}

	// Calculate Final View Matrix
	_view *= matrix;
	

	return _view;
}


/*

*/
void Camera::setTarget(std::weak_ptr<ITarget> target)
{
	_target = target;
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