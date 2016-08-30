#pragma once
/*
	TODO:
	- Make Thread Safe
	- Add a channel system
		Different logging channels should be able to be configured. Configuration should be "soft" :: IE, "registration" only occurs when a filter is first used - and it would also ONLY be relevant to the logger
		A channel would logically group logs.
		It can be used for filtering, alternate "roots" in a tree structure, or labels.
		REASON:
		Multi-threaded code that has logging can output logs mixed in with different threads, making the logs harder to follow
*/

#include <list>
#include <mutex>
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

	//	std::mutex _mutex;


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


