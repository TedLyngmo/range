#include <iostream>
#include <vector>

#include "range.hpp"
using namespace lyn;


template <typename T>
void ranger(T& r) {
    for(const auto& v : r) std::cout << v << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "integral range: ";
    for(auto v : range(10)) std::cout << v << " ";
    std::cout << "\n";

    std::cout << "negative integral range: ";
    for(auto v : range(-10)) std::cout << v << " ";
    std::cout << "\n";

    std::cout << "real range: ";
    for(const auto& v : range(1.2, 5.2)) std::cout << v << " ";
    std::cout << "\n";

    std::cout << "negative real range, with stepping: ";
    for(const auto& v : range(-1.2, -4.5, -1.1)) std::cout << v << " ";
    std::cout << "\n";

    std::cout << "iterator hi-jacking with stepping: ";
    std::vector<int> vi{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    for(const auto& v : range(vi.begin()+4, vi.end()-4, 2)) std::cout << *v << " ";
    std::cout << "\n";

    std::cout << "a range as an argument to a function: ";
    range arg(-10, 10, 3);
    ranger(arg);
}
