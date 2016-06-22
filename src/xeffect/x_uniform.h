#pragma once

#include <memory>
#include <string>
#include <vector>

#include <andromeda/stddef.h>
#include <andromeda/Utilities/log.h>

#include "x_shader.h"

namespace andromeda
{
	class IShader;

	namespace xeffect
	{
		/*
		
		*/
		class XUniform
		{
		public:
			XUniform(const std::string & name) 
				: _name(name)
			{

			}
			virtual ~XUniform() {}

			virtual void apply(const std::shared_ptr<IShader> & shader) = 0;

			inline const std::string name() const { return _name; }

		private:
			std::string _name;
		};


		/*
		
		*/
		template <typename T>
		class XUniformType : virtual public XUniform
		{
		public:
			XUniformType(const std::string & name, const T & value)
				: XUniform(name)
				, _value(value)
			{

			}

			virtual ~XUniformType() {}


			/*

			*/
			void apply(const std::shared_ptr<IShader> & shader) override
			{
				assert(shader);
				shader->setUniform(name(), _value);

				//log_infop("")
			}


		private:
			T _value;
		};


#if 0
		/*
		
		*/
		template <typename T, enum glm::precision P = glm::precision::defaultp, template <typename, glm::precision> class V>
		class XUniformGLM : virtual public XUniform
		{
		private:
			typedef V<T, P> TYPE;
		public:
			XUniformGLM(const std::string & name, const TYPE & value)
				: XUniform(name)
				, _value(value)
			{
			
			}

			virtual ~XUniformGLM() {}


			/*
			
			*/
			void apply(const std::shared_ptr<IShader> & shader) override
			{

			}


		private:
			TYPE _value;
		};
#endif



	}
}