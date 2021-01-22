#pragma once

#include <iostream>
#include <type_traits>

#include <string>
#include <exception>

namespace JuNOCpp
{
	namespace Utils
	{
		template <typename Type, typename = void>
		struct has_esft_base: std::false_type {};

		template <typename Type>
		struct has_esft_base<Type, std::void_t<decltype(enable_shared_from_this_base(std::declval<Type*>()))>>
		: std::__not_<std::is_array<Type>> {};

		struct manage_count
		{
			size_t m_use_count;
			size_t m_weak_count;

			manage_count(size_t uses = 0, size_t weaks = 0):
				m_use_count{ uses }, m_weak_count{ weaks } {}
		};

		template<typename ElementType>
		struct representation
		{
			ElementType* m_element_ptr;
			manage_count* m_count_ptr;

			representation(ElementType *ele_ptr = nullptr,
				manage_count* count_ptr = nullptr):
				m_element_ptr{ele_ptr}, m_count_ptr{count_ptr} 	{ }
		};

		// forward declaration for weak_ptr
		template<typename ElementType> class weak_ptr;
		template<typename ElementType> class enable_shared_from_this;
		
		template<typename ElementType>
		class shared_ptr: public representation<ElementType>
		{
			template<typename Type> friend class weak_ptr;
			template<typename Type> friend class enable_shared_from_this;

		public:
			class bad_shared_ptr: public std::exception
			{
			private:
				const char* m_msg;

			public:
				bad_shared_ptr(const char* msg = "bad_shared_ptr"):
					m_msg{msg} { }

				const char* what() const noexcept override
				{
					return this->m_msg;
				}
			};

		private:
			using base_t = representation<ElementType>;

			using representation<ElementType>::m_element_ptr;
			using representation<ElementType>::m_count_ptr;
			
			void increment_use_count()
			{
				if (m_element_ptr)
					++m_count_ptr->m_use_count;
			}

		public:
			shared_ptr()
			{
				/*
					m_element_ptr = nullptr;
					m_count_ptr = nullptr;
				*/
			}

			explicit shared_ptr(ElementType* ele_ptr) :
				base_t{ ele_ptr, new manage_count{ (size_t)1, (size_t)0 } }
			{
				
				// m_element_ptr = ele_ptr;
				// m_count_ptr = 
				//			new manage_count{ 1 /* uses */, 0 /* weaks */ }
				//
				// m_count_ptr->m_use_count = 1
				// m_count_ptr->m_weak_count = 0
				// std::cout << "sp - " << &*m_element_ptr << std::endl;
				enable_shared_from_this_with(m_element_ptr);
			}

			shared_ptr(ElementType* ele_ptr, manage_count* count_ptr) :
				base_t{ ele_ptr, count_ptr } { }

			operator bool() const noexcept
			{
				return m_element_ptr != nullptr;
			}

			bool operator==(shared_ptr& rhs)
			{
				return m_element_ptr == rhs.m_element_ptr;
			}

			ElementType& operator*()
			{
				if (m_element_ptr)
					return *m_element_ptr;
				else
					throw bad_shared_ptr("shared_ptr: invalid element pointer");
			}

			ElementType* get()
			{
				if (m_element_ptr)
					return m_element_ptr;
				else
					throw bad_shared_ptr("shared_ptr: invalid element pointer");
			}

			template<typename Type = ElementType>
			std::enable_if_t< std::is_same_v<Type, ElementType> && std::is_class_v<Type>,
				ElementType*> operator->()
			{
				if (m_element_ptr)
					return m_element_ptr;
				else
					throw bad_shared_ptr("shared_ptr: invalid element pointer");
			}

			template <typename Type, typename Type2 = typename std::remove_cv_t<ElementType>>
			std::enable_if_t<has_esft_base<Type>::value> enable_shared_from_this_with(Type* obj)
			{
				// std::cout << m_element_ptr << " - ";
				if (auto __base = enable_shared_from_this_base(obj))
					__base->weak_this.weak_assign(m_element_ptr, m_count_ptr);
			}
			
			template <typename Type>
			std::enable_if_t<!has_esft_base<Type>::value> enable_shared_from_this_with(Type* obj)
			{
			}

			shared_ptr(const shared_ptr& rhs):
				base_t{ rhs.m_element_ptr, rhs.m_count_ptr}
			{
				// std::cout << "sp - " << &*m_element_ptr << std::endl;

				increment_use_count();
			}

			shared_ptr& operator=(const shared_ptr& rhs)
			{
				if (this != std::addressof(rhs))
				{
					// free existing memory
					this->reset();

					m_element_ptr = rhs.m_element_ptr;
					m_count_ptr = rhs.m_count_ptr;

					increment_use_count();
				}
				
				return *this;
			}

			shared_ptr(shared_ptr&& rhs) noexcept:
				base_t{ rhs.m_element_ptr, rhs.m_count_ptr }
			{
				// std::cout << "sp - " << &*m_element_ptr << std::endl;
				rhs.m_element_ptr = nullptr;
			}

			shared_ptr& operator=(shared_ptr&& rhs)
			{
				if (this != std::addressof(rhs))
				{
					this->reset();

					m_element_ptr = rhs.m_element_ptr;
					m_count_ptr = rhs.m_count_ptr;

					rhs.m_element_ptr = nullptr;
				}

				return *this;
			}

