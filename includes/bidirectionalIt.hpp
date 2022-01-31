#ifndef BIDIRECTIONALIT_H
#define BIDIRECTIONALIT_H

#include "Iter.hpp"

namespace ft
{
    template< typename T >
    class bidirIter
    {
        private:
            T _it;
        public:
            typedef typename iterator_traits<T>::value_type			value_type;
            typedef typename iterator_traits<T>::difference_type	difference_type;
            typedef typename iterator_traits<T>::pointer			pointer;
            typedef typename iterator_traits<T>::reference			reference;
            typedef typename iterator_traits<T>::iterator_category	iterator_category;
            typedef T iterator_type;
            typedef const value_type *			const_iterator_type;

            bidirIter() : _it(T()) {}
            bidirIter(iterator_type x) : _it(x) {}
            template< class U >
            bidirIter(U const & other) : _it(&(*other)) {}
            template< class U >
            bidirIter& operator=(U const & other) {_it = &(*other); return *this;}
            virtual ~bidirIter() {}
            bidirIter& operator++() {_it = _it + 1; return *this;}
            bidirIter operator++(int) {bidirIter retval = *this; ++(*this); return retval;}
            bidirIter& operator--() {_it = _it - 1; return *this;}
            bidirIter operator--(int) {bidirIter retval = *this; --(*this); return retval;}
            bidirIter& operator-=(difference_type n) {_it -= n; return *this;}
            bidirIter operator-(difference_type n) const {return bidirIter(_it - n);}
            bidirIter& operator+=(difference_type n) {_it += n; return *this;}
            bidirIter operator+(difference_type n) const {return bidirIter(_it + n);}
            reference operator[](difference_type n) const {return *(_it + n);}
            pointer operator->() const {return &operator*();}
            reference operator*() const {return *_it;}
            iterator_type base() const {return _it;}

            operator bidirIter<const_iterator_type>()
            {
                return (bidirIter<const_iterator_type>(const_cast<const iterator_type>(_it)));
            }
    };
    template< typename T >
    class bidirReviter
    {
        private:
            T _it;
        public:
            typedef	typename iterator_traits<T>::difference_type		difference_type;
            typedef	typename iterator_traits<T>::value_type			value_type;
            typedef	typename iterator_traits<T>::pointer				pointer;
            typedef	typename iterator_traits<T>::reference			reference;
            typedef	typename iterator_traits<T>::iterator_category	iterator_category;
            typedef T iterator_type;
            typedef const value_type *			const_iterator_type;
            bidirReviter() : _it(T()) {}
            bidirReviter(iterator_type x) : _it(x) {}
            template< class U >
            bidirReviter(U const & other) : _it(other.base()) {}
            template< class U >
            bidirReviter& operator=(U const & other) {_it = other.base(); return *this;}
            virtual ~bidirReviter() {}
            bidirReviter& operator++() {_it--; return *this;}
            bidirReviter operator++(int) {bidirReviter retval = *this; ++(*this); return retval;}
            bidirReviter& operator--() {_it++; return *this;}
            bidirReviter operator--(int) {bidirReviter retval = *this; --(*this); return retval;}
            bidirReviter& operator-=(difference_type n) {_it += n; return *this;}
            bidirReviter operator-(difference_type n) const {return bidirReviter(_it + n);}
            bidirReviter& operator+=(difference_type n) {_it -= n; return *this;}
            bidirReviter operator+(difference_type n) const {return bidirReviter(_it - n);}
            reference operator[](difference_type n) const {return *(_it - n - 1);}
            pointer operator->() const {return &operator*();}
            reference operator*() const {T tmp(_it); return *--tmp;}
            iterator_type base() const {return _it;}

            operator bidirReviter<iter<const_iterator_type> >()
            {
                return (bidirReviter<iter<const_iterator_type> >(iter<const_iterator_type>(_it)));
            }
    };

    template< class Iter>
    bidirIter<Iter> operator+( typename bidirIter<Iter>::difference_type n, const bidirIter<Iter>& it )
    {
        return iter<Iter>(it.base() + n);
    }
    template< class Iterator, class U >
    typename bidirIter<Iterator>::difference_type operator-( const bidirIter<Iterator>& lhs, const bidirIter<U>& rhs )
    {
        return lhs.base() - rhs.base();
    }

    template< class Iter >
    bidirReviter<Iter> operator+( typename bidirReviter<Iter>::difference_type n, const bidirReviter<Iter>& it )
    {
        return bidirReviter<Iter>(it.base() - n);
    }
    template< class Iterator, class U >
    typename bidirReviter<Iterator>::difference_type operator-( const bidirReviter<Iterator>& lhs, const bidirReviter<U>& rhs )
    {
        return rhs.base() - lhs.base();
    }

    template<typename Iterator1, typename Iterator2>
	bool			operator==(bidirIter<Iterator1> const &lhs, bidirIter<Iterator2> const &rhs) { return (lhs.base() == rhs.base()); }
    template<typename Iterator1, typename Iterator2>
    bool operator!=(bidirIter<Iterator1> const &lhs, bidirIter<Iterator2> const &rhs) {return (lhs.base() != rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>(bidirIter<Iterator1> const &lhs, bidirIter<Iterator2> const &rhs) {return (lhs.base() > rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>=(bidirIter<Iterator1> const &lhs, bidirIter<Iterator2> const &rhs) {return (lhs.base() >= rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<(bidirIter<Iterator1> const &lhs, bidirIter<Iterator2> const &rhs) {return (lhs.base() < rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<=(bidirIter<Iterator1> const &lhs, bidirIter<Iterator2> const &rhs) {return (lhs.base() <= rhs.base());}

    template<typename Iterator1, typename Iterator2>
	bool			operator==(bidirReviter<Iterator1> const &lhs, bidirReviter<Iterator2> const &rhs) { return (lhs.base() == rhs.base()); }
    template<typename Iterator1, typename Iterator2>
    bool operator!=(bidirReviter<Iterator1> const &lhs, bidirReviter<Iterator2> const &rhs) {return (lhs.base() != rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>(bidirReviter<Iterator1> const &lhs, bidirReviter<Iterator2> const &rhs) {return (lhs.base() < rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>=(bidirReviter<Iterator1> const &lhs, bidirReviter<Iterator2> const &rhs) {return (lhs.base() <= rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<(bidirReviter<Iterator1> const &lhs, bidirReviter<Iterator2> const &rhs) {return (lhs.base() > rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<=(bidirReviter<Iterator1> const &lhs, bidirReviter<Iterator2> const &rhs) {return (lhs.base() >= rhs.base());}
}

#endif