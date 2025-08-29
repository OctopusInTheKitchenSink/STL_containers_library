#include <iostream>
#include <limits>
#include <utility>  // std::pair

#include "../../Sequence_Containers/vector/s21_vector.h"
#include "../RB_tree.h"
#include "../s21_set_map.h"

namespace s21 {
template <typename Key, typename T>
class map : public Common_s_m<std::pair<Key, T>> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<Key, T>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Red_black_tree<value_type>::Iterator;
  using size_type = size_t;

 private:
  Red_black_tree<value_type> tree;
  size_type size_ = 0;

 public:
  map() : tree(), size_(0){};
  map(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      tree.insert_node(item);
      size_++;
    }
  }
  map(const map &other) {
    tree.add_tree(other.tree);
    size_ = other.size_;
  }
  map(map &&m) noexcept : tree(std::move(m.tree)), size_(m.size_) {
    m.size_ = 0;
  }
  ~map() {
    clear();
    size_ = 0;
  }

  iterator begin() const override { return tree.get_start(); }
  iterator end() const override { return tree.get_end(); }

  T &at(const Key &key) {
    value_type tmp(key, T{});
    auto [it, found] = tree.find_map_element(tmp);
    if (!found) {
      throw std::out_of_range("Ключ не найден");  // GCOVR_EXCL_LINE
    }
    return (*it).second;
  }

  T &operator[](const Key &key) {
    value_type temp(key, T{});
    auto result = tree.insert_node(temp);
    if (result.second) size_++;
    return result.first->data.second;
  }

  map &operator=(map &&m) {
    if (this != &m) {
      tree = std::move(m.tree);
      size_ = m.size_;
      m.size_ = 0;
    }
    return *this;
  }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / tree.node_size();
  }
  void clear() {
    tree.make_clean();
    size_ = 0;
  }
  std::pair<iterator, bool> insert(const value_type &value) {
    auto result = tree.insert_node(value);
    if (result.second) size_++;
    return result;
  }
  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    value_type tmp(key, obj);
    auto result = tree.insert_node(tmp);
    if (result.second) size_++;
    return result;
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    value_type tmp(key, T{});
    auto result = tree.find_map_element(tmp);

    if (result.second) {
      (*result.first).second = obj;
      return {iterator(result.first.get_curr()), false};
    } else {
      auto insert_result = tree.insert_node(value_type(key, obj));
      if (insert_result.second) size_++;
      return {iterator(insert_result.first), true};
    }
  }

  void erase(iterator pos) override {
    tree.remove(pos);
    size_--;
  }

  iterator end_iter() { return tree->get_iter_end(); };

  void swap(map &other) {
    tree.swap(other.tree);
    std::swap(this->size_, other.size_);
  }

  void merge(map &other) {
    tree.merge_nodes(other.tree, size_);
    other.size_ = 0;
  }
  bool contains(const Key &key) const {
    value_type tmp(key, T{});
    return tree.find_element(tmp).second;
  }

  template <typename... Args>
  typename s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> result;
    (result.push_back(this->insert(std::forward<Args>(args))), ...);

    return result;
  }
};

}  // namespace s21
