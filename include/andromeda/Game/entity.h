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
	private:
		typedef std::unordered_map<Int32, std::shared_ptr<IComponent>> ComponentMap;

	public:
		Entity() {}
		virtual ~Entity() {}

		/*
			Gets the Component ID
		*/
		template <class T>
		const inline Int32 getComponentID() const { return TemplateID<T, IComponent>::getTemplateID(); }

		/*
			Determine whether a component type exists
			:: May be a bug here. That Syntax may actually add a dummy component
			:: Use .exists() (or .find() or whatever :)
		*/
		template <class T>
		//const inline Boolean hasComponent() { return !!_components[getComponentID<T>()]; }
		const inline Boolean hasComponent() { return _components.find(getComponentID<T>()) != _components.end(); }


		/*
			Creates and Adds a Component
		*/
		template <typename T, typename ... Args>
		Boolean addComponent(const Args& ... args);

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
		const std::shared_ptr<T> getComponentPtr();

		/*
			Get the RAW Component Pointer
		*/
		template <typename T>
		const T * getComponent() const;


		/*
			Add Direct Iteration Support ????
		*/

	//protected:
		inline ComponentMap & components() { return _components; }


	private:
		ComponentMap _components;
	};
}

#include "entity.hpp"


typedef andromeda::Entity aEntity;

#endif