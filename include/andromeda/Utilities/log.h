#ifndef _ANDROMEDA_UTILITIES_LOG_H_
#define _ANDROMEDA_UTILITIES_LOG_H_

/*
	TODO:
	Add a begin/end indent system to allow for a more detailed set of logging where implementations can auto-tab correctly
	and other implementations could in theory set up a expandable tree UI
*/

#include <list>
#include <string>
#include <sstream>
#include <cstdarg>

#include <boost/format.hpp>
#include <boost/optional.hpp>

#include <andromeda/stddef.h>
#include <andromeda/glm.h>

#include <andromeda/Utilities/observer.h>
#include <andromeda/Utilities/singleton.h>


/*
	Non Variable Macros
*/
#define log_err(message) andromeda::Log::instance()->log(andromeda::Log::Error, (message))
#define log_warn(message) andromeda::Log::instance()->log(andromeda::Log::Warning, (message))
#define log_info(message) andromeda::Log::instance()->log(andromeda::Log::Information, (message))
#define log_debug(message) andromeda::Log::instance()->log(andromeda::Log::Debug, (message))
#define log_verbose(message) andromeda::Log::instance()->log(andromeda::Log::Verbose, (message))

#define log_event(message) andromeda::Log::instance()->log(andromeda::Log::Event, (message))

#define log_trace(message) andromeda::Log::instance()->log(andromeda::Log::Trace, (message))


/*
	Variable Macros [Boost Syntax]
*/
#define log_errp(...) andromeda::Log::instance()->logp(andromeda::Log::Error, __VA_ARGS__)
#define log_warnp(...) andromeda::Log::instance()->logp(andromeda::Log::Warning, __VA_ARGS__)
#define log_infop(...) andromeda::Log::instance()->logp(andromeda::Log::Information, __VA_ARGS__)
#define log_debugp(...) andromeda::Log::instance()->logp(andromeda::Log::Debug, __VA_ARGS__)
#define log_verbosep(...) andromeda::Log::instance()->logp(andromeda::Log::Verbose, __VA_ARGS__)

#define log_eventp(...) andromeda::Log::instance()->logp(andromeda::Log::Event, __VA_ARGS__)

#define log_tracep(...) andromeda::Log::instance()->logp(andromeda::Log::Trace, __VA_ARGS__)



/*
	Increase/Decrease the Logging Depth.
	This allows the logging system to better show log "flow"

	Recieving push/pop messages allows the log display to:
	- For example, increase TAB depth
	- Add Depth Heirarchy to a tree based log

	From now on, use the log_tree() system defined below :D
*/
//#define log_push() andromeda::Log::instance()->log(andromeda::Log::Push, "")
//#define log_pop() andromeda::Log::instance()->log(andromeda::Log::Pop, "")

#define log_break() andromeda::Log::instance()->log(andromeda::Log::Break, "'")


namespace andromeda
{
	struct LogMessage
	{
		Int32 level;
		std::string message;
	};


	/*
		
	*/
	class Log : public Singleton<Log>
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

			// Management
			Push,				// :: Message should be ignored - Increases Info Depth
			Pop,				// :: Message should be ignored - Decrease Info Depth
			Break,				// :: Break, Do Nothin
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

		inline void push()
		{
			log(Log::Push, "");
		}
		inline void pop()
		{
			log(Log::Pop, "");
		}
	


		/*
			Better way of logging supported by BOOOOOOST
		*/
		template <typename ... Args>
		void logp(LogLevel level, const std::string & format, Args const & ... args) noexcept
		{
			boost::format fmt = boost::format(format);

			int a[] = { 0, ((void)(fmt % argument(args)), 0) ... };

			log(level, boost::str(fmt));
		}

	private:

		/*
			Passes the argument straight though
		*/
		template <typename T>
		T argument(T value) noexcept
		{
			return value;
		}


		/*
			Converts std::basic_string to [w]char* pointer 

			Not sure if this will be needed again... but it may come in handy later on
		*/
#if 0
		template <typename T>
		T const * argument(const std::basic_string<T> & value) noexcept
		{
			return value.c_str();
		}
#endif

		/*
			Converts std::string to char * pointer 
		*/
		const char * argument(const std::string & value) noexcept
		{
			return value.c_str();
		}

		/*
			Converts Boolean to string representation of true/false
		*/
		const char * argument(Boolean b) noexcept
		{
			return (b) ? "true" : "false";
		}

		/*
			Converts boost::optional to string representation of null ... or send the value down the pipe
		*/
		template <typename T>
		const char * argument(const boost::optional<T> & value) noexcept
		{ 
			return value.is_initialized() ? argument(value.get()) : "null";
		}

		/*
			TODO: Representations of numerous "common" formats.

			glm types, etc
		*/
	};


	/*
		TODO: [Test]
		An Automatic Pusher/Popper

		As soon as it goes out of scope it "pops"
	*/
	struct __LogTree
	{
	public:
		__LogTree()
		{
			push();
		}

		~__LogTree()
		{
			while (_count > 0)
				pop();
		}

		void push()
		{
			_count++;
		//	log_push();
			Log::instance()->push();
		}

		void pop()
		{
			if (_count <= 0)
				return;

		//	log_pop();
			Log::instance()->pop();
			_count--;
		}

	private:
		Int32 _count = 0;
	};
}


#if defined(_DEBUG)
#define log_tree() __LogTree _logger
#define log_treepush() _logger.push()
#define log_treepop() _logger.pop()
#else
#define log_tree() ()
#define log_treepush() ()
#define log_treepop() ()
#endif


#endif