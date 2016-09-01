#include "circular_path_component.h"

#include <cassert>

#include <andromeda/Renderer/transform.h>

/*

*/
CircularPathComponent::CircularPathComponent(std::shared_ptr<andromeda::ITransform> transform, aFloat beginAngle)
	: _transform(transform)
	, _angle(beginAngle)
{
	assert(transform);


}


/*

*/
CircularPathComponent::~CircularPathComponent()
{

}

/*

*/
void CircularPathComponent::update(aFloat timeStep)
{
	aFloat speed = 0.25f;	//radians /s

	_angle += timeStep * speed;

	aFloat x = glm::cos(_angle) * 8.0f;
	aFloat z = glm::sin(_angle) * 8.0f;

	//_transform->position(x, 0.0f, z);
	_transform->x(x);
	_transform->z(z);

}