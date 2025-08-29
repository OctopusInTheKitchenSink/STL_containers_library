#ifndef MULTISET
#define MULTISET

#include "../RB_tree.h"
#include "../s21_set_map.h"

namespace s21 {
template <typename T>
class multiset : public Common_s_m<T> {
 public:
  using typename container<T>::key_type;
  using typename container<T>::value_type;
  using typename container<T>::reference;
  using typename container<T>::const_reference;
  using typename container<T>::size_type;
  using typename Common_s_m<T>::iterator;
  using typename Common_s_m<T>::const_iterator;

 private:
  Red_black_tree<key_type> *tree{nullptr};
  size_type nodes_counter{0};

 public:
  multiset() : tree(new Red_black_tree<T>) {};

  multiset(std::initializer_list<value_type> const &items) {
    tree = new Red_black_tree<T>;
    for (const_reference item : items) {
      tree->insert_node(item, multiset_);
      nodes_counter++;
    }
  };

  multiset(const multiset &ms) {
    tree = new Red_black_tree<T>;
    if (!ms.empty()) {
      tree->add_tree(*ms.tree);
      nodes_counter = ms.nodes_counter;
    }
  };

  void show() const { tree->show_tree(); };

  multiset(multiset &&ms) {
    tree = ms.tree;
    ms.tree = nullptr;
    nodes_counter = ms.nodes_counter;
    ms.nodes_counter = 0;
  };

  ~multiset() {
    if (tree) {
      delete tree;
    }
  };

  multiset &operator=(multiset &&ms) {
    if (this != &ms && ms.tree) {
      if (tree) {
        delete tree;
      }
      tree = ms.tree;
      ms.tree = nullptr;
      nodes_counter = ms.nodes_counter;
      ms.nodes_counter = 0;
    }
    return *this;
  };

  virtual iterator begin() const override {
    return empty() ? iterator(nullptr) : tree->get_start();
  };

  const iterator end_elem() const { return tree->get_iter_end(); };

  virtual iterator end() const override { return tree->get_end(); };

  // для удобства
  iterator end_iter() const {
    return empty() ? iterator(nullptr) : tree->get_iter_end();
  };

  virtual bool empty() const override { return !nodes_counter; };

  virtual size_type size() const override { return nodes_counter; };

  virtual size_type max_size() const override {
    return std::numeric_limits<size_type>::max() / tree->node_size();
  };

  virtual void clear() override {
    if (tree) {
      tree->make_clean();
      nodes_counter = 0;
    }
  };

  std::pair<iterator, bool> insert(const value_type &value) {
    if (!tree) tree = new Red_black_tree<T>;
    auto res = tree->insert_node(value, multiset_);
    nodes_counter++;
    return res;
  };

  virtual void erase(iterator pos) override {
    if (empty()) {
      throw std::out_of_range("The tree is empty");
    }
    if (!pos.get_curr())
      throw std::logic_error("You try to erase empty position");
    if (tree->remove(pos, multiset_)) nodes_counter--;
  };

  void swap(multiset &other) {
    std::swap(tree, other.tree);
    std::swap(nodes_counter, other.nodes_counter);
  };

  void merge(multiset &other) {
    size_t counter = 0;
    tree->merge_nodes(*other.tree, counter, multiset_);
    nodes_counter += counter;
    other.nodes_counter -= counter;
  };

  size_type count(const_reference key) const {
    return empty() ? 0 : tree->max_bound(key).second;
  };

  const iterator find(const_reference key) const {
    return tree->find_element(key).first;
  };

  bool contains(const_reference key) const {
    return tree->find_element(key).second;
  };

  std::pair<iterator, iterator> equal_range(const_reference key) const {
    return {lower_bound(key), upper_bound(key)};
  };

  iterator lower_bound(const_reference key) const {
    return empty() ? end() : tree->min_bound(key);
  };

  iterator upper_bound(const_reference key) const {
    return empty() ? end() : tree->max_bound(key).first;
  };

  // Bonus part
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> vec;
    (vec.push_back(insert(std::forward<Args>(args))), ...);
    return vec;
  };
};
};  // namespace s21

#endif
