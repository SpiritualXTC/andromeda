#include <andromeda/Renderer/view.h>

using namespace andromeda;

/*

*/
ScreenView::ScreenView(const std::shared_ptr<ISceneGraph> sceneGraph, std::shared_ptr<IProjection> projection, Float x, Float y, Float width, Float height, Int32 order)
	: View(sceneGraph, projection, x, y, width, height, order)
{
	/*
		TODO:
		Require the dimensions of the actual screen ....
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