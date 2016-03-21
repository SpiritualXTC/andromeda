#pragma once

/*
	This file needs to be redone once knowledge has been attained as to how the fucking nvFX library works... :D
*/

#include <string>
#include <cstdio>

#include <andromeda/glm.h>
#include <glm/gtc/type_ptr.hpp>

#include <andromeda/stddef.h>




#include <nvfx/FxParser.h>

namespace andromeda
{
	class IEffect
	{
	public:
		IEffect() {}
		virtual ~IEffect() {}

		virtual const inline void setUniformMat4(const std::string & name, glm::mat4 &m) const = 0;
		virtual const inline void setUniformVec2(const std::string &name, const glm::vec2 &v)const = 0;
		virtual const inline void setUniformVec3(const std::string &name, const glm::vec3 &v)const = 0;
		virtual const inline void setUniformVec4(const std::string &name, const glm::vec4 &v)const = 0;
		virtual const inline void setUniformTexture(const std::string &name, UInt32 bindIndex)const = 0;

		virtual const inline void updateUniformMat4(const std::string & name, glm::mat4 &m) const = 0;
		virtual const inline void updateUniformVec2(const std::string &name, const glm::vec2 &v)const = 0;		
		virtual const inline void updateUniformVec3(const std::string &name, const glm::vec3 &v)const = 0;		
		virtual const inline void updateUniformVec4(const std::string &name, const glm::vec4 &v)const = 0;
		virtual const inline void updatetUniformTexture(const std::string &name, UInt32 bindIndex)const = 0;
	};



	class Effect : public IEffect
	{
	public:
		Effect();
		virtual ~Effect();


		Boolean setActiveTechnique(const std::string & technique);

		Boolean beginTechnique(const std::string & technique);
		Boolean beginTechnique();
		Boolean endTechnique();


		Boolean beginPass(Int32 pass);
		Boolean endPass();


		/*
		
		*/
		const inline Int32 getNumPasses() const
		{
			assert(_active);
			return _active->getNumPasses();
		}




		const inline void setUniformMat4(const std::string & name, glm::mat4 &m) const
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->setMatrix4f(glm::value_ptr(m));
		}
		const inline void setUniformVec2(const std::string &name, const glm::vec2 &v)const
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->setValue2f(v.x, v.y);
		}
		const inline void setUniformVec3(const std::string &name, const glm::vec3 &v)const
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->setValue3f(v.x, v.y, v.z);
		}
		const inline void setUniformVec4(const std::string &name, const glm::vec4 &v)const
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->setValue4f(v.x, v.y, v.z, v.w);
		}

		const inline void setUniformTexture(const std::string &name, UInt32 bindIndex)const
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->setValue1i(bindIndex);	// NOT SURE ABOUT THIS
		}




		const inline void updateUniformMat4(const std::string & name, glm::mat4 &m) const
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->updateMatrix4f(glm::value_ptr(m), _activePass);
		}
		const inline void updateUniformVec2(const std::string &name, const glm::vec2 &v)const
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->updateValue2f(v.x, v.y, _activePass);
		}
		const inline void updateUniformVec3(const std::string &name, const glm::vec3 &v)const
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->updateValue3f(v.x, v.y, v.z, _activePass);
		}
		const inline void updateUniformVec4(const std::string &name, const glm::vec4 &v)const
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->updateValue4f(v.x, v.y, v.z, v.w, _activePass);
		}

		const inline void updatetUniformTexture(const std::string &name, UInt32 bindIndex)const
		{
			
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->updateValue1i(bindIndex, _activePass);	// NOT SURE ABOUT THIS
		}





	private:
		void infoOutput();
		void shaderHack();

		nvFX::IContainer * _effect = nullptr;
		

		nvFX::ITechnique * _active = nullptr;
		nvFX::IPass * _activePass = nullptr;
	};
}

