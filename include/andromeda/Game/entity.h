#ifndef _ANDROMEDA_GAME_ENTITY_H_
#define _ANDROMEDA_GAME_ENTITY_H_

#include <memory>
#include <unordered_map>
#include <vector>

#include "../stddef.h"

/*
	This class could do with some optimizations!
*/

namespace andromeda
{
	// Forward Declarations
	class IComponent;

	/*
	
	*/
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		/*
			Gets the Component ID
		*/
		template <class T>
		const inline Int32 getComponentID() const { return TemplateID<T, IModule>::getTemplateID(); }

		/*
			Determine whether a component type exists
		*/
		template <class T>
		const inline Boolean hasComponent() { return !!_components[getComponentID<T>()]; }


		/*
			Creates and Adds a Component
		*/
		template <typename T>
		Boolean addComponent();

		/*
			Adds the Component
		*/
		template <typename T>
		Boolean addComponent(std::shared_ptr<T> component);

		/*
			Remove a Component
		*/
		template <typename T>
		Boolean removeComponent();

		/*
			Get the Component Pointer
		*/
		template <typename T>
		std::shared_ptr<T> getComponentPtr();

		/*
			Get the RAW Component Pointer
		*/
		template <typename T>
		const T * getComponent() const;

	private:
		std::unordered_map<Int32, std::shared_ptr<IComponent>> _components;
	};
}

#include "entity.hpp"


typedef andromeda::Entity aEntity;

#endif