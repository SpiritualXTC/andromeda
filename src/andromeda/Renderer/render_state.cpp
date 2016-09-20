#include <andromeda/Renderer/render_state.h>

#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>

using namespace andromeda;



/*

*/
RenderState::RenderState()
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
void RenderState::push()
{
	_mask = _mask << 1;
}

/*
	pop():

	Decrements Mask. Pops Everything
*/
void RenderState::pop()
{
	// Pop & Restore Everything Here
	_viewport.pop(andromeda::graphics().get(), _mask);

	

	// Pop the Mask
	_mask = _mask >> 1;
}












