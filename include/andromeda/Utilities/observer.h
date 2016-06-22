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

		virtual void notify(const T * const) = 0;
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
		void notify(const T * const p)
		{
			// Are their any weak pointers that need to be removed?
			Boolean weak = false;

			// TODO: There may be a threading related crash occuring here when an observer dies

			// Notify Observers
			for (auto & it : _observers)
			{
				//std::shared_ptr<IObserver<T>> ptr = it.lock();
				if (! it.expired())
					it.lock()->notify(p);
				else
					weak = true;
			}

			// Remove any ... weak links!
			if (weak)
				_observers.remove_if([](std::weak_ptr<IObserver<T>> observer) {return observer.expired(); });
		}

	private:
		std::list<std::weak_ptr<IObserver<T>>> _observers;
	};
}

#endif










