#ifndef _ANDROMEDA_EVENTS_RESIZE_H_
#define _ANDROMEDA_EVENTS_RESIZE_H_

#include "../stddef.h"

namespace andromeda
{
	/*
	
	*/
	struct ResizeEventArgs
	{
		Int32 displayWidth;
		Int32 displayHeight;
	};



	/*
	
	*/
	class ResizeListener
	{
	public:
		ResizeListener();

		virtual ~ResizeListener();


	protected:
		virtual Boolean onResize(ResizeEventArgs & e) = 0;

	private:
		Int32 _hResize = -1;
	};
}

#endif