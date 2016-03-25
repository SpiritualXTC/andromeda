#ifndef _ANDROMEDA_GAME_ENTITY_HPP_
#define _ANDROMEDA_GAME_ENTITY_HPP_

#include <cassert>

namespace andromeda
{
	/*
		Create and add a component
	*/
	template <typename T, typename ... Args>
	Boolean Entity::addComponent(const Args& ... args)
	{
		// Component Already Exists
		if (hasComponent<T>())
			return false;

		// Create  & Add Component
		return addComponent<T>(std::make_shared<T>(args));
	}


	/*
		Add a component from existing pointer
	*/
	template <typename T>
	Boolean Entity::addComponent(std::shared_ptr<T> component)
	{
		assert(component);

		// Component Exists ?
		if (hasComponent<T>())
			return false;

		// Get ID
		Int32 id = getComponentId<T>();

		// Add Component
		_components[id] = component;

		// Return whether component exists [Success]
		return hasComponent<T>();
	}


	/*
		Remove a component
	*/
	template <typename T>
	Boolean Entity::removeComponent()
	{
		// Component Exists ?
		if (!hasComponent<T>())
			return false;

		// Get ID
		Int32 id = getComponentId<T>();

		// Erase
		_components.erase(id);

		// Return whether the component still exists
		return !hasComponent<T>();
	}


	/*
		Obtain a pointer to the component
	*/
	template <typename T>
	const std::shared_ptr<T> Entity::getComponentPtr()
	{
		// Component Doesn't Exist
		if (!hasComponent<T>())
		{
			// Auto Create
			return nullptr;
		}

		// Get Module ID
		Int32 id = getComponentId<T>();

		// Retrieve the Module
		return std::static_pointer_cast<T>(_components[id]);
	}

	/*
		Obtain a RAW pointer to the component
	*/
	template <typename T>
	const T * Entity::getComponent() const
	{
		std::shared_ptr<T> ptr = getComponentPtr<T>();

		return ptr.get();
	}



}

#endif