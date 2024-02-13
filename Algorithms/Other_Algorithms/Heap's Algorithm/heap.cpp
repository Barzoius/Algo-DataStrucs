#include <iostream>
#include <vector>
#include <string>

template<typename T>
void Heap(T& s, int n) {
    if (n == 1) {
        for (const auto& elem : s) {
            std::cout << elem;
        }
        std::cout << std::endl;
        return;
    }
    else {
        for (int i = 0; i < n; i++) {
            Heap(s, n - 1);
            if (n & 1)
                std::swap(s[i], s[n - 1]);
            else
                std::swap(s[0], s[n - 1]);
        }
    }
}

int main() {
    std::string str = "abc";
    std::vector<int> vec = {1, 2, 3};

    Heap(str, str.size());
//    abc
//    bac
//    cba
//    bca
//    cab
//    acb
    Heap(vec, vec.size());
//    123
//    213
//    321
//    231
//    312
//    132

    return 0;
}
