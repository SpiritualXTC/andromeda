#include "renderable_group.h"

#include <cassert>

#include <andromeda/Math/matrix_stack.h>
#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/renderable.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;


/*

*/
RenderableGroup::RenderableGroup(const std::string & groupName)
	: _groupName(groupName)
{

}



/*

*/
RenderableGroup::~RenderableGroup()
{

}


/*

*/
Boolean RenderableGroup::addRenderable(IRenderable * renderable)
{
	if (renderable == nullptr)
		return false;

	// TEMP, just add the renderable immediately
	_renderables.insert(renderable);

	return true;
}

/*

*/
Boolean RenderableGroup::removeRenderable(IRenderable * renderable)
{
	if (renderable == nullptr)
		return false;

	// TEMP, remove the renderable immediately
	_renderables.erase(renderable);

	return true;
}




/*

*/
void RenderableGroup::render(std::shared_ptr<Camera> & camera, std::shared_ptr<IShader> shader)
{
//	assert(camera);

	// Setup Matrix Stack :: Initialise with Camera View Matrix 
	// Camera needs to be Rewritten
	//MatrixStack ms(camera->getViewMatrix());
	MatrixStack ms;

	/*
		TODO:
		Render the RenderGroup
	*/
	// Render Objects With This Technique
	for (const auto r : _renderables)
	{
		// Render the Renderable
		r->render(shader, ms);
	}
}


void RenderableGroup::render(RenderState & rs)
{
	for (const auto r : _renderables)
	{
		r->render(rs);
	}
}
