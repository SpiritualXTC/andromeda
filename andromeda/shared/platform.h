#pragma once

#include <memory>
#include <boost/predef.h>

#include <common/types.h>

#include <core/Engine/module.h>

namespace andromeda
{
	class Engine;

	class IContext;
	class IGraphics;


	struct PlatformEventArgs
	{
		UInt32 type;
	};




	class IPlatform
	{
	public:
		IPlatform(std::shared_ptr<Engine> engine) {}
		//	virtual Boolean open() = 0;
		//	virtual Boolean close() = 0;

		//	virtual Boolean update() = 0;

		virtual std::shared_ptr<IContext> getContext() = 0;
		virtual std::shared_ptr<IGraphics> getGraphics() = 0;
	};


	class Platform : public IPlatform
	{
	public:
		Platform(std::shared_ptr<Engine> engine);
		virtual ~Platform();


		// IPlatform
		inline std::shared_ptr<IContext> getContext() override { return _impl->getContext(); }
		inline std::shared_ptr<IGraphics> getGraphics() override { return _impl->getGraphics(); }

	private:

		std::shared_ptr<IPlatform> _impl;
	};
}