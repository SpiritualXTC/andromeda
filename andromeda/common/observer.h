#pragma once

#include <functional>
#include <list>

#include "debug.h"
#include "types.h"

namespace andromeda
{
	/*
		TODO:
		Less public scope would be nice :)
	*/
	class IObservable
	{
	public:
		friend class ObserverTracker;
		
	protected:
		virtual Boolean removeTracked(UInt64 trackerId) = 0;
	};
	

	class ObserverTracker
	{
	private:
		static UInt64 AUTO_TRACKER;

		template <typename ... ARGS>
		friend class Observable;
	public:
		ObserverTracker()
			: _trackerId(++ObserverTracker::AUTO_TRACKER)
		{

		}

		virtual ~ObserverTracker()
		{
			// TODO: Crash occuring here ?!?
			for (auto it : _subjects)
			{
			
				it->removeTracked(_trackerId);
			}
		}

		void track(IObservable * const o )
		{
			_subjects.push_back(o);
		}

		void untrack(IObservable * const o)
		{
			auto it = std::find(_subjects.begin(), _subjects.end(), o);
			if (it != _subjects.end())
				_subjects.remove(o);
		}

		void destroy(IObservable * const o)
		{
			untrack(o);
		}

		inline UInt64 getTrackerId() { return _trackerId; }

	private:
		UInt64 _trackerId;
		std::list<IObservable*> _subjects;
	};


	template <typename ... ARGS>
	class IObserver : virtual public ObserverTracker
	{
	public:
		IObserver() {}
		virtual ~IObserver() {}

		virtual void notify(ARGS ...) = 0;
	};


	template <typename ... ARGS>
	class Observable : protected IObservable
	{
	public:
		friend class ObserverTracker;

	public:
		typedef IObserver<ARGS...> Observer;

	public:
		Observable(){}
		virtual ~Observable()
		{
		
		}

		Boolean addObserver(IObserver<ARGS ...> * obs)
		{
			if (!obs) return false;

			obs->track(this);
			_observers.push_back(obs);

			return true;
		}

		Boolean removeObserver(IObserver<ARGS ...> * obs)
		{
			Int32 size = _observers.size();
			_observers.remove(obs);
			obs->untrack(this);

			return size != _observers.size();

			// Weak-Ptr Removal
			//_observers.remove_if([observer](std::weak_ptr<IObserver<T>> obs) {return observer.lock() == obs.lock(); });
		}

	protected:
		// Notify the Observers about events
		void notify(ARGS ... args)
		{
			for (const auto & it : _observers)
			{
				it->notify(args ...);
			}
		}

		// Notify the Observers this class is being destroyed
		void destroy()
		{
			for (const auto & it : _observers)
				it->destroy(this);
		}

		// Special automatic removal
		Boolean removeTracked(UInt64 trackerId)  override
		{
			Int32 size = _observers.size();
			_observers.remove_if([trackerId](Observer* o) {return o->getTrackerId() == trackerId; });

			return size != _observers.size();
		}

	private:
		std::list<Observer*> _observers;
	};

}