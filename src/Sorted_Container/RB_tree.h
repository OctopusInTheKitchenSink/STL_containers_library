#ifndef RB_TREE_H
#define RB_TREE_H
#include <iostream>

enum Color { red, black };
enum Side { left, right, null };
enum Error { error = 404 };
enum Container_type { not_multiset, multiset_ };

namespace {
template <typename T>  // функтор для set
struct get_key {
  const T &operator()(const T &value) const { return value; }
};

template <typename Key, typename Value>  // функтор для map
struct get_key<std::pair<Key, Value>> {
  const Key &operator()(const std::pair<Key, Value> &p) const {
    return p.first;
  }
};
}  // namespace

namespace s21 {

template <typename T>
class Red_black_tree {
 protected:
  struct Node {
    Node *left{nullptr};
    Node *right{nullptr};
    T data{0};
    Node *prev{nullptr};
    Color color{red};
    Node(T data, Node *prev = nullptr, Color col = red)
        : data(data), prev(prev), color(col) {};
    ~Node() = default;
  };
  Node *root{nullptr};

 public:
  Red_black_tree(Red_black_tree &&other) noexcept : root(other.root) {
    other.root = nullptr;
  }
  Red_black_tree &operator=(Red_black_tree &&other) noexcept {
    if (this != &other) {
      make_clean();
      root = other.root;
      other.root = nullptr;
    }
    return *this;
  }

  void swap(Red_black_tree &other) { std::swap(root, other.root); }
  class Map_iterator {
   private:
    Node *current{nullptr};

   public:
    Map_iterator(Node *p = nullptr) : current(p) {};

    Node *get_curr() const { return current; };

    Map_iterator operator++() {
      if (current == nullptr)
        throw std::out_of_range("You try to work with nullptr");
      if (current->right) {
        current = current->right;
        while (current->left) {
          current = current->left;
        }
      } else {
        Node *parent = current->prev;
        while (parent && current == parent->right) {
          current = parent;
          parent = current->prev;
        }
        current = parent;
      }
      return *this;
    };

    Map_iterator operator++(int d) {
      (void)d;
      Map_iterator tmp(current);
      ++(*this);
      return tmp;
    };

    Map_iterator operator--() {
      if (current == nullptr)
        throw std::out_of_range("You try to work with nullptr");
      if (current->left) {
        current = current->left;
        while (current->right) {
          current = current->right;
        }
      } else {
        Node *parent = current->prev;
        while (parent && current == parent->left) {
          current = parent;
          parent = current->prev;
        }
        current = parent;
      }
      return *this;
    };

    Map_iterator operator--(int d) {
      (void)d;
      Map_iterator tmp(current);
      --(*this);
      return tmp;
    };

    T &operator*() const {
      if (current == nullptr)
        throw std::out_of_range("You try to work with nullptr");
      return current->data;
    };

    bool operator!=(Map_iterator other) const {
      return current != other.current;
    };

    bool operator==(const Map_iterator &other) const {
      return current == other.current;
    };
  };

  class Iterator {
   private:
    const Node *current{nullptr};

   public:
    Iterator(const Node *p = nullptr) : current(p) {};

    const Node *get_curr() const { return current; };

    Iterator operator++() {
      if (current == nullptr)
        throw std::out_of_range("You try to work with nullptr");
      if (current->right) {
        current = current->right;
        while (current->left) {
          current = current->left;
        }
      } else {
        Node *parent = current->prev;
        while (parent && current == parent->right) {
          current = parent;
          parent = current->prev;
        }
        current = parent;
      }
      return *this;
    };

    Iterator operator++(int d) {
      (void)d;
      Iterator tmp(current);
      ++(*this);
      return tmp;
    };

    Iterator operator--() {
      if (current == nullptr)
        throw std::out_of_range("You try to work with nullptr");
      if (current->left) {
        current = current->left;
        while (current->right) {
          current = current->right;
        }
      } else {
        Node *parent = current->prev;
        while (parent && current == parent->left) {
          current = parent;
          parent = current->prev;
        }
        current = parent;
      }
      return *this;
    };

