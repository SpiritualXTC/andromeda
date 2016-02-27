#ifndef _ANDROMEDA_GAME_COMPONENT_H_
#define _ANDROMEDA_GAME_COMPONENT_H_

#include <vector>
#include <cassert>

#include "../stddef.h"
#include "../Containers/vector.h"


#include "../Utilities/dependancy.h"
#include "../Utilities/template.h"

namespace andromeda
{
	class IComponent
	{
	public:
		IComponent(){}
		virtual ~IComponent(){}
	};



	template <typename T>
	class Component : public IComponent, public Dependancy <T, IComponent>
	{
	public:
		Component(){}
		virtual ~Component(){}

	private:

	};
}

#endif