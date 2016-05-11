#ifndef _ANDROMEDA_WINDOWS_GRAPHICS_CONTEXT_WINDOWS_H_
#define _ANDROMEDA_WINDOWS_GRAPHICS_CONTEXT_WINDOWS_H_

#include <boost/predef.h>

// OS Restriction: Windows
#if BOOST_OS_WINDOWS


#define VC_EXTRALEAN
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <andromeda/Renderer/context.h>

namespace andromeda
{
	namespace windows
	{
		class PlatformWindows;

		class ContextWindows : public Context
		{
		public:
			ContextWindows(HDC hDC);
			virtual ~ContextWindows();


		protected:
			void swap() override;

		private:
			HGLRC		_hGL;
			HDC			_hDC;
		};
	}
}

#endif //OS Restrictions
#endif