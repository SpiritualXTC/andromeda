#pragma once


/*
	This ISN"T just for OpenGL.
	This will be used for all API's.

	It is currently just based on the OpenGL 1.0 Spec and trimmed down.

	TODO:
	Find the 4.5 CORE Header :)

	NOTE:
	This file is NOT in use anywhere yet
*/


namespace andromeda
{
	// From Here
	// https://www.khronos.org/registry/gles/api/1.0/gl.h
	//
	// This is like the first version of opengl, so their are bound to be plenty more...

	enum class ErrorCode		// Not sure if needed
	{
		None,
		InvalidEnum,
		InvalidValue,
		InvalidOperation,
		StackOverflow,
		StackUnderflow,
		OutOfMemory,
	};


#if 0
	// This really isn't needed
	enum Boolean
	{
		False = 0,
		True = 1,
	};
#endif


#if 0
	// This can be more "function" based
	enum Enable
	{
		CullFace,
		AlphaTest,
		Blend,
		ColorLogicOp,
		Dither,
		StencilTest,
		DepthTest,
		PointSmooth,
		LineSmooth,
		ScissorTest,
		PolygonOffsetFill,
		MultiSample,
		SampleAlphaToCoverage,
		SampleAlphaToOne,
		SampleCoverage,
	};
#endif

	/*
		TODO:
		Implement this... lol
	*/
	enum ClearMask
	{
		Color = 0x01,
		Depth = 0x02,
		Stencil = 0x04,
	};





	// [Required]
	enum class PolygonMode
	{
		Fill,		// (?)
		Wireframe,	// (?)
	};


	// [Required - Cleaner Culling Setup]
	enum class CullMode
	{
		Front,
		Back,
		FrontAndBack,
		None
	};



	// [Required]
	enum class PrimitiveMode
	{
		Points,
		Lines,
		LineLoop,
		LineStrip,
		Triangles,
		TriangleStrip,
		TriangleFan,
	};


	// [Required] Used for Alpha, Depth, Stencil Functions
	enum class Function
	{
		Never,
		Less,
		Equal,
		LessEqual,
		Greater,
		NotEqual,
		GreaterEqual,
		Always
	};



	enum class BlendEquation
	{
		Add,
		Subtract,
		ReverseSubtract,
		Minimum,
		Maximum
	};

	enum class BlendFunction
	{
		Zero,
		One,

		SourceColor,
		OneMinusSourceColor,
		DestinationColor,
		OneMinusDestinationColor,

		SourceAlpha,
		OneMinusSourceAlpha,
		DestinationAlpha,
		OneMinusDestinationAlpha,
		
		ConstantColor,
		OneMinusConstantColor,
		ConstantAlpha,
		OneMinusConstantAlpha,

		SourceAlphaSaturate,

		/*
			Not Sure what these represent : Or how they work

			Source1Color,
			OneMinusSource1Color,
			Source1Alpha,
			OneMinusSource1Alpha,
		*/
	};

	// [Required]
	enum class FaceMode
	{
		Front,
		Back,
		FrontAndBack,
	};

	// [Required]
	enum class FaceDirection
	{
		Clockwise,
		CounterClockwise,
	};


	// [Required - I think]
	enum class DataType
	{
		Byte,
		UnsignedByte,
		Short,
		UnsignedShort,
		Int,
		UnsignedInt,
		Float,
		Fixed,
	};


	// Don't know where this is used
	enum class LogicalOperation
	{
		Clear,
		And,
		AndReverse,
		Copy,
		AndInverted,
		NoOperation,
		ExclusiveOr,
		Or,
		NotOr,
		Equiv,
		Invert,
		OrReverse,
		CopyInverted,
		OrInverted,
		NotAnd,
		Set,
	};


	// [Required]
	enum class StencilOperation
	{
		Zero,
		Keep,
		Replace,
		Increment,
		IncrementWrap,
		Decrement,
		DecrementWrap,
		Invert,		// 
	};






	/*
		Texturing	
	*/
	// Don't know where this is used
	enum class TextureEnvironmentMode				// Not sure if this is needed
	{
		Modulate,
		Decal,
		Blend,
		Add,
		Replace,
	};
	// Don't know where this is used
	enum class TextureEnvironmentParameter		// Not sure if this is needed
	{
		Mode,
		Color,
	};
	// Don't know where this is used
	enum class TextureEnvironmentTarget			// Not sure if this is needed
	{
		Environment,
	};

	// Used for texturing (How the texture is sampled)
	enum class TextureMagFilter
	{
		Nearest,
		Linear,
	};

	// Used for texturing (How the texture is sampled)
	enum class TextureMinFilter
	{
		Nearest,
		Linear,
		NearestMipmapNearest,
		LinearMipmapNearest,
		NearestMipmapLinear,
		LinearMipmapLinear,
	};

	// Not sure if used in creation of a texture or during rendering. lol
	enum class TextureWrapMode
	{
		Repeat,
		MirroredRepeat,
		ClampToEdge,
	};





	/*
		TODO: 
		Work out a better system to generate the formats.

		https://www.opengl.org/sdk/docs/man/html/glTexImage2D.xhtml


		This enum needs to define the Following (Related to OpenGL Textures)
			- Internal Format : Number of Color Components in the Texture
				R
				RG
				RGB
				RGBA
				Depth
				DepthStencil

			- Format of the Pixel Data



		There are a lot of formats. There should be a much simpler way of tying them together in a simpler manner.
			(The code to do the tying together, wont be quite as simple)
	*/
	// Not sure how many of these are useful!
	enum class StorageFormat
	{
		RGBA,

		RGBA16F,
		RGBA32F,


		Depth16,
		Depth24,
		Depth32,
		DepthStencil,



		Unknown,
	};

	/*
	GL_RED, 
	GL_RG, 
		GL_RGB, 
		GL_BGR, 
		GL_RGBA, 
		GL_BGRA, 
		GL_RED_INTEGER, 
		GL_RG_INTEGER, 
		GL_RGB_INTEGER, 
		GL_BGR_INTEGER, 
		GL_RGBA_INTEGER, 
		GL_BGRA_INTEGER, 
		GL_STENCIL_INDEX, 
		GL_DEPTH_COMPONENT, 
		GL_DEPTH_STENCIL.
		*/





	/*
		Shader Annotations
	*/

}