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
	// Add Message
	LogMessage msg;
	msg.level = level;
	msg.message = message;

	// Send Notification to Observers
	//notify(this);

	// Send Event
	dispatch<LogMessage>(Log::Message, msg);
}






