#ifndef COMMON_QUEUE_STACK
#define COMMON_QUEUE_STACK

#include "../container/s21_container.h"

namespace s21{
    template <typename T>
    class Common_q_s : public container<T>{
    protected:
        struct Node{
            T data;
            Node *next{nullptr};
            Node(T data) : data(data) {};
        };
        using typename container<T>::size_type;
        size_type nodes_counter{0};

    public:
        virtual bool empty() const override{
            return !nodes_counter;
        };
        virtual size_type size() const override{
            return nodes_counter;
        };
    };
};
#endif