#ifndef LIST_H
#define LIST_H

#include "../vector_list.h"

namespace s21{
    template <typename T>
    class list : public Vector_list<T>{
    public:
        using typename container<T>::value_type;
        using typename container<T>::reference;
        using typename container<T>::const_reference;
        using typename container<T>::size_type;
    private:
        struct Node{
        private:
            T data;
            Node *next{nullptr};
            Node *prev{nullptr};
        public:
            Node(T data, Node *next = nullptr) : data(data), next(next) {};
            friend class list;
        };
        Node *tail{nullptr}, *head{nullptr};
        size_type nodes_counter{0};

        class ListIterator{
        private:
            Node *current{nullptr};
        public:
            ListIterator(Node *ptr = nullptr) : current(ptr){};

            ListIterator& operator++(){
                if(current && current->next){
                    current = current->next;
                }
                else current = nullptr;
                return *this;
            };

            ListIterator& operator++(int) const {
                ListIterator tmp(current);
                current++;
                return ListIterator(tmp);
            };

            ListIterator& operator--(){
                if(current && current->prev){
                    current = current->prev;
                }
                else current = nullptr;
                return *this;
            };

            ListIterator& operator--(int) const{
                ListIterator tmp(current);
                current--;
                return ListIterator(tmp);
            };

            ListIterator operator[](int index){
                current = head;
                if(index < nodes_counter){
                    for(size_type i = 0; i < index; ++i){
                        ++current;
                    }
                }
                return *this;
            };

            T operator*(){
                return current->data;
            };

            bool operator==(const ListIterator &other) const {
                return current == other.current;
            };

            bool operator!=(const ListIterator &other) const{
                return current != other.current;
            };

            Node *get_prev(){
                return current->prev;
            };

            Node *get_next(){
                return current->next;
            };

            Node *get_current(){
                return current;
            }
        };

        ListIterator start() const{
            return ListIterator(head);
        };
    
        ListIterator finish() const{
            return ListIterator(tail);
        };

    public:

        class ListConstIterator{
        private:
            const Node *current{nullptr};
        public:
            ListConstIterator(Node *ptr = nullptr) : current(ptr){};

            ListConstIterator operator++(){
                if(current && current->next){
                    current = current->next;
                }
                else current = nullptr;
                return *this;
            };

            ListConstIterator operator++(int){
                Node *tmp = current;
                current++;
                return ListIterator(tmp);
            };

            ListConstIterator operator--(){
                if(current && current->prev){
                    current = current->prev;
                }
                else current = nullptr;
                return *this;
            };

            ListConstIterator operator--(int){
                Node *tmp = current;
                current--;
                return ListIterator(tmp);
            };

            ListConstIterator operator[](int index){
                current = head;
                if(index < nodes_counter){
                    for(size_type i = 0; i < index; ++i){
                        ++current;
                    }
                }
                return *this;
            };

            T operator*(){
                return current->data;
            };

            bool operator==(const ListConstIterator &other) const{
                return current == other.current;
            };

            bool operator!=(const ListConstIterator &other) const{
                return !(*this == other);
            };

            Node *get_prev(){
                return current->prev;
            };

            Node *get_next(){
                return current->next;
            };

            Node *get_current(){
                return current;
            }
        };

        using iterator = ListIterator;
        using const_iterator = ListIterator;
        size_type node_size(){
            return sizeof(Node);
        };

    public:

        const_reference get_data(Node *ptr){
            return ptr.data;
        };

        list() : tail(nullptr), head(nullptr), nodes_counter(0) {};

        list(size_type n) {
            for(size_type i = 0; i < n; ++i){
                push_back(T());
            }
        };

        list(std::initializer_list<value_type> const &items){
            for(auto item : items){
                push_back(item);
            }
        };

        list(const list &l){
            Node *tmp = l.head;
            while(tmp != nullptr){
                push_back(tmp -> data);
                tmp = tmp -> next;
            }
        };

        list(list &&l){
            head = l.head;
            l.head = nullptr;
            tail = l.tail;
            l.tail = nullptr;
            nodes_counter = l.nodes_counter;
            l.nodes_counter = 0;
        };

        ~list(){
            clear();
        };

        list &operator=(list &&l){
            if(this != &l){
                clear();
                head = l.head;
                l.head = nullptr;
                tail = l.tail;
                nodes_counter = l.nodes_counter;
                l.nodes_counter = 0;
            }
            return *this;
        };

        virtual const_reference front() override{
            if(!head) throw std::logic_error("front() called to empty list");
            return head->data;
        };

