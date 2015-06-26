#ifndef _ANDROMEDA_GRAPHICS_DISPLAY_H
#define _ANDROMEDA_GRAPHICS_DISPLAY_H

#include "../stddef.h"

namespace andromeda
{
	enum class DisplayMode
	{
		//	Fullscreen,		// Fullscreen Exclusive Mode
		Borderless,		// Fullscreen Borderless Window Mode
		Windowed,		// Windowed Mode
	};



	struct DisplayFormat
	{
		Int32 width;
		Int32 height;
		//Int32 bitDepth;		// Is anything else other 32bit likely to be needed ??

		/*
		operators for the std::set.
		*/
		friend Boolean operator ==(const DisplayFormat & lhs, const DisplayFormat & rhs)
		{
			return lhs.width == rhs.width && lhs.height == rhs.height;// && lhs.bitDepth == rhs.bitDepth;
		}
		friend Boolean operator <(const DisplayFormat & lhs, const DisplayFormat & rhs)
		{
			return lhs.width < rhs.width || lhs.height < lhs.height;// || lhs.bitDepth < rhs.bitDepth;
		}
	};


	struct DisplayParameters
	{
		//	Int32 width;
		//	Int32 height;
		DisplayFormat format;

		DisplayMode mode;
	};
}

#endif