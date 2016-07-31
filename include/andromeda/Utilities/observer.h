#pragma once



#include "../stddef.h"

namespace andromeda
{
	template <typename T>
	class IObserver 
	{
	public:
		IObserver() {}
		virtual ~IObserver() {}

		virtual void notify(const T * const) = 0;
	};





	/*
		TEMPORARY.
		Helps implement observers that need to pass "this" into a class in the constructor
	*/
	template <typename OBSERVABLE>
	class ObserverHelper : public IObserver<OBSERVABLE>
	{
	public:
		ObserverHelper(IObserver<OBSERVABLE> * self)
			: _observer(self)
		{
			assert(_observer);
		}

		void notify(const OBSERVABLE * const obs) override
		{
			_observer->notify(obs);
		}

	private:
		IObserver<OBSERVABLE> * _observer;
	};




#if 0
	template <class T>
	class IObserverSelf : public IObserver<T>, public std::enable_shared_from_this<IObserverSelf<T>>
	{
	public:
		void bind(Observable<T> * o)
		{
			o->add(shared_from_this());
		}
		void unbind(Observable<T> * o)
		{
			o->remove(shared_from_this());
		}
	};
#endif



	/*
		New Observer System.... /SIGH
	*/



}










