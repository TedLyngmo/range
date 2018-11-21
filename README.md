# range [a,b)
Range template library for C++17

## Purpose
The `range` library is a single header template library making python-like ranges easy. Typically in range-based for-loops.

## Getting started
Just copy `range.hpp` to your project, include it, and then you're ready. `range` supports not only making ranges of integral and real types. You can use your own data types for stepping etc.

## Usage
### `range(<stop-value>)`
Stepping will be started by default constructing a value of the same type as `stop-value`. Stepping will be done towards the `stop-value` using a default constructed value of `T` with `operator++()` or `operator--()` applied depending on the direction.
### `range(<start-value>, <stop-value>)`
Stepping will be done towards the `stop-value` using the same technique as above.
### `range(<start-value>, <stop-value>, <step-value>)`
Stepping will be done using `<step-value>`.

The values don't need to be of the same type as long as they can be compared/used for stepping. If `range` is used to hi-jack iterators, `start-value` (example: `begin()`), `stop-value` (example: `end()`) and `step-value` (example: `unsigned`) may very well be three different types.

## Example
```c++
#include <iostream>
#include <vector>

#include "range.hpp"
using namespace lyn;


template <typename T>
void ranger(T& r) {
    for(const auto& v : r)
        std::cout << v << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "integral range: ";
    for(auto v : range(10))
        std::cout << v << " ";
    std::cout << "\n";

    std::cout << "negative integral range: ";
    for(auto v : range(-10))
        std::cout << v << " ";
    std::cout << "\n";

    std::cout << "real range: ";
    for(const auto& v : range(1.2, 4.5))
        std::cout << v << " ";
    std::cout << "\n";

    std::cout << "negative real range, with stepping: ";
    for(const auto& v : range(-1.2, -4.5, -1.1))
        std::cout << v << " ";
    std::cout << "\n";

    std::vector<int> vi{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    std::cout << "iterator hi-jacking with stepping: ";
    for(const auto& v : range(vi.begin()+4, vi.end()-4, 2))
        std::cout << *v << " ";
    std::cout << "\n";

    std::cout << "a range as an argument to a function: ";
    range arg(-10, 10, 3);
    ranger(arg);
}
```

Output

    integral range: 0 1 2 3 4 5 6 7 8 9
    negative integral range: 0 -1 -2 -3 -4 -5 -6 -7 -8 -9
    real range: 1.2 2.2 3.2 4.2
    negative real range, with stepping: -1.2 -2.3 -3.4
    iterator hi-jacking with stepping: 4 6 8 10
    a range as an argument to a function: -10 -7 -4 -1 2 5 8

