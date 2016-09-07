#include <andromeda/Renderer/view.h>

#include <andromeda/graphics.h>

#include <andromeda/Renderer/graphics_state.h>
#include <andromeda/Renderer/renderer.h>

#include <andromeda/Utilities/log.h>


using namespace andromeda;













/*

*/
View::View(Float x, Float y, Float width, Float height, Int32 order)
	: _zOrder(order)
{
	assert(_zOrder != View::_ZOrder::Target);


	// Create the Target
	_target = std::make_shared<ViewScreen>();

	// Observer Workaround/Setup
	_helper = std::make_shared<ObserverHelper<IViewTarget>>(this);
	_target->add(_helper);
	


	// Set the Region
	_view = Region2f({ x, y }, { width + x, height + y });
}


/*

*/
View::~View()
{

}


/*

*/
void View::notify(const IViewTarget * const vt)
{
	resize(vt->width(), vt->height());
}






/*

*/
Boolean View::addRenderer(const std::string & rendererName, const std::shared_ptr<IRenderer> & renderer)
{
	assert(renderer);

	// Renderer Exists
	if (_renderer.find(rendererName) != _renderer.end())
		return false;

	// Insert
	_renderer[rendererName] = renderer;

	return true;
}


/*
	Gets the Renderer
*/
std::shared_ptr<IRenderer> View::getRenderer(const std::string & rendererName)
{
	// Find the Renderer
	const auto & it = _renderer.find(rendererName);

	// Found ??
	return it == _renderer.end() ? nullptr : it->second;
}





/*

*/
void View::clear()
{
	// Clear all the renderers
	for (const auto & it : _renderer)
		it.second->clear();
}


/*
	resize():

	Resize the Viewport
*/
void View::resize(const Int32 width, const Int32 height)
{
	// Set Screen Dimensions
	_screen.minimum = glm::ivec2(0, 0);
	_screen.maximum = glm::ivec2(width, height);

	// Recalculate Screen Region
	glm::fvec2 screen(width, height);

	_display.minimum = _view.minimum * screen;
	_display.maximum = _view.maximum * screen;



	// Recalculate Projection
	glm::fvec2 display(_display.size());

	// Resize the Renderer
	for (const auto & renderer : _renderer)
		renderer.second->resize(display.x, display.y);

	return;
}

/*
	render():

	Render the View
*/
void View::render()
{
	GraphicsState gfxs;

	/*
		This should be an automatic component of the Graphics API when setting a weighted viewport
	*/
	// Viewport Attributes
	Int32 left = _display.minimum.x;
	Int32 top = _display.minimum.y;
	Int32 width = _display.maximum.x - _display.minimum.x;
	Int32 height = _display.maximum.y - _display.minimum.y;

	// Flip Top to Bottom, offset by height
	Int32 bottom = _screen.maximum.y - top;
	bottom -= height;


	/*
		TODO: 
		ReAdd support for RenderTargets
		Do this after texturing is working and back in place :D
	*/

	
	// THE RENDER TARGET NEEDS TO DO SHIT HERE
	// IViewTarget Interface
	//IViewTarget->begin();

	// Set Viewport
	//glViewport(left, bottom, width, height);
	

	gfxs.setViewport(left, bottom, width, height);




	// Update the Renderer Caches, Cameras, etc
	// This may make more sense to do elsewhere... investigate
	for (const auto & renderer : _renderer)
		renderer.second->update();

	// Render Renderer
	for (const auto & renderer : _renderer)
	{
		gfxs.push();
		renderer.second->render(gfxs);
		gfxs.pop();
	}



	// THE RENDER TARGET NEEDS TO CLEAN SHIT UP HERE
	// IViewTarget Interface
	//IViewTarget->end();
}


