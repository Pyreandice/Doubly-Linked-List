#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <algorithm>
#include <ppltasks.h>

namespace the_boot
{
	template <typename T>
	class linked_list
	{
	private:
		struct node
		{
			T data;
			node *previous;
			node *next;

			/**
			 * Summary
			 * Construct a node with values.
			 */
			node(
				const T &value = T {},
				node *previous = nullptr,
				node *next = nullptr
				) : data { value }, previous { previous }, next { next } {}

			/**
			 * Summary
			 * Initiate all nodes with null previous and next pointers.
			 */
			node(T &&value, node *previous = nullptr, node *next = nullptr) 
				: data { std::move(value) }, previous { previous }, next { next } {}
		};
	public:
		class const_iterator
		{
		public:

			/**
			 * Summary
			 * Initiate current with a null pointer.
			 */
			const_iterator() : current { nullptr } {}

			/**
			 * Summary
			 * Overload the pointer operator.
			 */
			const T & operator*() const
			{
				return this->retrieve();
			}

			/**
			 * Summary
			 * Overload the ++ operator.
			 */
			const_iterator & operator++()
			{
				this->current = this->current->next;
				return *this;
			}
			/**
			 * Summary
			 * c++ REQUIRES! single anonymous int param
			 * so the signatures of the methods are different. 
			 * this is the postfix operator.
			 */
			const_iterator operator++(int)
			{
				auto old = *this;
				++(*this);
				return old;
			}

			/**
			 * Summary
			 * Overload the -- Operator.
			 */
			const_iterator & operator--()
			{
				this->current = this->current->previous;
				return *this;
			}

			/**
			 * Summary
			 * Overload the -- operator.
			 */
			const_iterator operator--(int)
			{
				auto old = *this;
				--(*this);
				return old;
			}

			/***
			 * Summary
			 * Overload the bool operator == to make it
			 * constant so it will compare the rhs values.
			 */
			bool operator== (const const_iterator & rhs) const
			{
				return this->current == rhs.current;
			}

			/**
			 * Summary
			 * Overload the != operator for the const iterator
			 * implementation &rhs values.
			 */
			bool operator!= (const const_iterator & rhs) const
			{
				return !(*this == rhs);
			}

		protected:
			node *current;

			/**
			 * Summary
			 * Retrieve data at the current position.
			 */
			T &retrieve() const
			{
				return this->current->data;
			}

			/**
			 * Summary
			 * Const iterator iterator.
			 */
			const_iterator(node *current) : current{ current } {}

			friend class linked_list<T>;
		};

		 /**
		 * This is the IS-A relationship. We now say
		 * iterator IS-A const_iterator. iterator is a sub class of 
		 * const_iterator. const_iterator is a super class to iterator.
		 */
		class iterator : public const_iterator
		{
		public:

			iterator() {}

			/**
			 * Summary
			 * Retrieve the data from x pointer.
			 */
			T & operator*()
			{
				return const_iterator::retrieve();
			}

			/**
			 * Summary
			 * Return the object stored at the current position.
			 * For iterator, there is an accessor with a
			 * const reference return type and a mutator with
			 * a reference return type. The accessor is shown first.
			 */
			const T & operator* () const
			{
				return const_iterator::operator*();
			}

			/**
			 * Overload the ++ operator.
			 */
			iterator & operator++ ()
			{
				this->current = this->current->next;
				return *this;
			}

			/**
			 * Summary
			 * Overload the ++ operator.
			 */
			iterator operator++ (int)
			{
				auto old = *this;
				++(*this);
				return old;
			}

			/***
			 * Summary
			 * Overload the -- operator.
			 */
			iterator & operator-- ()
			{
				this->current = this->current->previous;
				return *this;
			}

			/***
			* Summary
			* Overload the -- operator.
			*/
			iterator operator-- (int)
			{
				auto old = *this;
				--(*this);
				return old;
			}
		protected:
			/**
			 * Summary
			 * Protected constructor for iterator.
			 * Expects the current position.
			 */
			iterator(node *current) : const_iterator{ current } { }

			friend class linked_list<T>;
		};

		/**
		* Summary
		* Overload the stream insertion operator.
		*/
		std::ostream & operator<<(std::ostream & out, linked_list<T> & value)
		{
			out << value;

			return out;
		}

		/**
		 * Summary
		 * Initiate the init() constructor.
		 */
		linked_list()
		{
			this->init();
		}

		/**
		 * Summary
		 * Assign values a rhs value.
		 */
		linked_list(const linked_list & rhs)
		{
			this->init();
			for (auto &value : rhs)
			{
				this->push_back(value);
			}
		}

		/***
		 * Summary
		 * Delete the head and tail pointers.
		 */
		~linked_list()
		{
			this->clear();
			delete this->head;
			delete this->tail;
		}

