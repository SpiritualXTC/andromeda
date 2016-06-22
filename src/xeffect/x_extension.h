#pragma once

#include <string>
#include <list>

#include <boost/optional.hpp>

#include <andromeda/stddef.h>

namespace andromeda
{
	namespace xeffect
	{




		/*
			TODO:
			This is really a shader header now... lolololol
		*/
		class XExtension
		{
		public:
#if 0
			enum _Behaviour
			{
				Enable,
				Require,
				Warning,
				Disable,
			};
#endif
		private:
			struct _Extension
			{
				std::string extension;
				std::string behaviour;
			};

		



		public:
			XExtension();
			virtual ~XExtension();

			void setVersion(boost::optional<std::string> & version);

			Boolean addExtension(const std::string & extension, const std::string & behaviour);
	

			std::string getHeader();



		private:
			
			// Shader Version
			boost::optional<std::string> _version;

			// OpenGL Extensions
			std::list<_Extension> _extensions;
		};

	}
}
