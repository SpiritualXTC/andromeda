#pragma once

#include <Windows.h>

#include <shared/context.h>

namespace andromeda
{
	namespace windows
	{
		
		class WindowsOpenGLContext : public IContext
		{
		public:
			WindowsOpenGLContext(HDC hdc);
			virtual ~WindowsOpenGLContext();

			Boolean swap() override;

		private:
			HDC			_hDC;
			HGLRC		_hGL;
		};
		
	}
}