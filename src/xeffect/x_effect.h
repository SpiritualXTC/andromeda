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
			
		*/
		class XEffect : public virtual Effect
		{
		public:
			XEffect();
			virtual ~XEffect();

			// Technique Exists 
			Boolean hasTechnique(const std::string & name) const override;

			// Get the Technique
			std::shared_ptr<ITechnique> getTechnique(const std::string & name) const override;

			// Get the Default Technique
			std::shared_ptr<ITechnique> getTechniqueDefault() const override;




			// Add a Technique
			Boolean addTechnique(std::shared_ptr<XTechnique> & technique);

		private:
			
			// Map of Techniques
			std::unordered_map<std::string, std::shared_ptr<XTechnique>> _technique;
		};
	}
}
