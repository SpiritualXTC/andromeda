#if 0
#include <andromeda/Renderer/render_list.h>

#include <andromeda/Renderer/renderable.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
RenderList::RenderList(Int32 group) : _group(group)
{
	log_verbose("RenderList: Create");
}


/*

*/
RenderList::~RenderList()
{
	log_verbose("RenderList: Destroy");
}


/*

*/
Boolean RenderList::addRenderable(RenderablePtr r)
{
	const Int32 id = r->id();

	// Already Exists in Map
	if (_map[id] == true)
	{
		log_warn("Already Exists in Map ID = ", id);
		return true;
	}
	
	// Set in Map
	_map[id] = true;

	// Add Renderable
	_list.push_back(r);

	return true;
}


/*

*/
Boolean RenderList::removeRenderable(RenderablePtr r)
{
	const Int32 id = r->id();

	if (_map[id] == true)
	{
		// Remove From list
		_list.remove(r);
		

		// Set Map (Should it be removed [_map.erase(id)] ?)
		_map[id] = false;
	}

	return true;
}


/*

*/
Boolean RenderList::isRendered(RenderablePtr r)
{
	// Lookup the Map.
	const Int32 id = r->id();

	return _map[id];
}


#endif