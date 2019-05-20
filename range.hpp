#pragma once
#ifndef _LYN_RANGE_HPP_
#define _LYN_RANGE_HPP_

#include <iterator>

namespace lyn {
    template<typename T, typename U = T, typename V = T>
    struct range {
    private:
        inline T backward() { T v{}; return --v; }
        inline T forward() { T v{}; return ++v; }
        const T m_start;
        const U m_stop;
        const V m_step;
        bool (*const m_ltgt)(T, T);
    public:
        range(const T& start, const U& stop, const V& step) : m_start(start), m_stop(stop), m_step(step),
            m_ltgt(T()<(T()+m_step) ? [](T l, T r){
                    if constexpr (std::is_floating_point_v<T>) return l<=r;
                    else return l<r;
                } : [](T l, T r){
                    if constexpr (std::is_floating_point_v<T>) return r<=l;
                    else return r<l;
                })
        {}

        range(const T& start, const U& stop) : range(start, stop, stop<start ? backward() : forward()) {}
        range(const T& stop) : range(T(), stop) {}

        class iterator { // : public std::iterator<std::forward_iterator_tag, T> {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = std::remove_cv_t<T>;
            using difference_type = V;
            using pointer = T*;
            using reference = T&;
        private:
            T m_val;
            V m_step;
            bool (*m_ltgt)(T, T);
        public:
            iterator() : m_val(), m_step(), m_ltgt(nullptr) {}
            iterator(T val) : m_val(val), m_step(), m_ltgt(nullptr) {}
            iterator(T val, V step, bool (*const ltgt)(T,T)) :
                m_val(val), m_step(step), m_ltgt(ltgt)
            {}
            iterator& operator=(const iterator& rhs) {
                m_val = rhs.m_val;
                m_step = rhs.m_step;
                m_ltgt = rhs.m_ltgt;
                return *this;
            }
            inline iterator& operator++() { m_val += m_step; return *this; }
            inline iterator operator++(int) { auto cp=m_val; m_val += m_step; return cp; }

            inline const T& operator*() const { return m_val; }
            inline const T* operator&() const { return &m_val; }
            inline reference operator*() { return m_val; }
            inline pointer operator&() { return &m_val; }

            inline bool operator!=(const iterator& rhs) const { return m_ltgt(m_val, rhs.m_val); }
            inline bool operator==(const iterator& rhs) const { return !(*this!=rhs); }
            inline bool operator!=(const U& rhs) const { return m_ltgt(m_val, rhs); }
            inline bool operator==(const U& rhs) const { return !(*this!=rhs); }
        };

        const iterator begin() const { return iterator(m_start, m_step, m_ltgt); }
        #ifdef _WIN32
        const iterator end() const { return iterator{m_stop}; }
        #else
        const U& end() const { return m_stop; } // prefered but does not compile with msvc
        #endif
    };
}

#endif
