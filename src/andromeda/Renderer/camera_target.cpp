#include <andromeda/Renderer/camera_target.h>

using namespace andromeda;

/*

*/
void CameraTarget::calculate()
{
	assert(_transform);

	
	glm::mat4 matrix(1.0f);

	// Distance camera is from view point
	matrix = glm::translate(matrix, glm::vec3(0, 0, -distance()));

	// Camera Rotation
	matrix = glm::rotate(matrix, -pitch(), glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, -yaw(), glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, -roll(), glm::vec3(0.0f, 0.0f, 1.0f));

	// Camera Translation
	matrix = glm::translate(matrix, -position());

	// Calculate Final View Matrix
	_view = matrix;
	
	// Reset View Matrix
	_view *= glm::inverse(_transform->matrix());


	/*
	TEMPORARY
	*/
	// Camera Translation
	glm::mat4 m(1.0f);
	_world = glm::translate(m, _transform->position());
//	_world *= _transform->matrix();



	return;
}