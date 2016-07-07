#pragma once

#include <andromeda/Game/component.h>
#include <andromeda/Game/transform_component.h>
#include <andromeda/Game/geometry_component.h>

#include <andromeda/Math/plane.h>

class PlaneTestComponent : public andromeda::Component<PlaneTestComponent>
{
public:
	PlaneTestComponent(std::shared_ptr<andromeda::GeometryRenderComponent> & geometry, std::shared_ptr<andromeda::TransformComponent> & transform);
	virtual ~PlaneTestComponent();

	void update(const aFloat timeStep);

private:
	std::shared_ptr<andromeda::GeometryRenderComponent> _geometry;
	std::shared_ptr<andromeda::TransformComponent> _transform;

	andromeda::Plane3f _plane;
};
