#pragma once

#include <shared/platform.h>

#include "windows_gui.h"
#include "windows_opengl.h"

namespace andromeda
{
	// Forward-Declarations
	class Keyboard;
	class Mouse;
	class Graphics;

	namespace windows
	{
		class WindowsPlatform : public IPlatform, public WindowsGUI::Observer
		{
		public:
			WindowsPlatform(std::shared_ptr<Engine> engine);
			virtual ~WindowsPlatform();

			// IPlatform
			std::shared_ptr<IContext> getContext() override { return _context; }
			std::shared_ptr<IGraphics> getGraphics() override { return _graphics; }

		private:
			void notify(LRESULT&, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

			std::shared_ptr<WindowsGUI> _gui;
			std::shared_ptr<Mouse> _mouse;
			std::shared_ptr<Keyboard> _keyboard;

			std::shared_ptr<WindowsOpenGLContext> _context;

			std::shared_ptr<IGraphics> _graphics;
		};

	}
}