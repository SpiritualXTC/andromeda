#pragma once

#include <common/observer.h>

namespace andromeda
{
	/*
		Ideally use a union to build the system level events up :)
	*/

	struct QuitEvent
	{
		QuitEvent() { cancel = false; }
		bool cancel;
	};

	typedef Observable<QuitEvent&> QuitObservable;

	class QuitListener : public QuitObservable::Observer
	{
	public:
		virtual void quit(QuitEvent& evt) = 0;
	};
}