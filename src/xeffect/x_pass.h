#pragma once

#include <cassert>
#include <string>
#include <vector>

#include <andromeda/stddef.h>
#include <andromeda/Graphics/effect.h>


#include "x_shader.h"

namespace andromeda
{
	namespace xeffect
	{
		class IState;

		class XUniform;
		class XShaderProgram;

		/*
		
		*/
		class XPass : public virtual IPass
		{
		public:
			XPass(const std::string & name, const std::shared_ptr<XShaderProgram> & shader);
			virtual ~XPass();

			

			// Gets the Pass Name
			const inline std::string & getName() const override { return _name; }

			// Is the pass enabled?
			Boolean isEnabled() const override { return _enabled; }


			// Apply the Pass
			Boolean apply() override;




			/*

			*/
			inline void setUniform(const std::string & name, const glm::mat3 &m) const override
			{
				assert(_shader);
				_shader->setUniform(name, m);
			}
			/*
			
			*/
			inline void setUniform(const std::string & name, const glm::mat4 &m) const override
			{
				assert(_shader);
				_shader->setUniform(name, m);
			}


			/*
			
			*/
			inline void setUniform(const std::string &name, const glm::fvec2 &v) const override
			{
				assert(_shader);
				_shader->setUniform(name, v);
			}
			inline void setUniform(const std::string &name, const glm::fvec3 &v) const override
			{
				assert(_shader);
				_shader->setUniform(name, v);
			}
			inline void setUniform(const std::string &name, const glm::fvec4 &v) const override
			{
				assert(_shader);
				_shader->setUniform(name, v);
			}


			/*
			
			*/
			inline void setUniform(const std::string &name, const glm::ivec2 &v) const override
			{
				assert(_shader);
				_shader->setUniform(name, v);
			}
			inline void setUniform(const std::string &name, const glm::ivec3 &v) const override
			{
				assert(_shader);
				_shader->setUniform(name, v);
			}
			inline void setUniform(const std::string &name, const glm::ivec4 &v) const override
			{
				assert(_shader);
				_shader->setUniform(name, v);
			}

#if 0
			inline void setUniformTexture(const std::string &name, UInt32 bindIndex) const override
			{
				assert(_shader);
				_shader->setUniformTexture(name, bindIndex);
			}
#endif
			inline void setUniform(const std::string &name, const Float f) const override
			{
				assert(_shader);
				_shader->setUniform(name, f);
			}
			inline void setUniform(const std::string &name, const Int32 i) const override
			{
				assert(_shader);
				_shader->setUniform(name, i);
			}
			inline void setUniform(const std::string &name, const Boolean b) const override
			{
				assert(_shader);
				_shader->setUniform(name, b);
			}




			void addUniform(const std::string & name, const glm::fvec2 & v);
			void addUniform(const std::string & name, const glm::fvec3 & v);
			void addUniform(const std::string & name, const glm::fvec4 & v);

			void addUniform(const std::string & name, const glm::ivec2 & v);
			void addUniform(const std::string & name, const glm::ivec3 & v);
			void addUniform(const std::string & name, const glm::ivec4 & v);

			void addUniform(const std::shared_ptr<XUniform> & uniform);



			void addState(const std::shared_ptr<IState> & state);

			void setEnabled(Boolean enabled) { _enabled = enabled; }

		private:
			

			std::string _name;
			Boolean _enabled = true;

			/*
				TODO:
				Use the Interface
			*/
			std::shared_ptr<XShaderProgram> _shader;



			/*
				TODO: 
				This doesn't have to be JUST uniforms - after all, this function just loops through the array and calls the apply() function
				It could be a uniform variable - it could be a state change ?

				Currently the "Apply" function is different. Uniforms require a reference to the shader
			*/
			std::vector<std::shared_ptr<XUniform>> _uniforms;	
			std::vector<std::shared_ptr<IState>> _states;
		};
	}
}