    Iterator operator--(int d) {
      (void)d;
      Iterator tmp(current);
      --(*this);
      return tmp;
    };

    const T &operator*() const {
      if (current == nullptr)
        throw std::out_of_range("You try to work with nullptr");
      return current->data;
    };

    bool operator!=(Iterator other) const { return current != other.current; };

    bool operator==(const Iterator &other) const {
      return current == other.current;
    };
  };

  Iterator get_start() const {
    if (!root) throw std::out_of_range("Дерева не существует!");
    Node *ptr = root;
    while (ptr->left) {
      ptr = ptr->left;
    }
    return Iterator(ptr);
  };

  Iterator get_end() const { return Iterator(nullptr); };

  Iterator get_iter_end() {
    if (!root) throw std::out_of_range("Дерева не существует");
    Node *ptr = root;
    while (ptr->right) {
      ptr = ptr->right;
    }
    return Iterator(ptr);
  };

  Red_black_tree() : root(nullptr) { Iterator(); };

  Red_black_tree(T data) {
    root = new Node(data, nullptr, black);
    Iterator();
  };

  void merge_nodes(Red_black_tree &other, size_t &counter,
                   Container_type tp = not_multiset) {
    Red_black_tree<T> q;
    for (auto t = other.get_start(); t != other.get_end(); ++t) {
      if (tp || (!root || !find_element(*t).second)) {
        q.insert_node(*t, tp);
        counter++;
      }
    }
    if (counter) {
      for (auto t = q.get_start(); t != q.get_end(); ++t) {
        insert_node(*t, tp);
        if (!tp) other.remove(t);
      }
      if (tp) other.make_clean();
      q.make_clean();
    }
  };

  ~Red_black_tree() {
    if (root) {
      make_clean();
    }
  };

  std::pair<Iterator, bool> find_element(const T &data) const {
    Node *tmp = root;
    bool flag = false;
    get_key<T> getKey;
    while (tmp && !flag) {
      if (getKey(tmp->data) > getKey(data)) {
        tmp = tmp->left;
      } else if (getKey(tmp->data) < getKey(data)) {
        tmp = tmp->right;
      } else if (getKey(tmp->data) == getKey(data)) {
        flag = true;
      }
    }
    return {(flag ? Iterator(tmp) : Iterator(nullptr)), flag};
  };

  std::pair<Map_iterator, bool> find_map_element(const T &data) {
    Node *tmp = root;
    bool flag = false;
    get_key<T> getKey;
    while (tmp && !flag) {
      if (getKey(tmp->data) > getKey(data)) {
        tmp = tmp->left;
      } else if (getKey(tmp->data) < getKey(data)) {
        tmp = tmp->right;
      } else if (getKey(tmp->data) == getKey(data)) {
        flag = true;
      }
    }
    return {(flag ? Map_iterator(tmp) : Map_iterator(nullptr)), flag};
  };

  std::pair<Node *, bool> insert_node(T data, Container_type t = not_multiset) {
    Node *curr = this->root ? root : nullptr;
    Node *parent = curr;
    get_key<T> getKey;
    while (curr) {
      parent = curr;
      if (t ? (getKey(data) >= getKey(curr->data))
            : (getKey(data) > getKey(curr->data))) {
        curr = curr->right;
      } else if (getKey(data) < getKey(curr->data)) {
        curr = curr->left;
      } else if (getKey(data) == getKey(curr->data)) {
        return {curr, false};  // обработать ситуацию с имеющимся узлом
      }
    }
    curr = new Node(data, parent);
    if (!parent)
      root = curr;
    else if (t ? getKey(curr->data) >= getKey(parent->data)
               : getKey(curr->data) > getKey(parent->data)) {
      parent->right = curr;
    } else {
      parent->left = curr;
    }
    balance(curr);
    return {curr, true};
  };

