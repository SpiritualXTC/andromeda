#ifndef _ANDROMEDA_UTILITIES_LOG_H_
#define _ANDROMEDA_UTILITIES_LOG_H_

#include <list>
#include <string>
#include <sstream>
#include <cstdarg>

#include <boost/format.hpp>

#include <andromeda/stddef.h>
#include <andromeda/glm.h>

#include <andromeda/Utilities/observer.h>
#include <andromeda/Utilities/singleton.h>


#define log_err(...) andromeda::Log::instance()->log(andromeda::Log::Error, __VA_ARGS__)
#define log_warn(...) andromeda::Log::instance()->log(andromeda::Log::Warning, __VA_ARGS__)
#define log_info(...) andromeda::Log::instance()->log(andromeda::Log::Information, __VA_ARGS__)
#define log_debug(...) andromeda::Log::instance()->log(andromeda::Log::Debug, __VA_ARGS__)
#define log_verbose(...) andromeda::Log::instance()->log(andromeda::Log::Verbose, __VA_ARGS__)

#define log_event(...) andromeda::Log::instance()->log(andromeda::Log::Event, __VA_ARGS__)

#define log_trace(...) andromeda::Log::instance()->log(andromeda::Log::Trace, __VA_ARGS__)


#define log_errp(...) andromeda::Log::instance()->logp(andromeda::Log::Error, __VA_ARGS__)
#define log_warnp(...) andromeda::Log::instance()->logp(andromeda::Log::Warning, __VA_ARGS__)
#define log_infop(...) andromeda::Log::instance()->logp(andromeda::Log::Information, __VA_ARGS__)
#define log_debugp(...) andromeda::Log::instance()->logp(andromeda::Log::Debug, __VA_ARGS__)
#define log_verbosep(...) andromeda::Log::instance()->logp(andromeda::Log::Verbose, __VA_ARGS__)

#define log_eventp(...) andromeda::Log::instance()->logp(andromeda::Log::Event, __VA_ARGS__)

#define log_tracep(...) andromeda::Log::instance()->logp(andromeda::Log::Trace, __VA_ARGS__)



namespace andromeda
{
	struct LogMessage
	{
		Int32 level;
		std::string message;
	};


	/*
		
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
		*/
		template <typename T>
		T const * argument(std::basic_string<T> const & value) noexcept
		{
			return value.c_str();
		}

		/*
			Converts Boolean to string representation of true/false
		*/
		char * argument(Boolean b) noexcept
		{
			return (b) ? "true" : "false";
		}

		/*
			TODO: Representations of numerous "common" formats.

			glm types, etc
		*/



	};



}

#endif