#ifndef _ANDROMEDA_UTILITIES_LOG_H_
#define _ANDROMEDA_UTILITIES_LOG_H_

#include <list>
#include <string>
#include <sstream>
#include <cstdarg>

#include "../stddef.h"

#include "../Utilities/observer.h"
#include "../Utilities/singleton.h"


#define log_err(...) andromeda::Log::instance()->log(andromeda::Log::Error, __VA_ARGS__)
#define log_warn(...) andromeda::Log::instance()->log(andromeda::Log::Warning, __VA_ARGS__)
#define log_info(...) andromeda::Log::instance()->log(andromeda::Log::Information, __VA_ARGS__)
#define log_debug(...) andromeda::Log::instance()->log(andromeda::Log::Debug, __VA_ARGS__)
#define log_verbose(...) andromeda::Log::instance()->log(andromeda::Log::Verbose, __VA_ARGS__)

#define log_event(...) andromeda::Log::instance()->log(andromeda::Log::Event, __VA_ARGS__)

#define log_trace(...) andromeda::Log::instance()->log(andromeda::Log::Trace, __VA_ARGS__)


namespace andromeda
{
	// This is currently running through the event system :: For now. but it works, has global access, and allows it to be customised.
	// It also allows multiple logging implementations to react to log events :)
	struct LogMessage
	{
		Int32 level;
		std::string message;
	};


	/*
		This would be better using a observer pattern than tapping into the event manager .. but yolo :)

		The Log will probably be a singleton anyway.... being a utility class....
	*/
	class Log : public Singleton<Log>, public Observable<Log>
	{
	public:
		enum LogLevel
		{
			Error,
			Warning,
			Information,
			Debug,
			Verbose,

			Event,
			Trace,
		};

		enum LogEvent
		{
			Message,
		};

	public:
		Log();
		virtual ~Log();

		/*
		
		*/
		void log(LogLevel level, const std::string & message);

		/*
			A really bad way of doing logging.......
			but for now it will do, as it works!
		*/
		template <typename ... Args>
		void log(LogLevel level, const Args& ... args)
		{
			std::stringstream stream;

			int a[] = { 0, ((void)(stream << args << " "), 0) ... };

			log(level, stream.str());

			return;
		}


	private:
	};



}

#endif