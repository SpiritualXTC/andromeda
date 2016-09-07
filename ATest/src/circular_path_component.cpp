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
	//aFloat speed = 0.25f;	//radians /s

	_angle += timeStep * _speed;

	aFloat x = glm::cos(_angle) * _radius;
	aFloat z = glm::sin(_angle) * _radius;

	_transform->position(_center.x + x, _center.y, _center.z + z);
	//_transform->x(x);
	//_transform->z(z);

}