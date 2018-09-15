#pragma once

#include "module.h"

namespace andromeda
{
	class IScene
	{
	public:
		IScene() {}
		virtual ~IScene() {}
	};

	class SceneController : public IModule
	{
	public:
		void setScene(std::shared_ptr<IScene>& scene){ }

	};
}