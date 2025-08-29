#ifndef VECTOR_H
#define VECTOR_H

#include "../vector_list.h"

namespace s21 {
enum { start_size = 20 };
template <typename T>
class vector : public Vector_list<T> {
 public:
  using typename container<T>::value_type;
  using typename container<T>::reference;
  using typename container<T>::const_reference;
  using typename container<T>::size_type;

 private:
  size_type size_{0}, capacity_{0};
  T *vec{nullptr};
  class VectorIterator {
   private:
    T *curr_ptr{nullptr};

   public:
    VectorIterator(T *ptr = nullptr) : curr_ptr(ptr) {};

    VectorIterator &operator++() {
      ++curr_ptr;
      return *this;
    };

    VectorIterator &operator++(int) {
      VectorIterator tmp(curr_ptr);
      ++curr_ptr;
      return *tmp;
    };

    VectorIterator &operator--() {
      --curr_ptr;
      return *this;
    };

    VectorIterator &operator--(int) {
      VectorIterator tmp(curr_ptr);
      --curr_ptr;
      return *tmp;
    };

    T *get_curr() const { return curr_ptr; };

    T &operator*() { return *curr_ptr; };

    bool operator!=(const VectorIterator &other) const {
      return curr_ptr != other.curr_ptr;
    };

    bool operator==(const VectorIterator &other) const {
      return curr_ptr == other.curr_ptr;
    };
  };

 public:
  using iterator = VectorIterator;
  using const_iterator = VectorIterator;
  vector() = default;

  vector(size_type n) : size_(n), capacity_(n), vec(new T[n]()) {};

  vector(std::initializer_list<value_type> const &items) {
    vec = new T[start_size]();
    capacity_ = start_size;
    for (auto item : items) {
      push_back(item);
    }
  };

  vector(const vector &v) {
    capacity_ = v.capacity_;
    size_ = v.size_;
    vec = new T[capacity_];
    for (size_type i = 0; i < v.size_; ++i) {
      vec[i] = v.vec[i];
    }
  };

  vector(vector &&v) {
    capacity_ = v.capacity_;
    size_ = v.size_;
    vec = v.vec;
    v.vec = nullptr;
    v.capacity_ = 0;
    v.size_ = 0;
  };

  ~vector() {
    delete[] vec;
    vec = nullptr;
    capacity_ = 0;
    size_ = 0;
  };

  vector &operator=(vector &&v) {
    if (this != &v) {
      delete[] vec;
      capacity_ = v.capacity_;
      size_ = v.size_;
      v.capacity_ = 0;
      v.size_ = 0;
      vec = v.vec;
      v.vec = nullptr;
    }
    return *this;
  };

  reference at(size_type pos) {
    if (pos >= capacity_ || pos < 0)
      throw std::out_of_range("You try to access to element out of range");
    return vec[pos];
  };

  reference operator[](size_type pos) { return vec[pos]; };

  T *data() { return vec; };

  iterator begin() { return iterator(vec); };

  iterator end() { return iterator(&vec[size_ - 1]); };

  virtual bool empty() const override { return !size_; };

  virtual size_type size() const override { return size_; };

  virtual size_type max_size() override {
    return std::numeric_limits<size_type>::max() / sizeof(T);
  };

  void reserve(size_type size) {
    if (size > capacity_) {
      capacity_ = size;
      T *new_vec = new T[capacity_];
      for (size_type i = 0; i < size_; ++i) {
        new_vec[i] = vec[i];
      }
      delete[] vec;
      vec = new_vec;
      new_vec = nullptr;
    }
  };

  size_type capacity() { return capacity_; };

  void shrink_to_fit() {
    if (size_ != capacity_) {
      T *new_vec = new T[size_];
      for (size_type i = 0; i < size_; ++i) {
        new_vec[i] = vec[i];
      }
      delete[] vec;
      vec = new_vec;
      new_vec = nullptr;
      capacity_ = size_;
    }
  };

  virtual void clear() override {
    for (size_type i = 0; i < size_; ++i) {
      vec[i].~T();
      vec[i] = T();
    }
    size_ = 0;
  };

 private:
  std::pair<bool, size_type> check_pos(iterator &pos) {
    if (pos.get_curr() < begin().get_curr() ||
        pos.get_curr() > &vec[capacity_ - 1])
      return {false, 0};
    if (pos == begin()) return {true, 0};
    return {true, pos.get_curr() - begin().get_curr()};
  };

  void resize() {
    capacity_ = capacity_ ? capacity_ * 2 : start_size;
    T *new_vec = new T[capacity_]();
    for (size_type i = 0; i < size_; ++i) {
      new_vec[i] = vec[i];
    }
    delete[] vec;
    vec = new_vec;
  };

 public:
  iterator insert(iterator pos, const_reference value) {
    std::pair<bool, size_type> res = check_pos(pos);
    if (!res.first)
      throw std::out_of_range("Try to access element out of range");
    if (size() + 1 >= capacity()) resize();
    size_type i = size();
    for (; i > res.second; --i) {
      vec[i] = vec[i - 1];
    }
    vec[i] = value;
    ++size_;
    return iterator(&vec[i]);
  };

  void erase(iterator pos) {
    std::pair<bool, size_type> res = check_pos(pos);
    if (!res.first || !size())
      throw std::out_of_range("Try to access element out of range");
    T *tmp = pos.get_curr();
    while (pos != end()) {
      *tmp = *(++pos);
      ++tmp;
    }
    --size_;
  };

  virtual const_reference front() override {
    if (!size_) throw std::logic_error("front() called to empty vector");
    return vec[0];
  };

  virtual const_reference back() override {
    if (!size_) throw std::logic_error("back() called to empty vector");
    return vec[size_ - 1];
  };

  virtual void push_back(const_reference value) override {
    if (!capacity_) resize();
    if (size_ + 1 == capacity_) resize();
    vec[size_] = value;
    ++size_;
  };

  virtual void pop_back() override {
    if (!size_) throw std::out_of_range("pop_back() called to empty vector");
    --size_;
  };
};
};  // namespace s21

#endif