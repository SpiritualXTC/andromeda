#ifndef _ANDROMEDA_RENDERER_VISIBILITY_H_
#define _ANDROMEDA_RENDERER_VISIBILITY_H_

#include <memory>

#include <andromeda/stddef.h>
#include <andromeda/Math/region.h>

namespace andromeda
{
	class ICamera;
	class IProjection;
	class GameObject;

	/*
	
	*/
	class IVisibility
	{
	public:
		IVisibility() {}
		virtual ~IVisibility() {}

		/*
			Updates the Visbility Region by the camera
		*/
		virtual void update(std::shared_ptr<IProjection> & projection, std::shared_ptr<ICamera> & camera) = 0;


		/*
			Determines whether an object is in the visible region
		*/
		virtual Boolean isVisible(const std::shared_ptr<GameObject> & go) = 0;
	};


	//class VisibilityAlways		:: Everything is visible. Always
	//class VisibilityFrustrum		:: Projection Matrix, using clipping planes to test for visibility
	//class VisibilityRegion		:: Region, 3D region


	class VisibilityRegion : public virtual IVisibility
	{
	public:
		VisibilityRegion();
		virtual ~VisibilityRegion();


		void update(std::shared_ptr<IProjection> & projection, std::shared_ptr<ICamera> & camera) override;

		Boolean isVisible(const std::shared_ptr<GameObject> & go) override;

	private:
		Region3f _region;
	};
}


#endif
