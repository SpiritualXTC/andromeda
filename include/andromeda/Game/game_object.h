#ifndef _ANDROMEDA_GAME_GAME_OBJECT_H_
#define _ANDROMEDA_GAME_GAME_OBJECT_H_

#include <andromeda/stddef.h>

#include "entity.h"

#include <andromeda/Utilities/log.h>

namespace andromeda
{
	class IRenderable;	// TEMP
	class View;
	

	/*
		Object that exists in the game
	*/
	class GameObject : public Entity
	{
	private:
		static const Int32 GAME_OBJECT_COUNTER = 0;
		static const std::string GAME_OBJECT_GENERIC_NAME;


		static inline std::string nextGenericName()
		{
			return GAME_OBJECT_GENERIC_NAME + std::string(GAME_OBJECT_COUNTER);
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