			template <class T>
			shared_ptr(weak_ptr<T> const& w_ptr)
			{
				m_count_ptr = w_ptr.m_count_ptr;
				m_element_ptr = w_ptr.m_element_ptr;

				// std::cout << "sp - " << &*m_element_ptr << std::endl;

				if(m_element_ptr)
					increment_use_count();
			}

			template <class Type>
			shared_ptr(shared_ptr<Type>& rhs):
			base_t{ rhs.get(), rhs.get_m_count_ptr() }
			{
				// std::cout << "sp - " << &*m_element_ptr << std::endl;
				increment_use_count();
			}

			manage_count* get_m_count_ptr()
			{
				return m_count_ptr;
			}

			void reset()
			{
				if (m_element_ptr)
				{
					--m_count_ptr->m_use_count;

					if (m_count_ptr->m_use_count == 0)
					{
						delete m_element_ptr;

						if (m_count_ptr->m_weak_count == 0)
						{
							m_count_ptr->m_weak_count = (size_t)(-1);

							delete m_count_ptr;
						}
					}

					m_element_ptr = nullptr;
				}
			}

			size_t use_count() const
			{
				if (m_element_ptr)
				{
					return m_count_ptr->m_use_count;
				}
				else
					return 0;
			}

			size_t weak_count() const
			{
				if (m_element_ptr)
					return m_count_ptr->m_weak_count;
				else
					return 0;
			}

			~shared_ptr()
			{
				reset();
			}
		}; // shared_ptr

		template<typename ElementType>
		class weak_ptr : public representation<ElementType>
		{
			template<typename Type> friend class shared_ptr;

		private:
			
			using representation<ElementType>::m_element_ptr;
			using representation<ElementType>::m_count_ptr;

			void increment_use_count()
			{
				if (m_element_ptr)
					++m_count_ptr->m_use_count;
			}

		public:

			weak_ptr()
			{
				/*
					m_element_ptr = nullptr;
					m_count_ptr = nullptr;
				*/
			}

			weak_ptr(shared_ptr<ElementType>& sp):
				representation<ElementType>{ sp.m_element_ptr, sp.m_count_ptr }
			{ 
				if (m_element_ptr)
					++m_count_ptr->m_weak_count;
			}
			
			shared_ptr<ElementType> lock()
			{
				increment_use_count();

				return { m_element_ptr, m_count_ptr };
			}
			size_t use_count()
			{
				if (m_element_ptr)
					return m_count_ptr->m_use_count;
				else
					return 0;
			}

			size_t weak_count() const
			{
				if (m_element_ptr)
					return m_count_ptr->m_weak_count;
				else
					return 0;
			}

			void reset()
			{
				if (m_element_ptr)
				{
					--m_count_ptr->m_weak_count;

					if (m_count_ptr->m_use_count == 0
						&& m_count_ptr->m_weak_count == 0)
					{
						m_count_ptr->m_weak_count = -1;

						delete m_count_ptr;
					}

					m_element_ptr = nullptr;
				}
			}

			void weak_assign(shared_ptr<ElementType>* ptr)
			{
				this->m_element_ptr = ptr->m_element_ptr;
				this->m_count_ptr = ptr->m_count_ptr;
			
				if(m_element_ptr)
					++m_count_ptr->m_weak_count;
			}

			template <class Type>
			void weak_assign(shared_ptr<Type>* ptr)
			{
				this->m_element_ptr = ptr->m_element_ptr;
				this->m_count_ptr = ptr->m_count_ptr;
			
				if(m_element_ptr)
					++m_count_ptr->m_weak_count;
			}

			void weak_assign(ElementType* ele_ptr, manage_count* count_ptr)
			{
				// std::cout << ele_ptr << " - " << &*ele_ptr << std::endl;
				this->m_element_ptr = ele_ptr;
				this->m_count_ptr = count_ptr;
			}

			~weak_ptr()
			{
				reset();
			}

		}; // weak_ptr

		template <typename T>
		class enable_shared_from_this
		{
			template <class OT> friend class shared_ptr; 
			template <class OT> friend class weak_ptr; 
		protected:
			mutable weak_ptr<T> weak_this;
		
		protected:
			constexpr enable_shared_from_this()
			{
			}

			constexpr enable_shared_from_this(enable_shared_from_this const&)
			{
			}

			template <class OT>
			enable_shared_from_this(enable_shared_from_this<OT> const&)
			{
			}

			enable_shared_from_this& operator=(enable_shared_from_this const&)
			{
				return *this;
			}

			~enable_shared_from_this()
			{
			}
		private:
			friend const enable_shared_from_this*
			enable_shared_from_this_base(const enable_shared_from_this* __p)
			{ return __p; }
		public:
			shared_ptr<T> shared_from_this()
			{
				return {weak_this};
			}

			shared_ptr<T const> shared_from_this() const
			{
				shared_ptr<T const> ptr(weak_this);
				return ptr;
			}

			weak_ptr<T> weak_from_this()
			{
				return weak_this;
			}

			weak_ptr<T const> weak_from_this() const
			{
				return weak_this;
			}
		};
		
	} // Utils
} // JuNOCpp