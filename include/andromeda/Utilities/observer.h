#ifndef _ANDROMEDA_UTILITY_OBSERVER_H_
#define _ANDROMEDA_UTILITY_OBSERVER_H_

#include <list>
#include <memory>

#include "../stddef.h"

namespace andromeda
{
	template <class T>
	class IObserver
	{
	public:
		IObserver() {}
		virtual ~IObserver() {}

		virtual void notify(T *) = 0;
	};


	template <class T>
	class Observable
	{
	public:
		Observable(){}
		virtual ~Observable(){}


		/*
			Add an Observer
		*/
		void add(std::weak_ptr<IObserver<T>> observer)
		{
			// Is the observer already in the list ??

			// Add to List
			_observers.push_back(observer);
		}

		/*
			Remove the Observer
		*/
		void remove(std::weak_ptr<IObserver<T>> observer)
		{
			// Remove the Observer from the list
			_observers.erase(observer);
		}


		/*
			Generic Notification
		*/
		void notify(T * p)
		{
			//T* p = static_cast<T*>(this);

			// Remove any ... weak links!
			_observers.remove_if([](std::weak_ptr<IObserver<T>> observer){return observer.expired(); });

			// Notify Observers
			for (auto it : _observers)
				it.lock()->notify(p);
		}

	private:
		std::list<std::weak_ptr<IObserver<T>>> _observers;
	};
}

#endif










