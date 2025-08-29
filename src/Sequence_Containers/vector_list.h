#ifndef VECTOR_LIST_COMMON
#define VECTOR_LIST_COMMON

#include "../container/s21_container.h"

#include <limits>

namespace s21{
    template <typename T>
    class Vector_list : public container<T>{
    public:
        using typename container<T>::const_reference;
        using typename container<T>::size_type;
        virtual const_reference front() = 0;
        virtual const_reference back() = 0;
        virtual size_type max_size() = 0;
        virtual void clear() = 0;
        virtual void push_back(const_reference value) = 0;
        virtual void pop_back() = 0;
    };
};

#endif