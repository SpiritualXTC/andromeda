#pragma once

#include <stack>

#include <andromeda/stddef.h>

#include <andromeda/Math/region.h>

#include <andromeda/graphics.h>

namespace andromeda
{
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


	class RenderState
	{
	public:
		RenderState();

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




