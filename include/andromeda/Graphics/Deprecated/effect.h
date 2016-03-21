#ifndef _ANDROMEDA_GRAPHICS_EFFECT_H_
#define _ANDROMEDA_GRAPHICS_EFFECT_H_

#include <memory>
#include <string>
#include <unordered_map>

#include <andromeda/stddef.h>
#include "technique.h"

namespace andromeda
{
	// Forward Declaration
	class Pass;
	class Technique;
	class Shader;



	/*
		Note:

		A lot of functionality CANNOT be done, while a pass is active
	*/
	class Effect
	{
	public:
		typedef std::unordered_map<std::string, std::shared_ptr<Technique>>::iterator iterator;
		typedef std::unordered_map<std::string, std::shared_ptr<Technique>>::const_iterator const_iterator;
		
	public:
		Effect();
		virtual ~Effect();

		// Technique
		Boolean addTechnique(const std::string & technique, const Int32 group = 0);
		Boolean removeTechnique(const std::string & technique);

		Boolean setActiveTechnique(const std::string & technique);

		Boolean hasTechnique(const std::string & technique);

		const inline Boolean hasActiveTechnique() const { return !!_curTechnique; }
		

		// Pass
	//	Boolean addPass(const std::string & technique, const std::string & pass);
	//	Boolean addPass(const std::string & pass);
		Boolean addPass(const std::string & technique, std::shared_ptr<Pass> pass);

		Boolean removePass(const std::string & technique, const std::string & pass);
		Boolean removePass(const std::string & pass);


		Int32 numPasses();
		Boolean beingPass(Int32 index);
		Boolean endPass();

		Boolean isActive();

		// BAD!
		// Shortcut to Shader..... (TEMPORARY FOR NOW)
		const std::shared_ptr<Shader> shader() const { return _curTechnique == nullptr ? nullptr : _curTechnique->shader(); }


		iterator begin() { return _techniques.begin(); }
		iterator end() { return _techniques.end(); }

		const_iterator cbegin() { return _techniques.cbegin(); }
		const_iterator cend() { return _techniques.cend(); }


	private:
		std::shared_ptr<Pass> getPass(std::shared_ptr<Technique> technique, const std::string & pass);
		std::shared_ptr<Pass> getPass(std::shared_ptr<Technique> technique, Int32 index);

		Boolean addPass(std::shared_ptr<Technique> technique, std::shared_ptr<Pass> pass);
		Boolean removePass(std::shared_ptr<Technique> technique, const std::string & pass);


		std::shared_ptr<Technique> _curTechnique = nullptr;
	//	std::shared_ptr<Pass> _curPass = nullptr;

		std::unordered_map<std::string, std::shared_ptr<Technique>> _techniques;
	};



	/*
		Loads an Effect from File
	*/
	std::shared_ptr<Effect> LoadEffect(const std::string & filename);
}

typedef andromeda::Effect aEffect;

#endif