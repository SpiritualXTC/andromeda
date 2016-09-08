#include "ambient_light.h"

#include <andromeda/Graphics/light.h>

#include <andromeda/Renderer/camera.h>

#include "directional_light.h"

using namespace andromeda;
using namespace andromeda::deferred;


/*

*/
DeferredAmbientLight::DeferredAmbientLight()
{
	// Create Camera
	_camera = std::make_shared<Camera>();

	// Create Light View Matrix
	_viewMatrix = std::make_shared<AmbientLightViewMatrix>();

	// Set Matrices
	_camera->setView(_viewMatrix);
	_camera->setOrthogonal(20.0f, -20.0f, 20.0f);

	// 	// Create Renderable
	_renderable = std::make_shared<deferred::DeferredDirectionalLight>(_light);
}



/*

*/
DeferredAmbientLight::~DeferredAmbientLight()
{

}


/*
	Syncs some stuff together :)
*/
void DeferredAmbientLight::sync()
{
	// Update Light Direction
	_viewMatrix->setLightDirection(_light->getDirection());

	// This will update the camera :)
	_viewMatrix->update();


	glm::mat4 m = _camera->getProjectionMatrix() * _camera->getViewMatrix();
	_renderable->setLightMatrix(m);
}





void DeferredAmbientLight::setAmbientLight(const std::shared_ptr<LightDirectional> & ambient)
{
	_light = ambient; 
	_renderable->setLight(ambient);
}

																		// Sets the Shadow Map
void DeferredAmbientLight::setShadowMap(const std::shared_ptr<ITexture> & texture)
{
	_renderable->setShadowMap(texture);
}

