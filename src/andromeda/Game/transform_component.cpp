#include <andromeda/Game/transform_component.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace andromeda;



/*

*/
TransformComponent::TransformComponent()
{

}


/*

*/
TransformComponent::~TransformComponent()
{

}


/*
	calcualte():

	Recalculates the Matrix!
*/
void TransformComponent::calculate()
{
	glm::mat4 matrix(1.0f);

	// Translation only.
	//matrix = glm::translate(matrix, _position);

	// Object Translation
	matrix = glm::translate(matrix, _position);

	// Object Rotation
	matrix = glm::rotate(matrix, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	// Copy.
	_matrix = matrix;
}