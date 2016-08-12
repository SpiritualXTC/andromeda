#pragma once

/*
	Includes common graphics headers
*/
#include <cassert>
#include <memory>

/*
	TODO:
	Once the Graphics API is abstracted away : this can be moved :D
*/
#include "opengl.h"

#include "Events/resize.h"

#include "Graphics/buffer.h"
#include "Graphics/font.h"
#include "Graphics/effect.h"
#include "Graphics/mesh.h"
#include "Graphics/texture.h"






#include "graphics_types.h"

/*

#define GRAPHICS_OPENGL
	// Chooses Between OpenGL/OpenGL ES, and different versions of the libraries
#define GRAPHICS_DIRECTX
	// Chooses DirectX, and different versions of the libraries


	This will need to be created by the context(?) or should this REPLACE the context?

	Replacing the Context, will in turn, require some level of abstraction for context initialisation and swap()
*/





namespace andromeda
{
	// Forward Declarations
	class IFrameBuffer;



	/*
		TODO:
		Batch Rendering Setup

		I assume this will consist of:
		An array of 'GeometryGroup's (Probably a set, or map) : indexed or sorted by a Unique ID on the Geometry Buffer
			
		Each GeometryGroup will have an array of matrices that is then fed directly into the multi-draw call


		TODO:
		Create a 1x1 or 2x2 pure WHITE texture to be used when calls to setTexture() is null
	*/
	class Graphics : virtual protected ResizeListener
	{
	public:
		Graphics();
		virtual ~Graphics();

#if 0
		void update()
		{
			// clear();

			// render all scenes

			// swap();
		}
#endif

	public:






		










		// Getters
		const inline Int32 getDisplayWidth() const { return _displayWidth; }
		const inline Int32 getDipslayHeight() const { return _displayHeight; }




		// Abstract

		// API Information

		/*
			Create / Load Resources
		*/
		// Create FrameBuffer
		virtual std::shared_ptr<IFrameBuffer> createFrameBuffer(UInt32 width, UInt32 height) = 0;

		// Create Texture
		virtual std::shared_ptr<Texture> createTexture(UInt32 width, UInt32 height) = 0;

		// Create Cube Texture
		virtual std::shared_ptr<CubeTexture> createCubeTexture(UInt32 width, UInt32 height) = 0;

		// Create Volume Texture
		virtual std::shared_ptr<VolumeTexture> createVolumeTexture() = 0;

		// Create Shader
		virtual std::shared_ptr<IShader> createShader() = 0;

		// Create Effect [No Implementation :: This may not need to be fully abstracted]
		virtual std::shared_ptr<Effect> createEffect() { return nullptr; }





	//	virtual inline std::shared_ptr<Mesh> createMesh() = 0;





		// Important States
		virtual inline void setClearColor(Float r, Float g, Float b, Float a) = 0;

		/*
			TODO:
			This is directly effected by what the render target is as well
			RenderTarget = null = Backbuffer
			RenderTarget != null = A Texture
		*/
		virtual inline void setViewport(Int32 x, Int32 y, Int32 width, Int32 height) = 0;


		// Common Render States
		virtual inline void setFrontFace(FaceDirection face) = 0;
		virtual inline void setCulling(CullMode cull) = 0;


		virtual inline void setPolygonMode(FaceMode face, PolygonMode mode) = 0;

		// Blending
		virtual inline void setBlendEnabled(Boolean enable) = 0;

		virtual inline void setBlendColor(Float r, Float g, Float b, Float a) = 0;

		virtual inline void setBlendEquation(BlendEquation equation) = 0;
		virtual inline void setBlendEquation(BlendEquation rgbEquation, BlendEquation alphaEquation) = 0;

		virtual inline void setBlendFunction(BlendFunction source, BlendFunction destination) = 0;
		virtual inline void setBlendFunction(BlendFunction rgbSource, BlendFunction rgbDest
			, BlendFunction alphaSource, BlendFunction alphaDest
			) = 0;


		// Depth Functions
		virtual inline void setDepthEnable(Boolean enable) = 0;
		virtual inline void setDepthFunction(Function func) = 0;
		virtual inline void setDepthWriteEnable(Boolean mask) = 0;
		virtual inline void setDepthRange(Float zNear, Float zFar) = 0;

		// Stencil Functions
		virtual inline void setStencilEnable(Boolean enable) = 0;
		virtual inline void setStencilFunction(Function function, Int32 ref, UInt32 mask, FaceMode face = FaceMode::FrontAndBack) = 0;

		virtual inline void setStencilMask(UInt32 mask, FaceMode face = FaceMode::FrontAndBack) = 0;

		virtual inline void setStencilOperation(StencilOperation stencilFail
			, StencilOperation depthFail
			, StencilOperation depthPass
			, FaceMode face = FaceMode::FrontAndBack
			) = 0;







		// Drawing :: Get these Going ASAP
		/*
			TODO: Clear needs to be altered:
			clear() clears all buffers that are "active"
			clear(...) clears just the selected buffers.
		*/
		virtual inline void clear() = 0;
		virtual inline void draw() {}

	

		// Behavior
		/*
			TODO: Add an enum class for errors...
		*/
		virtual Int32 getLastError() = 0;
		virtual void errorCheck() = 0;
		 

	protected:
		Boolean onResize(ResizeEventArgs & e);

	private:
		Int32 _displayWidth = 0;
		Int32 _displayHeight = 0;

		// Store the current state as it gets assigned...
		// Do this from the implementation side of things for speeeeeeeed
	};
}


