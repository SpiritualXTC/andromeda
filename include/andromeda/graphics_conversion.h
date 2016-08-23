#pragma once

#include <string>

#include <andromeda/stddef.h>
#include <andromeda/graphics_types.h>


namespace andromeda
{
	namespace util
	{
		Boolean convertToBoolean(const std::string & value, Boolean def);

		PolygonMode convertToPolygonMode(const std::string & value, PolygonMode def);
		CullMode convertToCullMode(const std::string & value, CullMode def);
		FaceMode convertToFaceMode(const std::string & value, FaceMode def);
		FaceDirection convertToFaceDirection(const std::string & value, FaceDirection def);



		Function convertToFunction(const std::string & value, Function def);

		BlendFunction convertToBlendFunction(const std::string & value, BlendFunction def);
		BlendEquation convertToBlendEquation(const std::string & value, BlendEquation def);

		StencilOperation convertToStencilOperation(const std::string & value, StencilOperation def);


		TextureMinFilter convertToTextureMinFilter(const std::string & value, TextureMinFilter def);
		TextureMagFilter convertToTextureMagFilter(const std::string & value, TextureMagFilter def);


		StorageFormat convertToStorageFormat(const std::string & value, StorageFormat def);

	}
}