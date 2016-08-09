#ifndef _ANDROMEDA_CONTAINERS_VECTOR_H_
#define _ANDROMEDA_CONTAINERS_VECTOR_H_

/*
	vector.h:

	Needs an optimized version of erase, for the vector class that
	guarantees a swap deletion instead of decrement deletion.
	IE: The datatype is unstable.


	THIS IS CURRENTLY NOT USED FOR ANYTHING. :)
	IT WAS DEVELOPED FOR AN EXPERIMENTAL Entity-Component-System THAT 
	ULTIMATELY FAILED!
*/
#if 0
#include "../stddef.h"

#include <stdexcept>

#include "../Utilities/log.h"

namespace andromeda
{
	template <typename T>
	class vector
	{
	public:
		typedef T& reference;
		typedef const T& const_reference;

		typedef T* iterator;
		typedef const T* const_iterator;

	public:
		/*
		
		*/
		vector()
		{
			reserve(1);
		}

		/*
		
		*/
		vector(Int32 rsv)
		{
			reserve(rsv);
		}

		/*
		
		*/
		virtual ~vector() {}

		/*
			at():
		*/
		reference at(Size index)
		{
			if (index >= _size)
				throw std::range_error();

			return _elements[index];
		}

		/*
			at():
		*/
		const_reference at(Size index) const
		{
			if (index >= _size)
				throw std::range_error();

			return _elements[index];
		}

		/*
			clear():

			Clears the array.. as you would expect.
			Sets Size to 0.
			Sets Capacity to 1.
		*/
		void clear()
		{
			_size = 0;
			_capacity = 0;

			reserve(1);
		}


		/*
		
		*/
		Boolean empty()
		{
			return _size == 0;
		}


		/*
			reserve():
		*/
		void reserve(Size capacity)
		{
			// Shrinking? Don't need to worry about it :)
			if (capacity <= _capacity)
				return;

			// Get Memory Location of Original Array
			T * temp = _elements;

			// Allocate Memory
			_elements = new T[capacity];

			// Backup?
			if (temp != nullptr)
			{
				// Restore
				for (Size i = 0; i < size(); ++i)
					_elements[i] = std::move(temp[i]);
				//	_elements[i] = temp[i];
 

				// Delete Old
				delete temp;
			}

			// Set Capacity
			_capacity = capacity;
		}


		/*
			push():

			Adds a new Item of type T, to end of array
			Returns the index of the added item
		*/
		Int32 push(const_reference val)
		{
			Int32 pos = _size;

			// Increase Capacity ?
			if (_size >= _capacity)
			{
				// Resize!
				reserve(_capacity * 2);
			}

			// Place
			_elements[pos] = std::move(val);

			// Increment Size
			++_size;

			return pos;
		}


		/*
			pop():

			Removes the last item index in the array
		*/
		void pop()
		{
			--_size;

			return;
		}


		/*
			erase():

			Removes the element at 'index'.
			Swaps the element at the end of the array with the element to remove.
			Decreases the size

			Currently returns the new size.
		*/
		Int32 erase(Int32 index)
		{
			Int32 pos = _size - 1;

			//_elements[index] = _elements[pos];
			_elements[index] = std::move(_elements[pos]);

			_size--;

			return _size;
		}


		const inline Size size() const { return _size; }
		const inline Size capacity() const { return _size; }
		


		/*
		
		*/
		reference operator[](Size index)
		{
			if (index >= _size)
				throw std::range_error();

			return _elements[index]; 
		}

		/*
		
		*/
		const_reference operator[](Size index) const 
		{ 
			if (index >= _size)
				throw std::range_error();

			return _elements[index]; 
		}


		iterator begin()
		{
			return _elements;
		}

		iterator end()
		{
			return _elements + _size;
		}

		const_iterator cbegin() const
		{
			return _elements;
		}

		const_iterator cend() const
		{
			return _elements + _size;
		}


	protected:
		void resize();

	private:
		Size _size = 0;				// Size of the Vector: Number of elements that are accessable
		Size _capacity = 0;			// Capacity of the Vector: Number of elements in the internal array

		T * _elements = nullptr;
	};
}
#endif

#endif