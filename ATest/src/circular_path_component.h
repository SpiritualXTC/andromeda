#ifndef _CIRCULAR_PATH_COMPONENT_H_
#define _CIRCULAR_PATH_COMPONENT_H_

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

private:
	std::shared_ptr<andromeda::ITransform> _transform;
	aFloat _angle;
};




#endif