        virtual const_reference back() override{
            if(!tail) throw std::logic_error("front() called to empty list");
            return tail->data;
        };

        iterator begin() const{
            return start();
        };

        iterator end() const{
            return finish();
        };

        iterator end_iter() const{
            return nullptr;
        }

        virtual bool empty() const override{
            return !nodes_counter;
        };

        virtual size_type size() const override{
            return nodes_counter;
        };

        virtual size_type max_size() override{
            return std::numeric_limits<size_type>::max() / node_size();
        };

        virtual void clear() override{
            if(head){
                Node *n = head->next;
                while(n){
                    delete head;
                    head = n;
                    n = head -> next;
                }
            }
            head = nullptr;
            tail = nullptr;
            nodes_counter = 0;
        };

        iterator insert(iterator pos, const_reference value){
            check_iterator(pos);
            Node *tmp = new Node(value);
            if(pos != head){
                pos.get_current() -> prev -> next = tmp;
                tmp -> prev = pos.get_current() -> prev;
            }
            else{
                tmp -> next = head;
                head = tmp;
            }
            tmp -> next = pos.get_current();
            pos.get_current()->prev = tmp;
            ++nodes_counter;
            return iterator(tmp);
        };

        void erase(iterator pos){
            if(!pos.get_current() || empty()) throw std::out_of_range("You try to inserte node without addres");
            if(pos == end()){
                pos.get_prev() -> next = nullptr;
                tail = pos.get_prev();
            }
            else if(pos == begin()){
                pos.get_next() -> prev = nullptr;
                head = pos.get_next();
            }
            else{
                pos.get_prev() -> next = pos.get_next();
                pos.get_next() -> prev = pos.get_prev();
            }
            delete pos.get_current();
            --nodes_counter;
        };

        virtual void push_back(const_reference value) override{
            Node *tmp = new Node(value);
            if(!head){
                head = tmp;
                tail = tmp;
            }
            else{
                tail -> next = tmp;
                tmp -> prev = tail;
                tail = tmp;
            }
            ++nodes_counter;
        };

        // отладочный 
        void show(){
            Node *tmp = head;
            while(tmp){
                std::cout << tmp ->data << ' ';
                tmp = tmp -> next;
            }
            std::cout << std::endl;
            tmp = tail;
            while(tmp){
                std::cout << tmp -> data << ' ';
                tmp = tmp -> prev;
            }
            std::cout << std::endl;
        }

        virtual void pop_back() override{
            if(tail){
                Node *tmp = tail;
                if(tail -> prev){
                    tail = tail->prev;
                    tail -> next = nullptr;
                }
                else {
                    tail = nullptr;
                    head = nullptr;
                }
                delete tmp;
                --nodes_counter;
            }
            else throw std::out_of_range("List is empty");
        };

        void push_front(const_reference value){
            Node *tmp = new Node(value);
            if(head){
                head -> prev = tmp;
                tmp -> next = head;
                head = tmp;
            }
            else{
                head = tmp;
                tail = tmp;
            }
            ++nodes_counter;
        };

        void pop_front(){
            if(head){
                Node *tmp = head;
                if(head -> next){
                    head = head -> next;
                    head -> prev = nullptr;
                }
                else {
                    tail = nullptr;
                    head = nullptr;
                }
                delete tmp;
                --nodes_counter;
            }
            else throw std::out_of_range("List is empty");
        };

        void swap(list& other){
            std::swap(head, other.head);
            std::swap(tail, other.tail);
            std::swap(nodes_counter, other.nodes_counter);
        };

        void merge(list& other){
            if(this == &other) return;
            merge_sorted(head, other.head);
            nodes_counter += other.nodes_counter;
            other.head = nullptr, other.tail = nullptr, other.nodes_counter = 0;
        };

        bool check_iterator(const_iterator pos) const{
            if(pos == nullptr) throw std::invalid_argument("You try to splice other list into nullptr place");
            bool flag = false;
            for(auto i = begin(); i != end() && !flag; ++i){
                if(pos == i) flag = true;
            }
            if(pos == end()) flag = true;
            if(!flag) throw std::invalid_argument("Pos is not in the range [begin(), end())");
            return flag;
        };

