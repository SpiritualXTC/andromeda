#include <andromeda/Renderer/visibility.h>


#include <andromeda/Game/game_object.h>
#include <andromeda/Game/transform_component.h>

#include <andromeda/Math/glmx/glm_infinity.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/projection.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
VisibilityRegion::VisibilityRegion()
{

}


/*

*/
VisibilityRegion::~VisibilityRegion()
{

}

/*

*/
void VisibilityRegion::update(std::shared_ptr<IProjection> & projection, std::shared_ptr<ICamera> & camera)
{

	aFloat cam_size = 2.0f;

	// Dimensions of the Region
	/*
		TODO:
		Z-Axis needs to be calculated from [camera.distance(), projection.zoom()]
		X-Axis needs to be calculated from [Z-Axis, projection.aspect()]
	*/
	glm::vec3 size = glm::vec3(cam_size, 10000.0f, cam_size);

	// Calculate Region Center
	const glm::vec3 center = glm::vec3(camera->worldMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	// Update Region
	_region = Region3f(center - size, center + size);
}

/*

*/
Boolean VisibilityRegion::isVisible(const std::shared_ptr<GameObject> & go) 
{
	glm::vec3 size = glm::vec3(0.5f, 1.0f, 0.5f);

	// Transform Component
	std::shared_ptr<ITransform> transform = go->getComponentPtr<TransformComponent>();

	if (!transform) return false;

	const glm::vec3 & position = transform->position();

	// Build a temporary AABB for the object :: Pull this from the GameObject instead of using the TransformObject
	Region3f object = Region3f(position - size, position + size);

	// Does the Camera Region overlap the Object Region
	return _region.overlap(object);
}