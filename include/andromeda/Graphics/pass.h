#ifndef _ANDROMEDA_GRAPHICS_PASS_H_
#define _ANDROMEDA_GRAPHICS_PASS_H_

#include <memory>

#include "../stddef.h"

#include "opengl.h"

namespace andromeda
{
	// Forward Declarations
	class Shader;

	/*
	
	*/
	class Pass
	{
	private:
		struct _Option
		{
			(void*)glFunc(GLenum, GLint);	// Not sure how this will work........ lol
		};


	public:
		Pass(std::shared_ptr<Shader> shader);
		virtual ~Pass();

		const inline Boolean isEnabled() const { return _enabled; }
		const inline std::shared_ptr<Shader> & shader() { return _shader; }

		void begin();
		void end();


		void enable() { _enabled = true; }
		void disable() { _enabled = false; }

	private:
		Boolean _enabled = true;

		std::shared_ptr<Shader> _shader;
	};
}


#endif