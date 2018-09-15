#pragma once

#include <memory>
#include <string>

#include <common/types.h>

#include <core/region.h>

namespace andromeda
{


	class View
	{
	public:
		// View Order Sorting!
		friend Boolean operator <(const std::shared_ptr<View> & lhs, const std::shared_ptr<View> & rhs)
		{
			return lhs->zOrder() < rhs->zOrder();
		}

	public:
		View(const std::string & name);
		virtual ~View();

		// Camera
		/*
			Camera is made up of 3 components

			Perspective	- Tied to the aspect ratio : This MAY be influenced by things in the scene. DOF effects, Zoom, etc
			View		- Tied to object information in the scene
		*/
		inline const std::string& getName() { return _name; }
		inline Int32 zOrder() { return _zOrder; }


		Boolean resize(Int32 width, Int32 height);
		Boolean render();

	private:
		std::string _name;		// Name of hte View
		Int32		_zOrder;	// Order in which things are drawn

		Region2f	_view;
		Region2i	_viewport;
	};
}