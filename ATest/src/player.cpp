#include "player.h"

#include <andromeda/Game/game_object.h>

#include <andromeda/Renderer/view.h>
#include <andromeda/Renderer/renderer.h>


/*

*/
Player::Player(std::shared_ptr<andromeda::View> & view, std::shared_ptr<andromeda::Camera> & camera, std::shared_ptr<andromeda::GameObject> & object)
	: _view(view)
	, _camera(camera)
	, _object(object)
{
	assert(_view);
	assert(_camera);

	// Create View Matrix
	_viewMatrix = std::make_shared<andromeda::ViewMatrix>();
	_viewMatrix->distance(12.0f);

	// Create Proj matrix
	_projMatrix = std::make_shared<andromeda::PerspectiveMatrix>();
	_projMatrix->fov(glm::pi<aFloat>() / 3.0f);


	// Setup "Player" Camera
	_camera->setView(_viewMatrix);
	_camera->setProjection(_projMatrix);
}

/*

*/
Player::~Player()
{


}

/*

*/
void Player::alterCameraRotation(aFloat yaw, aFloat pitch)
{
	aFloat y = _viewMatrix->yaw();
	aFloat p = _viewMatrix->pitch();

	_viewMatrix->yaw(y + yaw);
	_viewMatrix->pitch(p + pitch);
	_viewMatrix->update();
}

/*

*/
void Player::alterCameraDistance(aFloat distance)
{
	andromeda::Float d = _viewMatrix->distance();

	d += distance;

	_viewMatrix->distance(d);
	_viewMatrix->update();
}

/*

*/
void Player::zoomIn()
{
	aFloat z = _projMatrix->zoom();

	_projMatrix->zoom(z * 2.0f);
	_projMatrix->update();
}


/*

*/
void Player::zoomOut()
{
	aFloat z = _projMatrix->zoom();

	_projMatrix->zoom(z / 2.0f);
	_projMatrix->update();
}