  bool remove(Iterator pos, Container_type t = not_multiset) {
    bool flag = false;
    auto rem = find_element(*pos);
    if (rem.second) {
      Node *tmp = const_cast<Node *>(t ? pos.get_curr() : rem.first.get_curr());
      if (tmp == root && !(tmp->right) && !(tmp->left)) {
        delete tmp;
        root = nullptr;
      } else
        delete_node(tmp);
      flag = true;
    }
    return flag;
  };

  void show_tree() {
    if (root) {
      show_tree(root->left);
      std::cout << root->data << ' ' << "(" << ((root->color) ? "black" : "red")
                << " - root)" << ' ';
      show_tree(root->right);
    }
  };

  void show_tree(Node *root) {
    if (root) {
      show_tree(root->left);
      std::cout << root->data << ' ' << "(" << ((root->color) ? "black" : "red")
                << ")" << " ";
      show_tree(root->right);
    }
  };

  void make_clean() {
    if (root) {
      make_clean(root->left);
      make_clean(root->right);
      delete root;
      root = nullptr;
    }
  };

  void make_clean(Node *root) {
    if (root) {
      make_clean(root->left);
      make_clean(root->right);
      delete root;
      root = nullptr;
    }
  };

  // гарантировано, что в multiset только первый же узел после нужного
  // может содержать в правых листьях повторяющиеся с искомым значения
  // ниже быть не может, потому что они больше предыдущего узла
  Iterator min_bound(const T &key) {
    Node *tmp = root, *potenc_min{nullptr};
    get_key<T> getKey;
    while (tmp) {
      if (getKey(tmp->data) == getKey(key)) {
        potenc_min = tmp;
        if (tmp->left)
          tmp = tmp->left;
        else
          break;
      } else {
        if (getKey(tmp->data) > getKey(key) && tmp->left) {
          tmp = tmp->left;
        } else if (tmp->right) {
          tmp = tmp->right;
        } else
          break;
      }
    }
    return potenc_min ? Iterator(potenc_min) : get_end();
  };

  std::pair<Iterator, size_t> max_bound(const T &key) {
    Iterator start = min_bound(key), end = get_iter_end();
    size_t counter{0};
    if (start.get_curr()) {
      while (*start == key) {
        counter++;
        if (start == end) return {get_end(), counter};
        start++;
      }
    }
    return {start, counter};
  }

  // работает как конструктор копирования
  void add_tree(const Red_black_tree &other) {
    if (other.root == nullptr) {
      root = nullptr;
      return;
    }
    root = new Node(other.root->data, nullptr, black);
    if (other.root->left) add_node(other.root->left, root, left);
    if (other.root->right) add_node(other.root->right, root, right);
  }

  bool operator!=(Red_black_tree other) { return (&root != &other.root); };

  size_t node_size() const { return sizeof(Node); };

 private:
  void add_node(Node *other_ptr, Node *prev, Side side) {
    Node *ptr = new Node(other_ptr->data, prev, other_ptr->color);
    side == left ? prev->left = ptr : prev->right = ptr;
    if (other_ptr->left) add_node(other_ptr->left, ptr, left);
    if (other_ptr->right) add_node(other_ptr->right, ptr, right);
  };

