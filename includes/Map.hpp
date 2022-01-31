#ifndef MAP_H
#define MAP_H

#include "RBTree.hpp"
#include "Vector.hpp"

namespace ft
{
    template< class Key, class T, class Compare = ft::Node<Key>, class Allocator = std::allocator<ft::RBTree<const Key, T> > >
    class value_compare
        {
            private:
                bool result_type;
                RBTree<Key, T> first_argument_type;
                RBTree<Key, T> second_argument_type;
            protected:
                Compare _comp;
                value_compare(Compare c) : _comp(c) {}
            public:
                bool operator()( const RBTree<Key, T>& lhs, const RBTree<Key, T>& rhs ) const {comp(lhs.first, rhs.first);}
        };
    template< class Key, class T, class Compare = ft::Node<Key>, class Allocator = std::allocator<ft::RBTree<const Key, T> > >
    class map : public value_compare< Key, T, Compare, Allocator >
    {
        private:
            size_t _n;
            size_t _capacity;
            RBTree< Key, T> *_p;
            Allocator _alloc;
        protected:
            bool comp(T a, T b) {return a < b;}
            bool equiv(T a, T b) {return (!comp(a, b) && !comp(b, a));}
        public:
            typedef Key key_type;
            typedef T mapped_type;
            typedef RBTree<Key, T> value_type;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef Compare key_compare;
            typedef Allocator allocator_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef	RBTree<Key, T>	*tree_type;
			typedef	RBTree<const Key, T> *const_tree_type;
            typedef iter< tree_type > *iterator;
			typedef	iter< const_tree_type >	*const_iterator;
			typedef	reviter< tree_type > *reverse_iterator;
			typedef	reviter< const_tree_type > *const_reverse_iterator;
            map() : value_compare< Key, T, Compare, Allocator >(key_compare()), _n(0), _capacity(0), _p(0), _alloc(allocator_type())
            {
                _p = new RBTree< Key, T >();
            }
            explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : value_compare< Key, T, Compare, Allocator >(comp), _n(0), _capacity(0), _p(0), _alloc(alloc)
            {
                _p = new RBTree< Key, T >();
            }
            template< class InputIt > map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : value_compare< Key, T, Compare, Allocator >(comp), _n(0), _capacity(0), _p(0), _alloc(alloc)
            {
                _p = new RBTree< Key, T >();
                _p->insertion(first, last);
            }
            map (const map& x) : value_compare< Key, T, Compare, Allocator >(x.comp), _n(x._n), _capacity(x._capacity), _p(0), _alloc(x._alloc)
            {
                _p = new RBTree< Key, T >();
                _p->insertion(x.begin(), x.end());
            }
            virtual ~map()
            {
                erase(begin(), end());
            }
            map& operator=(const map& other)
            {
                (void)other;
            }
            allocator_type get_allocator() const
            {
                return _alloc;
            }
            iterator begin()
            {
                return iterator(_p);
            }
            const_iterator begin() const
            {
                return const_iterator(_p);
            }
            iterator end()
            {
                return iterator(_p + _n);
            }
            const_iterator end() const
            {
                return const_iterator(_p + _n);
            }
            reverse_iterator rbegin()
            {
                return reverse_iterator(end());
            }
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(end());
            }
            reverse_iterator rend()
            {
                return reverse_iterator(begin());
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
            }
            T& operator[](const Key& key)
            {
                return _p[key];
            }
            bool empty() const
            {
                if (!_n)
                    return TRUE;
                return FALSE;
            }
            size_type size() const
            {
                return _n;
            }
            size_type max_size() const
            {
                return (std::pow(2, 32) / sizeof(T) * std::pow(2, 32)) - 1;
            }
            void clear()
            {
                erase(begin(), end());
            }
            RBTree<iterator, bool> insert(const value_type& value)
            {
                if (!_p->find(value))
                    _p->insertion(value);
                return _p;
            }
            iterator insert(iterator hint, const value_type& value)
            {
                iterator ite = end();
                iterator it = begin();

                (void)hint;
                for (; it != ite; it++)
                {
                    if (!_p->find(*it))
                    {
                        _p->insertion(value);
                        return it;
                    }
                }
                return it;
            }
            template< class InputIt >
            void insert(InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL)
            {
                for (InputIt it = first; it != last; it++)
                {
                    if (!_p->find(*it))
					    _p->insertion(*it);
                }
            }
            void erase(iterator pos)
            {
                _p->deleteNode(*pos);
            }
            void erase(iterator first, iterator last)
            {
                for (iterator it = first; it != last; it++)
                {
                    erase(it);
                }
            }
            size_type erase(const Key& key)
            {
                _p->deleteNode(key);
            }
            void swap(map& x)
            {
                T *tmpP = x._p;
                size_t tmpC = x._capacity;
                size_t tmpN = x._n;
                x._p = this->_p;
                x._capacity = this->_capacity;
                x._n = this->_n;
                this->_p = tmpP;
                this->_capacity = tmpC;
                this->_n = tmpN;
            }
            size_type count(const Key& key) const
            {
                if (_p->find(key))
                    return TRUE;
                return FALSE;
            }
            iterator find(const Key& key)
            {
                return *_p->find(key);
            }	
            const_iterator find(const Key& key) const
            {
                return *_p->find(key);
            }
            RBTree<iterator,iterator> equal_range(const Key& key)
            {
                return RBTree< Key, T >(lower_bound(key), upper_bound(key));
            }
            RBTree<const_iterator,const_iterator> equal_range(const Key& key) const
            {
                return RBTree< Key, T >(lower_bound(key), upper_bound(key));
            }
            iterator lower_bound(const Key& key)
            {
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (!comp(*it, key))
                        return it;
                    it++;
                }
            }
            const_iterator lower_bound(const Key& key) const
            {
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (!comp(*it, key))
                        return it;
                    it++;
                }
            }
            iterator upper_bound(const Key& key)
            {
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (!comp(*it, key) && !equiv(*it, key))
                        return it;
                    it++;
                }
            }
            const_iterator upper_bound(const Key& key) const
            {
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (!comp(*it, key) && !equiv(*it, key))
                        return it;
                    it++;
                }
            }
            key_compare key_comp() const
            {
                return key_type();
            }
            value_compare< Key, T, Compare, Allocator > value_comp() const
            {
                return mapped_type();
            }
            void print()
            {
                _p->prettyPrint();
            }
    };

    template< class Key, class T, class Compare, class Alloc >
    bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        (void)lhs;
        (void)rhs;
    }	
    template< class Key, class T, class Compare, class Alloc >
    bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        (void)lhs;
        (void)rhs;
    }
    template< class Key, class T, class Compare, class Alloc >
    bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        (void)lhs;
        (void)rhs;
    }
	template< class Key, class T, class Compare, class Alloc >
    bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        (void)lhs;
        (void)rhs;
    }
	template< class Key, class T, class Compare, class Alloc >
    bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        (void)lhs;
        (void)rhs;
    }
    template< class Key, class T, class Compare, class Alloc >
    bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        (void)lhs;
        (void)rhs;
    }
}

#endif