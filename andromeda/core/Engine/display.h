#pragma once

#include <common/types.h>

namespace andromeda
{
	enum class DisplayMode
	{
		Fullscreen,		// Fullscreen Exclusive Mode
		Borderless,		// Fullscreen Borderless Window Mode
		Windowed,		// Windowed Mode
	};

	struct DisplayFormat
	{
		Int32 width;
		Int32 height;

		// operators for the std::set.
		friend Boolean operator ==(const DisplayFormat & lhs, const DisplayFormat & rhs)
		{
			return lhs.width == rhs.width && lhs.height == rhs.height;
		}

		friend Boolean operator !=(const DisplayFormat & lhs, const DisplayFormat & rhs)
		{
			return !(lhs == rhs);
		}

		friend Boolean operator <(const DisplayFormat & lhs, const DisplayFormat & rhs)
		{
			return lhs.width < rhs.width || lhs.height < lhs.height;
		}
	};
}