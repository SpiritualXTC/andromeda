#include <andromeda/Renderer/view.h>

#include <andromeda/Renderer/visibility.h>

using namespace andromeda;

/*

*/
ScreenView::ScreenView(const std::shared_ptr<SceneGraph> sceneGraph, std::shared_ptr<IProjection> projection, std::shared_ptr<IVisibility> visibility, 
	Float x, Float y, Float width, Float height, Int32 order)
	: View(sceneGraph, projection, visibility, x, y, width, height, order)
{
	/*
		TODO:
		Requires the dimensions of the actual screen ....
	*/
}



/*

*/
ScreenView::~ScreenView()
{

}



/*

*/
Boolean ScreenView::onResize(ResizeEventArgs & e)
{
	// Resize
	resize(e.displayWidth, e.displayHeight);

	log_event("ON_RESIZE: ", e.displayWidth, e.displayHeight);

	return true;
}