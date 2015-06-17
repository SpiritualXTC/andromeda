#ifndef _ANDROMEDA_EVENTS_EVENT_MANAGER_HPP_
#define _ANDROMEDA_EVENTS_EVENT_MANAGER_HPP_

namespace andromeda
{



	/*
	Move to a .hpp file :)
	*/

	/*
	Register the Event
	*/
	template<class EVENT>
	Boolean EventManager::registerEvent(Int32 id)
	{
		// Event is already registered
		if (getEvent<EVENT>(id))
			return false;

		// Event ID
		Int32 uid = getEventId<EVENT>(id);

		// Insert Event
		_events[uid] = std::make_unique<Event<EVENT>>();

		// Success ?
		return !!_events[uid];
	}

	/*
	Unregister the Event
	*/
	template <class EVENT>
	Boolean EventManager::unregisterEvent(Int32 id)
	{
		// Event doesn't Exist
		if (!getEvent<EVENT>(id))
			return false;

		// Event ID
		Int32 uid = getEventId<EVENT>(id);

		// Destroy Event
		_events.erase(uid);

		// Success ?
		return !_events[uid];
	}

	/*
	Bind Listener: Binds a listener to the Event
	*/
	template <class EVENT>
	Int32 EventManager::bind(Int32 id, std::function<Boolean(EVENT)> callback)
	{
		Event<EVENT> * evt = getEvent<EVENT>(id);

		return !!evt ? evt->bind(callback) : false;
	}

	/*
	Unbind Listener: Unbinds a listener to the Event
	*/
	template <class EVENT>
	Boolean EventManager::unbind(Int32 id, Int32 listenerId)
	{
		Event<EVENT> * evt = getEvent<EVENT>(id);

		return !!evt ? evt->unbind(listenerId) : false;
	}

	/*
	Dispatch Event: Dispatches an Event
	*/
	template<class EVENT>
	Boolean EventManager::dispatch(Int32 id, EVENT & e)
	{
		Event<EVENT> * evt = getEvent<EVENT>(id);

		return !!evt ? evt->dispatch(e) : false;
	}
}

#endif