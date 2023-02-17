#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

constexpr auto NCOLS = 10;

template <typename E1, typename E2> struct VectorSum {
  E1 const *x;
  E2 const *y;

  VectorSum(E1 const &x, E2 const &y) : x(&x), y(&y) {}

  auto size() const { return x->size(); }

  auto operator[](std::size_t idx) const {
    return x->operator[](idx) + y->operator[](idx);
  }
};

template <typename T> struct Vector {
  std::vector<T> data;

  Vector() = default;

  explicit Vector(std::vector<T> xs) : data{std::move(xs)} {}

  template <typename E> Vector(E &&expr) {
    data.reserve(expr.size());
    for (std::size_t idx = 0; idx < expr.size(); ++idx) {
      data.push_back(expr[idx]);
    }
  }

  auto operator[](std::size_t idx) const { return data[idx]; }

  auto size() const { return data.size(); }

  auto to_string() const {
    std::string s;
    for (const auto &x : data) {
      s += std::to_string(x) + ", ";
    }
    return s;
  }
};

template <typename E1, typename E2> auto operator+(E1 const &xs, E2 const &ys) {
  return VectorSum<E1, E2>(xs, ys);
}

auto read_vectors_from(const char *filename) {
  std::ifstream ifs(filename, std::ifstream::ate | std::ifstream::binary);
  auto filesize = ifs.tellg();
  auto nrows = filesize / sizeof(double) / NCOLS;
  ifs.seekg(std::ifstream::beg);

  std::vector<Vector<double>> columns(NCOLS);
  for (auto &col : columns) {
    col.data.resize(nrows);
    ifs.read((char *)col.data.data(), nrows * sizeof(double));
  }
  return columns;
}

auto read_target_from(const char *filename) {
  std::ifstream ifs(filename, std::ifstream::ate | std::ifstream::binary);
  auto size = ifs.tellg() / sizeof(double);
  ifs.seekg(std::ifstream::beg);

  std::vector<double> target;
  target.resize(size);
  ifs.read((char *)target.data(), size * sizeof(double));
  return target;
}

template <typename T>
auto calculate_mse(std::vector<T> const &xs, std::vector<T> const &ys) {
  assert(xs.size() == ys.size());
  double sum = 0;
  for (std::size_t idx = 0; idx < xs.size(); ++idx) {
    sum += std::pow(xs[idx] - ys[idx], 2);
  }
  return sum / xs.size();
}

int main(int argc, char **argv) {
  auto columns = read_vectors_from(argv[1]);
  auto start = std::chrono::steady_clock::now();
  Vector<double> w = columns[0] + columns[1] + columns[2] + columns[3] +
                     columns[4] + columns[5] + columns[6] + columns[7] +
                     columns[8] + columns[9];
  auto end = std::chrono::steady_clock::now();

  auto target = read_target_from(argv[2]);
  auto mse = calculate_mse(w.data, target);

  std::cerr << "Elapsed time in milliseconds: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << " ms\n";
  std::cerr << "MSE: " << mse << "\n";
  return 0;
}
