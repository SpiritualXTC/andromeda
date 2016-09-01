#include <andromeda/Game/light_component.h>

#include <andromeda/Renderer/transform.h>

using namespace andromeda;

/*

*/
LightDirectionalComponent::LightDirectionalComponent(const std::shared_ptr<ITransform> & transform)
	: _transform(transform)
{
	assert(_transform);
}

LightDirectionalComponent::~LightDirectionalComponent()
{

}


/*

*/
void LightDirectionalComponent::update(const aFloat timeStep)
{
	// Update Light Direction
	setDirection(-_transform->position());
}