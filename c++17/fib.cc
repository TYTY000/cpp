#include <functional>
#include <iostream>

std::function<int()> intSeq() {
    int a = 0, b = 1;
    return [a, b]() mutable {
        b = a + b;
        a = b - a;
        return a;
    };
}

int main() {
    auto nextFib = intSeq();

    for (int i = 0; i < 10; i++) {
        std::cout << nextFib() << std::endl;
    }

    return 0;
}
