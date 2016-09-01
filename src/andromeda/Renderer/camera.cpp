#include <andromeda/Renderer/camera.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;


/*

*/
Camera::Camera()
{
	// Default View Matrices
	glm::mat4 m(1.0f);

	glm::vec3 v = glm::vec3(0, 0, -1.0f);
	_viewMatrix = glm::translate(m, v);

	// Default Projection Matrix
	_projectionMatrix = glm::ortho(-1, 1, -1, 1, -1, 1);
}


/*

*/
Camera::~Camera()
{

}


/*
	Sets a Perspective Matrix [Projection]
*/
std::shared_ptr<PerspectiveMatrix> Camera::setPerspectiveFov(Float fov, Float zN, Float zF)
{
	// Create Projection Matrix
	std::shared_ptr<PerspectiveMatrix> per = std::make_shared<PerspectiveMatrix>();

	per->fov(fov);
	per->zNear(zN);
	per->zFar(zF);

	setProjection(per);

	return per;
}


/*
	Sets an Orthogonal Matrix [Projection]
*/
std::shared_ptr<OrthogonalMatrix> Camera::setOrthogonal(Float mul, Float zN, Float zF)
{
	std::shared_ptr<OrthogonalMatrix> ortho = std::make_shared<OrthogonalMatrix>();

	ortho->multiplier(mul);
	ortho->zNear(zN);
	ortho->zFar(zF);

	setProjection(ortho);

	return ortho;
}

/*
	Sets an Orthogonal Screen Matrix [Projection]
*/
std::shared_ptr<ScreenMatrix> Camera::setOrthogonalScreen(Float zN, Float zF)
{
	std::shared_ptr<ScreenMatrix> screen = std::make_shared<ScreenMatrix>();

	screen->zNear(zN);
	screen->zFar(zF);

	setProjection(screen);

	return screen;
}



/*
	Sets the standard View Matrix
*/
std::shared_ptr<ViewMatrix> Camera::setView(Float distance)
{
	std::shared_ptr<ViewMatrix> view = std::make_shared<ViewMatrix>();

	view->distance(distance);
	setView(view);

	return view;
}


/*
	Sets a Look At View Matrix
*/
std::shared_ptr<LookAtViewMatrix> Camera::setView(const glm::vec3 & eye, const glm::vec3 & target, const glm::vec3 & up)
{
	std::shared_ptr<LookAtViewMatrix> view = std::make_shared<LookAtViewMatrix>();

	view->eye(eye).target(target).up(up);

	setView(view);

	return view;
}





/*
	Assign and Calculate Projection Matrix 
*/
void Camera::setProjection(std::shared_ptr<IProjectionMatrix> p)
{
	assert(p);

	// Remove Observer
	if (_projection)
		_projection->remove(shared_from_this());

	// Assign
	_projection = p;

	// Add Observer
	if (_projection)
		_projection->add(shared_from_this());

	// Recalculate Matrix
	_projection->update(getWidth(), getHeight());
}






/*

*/
void Camera::setView(std::shared_ptr<IViewMatrix> v)
{ 
	assert(v); 

	// Remove Observer
	if (_view)
		_view->remove(shared_from_this());

	// Assign
	_view = v;

	// Add Observer
	if (_view)
		_view->add(shared_from_this());

	// Calculate View Matrix
	_view->update();
}



/*
	Recalculate the Projection Matrix with new width/height Values
*/
void Camera::resize(Float width, Float height)
{
	_width = width;
	_height = height;

	// Recalculate Projection Matrix
	if (_projection)
		_projection->update(getWidth(), getHeight());
}



/*

*/
void Camera::notify(const IProjectionMatrix * const pm)
{
//	log_warn("Projection matrix updated");
	if (_projection)
		_projectionMatrix = _projection->matrix();

	calculate();
}


/*

*/
void Camera::notify(const IViewMatrix * const vm)
{
//	log_warn("View matrix updated");
	if (_view)
		_viewMatrix = _view->matrix();

	calculate();
}



/*

*/
void Camera::calculate()
{
//	assert(_projection);
//	assert(_view);

	// Calculate ViewProjection Matrix
	glm::mat4 m = getProjectionMatrix() * getViewMatrix();

	// Right Plane
	_planes[0].normal.x = m[0][3] - m[0][0];
	_planes[0].normal.y = m[1][3] - m[1][0];
	_planes[0].normal.z = m[2][3] - m[2][0];
	_planes[0].d = m[3][3] - m[3][0];

	// Left Plane
	_planes[1].normal.x = m[0][3] + m[0][0];
	_planes[1].normal.y = m[1][3] + m[1][0];
	_planes[1].normal.z = m[2][3] + m[2][0];
	_planes[1].d = m[3][3] + m[3][0];

	// Lower Plane
	_planes[2].normal.x = m[0][3] + m[0][1];
	_planes[2].normal.y = m[1][3] + m[1][1];
	_planes[2].normal.z = m[2][3] + m[2][1];
	_planes[2].d = m[3][3] + m[3][1];

	// Upper Plane
	_planes[3].normal.x = m[0][3] - m[0][1];
	_planes[3].normal.y = m[1][3] - m[1][1];
	_planes[3].normal.z = m[2][3] - m[2][1];
	_planes[3].d = m[3][3] - m[3][1];

	// Far Plane
	_planes[4].normal.x = m[0][3] - m[0][2];
	_planes[4].normal.y = m[1][3] - m[1][2];
	_planes[4].normal.z = m[2][3] - m[2][2];
	_planes[4].d = m[3][3] - m[3][2];

	// Near Plane
	_planes[5].normal.x = m[0][3] + m[0][2];
	_planes[5].normal.y = m[1][3] + m[1][2];
	_planes[5].normal.z = m[2][3] + m[2][2];
	_planes[5].d = m[3][3] + m[3][2];

	// Normalise Planes
	for (Int32 i = 0; i < PLANE_COUNT; ++i)
		_planes[i].normalize();
}


/*
	isVisible():

	Determine whether a bounding sphere is visible in the frustrum
*/
Boolean Camera::isVisible(const glm::vec3 & centre, Float radius) const
{
	for (Int32 i = 0; i < PLANE_COUNT; ++i)
	{
		if (!_planes[i].positive(centre, radius))
			return false;
	}

	return true;
}