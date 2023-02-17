#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cassert>

template<typename Impl>
struct Expression {
    auto GetImpl() const { return static_cast<Impl const &>(this); }

    auto operator[](std::size_t idx) const { return GetImpl()->operator[](idx); }

    auto size() const { return GetImpl()->size(); }
};

template<typename E1, typename E2>
struct VectorSum : Expression<VectorSum<E1, E2>> {
    E1 const *x;
    E2 const *y;

    VectorSum(E1 const &x, E2 const &y) : x(&x), y(&y) {}

    auto size() const { return x->size(); }

    auto operator[](std::size_t idx) const { return x->operator[](idx) + y->operator[](idx); }
};

template<typename T>
struct Vector : Expression<T> {
    std::vector<T> data;

    Vector() = default;

    explicit Vector(std::vector<T> xs) : data{std::move(xs)} {}

    template<typename E>
    Vector(E &&expr) {
        data.reserve(expr.size());
        for (std::size_t idx = 0; idx < expr.size(); ++idx) {
            data.push_back(expr[idx]);
        }
    }

    auto operator[](std::size_t idx) const { return data[idx]; }

    auto size() const { return data.size(); }

    auto to_string() const {
        std::string s;
        for (const auto &x: data) {
            s += std::to_string(x) + ", ";
        }
        return s;
    }
};

template<typename E1, typename E2>
auto operator+(E1 const &xs, E2 const &ys) {
    return VectorSum<E1, E2>(xs, ys);
}

int main(int argc, const char **argv) {
    std::string input_file = argc >= 2 ? argv[1] : "/dev/stdin";
    std::ifstream ifs{input_file};
    // read 5-columns of type doubles separated by whitespace
    std::vector<Vector<double>> columns(10);
    std::string line;
    double x;
    std::size_t counter = 0;
    while (ifs >> x) {
        columns[counter % 10].data.push_back(x);
        ++counter;
    }

    auto start = std::chrono::steady_clock::now();
    Vector<double> w =
            columns[0] + columns[1] + columns[2] + columns[3] + columns[4] + columns[5] + columns[6] + columns[7] +
            columns[8] + columns[9];
    auto end = std::chrono::steady_clock::now();
    std::cout << w.to_string() << "\n";

    std::cerr << "Elapsed time in milliseconds: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
    return 0;
}