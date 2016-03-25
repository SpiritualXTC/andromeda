#ifndef _RANDOM_PATH_COMPONENT_H_
#define _RANDOM_PATH_COMPONENT_H_

#include <cassert>

#include <andromeda/glm.h>
#include <andromeda/Game/component.h>



namespace andromeda
{
	class ITransform;
}




/*

*/
class RandomPathComponent : public andromeda::Component<RandomPathComponent>
{
public:
	RandomPathComponent(const std::shared_ptr<andromeda::ITransform> transform);
	virtual ~RandomPathComponent();

	void update(const aFloat timeStep);

private:
	void setDestination();

	std::shared_ptr<andromeda::ITransform> _transform;
	glm::vec3 _destination;
};

#endif
