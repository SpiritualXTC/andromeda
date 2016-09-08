#pragma once

#include <functional>
#include <list>

#include <andromeda/stddef.h>

namespace andromeda
{
	/*
		TODO:
		Make this observer self unbinding

		This will require a pointer to the observerable

		However due to a single class being able to observe multiple observables/subjects

		An Observer might benefit from some type of identification label.
	*/

	template <typename T, typename ... ARGS>
	class IObserverEx
	{
	private:
		//typedef ObservableEx<T, ARGS> Observable;

	public:
		IObserverEx() {}
		virtual ~IObserverEx() {}

	protected:
		virtual void notify(const T* const, const ARGS& ...) = 0;
		virtual void destroy(const T* const){}	// This is called by the Observable when it is destroyed

		//std::list<Subject> _subjects;
	};




	template <typename T, typename ... ARGS>
	class ObservableEx
	{
	private:
		typedef IObserverEx<T, ARGS...> Observer;

	public:
		ObservableEx(){}
		virtual ~ObservableEx()
		{
		
		}


		// Adds an Observer
		Boolean addObserver(Observer * obs)
		{
			if (!obs) return false;

			_observers.push_back(obs);

			return true;
		}

		// Removes an Observer
		Boolean removeObserver(Observer * obs)
		{
			Int32 size = _observers.size();
			_observers.remove(obs);

			return size != _observers.size();
		}


	protected:
		// Notify the Observers about events
		void notify(const ARGS& ... args)
		{
			const T * const t = static_cast<T*>(this);

			for (const auto & it : _observers)
			{
				it->notify(t, args);
			}
		}

		// Notify the Observers this class is being destroyed
		void destroy()
		{
			const T * const t = static_cast<T*>(this);

			for (const auto & it : _observers)
				it.destroy(t);
		}

	private:
		//Int32 _autoId = 0;
		std::list<Observer*> _observers;
	};

}