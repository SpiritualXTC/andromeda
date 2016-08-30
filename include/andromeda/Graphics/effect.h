#pragma once

#include <memory>
#include <string>
#include <cstdio>

#include <andromeda/glm.h>
#include <andromeda/stddef.h>


namespace andromeda
{
	/*

	*/
	class IShader
	{
	public:
		IShader() {}
		virtual ~IShader() {}

		/*
			TODO:
			These do not need to return const void... lol

			Should these even be const?
		*/

		// Matrices
		virtual const inline void setUniform(const std::string &name, const glm::mat3 &m) const = 0;
		virtual const inline void setUniform(const std::string &name, const glm::mat4 &m) const = 0;
		
		// Float Vec
		virtual const inline void setUniform(const std::string &name, const glm::fvec2 &v) const = 0;
		virtual const inline void setUniform(const std::string &name, const glm::fvec3 &v) const = 0;
		virtual const inline void setUniform(const std::string &name, const glm::fvec4 &v) const = 0;

		// Int Vec
		virtual const inline void setUniform(const std::string &name, const glm::ivec2 &v) const = 0;
		virtual const inline void setUniform(const std::string &name, const glm::ivec3 &v) const = 0;
		virtual const inline void setUniform(const std::string &name, const glm::ivec4 &v) const = 0;

		// Primitives
		virtual const inline void setUniform(const std::string &name, const Float f) const = 0;
		virtual const inline void setUniform(const std::string &name, const Int32 i) const = 0;
		virtual const inline void setUniform(const std::string &name, const Boolean b) const = 0;

		// This one is special :P
		virtual const inline void setUniformTexture(const std::string &name, UInt32 bindIndex) const = 0;
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
		Core Effect Interface:
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
	};












}

