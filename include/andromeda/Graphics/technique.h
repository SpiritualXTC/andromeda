#ifndef _ANDROMEDA_GRAPHICS_TECHNIQUE_H_
#define _ANDROMEDA_GRAPHICS_TECHNIQUE_H_


#include <memory>
#include <string>
#include <vector>


#include "../stddef.h"
#include "pass.h"


namespace andromeda
{
	// Forward Declarations
	class Pass;
	class Shader;


	/*
		The group ID is temporary
	*/
	class Technique
	{
	public:
		Technique(Int32 group = 0);
		virtual ~Technique();

		

		//Boolean addPass(const std::string & pass);
		Boolean addPass(std::shared_ptr<Pass> pass);

		Boolean removePass(const std::string & pass);


		/* Number of passes for this technique */
		const inline Int32 numPasses() const { return _passes.size(); }

		/* Is their an Active Pass? */
		const inline Boolean isActive() const { return !!_active; }


		Boolean beginPass(Int32 index);
		Boolean endPass();


		// Shortcut to Shader..... (TEMPORARY FOR NOW)
		const std::shared_ptr<Shader> shader() const { return _active == nullptr? nullptr : _active->shader(); }


		const inline Int32 group() const { return _group; }

	private:

		Int32 _group = 0;


		std::shared_ptr<Pass> _active = nullptr;
		std::vector<std::shared_ptr<Pass>> _passes;
	};
}

#endif