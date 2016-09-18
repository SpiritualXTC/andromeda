#pragma once

#include <andromeda/Graphics/texture.h>
#include <andromeda/Resources2/resource.h>
#include <andromeda/Resources2/resource_builder.h>

namespace andromeda
{
#if 0

	// Loads a VolumeTexture
	class VolumeTextureResourceBuilder : public ResourceBuilderEx<VolumeTexture>
	{
	public:
		virtual std::unique_ptr<ResourceEx<VolumeTexture>> build(const boost::property_tree::ptree & propTree) override;
		std::unique_ptr<VolumeTexture> load() override;
	};




	/*

	*/
	class VolumeTextureResource : public ResourceEx<VolumeTexture>
	{
	public:

	private:

	};
#endif
}