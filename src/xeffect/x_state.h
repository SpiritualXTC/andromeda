#pragma once

#include <memory>
#include <vector>

#include <andromeda/stddef.h>

#include <andromeda/graphics_types.h>


namespace andromeda
{
	namespace xeffect
	{
		/*
			This is an interface that should/could be moved to the Core Engine
		*/
		class IState
		{
		public:
			IState() {}
			virtual ~IState() {}

			virtual void apply() const = 0;

			virtual void log() const {}		// TEMPORARY

		private:

		};







		/*
			Collection of States

			This is part of the XEffect API and cannot be moved to the Core Engine

			TODO: Rename to XStateGroup or something else that indicates its a group/collection of IState
		*/
		class XStateGroup : virtual public IState
		{
		public:
			XStateGroup(const std::string & name);
			virtual ~XStateGroup();

			// Gets the State Name
			const inline std::string & getName() const { return _name; }

			// Is their any states
			inline Boolean isEmpty() const { return _states.empty(); }



			void apply() const override;

			void addState(const std::shared_ptr<IState> & state);



			void log() const override;

		private:

			std::string _name;
			std::vector<std::shared_ptr<IState>> _states;
		};


		/*
		
		*/
		class XStateCulling : virtual public IState
		{
		public:
			XStateCulling(CullMode c);

			void apply() const override;

			void log() const override;

		private:
			CullMode _culling = CullMode::None;
		};

		
		/*
		
		*/
		class XStatePolygon : virtual public IState
		{
		public:
			XStatePolygon();

			void setFaceMode(FaceMode face) { _face = face; }
			void setPolygonMode(PolygonMode pm) { _polygon = pm; }

			void apply() const override;

			void log() const override;



		private:
			FaceMode _face = FaceMode::FrontAndBack;
			PolygonMode _polygon = PolygonMode::Fill;
		};



		/*
		
		*/
		class XStateBlending : virtual public IState
		{
		public:
			struct _Color
			{
				Float red;
				Float green;
				Float blue;
				Float alpha;
			};

			XStateBlending();

			void apply() const override;

			void setEnabled(Boolean b) { _enabled = b; }

			void setEquation(BlendEquation eq) { _rgbEquation = eq; _alphaEquation = eq; }
			void setRGBEquation(BlendEquation eq) { _rgbEquation = eq; }
			void setAlphaEquation(BlendEquation eq) { _alphaEquation = eq; }


			void setSourceFunction(BlendFunction func) { _rgbSource = func; _alphaSource = func; }
			void setDestinationFunction(BlendFunction func) { _rgbDestination = func; _alphaDestination = func; }

			void setRGBSourceFunction(BlendFunction func) { _rgbSource = func; }
			void setAlphaSourceFunction(BlendFunction func) { _alphaSource = func; }
			void setRGBDestinationFunction(BlendFunction func) { _rgbDestination = func; }
			void setAlphaDestinationFunction(BlendFunction func) { _alphaDestination = func; }

			void setColor(Float red, Float green, Float blue, Float alpha)
			{
				_color.red = red;
				_color.green = green;
				_color.blue = blue;
				_color.alpha = alpha;
			}

			void setRed(Float f) { _color.red = f; }
			void setGreen(Float f) { _color.green = f; }
			void setBlue(Float f) { _color.blue = f; }
			void setAlpha(Float f) { _color.alpha = f; }


			void log() const override;

		private:
			Boolean _enabled = false;

			_Color _color = { 0,0,0,0 };

			BlendEquation _rgbEquation = BlendEquation::Add;
			BlendEquation _alphaEquation = BlendEquation::Add;

			BlendFunction _rgbSource = BlendFunction::One;
			BlendFunction _rgbDestination = BlendFunction::Zero;
			BlendFunction _alphaSource = BlendFunction::One;
			BlendFunction _alphaDestination = BlendFunction::Zero;
		};


		/*
		
		*/
		class XStateDepth : virtual public IState
		{
		public:
			XStateDepth();

			void apply() const override;

			void setEnabled(Boolean b) { _enabled = b; }
			void setWriteEnabled(Boolean b) { _writeEnabled = b; }

			void setFunction(Function f) { _function = f; }

			void setZNear(Float f) { _zNear = f; }
			void setZFar(Float f) { _zFar = f; }

			void log() const override;

		private:
			Boolean _enabled = true;
			Boolean _writeEnabled = true;
			Function _function = Function::Less;
			Float _zNear = 0.0f;
			Float _zFar = 1.0f;

			/*
				TODO:
				Enable / Disable Range Clamping
			*/
		};


		/*
		
		*/
		class XStateStencil : virtual public IState
		{
		public:
			XStateStencil();

			void apply() const override;

			void setEnabled(Boolean b) { _enabled = b; }

			void setFaceMode(FaceMode face) { _face = face; }

			void setFunction(Function func) { _function = func; }
			void setFunctionReference(Int32 ref) { _ref = ref; }
			void setFunctionMask(UInt32 mask) { _funcMask = mask; }

			void setMask(UInt32 mask) { _mask = mask; }

			void setStencilFailOperation(StencilOperation op) { _stencilFail = op; }
			void setDepthFailOperation(StencilOperation op) { _depthFail = op; }
			void setDepthPassOperation(StencilOperation op) { _depthPass = op; }


			void log() const override;

		private:
			FaceMode _face = FaceMode::FrontAndBack;


			Boolean _enabled = false;

			Function _function = Function::Always;
			Int32 _ref = 0;
			UInt32 _funcMask = 0xFFFFFFFF;

			UInt32 _mask = 0xFFFFFFFF;

			StencilOperation _stencilFail = StencilOperation::Keep;
			StencilOperation _depthFail = StencilOperation::Keep;
			StencilOperation _depthPass = StencilOperation::Keep;
		};

	}
}
