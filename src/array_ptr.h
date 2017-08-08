#include <memory>

template <typename T>
class array_ptr {
public:
  using value_type = T;
  using allocator_type = std::allocator<T>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = typename std::allocator_traits<allocator_type>::pointer;
  using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;
  using iterator = T*;
  using const_iterator = T* const;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
  value_type* m_arr;
  size_type m_size;

public:

  array_ptr() : m_arr{nullptr}, m_size{0}
  {}
  array_ptr(std::size_t size) : m_arr{new value_type[size]}, m_size{size}
  {}

  array_ptr(const array_ptr& other) : m_arr{other.m_arr}, m_size{other.m_size}
  {}

  array_ptr& operator=(const array_ptr& other) {
    this->m_arr = other.m_arr;
    this->m_size = other.m_size;
    return *this;
  }

  reference at(size_type pos) const {
    if (pos < size()) {
      return (*this)[pos];
    }
    throw std::out_of_range("index out of bounds");
  }

  reference operator[](size_type pos) const {
    return m_arr[pos];
  }

  reference front() const {
    return *this->begin();
  }

  reference back() const {
    auto tmp = this->end();
    --tmp;
    return *tmp;
  }

  T* data() noexcept {
    return m_arr;
  }

  const T* data() const noexcept {
    return m_arr;
  }

  iterator begin() noexcept {
    return m_arr;
  }

  const_iterator begin() const noexcept {
    return m_arr;
  }

  const_iterator cbegin() const noexcept {
    return m_arr;
  }

  iterator end() noexcept {
    return m_arr + size();
  }

  const_iterator end() const noexcept {
    return m_arr + size();
  }

  const_iterator cend() const noexcept {
    return m_arr + size();
  }

  bool empty() const noexcept {
    return size() == 0;
  }

  size_type size() const noexcept {
    return m_size;
  }

  size_type max_size() const noexcept {
    return size();
  }

  void clear() noexcept {
    delete[] m_arr;
    m_size = 0;
  }

  void resize(size_type count) {
    resize(count, {});
  }

  void resize(size_type count, const value_type& value) {
    if ((!m_arr) || (size() == 0)) {
      m_arr = new T[count]{value};
    }

    else if (size() > count) {
      allocator_type a;
      T* new_arr = a.allocate(count);
      std::uninitialized_copy_n(m_arr, count, new_arr);
      delete[] m_arr;
      m_arr = new_arr;
    }

    else if (size() < count) {
      allocator_type a;
      T* new_arr = a.allocate(count);
      std::uninitialized_copy_n(m_arr, size(), new_arr);
      delete[] m_arr;
      std::uninitialized_fill(new_arr+size(), new_arr+count, value);
      m_arr = new_arr;
    }
    m_size = count;
  }
};

template<typename T>
bool operator==(const array_ptr<T>& lhs,
                const array_ptr<T>& rhs)
{
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T>
bool operator!=(const array_ptr<T>& lhs,
                const array_ptr<T>& rhs)
{
  return !(lhs == rhs);
}

template<typename T>
bool operator<(const array_ptr<T>& lhs,
               const array_ptr<T>& rhs)
{
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}


template<typename T>
bool operator>(const array_ptr<T>& lhs,
               const array_ptr<T>& rhs)
{
  return rhs < lhs;
}

template<typename T>
bool operator<=(const array_ptr<T>& lhs,
                const array_ptr<T>& rhs) {
  return !(lhs > rhs);
}

template<typename T>
bool operator>=(const array_ptr<T>& lhs,
                const array_ptr<T>& rhs) {
  return !(lhs < rhs);
}
