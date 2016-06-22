#pragma once

#include <memory>
#include <vector>
#include <sstream>

#include <andromeda/stddef.h>

namespace andromeda
{
	namespace xeffect
	{
		class XExtension;
		class XShader;
		class XShaderProgram;
		class XShaderSource;

		enum class XShaderType;

		/*
			Builds a Shader
		*/
		class XShaderBuilder
		{
		public:
			XShaderBuilder(XShaderType shaderType);
			virtual ~XShaderBuilder();


			/*
			
			*/
			Boolean attachHeader(XExtension & extensions);

			/*
			
			*/
			Boolean attachCode(std::shared_ptr<XShaderSource> & source);


			/*
			
			*/
			std::shared_ptr<XShader> compile();


			const inline std::string source() const { return _source.str(); }

		private:
			std::stringstream _source;
			XShaderType _shaderType;
		};



		/*
			Builds a Shader Program
		*/
		class XShaderProgramBuilder
		{
		public:
			XShaderProgramBuilder();
			virtual ~XShaderProgramBuilder();


			/*
			
			*/
			void attachShader(const std::shared_ptr<XShaderBuilder> & shader);

			/*
			
			*/
			std::shared_ptr<XShaderProgram> link();

		private:
			std::vector<std::shared_ptr<XShaderBuilder>> _shaders;
		};

	}
}
