#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <cassert>

template<typename T>
struct Vector {
    std::vector<T> data;

    std::size_t size() const { return data.size(); }

    const T &operator[](std::size_t idx) const { return data[idx]; }

    auto to_string() const {
        std::string s;
        for (const auto &x: data) {
            s += std::to_string(x) + ", ";
        }
        return s;
    }
};

template<typename T>
auto operator+(Vector<T> const &x, Vector<T> const &y) {
    assert(x.size() == y.size());
    std::vector<decltype(x[0] + y[0])> result;
    result.reserve(x.size());
    for (std::size_t idx = 0; idx < x.size(); ++idx) {
        result.push_back(x[idx] + y[idx]);
    }
    return Vector<T>{result};
}

int main(int argc, char **argv) {
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
