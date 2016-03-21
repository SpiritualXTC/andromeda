#ifndef _ANDROMEDA_GAME_COMPONENT_H_
#define _ANDROMEDA_GAME_COMPONENT_H_

#include <vector>
#include <cassert>

#include <andromeda/stddef.h>



#include <andromeda/Utilities/dependancy.h>
#include <andromeda/Utilities/template.h>

namespace andromeda
{
	class View;

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
		virtual inline void onViewActivate() = 0;

		/*
			Deactivation that occurs when ANY view deactivates the objects
		*/
		virtual inline void onViewDeactivate() = 0;

		/*
			Activation that occurs when a SPECIFIC view activates the object
		*/
		virtual inline void onViewActivate(View * view) = 0;

		/*
			Deactivation that occurs when a SPECIFIC view activates the object
		*/
		virtual inline void onViewDeactivate(View * view) = 0;
	};



	/*
		I Dont think this really needs the Dependancy Chain :P
	*/
	template <typename T>
	class Component : public IComponent, public Dependancy <T, IComponent>
	{
	public:
		Component(){}
		virtual ~Component(){}



		virtual inline void onViewActivate() override
		{
			// Do Nothing
		}
		virtual inline void onViewDeactivate() override
		{
			// Do Nothing
		}


		virtual inline void onViewActivate(View * view) override
		{
			// Do Nothing
		}
		virtual inline void onViewDeactivate(View * view) override
		{
			// Do Nothing
		}

	private:

	};
}

#endif