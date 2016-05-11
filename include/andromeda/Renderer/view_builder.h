#ifndef _ANDROMEDA_RENDERER_VIEW_BUILDER_H_
#define _ANDROMEDA_RENDERER_VIEW_BUILDER_H_

#include <memory>

#include <andromeda/stddef.h>
#include <andromeda/Math/region.h>

namespace andromeda
{
	class IProjection;
	class View;


	/*
		Creates a View
	*/
	class ViewBuilder
	{



	public:
		ViewBuilder() {}
		virtual ~ViewBuilder() {}


		/*
			Projection Matrices
		*/
		ViewBuilder & setProjectionOrth();
		ViewBuilder & setProjectionPerspective();

		/*
			View Matrices / Camera
		*/

		/*
			Region
		*/
		ViewBuilder & setRegion(Float x, Float y, Float width, Float height);


		/* Creates the View */
		std::shared_ptr<View> create();

	private:
		Region2f _screen{ {0, 0}, {1, 1} };

		std::shared_ptr<IProjection> _projection;
	};

}

#endif
