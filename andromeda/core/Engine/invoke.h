#pragma once

#include <mutex>
#include <functional>

#include "module.h"

namespace andromeda
{
	class ICommand
	{
	public:
		ICommand() {}

		virtual Boolean execute() = 0;
	};

#if 0
	// TODO: This needs testing, and it probably wont work ... need to store arguments?
	template <class RETURN, class... ARGS>
	class CommandFunctionProxy : public ICommand
	{
	public:
		CommandFunctionProxy(std::function<RETURN(ARGS)>& fn)
			: _function(fn)
		{

		}

		Boolean execute() override
		{
			_function();
		}
	private:

		std::function<RETURN(ARGS)> _function;
	};
#endif

	class Invoke : public IModule
	{
	public:
		Invoke();
		virtual ~Invoke();

		void addCommand(std::unique_ptr<ICommand> command);

		// TODO: Add a command 
		template <class RETURN, class... ARGS>
		void addCommand(std::function<RETURN(ARGS...)>& fn)
		{
			// TODO: Implement
			return;
		}

	protected:

		// IModule
		Boolean pause() override { return true; }
		Boolean resume() override { return true; }

		Boolean open() override { return true; }
		Boolean close() override { return true; }
		
		Boolean update() override;

	private:
		std::mutex _mutex;

		std::list<std::unique_ptr<ICommand>> _commands;
	};
}