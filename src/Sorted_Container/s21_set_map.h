#ifndef SET_MAP_COMMON
#define SET_MAP_COMMON

#include <limits>

#include "../Sequence_Containers/vector/s21_vector.h"
#include "../container/s21_container.h"

namespace s21 {
template <typename T>
class Common_s_m : public container<T> {
 public:
  using iterator = typename Red_black_tree<T>::Iterator;
  using const_iterator = typename Red_black_tree<T>::Iterator;
  using typename container<T>::value_type;
  using typename container<T>::size_type;
  virtual iterator begin() const = 0;
  virtual iterator end() const = 0;
  virtual size_type max_size() const = 0;
  virtual void clear() = 0;
  virtual void erase(iterator pos) = 0;
};
};  // namespace s21

#endif

