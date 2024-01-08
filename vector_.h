#ifndef __vector_h__
#define __vector_h__

#include <vector>
#include <iostream>

template <typename T>
class vector_ {
public:
  vector_() : vector_(0) {}
  vector_(int n) : data_(n) {}

  vector_(const std::initializer_list<T> &li) {
    for (auto el : li) {
      data_.push_back(el);
    }
  }

  void push_back(T value) { data_.push_back(value); }

  T at(size_t index) const {
    check(index);
    return data_.at(index);
  }
  T operator[](int index) const { // int val = v[3];
    check(index);
    return data_[index];
  }
  T &operator[](int index) { // v[3] = 7;
    check(index);
    return data_[index];
  }

  int size() const { return data_.size(); }

  bool empty() const { return data_.empty(); }
  
  bool is_zero() const {
    for (int i = 0; i < size(); ++i) {
      if (data_[i] != 0) {
        return false;
      }
    }
    return true;
  }

  void resize(int n) { data_.resize(n); }

  friend vector_<T> operator+(const vector_<T> &a,
                              const vector_<T> &b) {
    if (a.size() != b.size())
      throw std::runtime_error("vector_s must be the same size");
    vector_<T> result;
    for (size_t i = 0; i < b.size(); ++i) {
      result.push_back(a[i] + b[i]);
    }
    return result;
  }

  vector_<T> &operator+=(const vector_<T> &other) {
    if (size() != other.size()) {
      throw std::runtime_error("vector_s must be the same size");
    }
    for (size_t i = 0; i < size(); ++i) {
      data_[i] += other[i];
    }
    return *this;
  }

  vector_<T> &operator-=(const vector_<T> &other) {
    if (size() != other.size()) {
      throw std::runtime_error("vector_s must be the same size");
    }
    for (size_t i = 0; i < size(); ++i) {
      data_[i] -= other[i];
    }
    return *this;
  }

  friend vector_<T> operator-(const vector_<T> &a, vector_<T> &b) { return a + -b; } // b is NOT const

  vector_<T> operator-() {
    vector_<T> result;
    for (size_t i = 0; i < size(); ++i) {
      result.push_back(-data_[i]);
    }
    return result;
  }

  bool operator==(const vector_<T> &other) const {
    if (this->size() != other.size())
      throw std::runtime_error("vector_s must be the same size");
    for (size_t i = 0; i < this->size(); ++i) {
      if (at(i) != other.at(i))
        return false;
    }
    return true;
  }

  bool operator!=(const vector_<T> &other) const { return !(*this == other); }

  bool is_enough_for(const vector_<T> &request) const {
    if (this->size() != request.size()) {
      throw std::runtime_error("Vectors must be the same size to compare");
    }
    for (size_t i = 0; i < this->size(); ++i) {
      if (data_[i] < request[i]) {
        return false;
      }
    }
    return true;
  }

  friend bool operator<(const vector_<T> &a,
                        const vector_<T> &b) {
    if (a.size() != b.size())
      throw std::runtime_error("vector_s must be the same size");
    for (size_t i = 0; i < a.size(); ++i) {
      if (a[i] >= b[i]) {
        return false;
      }
    }
    return true;
  }

  friend bool operator<=(const vector_<T> &a, const vector_<T> &b) { return !(b < a); }
  friend bool operator>=(const vector_<T> &a, const vector_<T> &b) { return !(a < b); }

  typename std::vector<T>::const_iterator begin() const { return data_.begin(); }
  typename std::vector<T>::const_iterator end() const { return data_.end(); }
  typename std::vector<T>::iterator begin() { return data_.begin(); }
  typename std::vector<T>::iterator end() { return data_.end(); }

  friend std::istream &operator>>(std::istream &is, vector_<T> &v) { // v must be initialized with desired size
    T val;
    int size = v.size();
    v.resize(0);

    for (int i = 0; i < size; ++i) {
      is >> val;
      // std::cout << "i is: " << i << " and val is: " << val << "\n";
      v.push_back(val);
    }
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const vector_ &v) {
    T val = T();
    for (int i = 0; i < v.size(); ++i) {
      if (v[i] == val) {
        os << "-";
      }else{
        os << v[i];
      }
      if (i < v.size() - 1) {
        os << "  ";
      }
    }
    return os;
  }

  static void run_tests() {
    vector_<int> v = {
        1,
        2,
        3};
    vector_<int> u = {
        1,
        1,
        2};
    vector_<int> v_plus_u = v + u;
    vector_<int> neg_v = -v;
    std::cout << "v is: " << v << "\n";
    std::cout << "u is: " << u << "\n";
    std::cout << u << " - " << v << " = " << u - v << "\n";
    std::cout << v << " + " << u << " = " << v + u << "\n";
    std::cout << "-" << u << " = " << -u << "\n";
  }

private:
  void check(int index) const {
    if (index >= data_.size())
      throw std::out_of_range("Index out of range");
  }

  std::vector<T> data_;
};

#endif