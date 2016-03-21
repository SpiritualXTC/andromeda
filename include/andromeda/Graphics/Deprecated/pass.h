#ifndef _ANDROMEDA_GRAPHICS_PASS_H_
#define _ANDROMEDA_GRAPHICS_PASS_H_


#include <memory>
#include <string>

#include <andromeda/stddef.h>
#include <andromeda/opengl.h>

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
		//	(void*)glFunc(GLenum, GLint);	// Not sure how this will work........ lol
											// I haz a feint idea :D
		};


	public:
		Pass(const std::string & name, std::shared_ptr<Shader> shader);
		virtual ~Pass();

		const inline std::string & name() const { return _name; }

		
		const inline std::shared_ptr<Shader> & shader() { return _shader; }

		


		Boolean begin();
		Boolean end();


		// Enabled
		const inline Boolean isEnabled() const { return _enabled; }
		void enable() { _enabled = true; }
		void disable() { _enabled = false; }


		

	private:
		Boolean _enabled = true;
		std::string _name;


		std::shared_ptr<Shader> _shader;
	};
}


#endif