		/***
		 * Summary
		 * Construct the "right hand side" pointer and object with nullptr.
		 */
		linked_list(linked_list && rhs) noexcept
			: my_size{ rhs.my_size }, head{ rhs.head }, tail{ rhs.tail }
		{
			rhs.my_size = 0;
			rhs.head = nullptr;
			rhs.tail = nullptr;
		}

		/***
		 * Summary
		 * Overload the "right hand side" = operator.
		 */
		linked_list & operator=(linked_list && rhs) noexcept
		{
			std::swap(this->my_size, rhs.my_size);
			std::swap(this->head, rhs.head);
			std::swap(this->tail, rhs.tail);
			return *this;
		}

		/***
		 * Summary
		 * Overload the = operator.
		 */
		linked_list & operator= (const linked_list & rhs)
		{
			auto copy = rhs;
			std::swap(*this, copy);
			return *this;
		}

		/***
		 * Summary
		 * Overload the begin() operator.
		 */
		iterator begin()
		{
			return iterator(this->head->next);
		}

		/***
		 * Overload the begin() operator while making sure it cannot
		 * change ANY of the data passed to it.
		 */
		const_iterator begin() const
		{
			return const_iterator(this->head->next);
		}

		/***
		 * Summary
		 * Overload the end() operator.
		 */
		iterator end()
		{
			return iterator(this->tail);
		}

		/***
		 * Summary
		 * Overload the end() operator while making sure it cannot
		 * change ANY of the data passed to it.
		 */
		const_iterator end() const
		{
			return const_iterator(this->tail);
		}

		/***
		 * Overload the size() operator to return out custom
		 * defined size.
		 */
		int size() const
		{
			return this->my_size;
		}

		/**
		 * Summary
		 * Return true is the size of the list is equal to zero.
		 */
		bool is_empty() const
		{
			return this->size() == 0;
		}

		/**
		 * Summary
		 * Delete the empty items in the list.
		 */
		void clear()
		{
			while (!this->is_empty())
			{
				this->pop_front();
			}
		}

		/**
		 * Summary
		 * Returns the first item of the list
		 */
		T & front()
		{
			return *begin();
		}

		/**
		 * Summary
		 * Returns the first item in the list while making
		 * sure not to change ANY of the data passed to it.
		 */
		const T & front() const
		{
			return *begin();
		}

		/**
		 * Summary
		 * Returns the last item in the array.
		 */
		T & back()
		{
			return *--end();
		}

		/**
		 * Summary
		 * Returns the last item in the array while
		 * making sure not to change ANY of the data passed to it.
		 */
		const T & back() const
		{
			return *--end();
		}

		/**
		 * Summary
		 * Insert T &value at the first item in the list.
		 */
		void push_front(const T & value)
		{
			this->insert(this->begin(), value);
		}

		/**
		 *	Summary
		 * Overload the push_back() operator.
		 * Insert T &value at the last item in the list.
		 */
		void push_back(const T & value)
		{
			this->insert(this->end(), value);
		}

		/**
		 * Summary
		 * Push and insert T &&value at the first item in the array.
		 */
		void push_front(T && value)
		{
			this->insert(this->begin(), std::move(value));
		}

		/**
		 * Summary
		 * Overload the push_back() operator.
		 * Insert a de-referenced T &value at the last item in the list.
		 */
		void push_back(T && value)
		{
			this->insert(this->end(), std::move(value));
		}

		/**
		 * Summary
		 * Delete the first item in the list.
		 */
		void pop_front()
		{
			this->erase(this->begin());
		}

		/**
		 * Summary
		 * Delete the last item in the list.
		 */
		void pop_back()
		{
			this->erase(--this->end());
		}

		// insert a value BEFORE iterator. 
		iterator insert(iterator current_iterator, const T & value)
		{
			auto *current = current_iterator.current;
			// ReSharper disable once CppDiscardedPostfixOperatorResult
			this->my_size++;
			return iterator(
				current->previous = current->previous->next =
				new node{ value, current->previous, current });
		}

		iterator insert(iterator current_iterator, T && value)
		{
			auto *current = current_iterator.current;
			// ReSharper disable once CppDiscardedPostfixOperatorResult
			this->my_size++;
			return iterator(
				current->previous = current->previous->next =
				new node{ std::move(value), current->previous, current });
		}

		// This will remove the value AT iterator. 
		iterator erase(iterator remove_iterator)
		{
			auto *current = remove_iterator.current;
			iterator value(current->previous);
			current->previous->next = current->next;
			current->next->previous = current->previous;
			delete current;
			// ReSharper disable once CppDiscardedPostfixOperatorResult
			this->my_size--;
			return value;
		}

	private:

		// ReSharper disable once CppInconsistentNaming
		int my_size;
		// ReSharper disable once CppInconsistentNaming
		node *head;
		// ReSharper disable once CppInconsistentNaming
		node *tail;

		void init()
		{
			this->my_size = 0;
			this->head = new node;
			this->tail = new node;
			this->head->next = this->tail;
			this->tail->previous = this->head;
		}
	};

}

#endif