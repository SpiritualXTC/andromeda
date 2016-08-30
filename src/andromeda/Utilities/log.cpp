#include <andromeda/Utilities/log.h>

#include <andromeda/Events/event_manager.h>

using namespace andromeda;


/*

*/
Log::Log()
{
	// Register Message Event
	registerEvent<LogMessage>(Log::Message);
}


/*

*/
Log::~Log()
{
	// Unregister Message Event
	unregisterEvent<LogMessage>(Log::Message);
}





/*

*/
void Log::log(LogLevel level, const std::string & message)
{
	// TODO: Pull the Logger away from the event manager, use observer pattern or some such [PRIORITY]
	// This is required.
	// However the locking mechanism is crashing.
	// REASON: The constructor is registering an event, which in-turn is logging info.
	// The mutex hasn't been initialised at this point, so it fails.


//	std::lock_guard<std::mutex> guard(_mutex);

	// Add Message
	LogMessage msg;
	msg.level = level;
	msg.message = message;

	// Send Notification to Observers
	//notify(this);

	// Send Event
	dispatch<LogMessage>(Log::Message, msg);
}






