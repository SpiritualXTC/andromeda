#include <andromeda/Game/camera.h>

using namespace andromeda;




/*
	Set Camera Translation
*/
void CameraDefault::translate(Float x, Float y, Float z)
{
	if (isLocked())
		return;

	_position = glm::vec3(x, y, z);
}

/*
	Set Camera Translation
*/
void CameraDefault::translate(const glm::vec3 & position)
{
	if (isLocked())
		return;

	_position = position;
}



/*
	Set X-Axis Position
*/
void CameraDefault::x(Float x)
{
	if (isLocked())
		return;

	_position.x = x;
}

/*
	Set Y-Axis Position
*/
void CameraDefault::y(Float y)
{
	if (isLocked())
		return;

	_position.y = y;
}

/*
	Set Z-Axis Position
*/
void CameraDefault::z(Float z)
{
	if (isLocked())
		return;

	_position.z = z;
}


/*
	Set Camera Yaw
*/
void CameraDefault::yaw(Float yaw)
{
	if (isLocked())
		return;

	_rotation.y = yaw;
}

/*
	Set Camera Roll
*/
void CameraDefault::roll(Float roll)
{
	if (isLocked())
		return;

	_rotation.z = roll;
}

/*
	Set Camera Pitch
*/
void CameraDefault::pitch(Float pitch)
{
	if (isLocked())
		return;

	_rotation.x = pitch;
}