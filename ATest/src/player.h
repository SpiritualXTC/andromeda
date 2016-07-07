#pragma once

/*
	Class for each individual "Player"

	Keep in mind this is a test bed, NOT a game :P
*/
#include <memory>

#include <andromeda/stddef.h>
#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/projection.h>

namespace andromeda
{
	class View;
	class GameObject;
}



/*
	This is a typical camera controller :)
*/
class CameraControl : public virtual andromeda::ViewMatrix
{
public:
	


private:
};



class Player
{
public:
	Player(std::shared_ptr<andromeda::View> & view, std::shared_ptr<andromeda::GameObject> & object);
	virtual ~Player();


	const inline std::shared_ptr<andromeda::View> & getView() const { return _view; }


	void alterCameraDistance(aFloat distance);
	void alterCameraRotation(aFloat yaw, aFloat pitch);

private:
	std::shared_ptr<andromeda::View> _view;


	std::shared_ptr<andromeda::ViewMatrix> _viewMatrix;



	std::shared_ptr<andromeda::GameObject> _object;

};
