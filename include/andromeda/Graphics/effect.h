#pragma once

/*
	This file needs to be redone once knowledge has been attained as to how the fucking nvFX library works... :D
*/

#include <memory>
#include <string>
#include <cstdio>

#include <andromeda/glm.h>
#include <glm/gtc/type_ptr.hpp>

#include <andromeda/stddef.h>




#include <nvfx/FxParser.h>


/*
	TODO:
	Separate nvFX from Effect
	Rename Effect to NVEffect
	Rename IEffect to Effect
	Move NVEffect to src/ directory
*/

namespace andromeda
{
	/*
		Rename IPass to Pass
	*/
	
	class ITechnique;
	class IPass;



	/*
		TODO:
		Rename to Shader ... maybe
	*/
	class IShader
	{
	public:
		IShader() {}
		virtual ~IShader() {}

		virtual const inline void setUniform(const std::string &name, const glm::mat4 &m) const = 0;
		
		virtual const inline void setUniform(const std::string &name, const glm::fvec2 &v)const = 0;
		virtual const inline void setUniform(const std::string &name, const glm::fvec3 &v)const = 0;
		virtual const inline void setUniform(const std::string &name, const glm::fvec4 &v)const = 0;

		virtual const inline void setUniform(const std::string &name, const glm::ivec2 &v)const = 0;
		virtual const inline void setUniform(const std::string &name, const glm::ivec3 &v)const = 0;
		virtual const inline void setUniform(const std::string &name, const glm::ivec4 &v)const = 0;

		// This one is special :P
		virtual const inline void setUniformTexture(const std::string &name, UInt32 bindIndex)const = 0;
	};



	/*
		Core Effect Interface:

		TODO: Remove all da crap
	*/
	class Effect
	{
	public:
		Effect() {}
		virtual ~Effect() {}

		// NEW INTERFACE
		virtual std::shared_ptr<ITechnique> getTechnique(const std::string & name) const = 0;
		virtual std::shared_ptr<ITechnique> getTechniqueDefault() const = 0;

		virtual Boolean hasTechnique(const std::string & name) const = 0;






		/*
			TODO REMOVE
		*/
		// OLD INTERFACE
		virtual Boolean setActiveTechnique(const std::string & technique) = 0;

		virtual Boolean beginTechnique(const std::string & technique) = 0;
		virtual Boolean beginTechnique() = 0;
		virtual Boolean endTechnique() = 0;


		virtual Boolean beginPass(Int32 pass) = 0;
		virtual Boolean endPass() = 0;

		virtual const inline Int32 getNumPasses() const = 0;


		// Only the "Setter" is needed :: Move these to another interface. 
		// One that both IEffect and IPass extend
//		virtual const inline void setUniformMat4(const std::string &name, glm::mat4 &m) const = 0;
//		virtual const inline void setUniformVec2(const std::string &name, const glm::vec2 &v)const = 0;
//		virtual const inline void setUniformVec3(const std::string &name, const glm::vec3 &v)const = 0;
//		virtual const inline void setUniformVec4(const std::string &name, const glm::vec4 &v)const = 0;
//		virtual const inline void setUniformTexture(const std::string &name, UInt32 bindIndex)const = 0;
	};







	/*
		
	*/
	class ITechnique
	{
	public:
		ITechnique() {}
		virtual ~ITechnique() {}

		virtual const inline std::string & getName() const = 0;

		virtual std::shared_ptr<IPass> getPass(const std::string & name) const = 0;
		virtual std::shared_ptr<IPass> getPass(const Int32 index) const = 0;
		virtual const inline Int32 getNumPasses() const = 0;
	};




	/*
		
	*/
	class IPass : public virtual IShader
	{
	public:
		IPass() {}
		virtual ~IPass() {}


		virtual const inline std::string & getName() const = 0;

		virtual Boolean isEnabled() const = 0;

		virtual Boolean apply() = 0;
	};



}

