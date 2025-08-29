#ifndef S21_CPP_CONTAINER
#define S21_CPP_CONTAINER

#include <iostream>

namespace s21 {
template <typename T>
class container {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using key_type = T;

  virtual bool empty() const = 0;
  virtual size_type size() const = 0;

  virtual ~container() = default;
};
};  // namespace s21

#endif

