#ifndef _ANDROMEDA_GRAPHICS_RENDER_LIST_H
#define _ANDROMEDA_GRAPHICS_RENDER_LIST_H

#include <memory>
#include <list>
#include <unordered_map>

#include "../stddef.h"

namespace andromeda
{
	// Forward Declarations
	class IRenderable;


	class RenderList
	{
	public:
		typedef std::shared_ptr<IRenderable> RenderablePtr;
		typedef std::list<RenderablePtr>::iterator iterator;
		typedef std::list<RenderablePtr>::const_iterator const_iterator;

	public:
		RenderList(Int32 group);
		virtual ~RenderList();

		/*
		
		*/
		const inline Int32 group() const { return _group; }
		const inline Int32 size() const { return _list.size(); }


		Boolean addRenderable(RenderablePtr);
		Boolean removeRenderable(RenderablePtr);

		Boolean isRendered(RenderablePtr);



		iterator begin() { return _list.begin(); }
		const_iterator begin() const { return _list.begin(); }

		iterator end() { return _list.end(); }
		const_iterator end() const { return _list.end(); }

	private:

		Int32 _group = 0;

		std::unordered_map<Int32, Boolean> _map;	// Lookup Table : IFF, the int is found AND the value is true... then it is being rendered. Otherwise it's not
		std::list<RenderablePtr> _list;

	};
}

#endif