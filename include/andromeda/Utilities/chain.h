#pragma once

/*
	Generic Chain of Responsibility
*/

#include <memory>

#include <andromeda/stddef.h>

#include <boost/optional.hpp>

namespace andromeda
{
	template <typename RETURN, typename... ARGS>
	class Chain
	{
	public:
		typedef Chain<RETURN, ARGS...> type;

		/*
			Adds a new Responsibility
		*/
		void add(std::shared_ptr<Chain<RETURN, ARGS...>> link)
		{
			if (_next)
				_next->add(link);
			else
				_next = link;
		}

		/*
			Handle it
		*/
		boost::optional<RETURN> handle(ARGS&... args)
		{
			// Process the Input
			boost::optional<RETURN> p = process(std::forward<ARGS>(args)...);

			// Valid output ?
			if (p.is_initialized())
				return p;
			else if (_next)
				return _next->handle(std::forward<ARGS>(args)...);

			return p;
		}

	protected:
		/*
			Default Process
		*/
		virtual boost::optional<RETURN> process(ARGS&... args)
		{
			boost::optional<RETURN> p;
			
			return p;
		}

	private:
		std::shared_ptr<Chain<RETURN, ARGS...>> _next;
	};
}
