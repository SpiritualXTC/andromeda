#include "view.h"

#include <core/Math/matrix_stack.h>

using namespace andromeda;

View::View(const std::string& name)
	: _name(name)
{
	_view = Region2f({ 0.0f, 0.0f }, { 1.0f, 1.0f });
}

View::~View()
{

}


Boolean View::resize(Int32 width, Int32 height)
{
	glm::fvec2 resolution(width, height);

	_viewport.minimum = _view.minimum * resolution;
	_viewport.maximum = _view.maximum * resolution;

	//glm::fvec2 dimension(_viewport.dimensiuon());

	// TODO: Resize the Renderer (s) Some special effects will require the renderer to be resized
	
	return true;
}


Boolean View::render()
{


	// TEMP: Draw a simple scene

	MatrixStack camera;
	

	return true;
}


