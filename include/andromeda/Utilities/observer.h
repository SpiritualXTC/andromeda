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

}










