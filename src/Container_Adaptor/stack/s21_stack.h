#ifndef STACK
#define STACK

#include "../s21_queue_stack.h"

namespace s21 {
template <typename T>
class stack : public Common_q_s<T> {
 public:
  using typename container<T>::value_type;
  using typename container<T>::reference;
  using typename container<T>::const_reference;
  using typename container<T>::size_type;
  using Node = typename Common_q_s<T>::Node;

 private:
  Node *head{nullptr};

 public:
  stack() : head(nullptr) {};

  stack(std::initializer_list<value_type> const &items) {
    for (const_reference item : items) {
      push(item);
    }
  };

  void push(const_reference &value) {
    if (!head) {
      head = new Node(value);
    } else {
      Node *tmp = new Node(value);
      tmp->next = head;
      head = tmp;
    }
    Common_q_s<T>::nodes_counter++;
  };

  // отладочный!
  void read() {
    Node *tmp = head;
    while (tmp) {
      std::cout << tmp->data << ' ';
      tmp = tmp->next;
    }
    std::cout << std::endl;
  }

  stack(const stack &s) {
    Node *tmp = s.head;
    stack<T> tmp_stack;
    while (tmp) {
      tmp_stack.push(tmp->data);
      tmp = tmp->next;
    }
    tmp = tmp_stack.head;
    while (tmp) {
      push(tmp->data);
      tmp = tmp->next;
    }
  };

  stack(stack &&s) {
    this->head = s.head;
    s.head = nullptr;
    this->nodes_counter = s.nodes_counter;
    s.nodes_counter = 0;
  };

  stack &operator=(stack &&s) {
    if (this != &s) {
      while (head) {
        Node *tmp = head->next;
        delete head;
        head = tmp;
      }
      this->head = s.head;
      s.head = nullptr;
      this->nodes_counter = s.nodes_counter;
      s.nodes_counter = 0;
    }
    return *this;
  };

  ~stack() {
    while (head) {
      Node *tmp = head->next;
      delete head;
      head = tmp;
    }
  };

  const_reference top() {
    if (!head) throw std::out_of_range("Queue is empty");
    return head->data;
  };

  void pop() {
    if (!head) throw std::out_of_range("Queue is empty");
    Node *tmp = head;
    head = head->next;
    delete tmp;
    Common_q_s<T>::nodes_counter--;
  };

  void swap(stack &other) {
    std::swap(this->head, other.head);
    std::swap(this->nodes_counter, other.nodes_counter);
  };

  // Bonus part
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push(std::forward<Args>(args)), ...);
  };
};
};  // namespace s21

#endif