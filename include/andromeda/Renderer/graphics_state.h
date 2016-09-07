#pragma once

#include <stack>

#include <andromeda/stddef.h>

#include <andromeda/Math/region.h>

#include <andromeda/graphics.h>

namespace andromeda
{
#if 0
	/*
		Move me to containers
	*/
	template <typename T>
	class DualStateStack
	{
	public:
		DualStateStack(const T & t)
			: _original(t)
			, _value(t)
		{

		}

		virtual ~DualStateStack()
		{

		}

		// Sets the New State
		inline void setValue(T & value) { _altered = true; _value = value; }

		inline T & getOriginal() const { return _original; }
		inline T & getValue() const { return _value; }

		inline Boolean isAltered() const { return _altered; }



	private:
		T _original;
		T _value;
		Boolean _altered = false;
	};




	/*
		This is a temp class

		It is to be used until annotations are setup - unlike the other class this may not need to be changed after annotations are setup

		This is at the "view" level
	*/
	class IGraphicsState
	{
	public:
		IGraphicsState(){}

		virtual const Region2i & getViewport() const = 0;
	};


	// First Level
	class GraphicsState : public IGraphicsState
	{
	public:
		GraphicsState();						// First Level
		virtual ~GraphicsState();				// Restoration

		const Region2i & getViewport() const override { return _viewport; }


	private:
		//std::stack<Region2i> _viewport;
		Region2i _viewport;
	};



	class GraphicsStateStack : public IGraphicsState
	{
	public:
		GraphicsStateStack(IGraphicsState & gs);
		virtual ~GraphicsStateStack();

		inline const Region2i & getViewport() const override { return _viewport.getValue(); }

	private:
		DualStateStack<Region2i> _viewport;
	};

#endif




	class ViewportChange
	{
	public:
		inline void apply(Graphics * g, const Region2i & region)
		{
			g->setViewport(region.minimum.x, region.minimum.y, region.size().x, region.size().y);
		}
	};



	template <typename T, typename CB>
	class MaskedStack : public CB
	{
		using CB::apply;
	public:
		void push(Graphics * g, UInt32 mask, const T & value)
		{
			// Append the Bit
			_mask |= mask;
			
			// Set Value
			apply(g, value);

			// Add the Value
			_stack.push(value);
		}

		void pop(Graphics * g, UInt32 mask)
		{
			// Pop the Value
			if (_mask & mask)
			{
				// Pop the Top
				_stack.pop();

				// Restore Value
				apply(g, _stack.top());
			}

			// Remove the Bit
			_mask = _mask & ~mask;

		}

		T& top()
		{
			return _stack.top();
		}

	private:
		std::stack<T> _stack;

		UInt64 _mask = 0;
	};


	class GraphicsState
	{
	public:
		GraphicsState();

		void push();
		void pop();

		// Sets the Viewport
		inline void setViewport(const Region2i & region)
		{
			// Push Viewport
			_viewport.push(_graphics, _mask, region);
		}

		inline void setViewport(Int32 x, Int32 y, Int32 w, Int32 h)
		{
			_viewport.push(_graphics, _mask, Region2i(glm::ivec2(x, y), glm::ivec2(x + w, y + h)));
		}


		UInt32 mask() const { return _mask; }

	private:
		UInt32 _mask = 0x00000001;


		Graphics * _graphics = nullptr;
		MaskedStack<Region2i, ViewportChange> _viewport;
	};



#if 0
	// Automatically handles the GraphicsState
	class GraphicsStateStack
	{
	public:
		GraphicsStateStack(GraphicsState & gss)
			: _stack(gss)
		{
			_stack.push();
		}
		GraphicsStateStack(GraphicsStateStack & gssi)
			: _stack(gssi.getGraphicsStack())
		{
			_stack.pop();
		}

		virtual ~GraphicsStateStack()
		{
			_stack.pop();
		}




		// Sets the Viewport
		inline void setViewport(const Region2i & region)
		{
			_stack.setViewport(region);
		}



	private:
		inline GraphicsState & getGraphicsStack() { return _stack; }
		GraphicsState & _stack;
	};
#endif
}




