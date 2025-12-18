#include <iostream>

int main() {

    int n;
    std::cin >> n;

    int* a = new int[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> *(a + i);
    }

    for (int i = 0; i < n; ++i) {
        std::cout << *(a + i) << " ";
    }

    delete[] a;
    a = nullptr; 

    return 0;
}