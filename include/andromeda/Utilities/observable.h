#pragma once

#include <list>
#include <memory>

#include <andromeda/stddef.h>

#include "observer.h"

namespace andromeda
{
	/*
		TODO:
		Observers & Observables need to be made more "user-friendly" rather than requiring numerous fuckarounds to get them working "naturally"



		The ONLY reason why a weak_ptr<> is used in the observable is for removal, when the reference is uninitialised, but not removed from the list.
	*/



	template <typename T>
	class Observable
	{
	public:
		Observable() {}
		virtual ~Observable() {}


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
			/*
				TEST THIS :(
			*/

			// Remove the Observer from the list
			//	const auto & it = std::find_if(_observers.begin(), _observers.end(), [observer](std::weak_ptr<IObserver<T>> obs) {return observer.lock() == obs.lock(); });
			//	_observers.erase(it);


			_observers.remove_if([observer](std::weak_ptr<IObserver<T>> obs) {return observer.lock() == obs.lock(); });
		}

#if 0
		/*
		TEST
		*/
		void add(std::enable_shared_from_this<IObserver<T>> observer)
		{
			add(observer->shared_from_this());
		}

		void remove(std::enable_shared_from_this<IObserver<T>> observer)
		{
			remove(observer->shared_from_this());
		}
#endif

	protected:
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
				if (!it.expired())
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