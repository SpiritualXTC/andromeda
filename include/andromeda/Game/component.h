#pragma once

#include <vector>
#include <cassert>

#include <andromeda/stddef.h>



#include <andromeda/Utilities/dependancy.h>
#include <andromeda/Utilities/template.h>

namespace andromeda
{
	class IRenderableManager;


	/*
		TODO:
		Render events need to be only for a specific component... not on all components :)
	*/



	/*
	
	*/
	class IComponent
	{
	public:
		IComponent(){}
		virtual ~IComponent(){}

		/*
			Activation that occurs when ANY view activates the object
		*/
		virtual inline void onRenderActivate() = 0;

		/*
			Deactivation that occurs when ANY view deactivates the objects
		*/
		virtual inline void onRenderDeactivate() = 0;

		/*
			Activation that occurs when a SPECIFIC view activates the object
		*/
		virtual inline void onRenderActivate(IRenderableManager * view) = 0;

		/*
			Deactivation that occurs when a SPECIFIC view activates the object
		*/
		virtual inline void onRenderDeactivate(IRenderableManager * view) = 0;


		/*
			Update.... Updates the Component
		*/
		virtual inline void update(const Float timeStep) = 0;
	};



	/*
		I Dont think this really needs the Dependancy Chain :P
		...
		However it may allow building a tree dynamically so that any components that are dependants end up earlier in the list
	*/
	template <typename T>
	class Component : public IComponent, public Dependancy <T, IComponent>
	{
	public:
		Component(){}
		virtual ~Component(){}



		virtual void onRenderActivate() override
		{
			// Do Nothing
		}
		virtual void onRenderDeactivate() override
		{
			// Do Nothing
		}



		virtual void onRenderActivate(IRenderableManager * view) override
		{
			// Do Nothing
		}
		virtual void onRenderDeactivate(IRenderableManager * view) override
		{
			// Do Nothing
		}



		virtual void update(const Float timeStep)
		{
			// Do Nothing
		}

	private:

	};
}
