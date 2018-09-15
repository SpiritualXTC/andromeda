#pragma once

#include <map>

#include <core/Engine/module.h>

#include <core/Graphics/types.h>

namespace andromeda
{

	class IContext;

	class ITexture;
	class ICubeTexture;

	class IGeometry;
	class IVertexBuffer;
	class IIndexBuffer;

	class IShader;


	class IGraphicsFactory
	{
	public:
		virtual std::shared_ptr<ITexture> createTexture() = 0;
		virtual std::shared_ptr<ICubeTexture> createCubeTexture() = 0;

		virtual std::shared_ptr<IGeometry> createGeometry(PrimitiveMode mode, IndexType indexType) = 0;
		virtual std::shared_ptr<IVertexBuffer> createVertexBuffer() = 0;
		virtual std::shared_ptr<IIndexBuffer> createIndexBuffer() = 0;
	};


	class IGraphics
	{
	public:
		IGraphics() {}
		virtual ~IGraphics() {}

		// API Accessors
		virtual Boolean setClearColor(Float r, Float g, Float b) = 0;

		// API Methods
		virtual Boolean clear(ClearMaskBits mask) = 0;

		// Methods
		virtual std::shared_ptr<IGraphicsFactory> getFactory() = 0;

		// Resource Generation
	//	virtual std::shared_ptr<ITexture> CreateTexture() = 0;
	//	virtual std::shared_ptr<ICubeTexture> CreateCubeTexture() = 0;

	//	virtual std::shared_ptr<IGeometry> CreateGeometry(PrimitiveMode mode, IndexType indexType) = 0;
	//	virtual std::shared_ptr<IVertexBuffer> CreateVertexBuffer() = 0;
	//	virtual std::shared_ptr<IIndexBuffer> CreateIndexBuffer() = 0;

	private:

	};


}