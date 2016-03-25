#ifndef _ANDROMEDA_EVENT_EVENT_H_
#define _ANDROMEDA_EVENT_EVENT_H_

#include <cassert>
#include <functional>



#include "../stddef.h"
#include "../Utilities/template.h"

namespace andromeda
{
	/*
	
	*/
	class IEvent
	{
	public:
		IEvent(){}
		virtual ~IEvent(){}
	};



	/*
	
	*/
	template <class EVENT>
	class Event : public IEvent//, public TemplateIndex<EVENT, IEvent>
	{
	private:
		struct Listener
		{
			Int32 id;
			std::function<Boolean(EVENT&)> callback;
		};

	public:
		Event() {}
		virtual ~Event(){}


		/*
			Returns the listener ID
		*/
		Int32 bind(std::function<Boolean(EVENT&)> callback)
		{
			assert(callback);

			// Setup the Structure
			Listener listener;
			listener.id = ++_listenerIncrement;
			listener.callback = callback;

			// Add to List
			_listeners.push_back(listener);

			// Return ID
			return listener.id;
		}

		/*
			Unbind the Listener with matching ID
		*/
		Boolean unbind(Int32 listenerId)
		{
			_listeners.remove_if([listenerId](Listener & l){return l.id == listenerId; });

			return true;
		}

		/*
			Dispatch Events to All Listeners
		*/
		Boolean dispatch(EVENT & e)
		{
			for (auto it : _listeners)
			{
				it.callback(e);
			}

			return true;
		}


	private:


		std::list<Listener> _listeners;

		Int32 _listenerIncrement = 0;	// Auto-Increment Listener ID
	};
}

#endif