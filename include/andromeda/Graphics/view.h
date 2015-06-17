#ifndef _ANDROMEDA_GRAPHICS_VIEW_H_
#define _ANDROMEDA_GRAPHICS_VIEW_H_

#include <memory>

#include "../stddef.h"
#include "../Utilities/log.h"

namespace andromeda
{
	class View
	{
	public:
		friend Boolean operator <(const std::shared_ptr<View> & lhs, const std::shared_ptr<View> & rhs)
		{
			return lhs->layer() < rhs->layer();
		}





	public:
		View();
		virtual ~View();

		const inline Int32 layer() const { return _layer; }

	private:
		Int32 _layer;

	};
}

#endif