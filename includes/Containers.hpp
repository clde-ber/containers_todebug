#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <string>
#include <memory>
#include <cstddef>

#define TRUE 1
#define FALSE 0

namespace ft
{
    template< typename T >
    class stack
    {
        private:
            size_t _n;
            T* _p;
            class OutOfLimitsException : public std::exception
            {
                public:
                    virtual const char* what() const throw()
                    {
                        return "Stack element exception: out of limits!";
                    }
            };
            class EmptyStackException : public std::exception
            {
                public:
                    virtual const char* what() const throw()
                    {
                        return "Stack exception: empty stack!";
                    }
            };
        public:
            stack( void )
            {
                std::allocator< T > alloc;
                _n = 0;
                _p = alloc.allocate(0, this);
            }
            stack( size_t n )
            {
                std::allocator< T > alloc;
                _n = n;
                _p = alloc.allocate(_n, this);
            }
            stack( const stack & rhs )
            {
                *this = rhs;
            }
            stack & operator=( stack const & rhs )
            {
                std::allocator< T > alloc;
                alloc.deallocate(_p, _n);
                _n = rhs._n;
                _p = alloc.allocate(rhs._n, this);
                for (size_t i = 0; i < _n; i++)
                    _p[i] = rhs._p[i];
                return *this;
            }
            virtual ~stack( void )
            {
                std::allocator< T > alloc;
                alloc.deallocate(_p, _n);
            }
            size_t size() const
            {
                return _n;
            }
            bool empty() const
            {
                if (!_n)
                    return TRUE;
                return FALSE;
            }
            T & operator[](size_t n)
            {
                if (n < 0 or n >= _n)
                throw OutOfLimitsException();
                return _p[n];
            }
            T & top()
            {
                if (!empty())
                    return _p[_n - 1];
                throw EmptyStackException();
            }
            void push(T const & val)
            {
                stack< T > tmp(_n + 1);
                for (size_t i = 0; i < _n; i++)
                    tmp._p[i] = _p[i];
                tmp._p[_n] = val;
                tmp._n = _n + 1;
                *this = tmp;
            }
            void pop()
            {
                if (!_n)
                    throw EmptyStackException();
                std::allocator< T > alloc;
                stack< T > tmp(_n - 1);
                for (size_t i = 0; i < _n - 1; i++)
                    tmp._p[i] = _p[i];
                tmp._n = _n - 1;
                *this = tmp;
            }
        };
        class Vector;
        class Map;
}

    // empty : Test whether container is empty 
    // size : Return size OK
    // top : Access next element
    // push_back
    // pop_back
    // push : Insert element
    // pop : Remove top element 
    // back
    // push_back
    // pop_back

#endif