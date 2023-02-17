#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cassert>

template<typename T>
struct VectorBase {
    using value_type = T;

    virtual std::size_t size() const = 0;
    virtual T operator[](std::size_t idx) const = 0;
};

template<typename E1, typename E2>
struct VectorSum {
    using value_type = typename E1::value_type;
    E1 const& x;
    E2 const& y;

    VectorSum(E1 const& x, E2 const& y): x{x}, y{y} {
        assert(x.size() == y.size());
    }

    virtual std::size_t size() const { return x.size(); }

    virtual value_type operator[](std::size_t idx) const { return x[idx] + y[idx]; }
};

template<typename T>
struct Vector : VectorBase<T> {
    using value_type = T;

    std::vector<T> data;
    Vector() = default;
    Vector(std::initializer_list<T> list) : data{list} {}
    template<typename E>
    Vector(E const& e) {
        data.reserve(e.size());
        for (std::size_t idx = 0; idx < e.size(); ++idx)
            data.push_back(e[idx]);
    }

    virtual std::size_t size() const { return data.size(); }
    virtual T operator[](std::size_t idx) const { return data[idx]; }

    auto to_string() const {
        std::string s;
        for (const auto& x : data) {
            s += std::to_string(x) + ", ";
        }
        return s;
    }
};

template<typename E1, typename E2>
auto operator+(E1 const& x, E2 const& y) {
    assert(x.size() == y.size());
    return VectorSum{x, y};
}

int main(int argc, const char** argv) {
    std::string input_file = argc >= 2 ? argv[1] : "/dev/stdin";
    std::ifstream ifs{input_file};
    // read 5-columns of type doubles separated by whitespace
    std::vector<Vector<double>> columns(5);
    std::string line;
    double x;
    std::size_t counter = 0;
    while (ifs >> x) {
        columns[counter % 5].data.push_back(x);
        ++counter;
    }

    auto start = std::chrono::steady_clock::now();
    Vector<double> w = columns[0] + columns[1] + columns[2] + columns[3] + columns[4];
    auto end = std::chrono::steady_clock::now();
    std::cout << w.to_string() << "\n";

    std::cerr << "Elapsed time in milliseconds: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << " ms\n";
    return 0;
}
