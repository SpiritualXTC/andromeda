#include "invoke.h"

using namespace andromeda;

/*
	TODO: Complete the CommandProxy class
*/





Invoke::Invoke()
{

}

Invoke::~Invoke()
{

}

void Invoke::addCommand(std::unique_ptr<ICommand> command)
{
	std::lock_guard<std::mutex> guard(_mutex);
	_commands.push_back(std::move(command));
}

void addCommand(std::function<void(void)>& fn)
{

}

Boolean Invoke::update()
{
	// TODO: Add a CPU Timer to this Function. Will allow for limiting the per frame how much is being executed
	// TODO: Add a Max CPU time to the class. To control the limits
	// TODO: Maybe add a priority to the Commands for sorting? So Higher priority tasks get done sooner. This will require slowly increases the priority of tasks as they become stale

	std::list<std::unique_ptr<ICommand>> copy;

	{
		std::lock_guard<std::mutex> guard(_mutex);
		for (auto& it : _commands)
		{
			copy.push_back(std::move(it));
		}
		_commands.clear();
	}

	Size commands = 0;

	for (auto & it : copy)
	{
		if (it->execute())
			commands++;
	}

	return commands != copy.size();}