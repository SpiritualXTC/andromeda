#include <andromeda/Engine/invoker.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
Invoker::Invoker()
	: Module(Module::Idle)
{

}

/*

*/
Invoker::~Invoker()
{

}

/*

*/
void Invoker::addRunnable(std::unique_ptr<IRunnable> command)
{
	std::lock_guard<std::mutex> guard(_mutex);

	// Add Command
	_commands.push_back(std::move(command));
}

/*

*/
void Invoker::update()
{
	std::lock_guard<std::mutex> guard(_mutex);

	Int32 commands = 0;


	// Execute all the commands in order
	for (auto & it : _commands)
	{
		it->run();
		commands++;
	}

	// Clear List
	_commands.clear();
}
