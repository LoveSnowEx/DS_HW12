#include "bits/stdc++.h"
#define HIGHBIT(_x) (_x ? (1 << (32-__builtin_clz(_x))) : 1)

namespace mystl {
	template <typename T>
	class vector {
		size_t _size, _cap;
		T *_arr;
	public:
		class iterator : public std::iterator<std::random_access_iterator_tag, T> {
			T *_ptr;
		public:
			typedef T value_type;
		
			iterator(T *ptr) : _ptr(ptr) {}
					
			iterator &operator++() {
				_ptr++;
				return *this;
			}
			iterator operator++(int) {
				iterator tmp(this->_ptr);
				operator++();
				return tmp;
			}
			iterator &operator--() {
				_ptr--;
				return *this;
			}
			iterator operator--(int) {
				iterator tmp(this->_ptr);
				operator--();
				return tmp;
			}
			iterator operator+(const size_t n) {
				return iterator(this->_ptr+n);
			}
			iterator operator-(const size_t n) {
				return iterator(this->_ptr-n);
			}
			size_t operator-(const iterator &rhs) {
				return this->_ptr-rhs._ptr;
			}
			constexpr bool operator==(const iterator &rhs) const { return _ptr == rhs._ptr; }
			
			constexpr bool operator!=(const iterator &rhs) const { return _ptr != rhs._ptr; }
			
			constexpr T &operator*() const { return *_ptr; }
		};
		vector() : _size(0), _cap(1), _arr(new T[_cap]) { }
		
		vector(size_t size) : _size(size), _cap(HIGHBIT(_size)), _arr(new T[_cap]()) { }
		
		vector(const vector &other) : _size(other._size), _cap(other._cap), _arr(new T[_cap]) {
			std::copy(other.begin(), other.end(), this->begin());
		}
		~vector() {
			delete[] _arr;
		}		
		constexpr bool empty() const { return _size == 0; }
		
		constexpr iterator begin() { return iterator(_arr); }
		
		constexpr const iterator begin() const { return iterator(_arr); }
		
		constexpr iterator end() { return iterator(_arr+_size); }
		
		constexpr const iterator end() const { return iterator(_arr+_size); }
		
		constexpr size_t size() const { return _size; }
		
		constexpr T &operator[](int idx) { return _arr[idx]; }
		
		constexpr const T &operator[](int idx) const { return _arr[idx]; }
		
		void fill(iterator first, iterator last) { while(first != last) *(first++) = T(); }
		
		void resize(size_t size) {
			if(size > _cap) {
				_cap = HIGHBIT(size);
				auto tmp = new T[_cap]();
				std::copy(begin(), end(), tmp);
				delete[] _arr;
				_arr = tmp;
			}
			else _size = size;
		}
		void push_back(const T &value) {
			if(_size == _cap) resize(_cap*2);
			_arr[_size++] = value;
		}
		vector<T> &operator=(const vector<T> &other) {
			if(this == &other) return *this;
			resize(other._size);
			std::copy(other.begin(), other.end(), this->begin());
			return *this;
		}
	};
}