#include <andromeda/Renderer/camera_static.h>

#include <andromeda/Renderer/transform.h>

using namespace andromeda;


/*

*/
void CameraStatic::calculate()
{
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
	


	/*
		TEMPORARY
	*/
	// Camera Translation
	_world = glm::translate(matrix, position());

	return;
}
