#include "plane_test_component.h"




/*

*/
PlaneTestComponent::PlaneTestComponent(std::shared_ptr<andromeda::GeometryRenderComponent> & geometry, std::shared_ptr<andromeda::TransformComponent> & transform)
	: _geometry(geometry)
	, _transform(transform)
{
	assert(_geometry);
	assert(_transform);

	_plane.normal = glm::vec3(0, 0, 1);
	_plane.d = 0;
}


/*

*/
PlaneTestComponent::~PlaneTestComponent()
{

}

/*

*/
void PlaneTestComponent::update(const aFloat fTimeStep)
{
	andromeda::Material & m = _geometry->getMaterial();

	aBoolean intersect = _plane.intersect(_transform->position(), 0.5f);

	if (intersect)
		m.setDiffuse(0, 1, 0);
	else
	{
		if (_plane.positive(_transform->position(), 0.5f))
			m.setDiffuse(0, 0, 1);
		else
			m.setDiffuse(1, 0, 0);
	}
}