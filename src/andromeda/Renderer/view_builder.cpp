#include <andromeda/Renderer/view_builder.h>

#include <andromeda/Renderer/projection.h>

using namespace andromeda;





/*
	Create Orthogonal Projection Matrix
*/
ViewBuilder & ViewBuilder::setProjectionOrth()
{
	_projection = std::make_shared<ProjectionOrtho>();
	return *this;
}

/*
	Create Perspective Fov Projection Matrix
*/
ViewBuilder & ViewBuilder::setProjectionPerspective()
{
	_projection = std::make_shared<ProjectionPerspective>();
	return *this;
}





/*
	Sets the Views Region
*/
ViewBuilder & ViewBuilder::setRegion(Float x, Float y, Float width, Float height)
{
	_screen = Region2f(glm::vec2(x, y), glm::vec2(x + width, y + height));

	return *this;
}







/*

*/
std::shared_ptr<View> ViewBuilder::create()
{
	std::shared_ptr<View> view;


	return view;
}




