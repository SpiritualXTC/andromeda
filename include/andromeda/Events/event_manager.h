#ifndef _ANDROMEDA_EVENT_EVENT_MANAGER_H_
#define _ANDROMEDA_EVENT_EVENT_MANAGER_H_

/*
	Event Manager
*/


#include <memory>
#include <functional>
#include <unordered_map>

#include <andromeda/stddef.h>
#include <andromeda/Utilities/singleton.h>
#include <andromeda/Utilities/template.h>

#include "event.h"

namespace andromeda
{
	/*
	
	*/
	class EventManager : public Singleton<EventManager>, public TemplateContainer<IEvent>
	{
	public:
		EventManager(){}
		virtual ~EventManager(){}

		/*
			Register the Event
		*/
		template <class EVENT>
		Boolean registerEvent(Int32 id);

		/*
			Unregister the Event
		*/
		template <class EVENT>
		Boolean unregisterEvent(Int32 id);

		/*
			Binds a Listener to the Event
		*/
		template <class EVENT>
		Int32 bind(Int32 id, std::function<Boolean(EVENT)> callback);

		/*
			Unbinds a Listener to the Event
		*/
		template <class EVENT>
		Boolean unbind(Int32 id, Int32 listenerId);

		/*
			Dispatches the Event		
		*/
		template <class EVENT>
		Boolean dispatch(Int32 id, EVENT & e);
		
	private:

		/*
			Get the Event ID
		*/
		template <class EVENT>
		inline Int32 getEventId(Int32 id)
		{
			return (getTemplateId<EVENT>() << 16) | id;
			//return (TemplateIndex<EVENT, IEvent>::getTemplateID() << 16) | id;
		}

		/*
			Retrieve the Event
		*/
		template <class EVENT>
		inline Event<EVENT> * getEvent(Int32 id)
		{
			Int32 uid = getEventId<EVENT>(id);

			if (!_events[uid])
				return nullptr;

			return static_cast<Event<EVENT>*>(_events[uid].get());
		}

		// Map of all Events
		std::unordered_map<Int32, std::unique_ptr<IEvent>> _events;
	};


	/*
		Namespace Helpers
	*/
	/*
		Register the Event
	*/
	template <class EVENT>
	inline Boolean registerEvent(Int32 id)
	{
		return EventManager::instance()->registerEvent<EVENT>(id);
	}

	/*
		Unregister the Event
	*/
	template <class EVENT>
	inline Boolean unregisterEvent(Int32 id)
	{
		return EventManager::instance()->unregisterEvent<EVENT>(id);
	}

	/*
		Binds a Listener to the Event
	*/
	template <class EVENT>
	inline Int32 bind(Int32 id, std::function<Boolean(EVENT)> callback)
	{
		return EventManager::instance()->bind<EVENT>(id, callback);
	}

	/*
		Unbinds a Listener to the Event
	*/
	template <class EVENT>
	inline Boolean unbind(Int32 id, Int32 listenerId)
	{
		return EventManager::instance()->unbind<EVENT>(id, listenerId);
	}

	/*
		Dispatches the Event
	*/
	template <class EVENT>
	inline Boolean dispatch(Int32 id, EVENT & e)
	{
		return EventManager::instance()->dispatch<EVENT>(id, e);
	}




}

#include "event_manager.hpp"


#endif