#pragma once

#include <map>
#include <mutex>

#include <common/log.h>
#include <core/Engine/module.h>
#include <shared/graphics.h>


namespace andromeda
{

	class IContext;

	class ITexture;
	class ICubeTexture;
	
	class IGeometry;
	class IVertexBuffer; 
	class IIndexBuffer;
	
	class Shader;



	class View;


	class Graphics : public IModule, public IGraphics, public IGraphicsFactory
	{
	private:

		static inline IGraphicsFactory* GetFactory()
		{
			{
				std::unique_lock<std::mutex> lock(_m);
				assert(_factory != nullptr);
			}
			return _factory.get();
		}

		static inline IGraphicsFactory* SetFactory(std::shared_ptr<IGraphicsFactory> factory)
		{
			{
				std::unique_lock<std::mutex> lock(_m);
				assert(_factory==nullptr);
				_factory = factory;
			}
			return GetFactory();
		}
		static std::mutex _m;
		static std::shared_ptr<IGraphicsFactory> _factory;

		// Global Access to Factory Methods
		static inline std::shared_ptr<IVertexBuffer> CreateVertexBuffer() { return _factory->createVertexBuffer(); }
		static inline std::shared_ptr<IIndexBuffer> CreateIndexBuffer() { return _factory->createIndexBuffer(); }


	public:
		Graphics(std::shared_ptr<IContext> context, std::shared_ptr<IGraphics> graphics);
		virtual ~Graphics();

		// IModule
		Boolean open() override { return true; }
		Boolean close() override { return true; }
		Boolean pause() override { return true; }
		Boolean resume() override { return true; }

		Boolean update() override;


		

		// API Accessors
		inline Boolean setClearColor(Float r, Float g, Float b) override { return _impl->setClearColor(r, g, b); }

		// API Methods
		inline Boolean clear(ClearMaskBits mask) override { return _impl->clear(mask); }

		// Factory (Don't really need this)
		inline std::shared_ptr<IGraphicsFactory> getFactory() override { return _factory; }

		inline std::shared_ptr<ITexture> createTexture() override { return _factory->createTexture(); }
		inline std::shared_ptr<ICubeTexture> createCubeTexture() override { return _factory->createCubeTexture(); }

		inline std::shared_ptr<IGeometry> createGeometry(PrimitiveMode mode, IndexType indexType) override { return _factory->createGeometry(mode, indexType); }
		inline std::shared_ptr<IVertexBuffer> createVertexBuffer() override { return _factory->createVertexBuffer(); }
		inline std::shared_ptr<IIndexBuffer> createIndexBuffer() override { return _factory->createIndexBuffer(); }


		// View Manager
		//Boolean addDisplay();

	private:
		std::shared_ptr<IContext>						_context;
		std::map<std::string, std::shared_ptr<View>>	_views;
//		std::vector<std::shared_ptr<View>>		_views;		// Shouldn't be a vector, but a set. Ordered by View.zOrder
		
	//	std::vector<std::shared_ptr<View>>	_targets;	// Shouldn't matter if vector or not :: Order MAY be dependant or heirarchy. Textures that are render targets

		std::shared_ptr<IGraphics> _impl;
	};
}