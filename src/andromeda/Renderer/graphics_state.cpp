#include <andromeda/Renderer/graphics_state.h>

#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>

using namespace andromeda;


#if 0
/*

*/
GraphicsState::GraphicsState()
{
	// Default & Configure
	_viewport = Region2i(glm::ivec2(0, 0), glm::ivec2());
}


/*

*/
GraphicsState::~GraphicsState()
{

}







/*

*/
GraphicsStateStack::GraphicsStateStack(IGraphicsState &gs)
	: _viewport(gs.getViewport())
{


}


/*

*/
GraphicsStateStack::~GraphicsStateStack()
{
	// Restoration Phase

	// Restore Viewport
	if (_viewport.isAltered())
	{
		Region2i & vp = _viewport.getOriginal();
		andromeda::graphics()->setViewport(vp.minimum.x, vp.minimum.y, vp.size().x, vp.size().y);
	}

}


#endif
















/*

*/
GraphicsState::GraphicsState()
{
	// Initialise Callbacks
	_graphics = andromeda::graphics().get();

	// Set Initial State
	_viewport.push(_graphics, _mask, Region2i(glm::ivec2(0, 0), glm::ivec2(_graphics->getDisplayWidth(), _graphics->getDipslayHeight())));
}


/*
	push()

	Increments Mask
*/
void GraphicsState::push()
{
	_mask = _mask << 1;
}

/*
	pop():

	Decrements Mask. Pops Everything
*/
void GraphicsState::pop()
{
	// Pop & Restore Everything Here
	_viewport.pop(andromeda::graphics().get(), _mask);

	

	// Pop the Mask
	_mask = _mask >> 1;
}












