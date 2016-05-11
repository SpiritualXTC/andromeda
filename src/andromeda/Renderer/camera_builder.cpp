#include <andromeda/Renderer/camera_builder.h>

#include <cassert>

#include <andromeda/Game/game_object.h>
#include <andromeda/Game/camera_component.h>
#include <andromeda/Game/transform_component.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/camera_static.h>		
#include <andromeda/Renderer/camera_target.h>


using namespace andromeda;

/*
	Create a default Camera
*/
std::shared_ptr<ICamera> CameraBuilder::create()
{
	return std::shared_ptr<CameraStatic>(new CameraStatic());
}


/*
	Create a Targeting Camera against a GameObject
*/
std::shared_ptr<ICamera> CameraBuilder::create(const std::shared_ptr<GameObject> go)
{
	// Validate
	assert(go);

	// Look for CameraComponent
	std::shared_ptr<ICamera> cameraComp = go->getComponentPtr<CameraComponent>();

	// The Camera is managed by a Camera Component
	if (cameraComp)
		return cameraComp;

	// Look for TransformComponent
	std::shared_ptr<ITransform> transformComp = go->getComponentPtr<TransformComponent>();

	// Create a Target Camera
	if (transformComp)
		return std::make_shared<CameraTarget>(transformComp);

	return nullptr;
}