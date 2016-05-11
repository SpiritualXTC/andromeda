#pragma once

#include <andromeda/Resources/resource_manager.h>

namespace andromeda
{
	class ResourceLocationFileSystem : public ResourceLocation
	{
	public:
		ResourceLocationFileSystem(const std::string & location);

		/*
			Load a file from the Filesystem
		*/
		std::shared_ptr<File> load(const std::string & filename, Boolean binary) override;

	private:

	};
}
