#include "player.h"

#include <andromeda/Game/game_object.h>

#include <andromeda/Renderer/view.h>



/*

*/
Player::Player(std::shared_ptr<andromeda::View> & view, std::shared_ptr<andromeda::GameObject> & object)
	: _view(view)
	, _object(object)
{
	assert(_view);


	_viewMatrix = std::make_shared<andromeda::ViewMatrix>();

	_viewMatrix->distance(12.0f);


	// Setup "Player" Camera
	_view->getCamera()->setView(_viewMatrix);
	_view->getCamera()->setPerspectiveFov(glm::pi<aFloat>() / 3.0f, 0.1f, 1000.0f);
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