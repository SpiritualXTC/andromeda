#pragma once
#include <andromeda/glm.h>

#include <andromeda/Game/component.h>

namespace andromeda
{
	class ITransform;
}


class CircularPathComponent : public andromeda::Component<CircularPathComponent>
{
public:
	CircularPathComponent(std::shared_ptr<andromeda::ITransform> transform, aFloat beginAngle);
	virtual ~CircularPathComponent();

	void update(const aFloat timeStep);

	inline void setSpeed(aFloat s) { _speed = s; }
	inline void setRadius(aFloat r) { _radius = r; }
	inline void setCenter(const glm::vec3 & v) { _center = v; }

private:
	std::shared_ptr<andromeda::ITransform> _transform;
	
	aFloat _angle;

	aFloat _speed = 1.0f;
	aFloat _radius = 1.0f;

	glm::vec3 _center{ 0.0f, 0.0f, 0.0f };
};