        void splice(const_iterator pos, list& other){
            if(pos.get_current()) check_iterator(pos);
            Node *remember_end = pos.get_current();
            if(pos.get_current() == nullptr){
                tail -> next = other.head;
                other.head -> prev = tail;
                tail = other.tail;
            }
            else{
                if(remember_end != head){
                    other.head->prev = pos.get_current() -> prev;
                    (pos.get_current()) -> prev -> next = other.head;
                }
                else{
                    head = other.head;
                }
                other.tail -> next = remember_end;
                remember_end -> prev = other.tail;
            }
            nodes_counter += other.nodes_counter;    
            other.head = nullptr, other.tail = nullptr, other.nodes_counter = 0;
        };

        void reverse(){
            if(!size()) throw std::logic_error("You try to reverse empty list");
            list a;
            Node *tmp = tail;
            head = tmp;
            tmp -> prev = nullptr;
            while(tmp){
                a.push_back(tmp->data);
                tail = tmp;
                tmp = tmp->next;
            }
            std::swap(a, *this);
        };

        void unique(){
            Node *tmp = head;
            while(tmp != tail){
                if(tmp ->data == tmp -> next -> data){
                    Node *eq_el = tmp -> next;
                    Node *new_next = tmp -> next -> next ? tmp -> next -> next : nullptr;
                    tmp -> next = new_next;
                    if(new_next){
                        new_next->prev = tmp;
                    }
                    else {
                        tail = tmp;
                    }
                    delete eq_el;
                    --nodes_counter;
                }
                else {
                    tmp = tmp -> next;
                }
            }
        };

        Node *split(Node *node, size_type size){
            Node *tmp = node;
            size_type i = 1;
            while(tmp && i < size){
                tmp = tmp -> next;
                i++;
            }
            if(!tmp) return nullptr;
            Node *tmp_next = tmp -> next;
            tmp -> next = nullptr;
            // рвем связь, чтобы последнее значение подмассива не 
            // тащило за собой следующие узлы. Сортировка только подмассива
            return tmp_next;
        };

        Node *merge_sorted(Node *left, Node *right){
            if(!right) return left;
            Node *merged{nullptr}, *merged_res;
            if(left -> data > right -> data){
                merged = right;
                right = right -> next;
                merged -> next = nullptr;
                if(right) right -> prev = nullptr;
            }
            else{
                merged = left;
                left = left -> next;
                merged -> next = nullptr;
                if(left) left -> prev = nullptr;
            }
            merged_res = merged;
            while(left && right){
                if(left -> data > right -> data){
                    merged -> next = right;
                    right -> prev = merged;
                    merged = right;
                    right = right -> next;
                    if(right) right -> prev = nullptr;
                }
                else{
                    merged -> next = left;
                    left -> prev = merged;
                    merged = left;
                    left = left -> next;
                    merged -> next = nullptr;
                    if(left) left -> prev = nullptr;
                }
            }
            if(left){
                merged -> next = left;
                left -> prev = merged;
            }
            if(right){
                merged -> next = right;
                right -> prev = merged;
            }
            return merged_res;
        };

        void sort(){
            if(nodes_counter <= 1) return;
            Node *left{nullptr}, *right{nullptr}, *curr{nullptr};
            Node *sorted_head{nullptr}, *sorted_tail{nullptr};
            for(size_type i = 1; i < nodes_counter; i *= 2){
                curr = (i == 1 ? head : sorted_head), sorted_head = nullptr, sorted_tail = nullptr;
                while(curr){
                    left = curr;
                    right = split(left, i);
                    curr = split(right, i);
                    Node *merged_part = merge_sorted(left, right);
                    if(!sorted_head){
                        sorted_head = merged_part;
                        sorted_tail = merged_part;
                    } else{
                        sorted_tail -> next = merged_part;
                        merged_part -> prev = sorted_tail;
                    }
                    while(sorted_tail -> next){
                        sorted_tail = sorted_tail -> next;
                    }
                }
            }
            head = sorted_head;
            tail = sorted_tail;
        };

        // write tests
        template <typename... Args>
        iterator insert_many(const_iterator pos, Args&&... args){
            if(!pos.get_current()) throw std::invalid_argument("You try to splice other list into nullptr place");
            iterator res{nullptr};
            if(pos.get_current() != head){
                res = pos.get_prev();
            }
            (insert(pos, std::forward<Args>(args)), ...);
            return res.get_current() ? res.get_next() : iterator(head);
        };

        template <typename... Args>
        void insert_many_back(Args&&... args){
            (push_back(std::forward<Args>(args)), ...);
        };

        template <typename... Args>
        void insert_many_front(Args&&... args){
            (push_front(std::forward<Args>(args)), ...);
        };
    };

};

#endif