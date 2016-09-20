#include "renderable_group.h"

#include <cassert>

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
	addRenderable():

	Adds a renderable to the list
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
	removeRenderable():

	Remove a renderable from the list
*/
Boolean RenderableGroup::removeRenderable(IRenderable * renderable)
{
	if (renderable == nullptr)
		return false;

	// TEMP :: remove the renderable immediately
	// TODO :: This may need to be removed in a much smart manner
	_renderables.erase(renderable);

	return true;
}


/*
	render():

	Render the list of renderables
*/
void RenderableGroup::render(GraphicsState & rs)
{
	for (const auto r : _renderables)
	{
		r->render(rs);
	}
}
