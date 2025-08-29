#ifndef SET
#define SET

#include "../RB_tree.h"
#include "../s21_set_map.h"

namespace s21 {
template <typename T>
class set : public Common_s_m<T> {
 public:
  using typename container<T>::key_type;
  using typename container<T>::value_type;
  using typename container<T>::reference;
  using typename container<T>::const_reference;
  using typename container<T>::size_type;
  using typename Common_s_m<T>::iterator;
  using typename Common_s_m<T>::const_iterator;

 private:
  Red_black_tree<T> *tree{nullptr};
  size_type nodes_counter{0};

 public:
  set() : tree(new Red_black_tree<T>()), nodes_counter(0){};

  set(std::initializer_list<value_type> const &items) {
    tree = new Red_black_tree<T>();  
    for (const_reference item : items) {
      auto res = tree->insert_node(item);
      if (res.second) nodes_counter++;
    }
  };

  set(const set &s) {
    tree = new Red_black_tree<T>();  
    nodes_counter = 0;
    if (!s.empty()) {
      tree->add_tree(*(s.tree));
      nodes_counter = s.nodes_counter;
    }
  };

  set(set &&s) {
    tree = s.tree;
    s.tree = nullptr;
    nodes_counter = s.nodes_counter;
    s.nodes_counter = 0;
  };

  ~set() {
    if (tree) {
      delete tree;  
    }
  };

  const set &operator=(const set &s) {
    if (this != &s && !s.empty()) {
      if (!empty()) {
        clear();
      }
      tree->add_tree(*(s.tree));
      nodes_counter = s.nodes_counter;
    }
    return *this;
  };

  set &operator=(set &&s) {
    if (this != &s && s.tree) {
      if (tree) {
        delete tree;  
      }
      tree = s.tree;
      s.tree = nullptr;
      nodes_counter = s.nodes_counter;
      s.nodes_counter = 0;
    }
    return *this;
  };

  virtual iterator begin() const override {
    return empty() ? iterator(nullptr) : tree->get_start();
  };

  // для удобства
  iterator end_iter() const {
    return empty() ? iterator(nullptr) : tree->get_iter_end();
  };

  virtual iterator end() const override {
    return empty() ? iterator(nullptr) : tree->get_end();
  };

  virtual bool empty() const override { return nodes_counter == 0; };

  virtual size_type size() const override { return nodes_counter; };

  virtual size_type max_size() const override {
    return std::numeric_limits<size_type>::max() / tree->node_size();
  };

  virtual void clear() override {
    tree->make_clean();
    nodes_counter = 0;
  };

  std::pair<iterator, bool> insert(const value_type &value) {
    auto result = tree->insert_node(value);
    if (result.second) nodes_counter++;
    return {iterator(result.first), result.second};
  };

  virtual void erase(iterator pos) override {
    if (empty()) {
      throw std::out_of_range("Дерево пустое");  
    }
    if (!pos.get_curr())
      throw std::logic_error(
          "You try to erase empty position");  
    if (tree->remove(pos)) nodes_counter--;
  };

  void swap(set &other) {
    std::swap(tree, other.tree);
    std::swap(nodes_counter, other.nodes_counter);
  };

  void merge(set &other) {
    size_t counter = 0;
    tree->merge_nodes(*other.tree, counter);
    nodes_counter += counter;
    other.nodes_counter -= counter;
  };

  iterator find(const T &key) const {
    auto res = tree->find_element(key);
    return iterator(res.first);
  };

  bool contains(const T &key) const {
    auto res = tree->find_element(key);
    return res.second;
  };

  // для вывода
  void show() const { tree->show_tree(); };

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
