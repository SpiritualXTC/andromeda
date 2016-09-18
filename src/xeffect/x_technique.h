#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <andromeda/stddef.h>
#include <andromeda/Graphics/effect.h>

namespace andromeda
{
	namespace xeffect
	{
		class XPass;


		/*
			This may end up being completely API agnostic :O
		*/
		class XTechnique : public virtual ITechnique
		{
		public:
			XTechnique(const std::string & name);
			virtual ~XTechnique();

			// Get Tecnique Name
			const inline std::string & getName() const override { return _name; }


			// Pass Exists 
			Boolean hasPass(const std::string & name) const;

			// Get the Pass
			std::shared_ptr<IPass> getPass(const std::string & name) const override;
			std::shared_ptr<IPass> getPass(const Int32 index) const override;


			// Add a Pass
			Boolean addPass(std::shared_ptr<XPass> & pass);


			// Get the number of passes
			const inline Int32 getNumPasses() const { return _passes.size(); }

			

		private:

			std::string _name;
			//std::unordered_map<std::string, std::shared_ptr<XPass>> _passes;
			std::vector<std::shared_ptr<XPass>> _passes;
		};
	}
}