  void balance(Node *new_node) {
    // отец черный - все ок
    // отец красный + дядя красный - перекрашиваем и проверяем деда
    while (new_node != root && new_node->color == red &&
           (new_node->prev)->color == red) {
      Side type_parent, type_new_node = get_node_type(new_node);
      if (!(new_node->prev)->prev) break;
      type_parent = get_node_type(new_node->prev);
      Node *uncle = (type_parent == right ? ((new_node->prev)->prev)->left
                                          : (new_node->prev)->prev->right);
      Node *granpa = (new_node->prev)->prev;
      if (uncle && uncle->color == red) {
        uncle->color = black, (new_node->prev)->color = black;
        if (uncle->prev != root) {
          (uncle->prev)->color = red;
        }
        new_node = uncle->prev;
      } else {
        if (type_parent == left) {  // родитель - левый потомок деда
          if (type_new_node == right) {
            left_rotation(new_node->prev);  // вокруг родителя
            if (new_node == root) break;
            granpa = new_node->prev;
            right_rotation(granpa);  // вокруг деда
            new_node->color = black;
          } else {
            right_rotation(granpa);  // вокруг деда
            (new_node->prev)->color = black;
          }
        } else {
          if (type_new_node == left) {
            right_rotation(new_node->prev);  // вокруг родителя
            if (new_node == root) break;
            granpa = new_node->prev;
            left_rotation(granpa);  // вокруг деда
            new_node->color = black;
          } else {
            left_rotation(granpa);  // вокруг деда
            (new_node->prev)->color = black;
          }
        }
        if (granpa) (granpa)->color = red;
        if (new_node != root) new_node = new_node->prev;
      }
    }
    root->color = black;
  };

  Side get_node_type(Node *node) {
    if (!node || !(node->prev)) return null;
    return (((node->prev)->data > node->data) ? left : right);
  };

  Side reverse_node_side(Node *node) {
    if (!node || !(node->prev)) return null;
    return (((node->prev)->data < node->data) ? left : right);
  }

  void right_rotation(Node *node, bool flag = false) {
    Node *new_parent = node->left;
    if (node == root) root = new_parent;
    Node *gran_pa = node->prev;
    Node *tmp_right = new_parent->right;
    Side side = get_node_type(node);
    (void)flag;
    new_parent->right = node;
    node->prev = new_parent;
    switch (side) {
      case (right):
        gran_pa->right = new_parent;
        break;
      case (left):
        gran_pa->left = new_parent;
        break;
      default:
        break;
    }
    if (new_parent == root)
      new_parent->prev = nullptr;
    else
      new_parent->prev = gran_pa;
    node->left = tmp_right;
    if (tmp_right) tmp_right->prev = node;
  };

  void left_rotation(Node *node, bool flag = false) {
    Node *new_parent = node->right;
    Node *tmp_left = new_parent->left;
    Node *gran_pa = node->prev;
    if (node == root) root = new_parent;
    Side side = !flag ? get_node_type(node) : reverse_node_side(node);
    switch (side) {
      case (left):
        gran_pa->left = new_parent;
        break;
      case (right):
        gran_pa->right = new_parent;
        break;
      default:
        break;
    }
    if (new_parent == root)
      new_parent->prev = nullptr;
    else
      new_parent->prev = gran_pa;
    new_parent->left = node;
    node->prev = new_parent;
    node->right = tmp_left;
    if (tmp_left) tmp_left->prev = node;
  };

  Node *find_successor(Node *n, bool &flag) {
    if (n->left) {
      n = n->left;
      while (n) {
        if (!(n->right)) break;
        n = n->right;
        flag = true;
      }
    } else if (n->right) {
      n = n->right;
      while (n) {
        if (!(n->left)) break;
        n = n->left;
      }
    }
    return n;
  };

  void del_node_without_child(Node *node, bool flag = false) {
    if (node->color == red) {  // красный узел
      if ((!flag ? get_node_type(node) : reverse_node_side(node)) == right) {
        (node->prev)->right = nullptr;
      } else {
        (node->prev)->left = nullptr;
      }
    } else {
      if ((!flag ? get_node_type(node) : reverse_node_side(node)) == right) {
        (node->prev)->right = nullptr;
      } else {
        (node->prev)->left = nullptr;
      }
      fix_deletion(node, flag);
    }
    delete node;
  };

