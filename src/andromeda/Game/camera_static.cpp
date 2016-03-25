#include <andromeda/Game/camera_static.h>

#include <andromeda/Game/transform.h>

using namespace andromeda;


/*

*/
void CameraStatic::calculate()
{
	glm::mat4 matrix(1.0f);

	// Distance camera is from view point
	matrix = glm::translate(matrix, glm::vec3(0, 0, -distance()));

	// Camera Rotation
	matrix = glm::rotate(matrix, pitch(), glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, yaw(), glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, roll(), glm::vec3(0.0f, 0.0f, 1.0f));

	// Camera Translation
	matrix = glm::translate(matrix, -position());

	// Calculate Final View Matrix
	_view = matrix;
	
	return;
}

#if 0
/*
	Set Camera Translation
*/
void CameraStatic::translate(Float x, Float y, Float z)
{
	if (isLocked())
		return;

	_position = glm::vec3(x, y, z);
}

/*
	Set Camera Translation
*/
void CameraStatic::translate(const glm::vec3 & position)
{
	if (isLocked())
		return;

	_position = position;
}



/*
	Set X-Axis Position
*/
void CameraStatic::x(Float x)
{
	if (isLocked())
		return;

	_position.x = x;
}

/*
	Set Y-Axis Position
*/
void CameraStatic::y(Float y)
{
	if (isLocked())
		return;

	_position.y = y;
}

/*
	Set Z-Axis Position
*/
void CameraStatic::z(Float z)
{
	if (isLocked())
		return;

	_position.z = z;
}


/*
	Set Camera Yaw
*/
void CameraStatic::yaw(Float yaw)
{
	if (isLocked())
		return;

	_rotation.y = yaw;
}

/*
	Set Camera Roll
*/
void CameraStatic::roll(Float roll)
{
	if (isLocked())
		return;

	_rotation.z = roll;
}

/*
	Set Camera Pitch
*/
void CameraStatic::pitch(Float pitch)
{
	if (isLocked())
		return;

	_rotation.x = pitch;
}

#endif
