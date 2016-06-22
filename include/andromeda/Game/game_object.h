#ifndef _ANDROMEDA_GAME_GAME_OBJECT_H_
#define _ANDROMEDA_GAME_GAME_OBJECT_H_

#include <andromeda/stddef.h>

#include "entity.h"

#include <andromeda/Utilities/log.h>

namespace andromeda
{
	class IRenderable;
	class View;
	

	/*
		TODO:
		An Optimized Caching Mechanism Stored in the game Object
		Use a 64 bit INT, where each bit represents a different view.

		0 = No in View
		1 = In View

		The ID of the View, determines what bit is used.

		Events work the Same as they currently do - only doesn't require the hashmap lookup 
	*/



	/*
		Object that exists in the game
	*/
	class GameObject : public Entity
	{
	private:
		static Int32 GAME_OBJECT_COUNTER;
		static const std::string GAME_OBJECT_GENERIC_NAME;


		static inline std::string nextGenericName()
		{
			std::stringstream s(GAME_OBJECT_GENERIC_NAME);

			s << (++GAME_OBJECT_COUNTER);

			return s.str();
		}

	public:
		GameObject()
			: GameObject(nextGenericName())
		{

		}
		GameObject(const std::string & name);

		virtual ~GameObject() {}

	
		/*
			When activated for a view
		*/
		void onViewActivate(View * view);

		/*
			When deactivated for a view
		*/
		void onViewDeactivate(View * view);


		/*
			Gets the name of the Game Object
		*/
		const std::string & getName() const { return _name; }





		void update(const Float timeStep);


		// EXTREMELY FUCKING TEMPORARY
		// TEMP
		//virtual const std::shared_ptr<IRenderable> getRenderable() const = 0;
		//virtual void getAABB() = 0;

	private:
		std::string _name;

		Int32 _viewReferenceCounter = 0;
	};
}
#endif
