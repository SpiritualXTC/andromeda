#pragma once

#include <list>
#include <memory>
#include <mutex>

/*
	invoker.h:

	Want that function to be executed on the main thread? Pass it too meeee :)
*/

#include "module.h"

namespace andromeda
{
	/*
	
	*/
	class IRunnable
	{
	public:
		virtual void run() = 0;
	};








	/*
		TODO:
		Seriously do not know what to name this class
	*/
	class Invoker : public Module<Invoker>
	{
	public:
		Invoker();
		virtual ~Invoker();

		/*
		
		*/
		void addRunnable(std::unique_ptr<IRunnable> command);

	protected:
		// IModule
		void onPause() override {}
		void onResume() override {}
		void onStop() override {}




		void update() override;

	private:
		std::mutex _mutex;

		std::list<std::unique_ptr<IRunnable>> _commands;
	};

}