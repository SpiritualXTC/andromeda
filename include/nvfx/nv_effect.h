#pragma once

#include <andromeda/Graphics/effect.h>

/*
	TODO:
	This entire set of code needs to be rewritten to support the new Effect Interfaces & Use

	For now... it compiles and probably wont work - in the engine at least.
*/


namespace andromeda
{
	/*

	*/
	class NVEffect : virtual public Effect, virtual public IShader
	{
	public:
		NVEffect();
		virtual ~NVEffect();



		std::shared_ptr<ITechnique> getTechnique(const std::string & name) const override { return nullptr; }




		Boolean setActiveTechnique(const std::string & technique) override;

		Boolean beginTechnique(const std::string & technique) override;
		Boolean beginTechnique() override;
		Boolean endTechnique() override;


		Boolean beginPass(Int32 pass) override;
		Boolean endPass() override;


		/*

		*/
		const inline Int32 getNumPasses() const override
		{
			assert(_active);
			return _active->getNumPasses();
		}

		/*
			Floats
		*/
		const inline void setUniform(const std::string & name, glm::mat4 &m) const override
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->updateMatrix4f(glm::value_ptr(m), _activePass);
		}
		const inline void setUniform(const std::string &name, const glm::fvec2 &v)const override
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->updateValue2f(v.x, v.y, _activePass);
		}
		const inline void setUniform(const std::string &name, const glm::fvec3 &v)const override
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->updateValue3f(v.x, v.y, v.z, _activePass);
		}
		const inline void setUniform(const std::string &name, const glm::fvec4 &v)const override
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->updateValue4f(v.x, v.y, v.z, v.w, _activePass);
		}

		/*
			Ints
		*/
		const inline void setUniform(const std::string &name, const glm::ivec2 &v)const override
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->updateValue2i(v.x, v.y, _activePass);
		}
		const inline void setUniform(const std::string &name, const glm::ivec3 &v)const override
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->updateValue3i(v.x, v.y, v.z, _activePass);
		}
		const inline void setUniform(const std::string &name, const glm::ivec4 &v)const override
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->updateValue4i(v.x, v.y, v.z, v.w, _activePass);
		}

		/*
			Texture
		*/
		const inline void setUniformTexture(const std::string &name, UInt32 bindIndex)const override
		{
			nvFX::IUniform * uniform = _effect->findUniform(name.c_str());
			uniform->updateSamplerUnit(bindIndex, _activePass);
			//	uniform->setValue1i(bindIndex);	// NOT SURE ABOUT THIS
		}







	private:
		void infoOutput();
		void shaderHack();

		Boolean validate();

		nvFX::IContainer * _effect = nullptr;


		nvFX::ITechnique * _active = nullptr;
		nvFX::IPass * _activePass = nullptr;
	};
}