  void del_node_with_one_child(
      Node *tmp,
      bool flag = true) {  // родитель точно черный, ребенок точно красный
    if (tmp->left) {       // только левый потомок (черный с красным потомком)
      Side side = flag ? get_node_type(tmp) : reverse_node_side(tmp);
      if (side == right) {  // удаляемый узел правый
        (tmp->prev)->right = tmp->left;
      } else if (side == left) {  // удаляемый узел левый
        (tmp->prev)->left = tmp->left;
      }
      (tmp->left)->color = black;
      if (tmp == root) root = tmp->left;
    } else if (tmp->right) {  // только правый потомок (черный с красным
                              // потомком)
      (tmp->right)->prev = tmp->prev;
      Side side = flag ? get_node_type(tmp) : reverse_node_side(tmp);
      if (side == right) {  // удаляемый узел правый
        (tmp->prev)->right = tmp->right;
      } else if (side == left) {  // удаляемый узел левый
        (tmp->prev)->left = tmp->right;
      }
      (tmp->right)->color = black;
      if (tmp == root) root = tmp->right;
    }
    delete tmp;
  };

  void delete_node(Node *tmp) {
    if (tmp->left && tmp->right) {  // два потомка
      bool flag = false;
      Node *successor = find_successor(
          tmp, flag);  // true если поиск нормальный false если поиск наоборот
      std::swap(tmp->data, successor->data);
      if (!(successor->left) && !(successor->right)) {
        del_node_without_child(successor, !flag);
      } else {
        del_node_with_one_child(successor, flag);
      }
    } else if (tmp->left || tmp->right) {  // один потомок
      del_node_with_one_child(tmp);
    } else {  // ни одного потомка
      del_node_without_child(tmp);
    }
  };

  void fix_deletion(Node *node, bool flag) {
    Node *parent = node->prev;  // родитель удаляемого узла
    Node *brother = nullptr;    // брат удаляемого узла
    if ((flag ? reverse_node_side(node) : get_node_type(node)) == left &&
        parent->right) {
      brother = parent->right;
      if (brother->color == red) {
        parent->color = red;
        brother->color = black;
        if (parent->right->data > parent->data) flag = false;
        left_rotation(parent, flag);
        parent = node->prev;
        brother = parent->right;
      }
      if (brother->color == black) {
        if (brother->left && (brother->left)->color == red &&
            (!brother->right || (brother->right)->color == black)) {
          std::swap((brother->left)->color, brother->color);
          right_rotation(brother, flag);
          parent = node->prev;
          brother = parent->right;
        }
        if (brother->right && (brother->right)->color == red) {
          brother->color = parent->color;
          parent->color = black;
          (brother->right)->color = black;
          left_rotation(parent);
        } else if ((!(brother->left) || (brother->left)->color == black) &&
                   ((!brother->right) || (brother->right)->color == black)) {
          brother->color = red;
          if (parent->color == red) parent->color = black;
        }
      }
    } else if (parent && parent->left) {
      brother = parent->left;
      if (brother->color == red) {
        parent->color = red;
        brother->color = black;
        if (parent->left->data < parent->data) flag = false;
        right_rotation(parent, flag);
        parent = node->prev;
        brother = parent->left;
      }
      if (brother->color == black) {
        if (brother->right && (brother->right)->color == red &&
            (!brother->left || (brother->left)->color == black)) {
          std::swap((brother->right)->color, brother->color);
          left_rotation(brother, flag);
          parent = node->prev;
          brother = parent->left;
        }
        if (brother->left && (brother->left)->color == red) {
          brother->color = parent->color;
          parent->color = black;
          (brother->left)->color = black;
          right_rotation(parent, flag);
        } else if ((!(brother->left) || (brother->left)->color == black) &&
                   ((!brother->right) || (brother->right)->color == black)) {
          brother->color = red;
          if (parent->color == red) {
            parent->color = black;
          } else {
            fix_deletion(parent, flag);
          }
        }
      }
    }
  };
};
};  // namespace s21
#endif
