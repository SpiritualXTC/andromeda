#ifndef _ANDROMEDA_GAME_ENTITY_HPP_
#define _ANDROMEDA_GAME_ENTITY_HPP_

//#include "../stddef.h"

namespace andromeda
{
	/*
	
	*/
	template <typename T>
	Boolean Entity::addComponent()
	{
		// Component Already Exists
		if (hasComponent<T>())
			return false;

		// Create  & Add Component
		return addComponent<T>(std::make_shared<T>());
	}


	/*

	*/
	template <typename T>
	Boolean Entity::addComponent(std::shared_ptr<T> component)
	{
		// Component Exists ?
		if (hasComponent<T>())
			return false;

		// Get ID
		Int32 id = getComponentID<T>();

		// Add Component
		_components[id] = component;

		// Return whether component exists [Success]
		return hasComponent<T>();
	}


	/*
	
	*/
	template <typename T>
	Boolean Entity::removeComponent()
	{
		// Component Exists ?
		if (!hasComponent<T>())
			return false;

		// Get ID
		Int32 id = getComponentID<T>();

		// Erase
		_components.erase(id);

		// Return whether the component still exists
		return !hasComponent<T>();
	}


	/*
	
	*/
	template <typename T>
	std::shared_ptr<T> Entity::getComponentPtr()
	{
		// Component Doesn't Exist
		if (!hasComponent<T>())
		{
			// Auto Create
			return nullptr;
		}

		// Get Module ID
		Int32 id = getComponentID<T>();

		// Retrieve the Module
		return std::static_pointer_cast<T>(_components[id]);
	}

	/*
	
	*/
	template <typename T>
	const T * Entity::getComponent() const
	{
		std::shared_ptr<T> ptr = getComponentPtr<T>();

		return ptr.get();
	}



}

#endif