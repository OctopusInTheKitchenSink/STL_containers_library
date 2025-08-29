#ifndef QUEUE
#define QUEUE

#include "../s21_queue_stack.h"

namespace s21 {
template <typename T>
class queue : public Common_q_s<T> {
 public:
  using typename container<T>::value_type;
  using typename container<T>::reference;
  using typename container<T>::const_reference;
  using typename container<T>::size_type;
  using Node = typename Common_q_s<T>::Node;

 private:
  Node *tail{nullptr};
  Node *head{nullptr};

 public:
  queue() : tail(nullptr), head(nullptr) {};

  queue(std::initializer_list<value_type> const &items) {
    for (const_reference item : items) {
      push(item);
    }
  };

  void push(const_reference &value) {
    if (tail == head && !head) {
      tail = new Node(value);
      head = tail;
    } else {
      tail->next = new Node(value);
      tail = tail->next;
    }
    Common_q_s<T>::nodes_counter++;
  };

  queue(const queue &q) {
    Node *tmp = q.head;
    while (tmp) {
      push(tmp->data);
      tmp = tmp->next;
    }
  };

  queue(queue &&q) {
    this->head = q.head;
    q.head = nullptr;
    this->tail = q.tail;
    q.tail = nullptr;
    this->nodes_counter = q.nodes_counter;
    q.nodes_counter = 0;
  };

  // отладочный!
  void check_elements() {
    Node *tmp = head;
    while (tmp) {
      std::cout << tmp->data << ' ';
      tmp = tmp->next;
    }
    std::cout << std::endl;
  };

  ~queue() {
    while (head) {
      Node *tmp = head;
      head = head->next;
      delete tmp;
    }
  };

  queue &operator=(queue &&q) {
    if (this != &q) {
      while (head) {
        Node *tmp = head;
        head = head->next;
        delete tmp;
      }
      this->head = q.head;
      q.head = nullptr;
      this->tail = q.tail;
      q.tail = nullptr;
      this->nodes_counter = q.nodes_counter;
      q.nodes_counter = 0;
    }
    return *this;
  };

  const_reference front() {
    if (!head) throw std::out_of_range("Queue is empty");
    return head->data;
  };

  const_reference back() {
    if (!tail) throw std::out_of_range("Queue is empty");
    return tail->data;
  };

  void pop() {
    if (!head) throw std::out_of_range("Queue is empty");
    Node *tmp = head;
    head = head->next;
    delete tmp;
    Common_q_s<T>::nodes_counter--;
  };

  void swap(queue &other) {
    std::swap(this->tail, other.tail);
    std::swap(this->head, other.head);
    std::swap(this->nodes_counter, other.nodes_counter);
  };

  // Bonus part
  // std::forward передает значения как они есть,
  // то есть гарантирует perfect forvarding
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push(std::forward<Args>(args)), ...);
  };
};
};  // namespace s21

#endif