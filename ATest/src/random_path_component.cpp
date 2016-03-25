#include "random_path_component.h"

#include <andromeda/Game/transform.h>

#include <andromeda/Utilities/log.h>

/*

*/
RandomPathComponent::RandomPathComponent(const std::shared_ptr<andromeda::ITransform> transform)
	: _transform(transform)
{
	assert(transform);

	setDestination();
}


/*

*/
RandomPathComponent::~RandomPathComponent()
{

}


/*

*/
void RandomPathComponent::update(const aFloat timeStep)
{
	aFloat speed = 1.0f;

	glm::vec3 v = _transform->position() - _destination;

	aFloat d = glm::length(v);

	if (d < speed * timeStep * 2.0f)
	{
		// RESET DESTINATION
		setDestination();


		// Recalculate
		v = _transform->position() - _destination;
		d = glm::length(v);
	}

	glm::vec3 dir = v / d;

	glm::vec3 pos = _transform->position() - dir * timeStep * speed;

	_transform->position(pos.x, pos.y, pos.z);

	


}


/*

*/
void RandomPathComponent::setDestination()
{
	aFloat x = ((rand() % 100) - 50) / 50.0f;
	aFloat y = ((rand() % 100) - 50) / 50.0f;
	aFloat z = ((rand() % 100) - 50) / 50.0f;

	_destination = glm::vec3(x, y, z);
}