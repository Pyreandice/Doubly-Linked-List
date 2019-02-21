#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

#include <algorithm>
#include <stdexcept>
#include "linked_list.h"

namespace nwacc
{
	// represents the first position in the array
	const int first_index = 0;
	template <typename T>
	class array_list
	{
	public:

		explicit array_list(int capacity = kDefaultCapacity) :
		my_size { 0 }, capacity { capacity >= kDefaultCapacity ? capacity : kDefaultCapacity }
		{
			this->data = new T[this->capacity];
		}

		// copy constructor. 
		array_list(const array_list &rhs) :
		my_size { rhs.my_size }, capacity { rhs.capacity }, data { nullptr }
		{
			this->data = new T[this->capacity];
			for (auto index = 0; index < this->my_size; index++)
			{
				this->data[index] = rhs.data[index];
			}
		}

		array_list(array_list &&rhs) :
		my_size { rhs.my_size }, capacity { rhs.capacity }, data { rhs.data }
		{
			rhs.data = nullptr;
			rhs.my_size = 0;
			rhs.capacity = 0;
		}

		~array_list()
		{
			delete[] this->data;
		}

		/***
		* Summary
		* Insert the value into the first position of the array.
		*/
		void push_front(T &value)
		{
			if (this->size() == this->capacity)
			{
				this->reserve();
			} // else my_size is within range, do_nothing();
			
			shift_right();
			this->data[first_index] = value;
		}

		/***
		 * Summary
		 * Insert the value into the first position of the array.
		 */
		void push_front(T &&value)
		{
			if (this->size() == this->capacity)
			{
				this->reserve();
			} //else my_size() is within range, do_nothing();

			shift_right();
			this->data[first_index] = std::move(value);
		}

		/***
		 * Summary
		 * Insert the right hand value into the last position of the array.
		 */
		void push_back(T &&value)
		{
			if (this->size() == this->capacity)
			{
				this->reserve();
			} // else, my_size is within range, do_nothing();
			this->data[this->my_size++] = std::move(value);
		}

		/***
		 * Summary
		 * Insert the current value into the last position of the array.
		 */
		void push_back(const T &value)
		{
			if (this->size() == this->capacity)
			{
				this->reserve();
			} // else my_size is within range, do_nothing();

			this->data[this->my_size++] = value;
		}

		/***
		 *  Summary
		 *  Shifts all the array elements one index to the right.
		 */
		void shift_right()
		{
			if (this->size() == this->capacity)
			{
				this->reserve();
			} // else my_size is within range, do_nothing();

			int position = this->my_size - 1;
			for (auto index = 0; index < this->my_size; index++)
			{
				const int size = this->my_size;
				this->data[size - index] = this->data[position];
				// for debugging
				//std::cout << this->data << " now at position " << position << std::endl;
				position--;
			}
		}

		/***
		 * Summary
		 * Looks for the item in the 4th position of the array.
		 * If it is found. Move the item to the front of the array
		 */
		void search_algorithm(T &value)
		{
			if (this->size() == this->capacity)
			{
				this->reserve();
			} // else my_size is within range, do_nothing();

			// set value equal to data at position 4 of the array
			value = this->data[4];
			for (auto index = 0; index < this->my_size; index++)
			{
				if (this->data[index] == value)
				{
					std::cout << "data found at position 4" << std::endl;
					push_front(value);
					std::cout << "successfully pushed data to position 0 of array" << std::endl;
				} // else &value is not the item we are looking for, do_nothing();
				std::cout << "no data found" << std::endl;
			}
		}

		/**
		* Summary
		* @return true if the size of the array is zero.
		*/
		bool is_empty() const
		{
			return this->size() == 0;
		}

		/**
		 * Summary
		 * @return the size of the array.
		 */
		int size() const
		{
			return this->my_size;
		}

		/**
		* Summary
		* @return the size of the array.
		*/
		int get_capacity() const
		{
			return this->capacity;
		}

		array_list &operator=(const array_list &rhs)
		{
			auto copy = rhs;
			std::swap(*this, copy);
			return *this;
		}

		array_list &operator=(array_list &&rhs)
		{
			std::swap(this->my_size, rhs.my_size);
			std::swap(this->capacity, rhs.capacity);
			std::swap(this->data, rhs.data);
			return *this;
		}

		/**
		 * Summary
		 * Delete the last item in the list if it is empty.
		 */
		void pop_back()
		{
			if (this->is_empty())
			{
				throw std::out_of_range("No elements in array list");
			} // else, we are not empty do_nothing();

			this->my_size--;
		}

		/**
		 * Summary
		 * Return exception if the list is empty or at he end of the list.
		 */
		const T & back() const
		{
			if (this->is_empty())
			{
				throw std::out_of_range("No elements in the array list");
			} // else, we are not empty, do_nothing();

			return this->data[this->my_size - 1];
		}

	private:
		static const int kDefaultCapacity = 16;

		/*
		* what is attribute
		*/
		int my_size;
		int capacity;
		T * data;

		/**
		 * Summary
		 * Resizes the array if the array is to small.
		 */
		void reserve()
		{
			if (this->size() < this->capacity)
			{
				return;
			} // else, we need to change the capacity do_nothing();

			// NOTE - Magic numbers here are fine! 
			auto new_capacity = (this->capacity * 3) / 2 + 1;
			T * new_array = new T[new_capacity];
			for (auto index = 0; index < this->size(); index++)
			{
				new_array[index] = std::move(this->data[index]);
			}

			this->capacity = new_capacity;
			std::swap(this->data, new_array);
			delete[] new_array;
		}
	};
}

#endif