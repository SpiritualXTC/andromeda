#pragma once

#include <memory>
#include <list>
#include <unordered_map>

#include <andromeda/stddef.h>
#include <andromeda/graphics.h>

#include "x_extension.h"

namespace andromeda
{
	namespace xeffect
	{
		// Forward Declarations
		class XTechnique;
		class XPass;






		/*
			This may end up being completely API agnostic :O

			The Global Shader will take effect here ... if it's worth going for....			[OPTIONAL]

			Essentially...
			
			EVERY shader that gets loaded will go to the same effect "pool"					[OPTIONAL]

			This can allow for optimizations across numerous shaders that share elements.	[OPTIMIZATION | OPTIONAL]
		*/
		class XEffect : public virtual Effect
		{
		public:
			XEffect();
			virtual ~XEffect();








		/*
			INTERFACE -- NOTHING SUPPORTED - REMOVE ALL OF THESE
		*/
			Boolean setActiveTechnique(const std::string & technique) override { return false; }

			Boolean beginTechnique(const std::string & technique) override { return false; }
			Boolean beginTechnique() override { return false; }
			Boolean endTechnique() override { return false; }


			Boolean beginPass(Int32 pass) override { return false; }
			Boolean endPass() override { return false; }


			/*

			*/
			const inline Int32 getNumPasses() const override
			{
			//	assert(_active);
			//	return _active->getNumPasses();
				return -1;
			}




			const inline void setUniformMat4(const std::string & name, glm::mat4 &m) const
			{

			}
			const inline void setUniformVec2(const std::string &name, const glm::vec2 &v)const
			{

			}
			const inline void setUniformVec3(const std::string &name, const glm::vec3 &v)const
			{

			}
			const inline void setUniformVec4(const std::string &name, const glm::vec4 &v)const
			{

			}

			const inline void setUniformTexture(const std::string &name, UInt32 bindIndex)const
			{

			}

			const inline void updateUniformMat4(const std::string & name, glm::mat4 &m) const
			{

			}
			const inline void updateUniformVec2(const std::string &name, const glm::vec2 &v)const
			{

			}
			const inline void updateUniformVec3(const std::string &name, const glm::vec3 &v)const
			{

			}
			const inline void updateUniformVec4(const std::string &name, const glm::vec4 &v)const
			{
	
			}

			const inline void updatetUniformTexture(const std::string &name, Int32 bindIndex)const
			{

			}





















			// Technique Exists 
			Boolean hasTechnique(const std::string & name) const;

			// Get the Technique
			std::shared_ptr<ITechnique> getTechnique(const std::string & name) const override;

			// Add a Technique
			Boolean addTechnique(std::shared_ptr<XTechnique> & technique);

		private:
			
			// Map of Techniques
			std::unordered_map<std::string, std::shared_ptr<XTechnique>> _technique;
		};
	}
}
