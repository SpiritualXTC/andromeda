#pragma once

#include <andromeda/andromeda_init.h>

#include "../andromeda/andromeda_config.h"

#include <andromeda/Utilities/log.h>

#include <Windows.h>

namespace andromeda
{
	namespace windows
	{
		class PlatformWindows;

		/*

		*/
		class AndromedaConfigWindows : virtual public IAndromedaConfig
		{
		public:
			AndromedaConfigWindows(HINSTANCE hInstance);

			void init() override;

			std::shared_ptr<Display> initDisplay(const DisplayParameters & dp) override;
			std::shared_ptr<Platform> initPlatform() override;
			std::shared_ptr<Context> initContext() override;
			std::shared_ptr<Graphics> initGraphics() override;

		private:
			std::shared_ptr<PlatformWindows> _platform;

			HINSTANCE _hInstance;
			HWND _hWnd;
			HDC _hDC;
		};
	}
}
