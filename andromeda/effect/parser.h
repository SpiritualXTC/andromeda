#pragma once

#include <memory>
#include <string>
#include <vector>

namespace andromeda
{
	namespace effect
	{
		class Function;
		class Uniform;
		class Shader;
		class Technique;
		class Pass;
		class Effect;
		
		class Parser
		{
		public:

			void parse(const std::string& fileContents);


		private:
			;

			void stripMultiLineComment(std::string& contents);

			void stripWhitespace(std::string& line);
			void stripSingleLineComment(std::string& line);

			bool includeFile(std::string& line);

		private:
			std::vector<Uniform> _uniforms;
			std::vector<Function> _functions;
			std::vector<Shader> _shader;
		};
	}
}