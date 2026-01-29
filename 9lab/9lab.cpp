#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

template <typename K, typename E, typename V>
struct GroupInfo {
    K key;
    int count;
    E minElem;
    E maxElem;
    V sum; 
    double avg;
};

template <typename E, typename KF, typename VF>
auto groupStats(E* arr, int n, KF keyFunc, VF valueFunc) -> std::vector<GroupInfo<decltype(keyFunc(arr[0])), E, decltype(valueFunc(arr[0]))>> {

    using K = decltype(keyFunc(arr[0]));
    using V = decltype(valueFunc(arr[0]));

    std::vector<GroupInfo<K, E, V>> result;

    for (int i = 0; i < n; ++i) {
        E el = arr[i];
        K elK = keyFunc(el);
        V elV = valueFunc(el);
        
        bool flag = false;

        for (int j = 0; j < (int)result.size(); ++j) {
            if (result[j].key == elK) {
                result[j].count++;
                if (el < result[j].minElem) result[j].minElem = el;
                if (el > result[j].maxElem) result[j].maxElem = el;
                result[j].sum += elV;
                flag = true;
                break;
            }
        }

        if (!flag) {
            GroupInfo<K, E, V> newG;
            newG.key = elK;
            newG.count = 1;
            newG.minElem = el;
            newG.maxElem = el;
            newG.sum = elV;
            newG.avg = 0.0;
            result.push_back(newG);
        }
    }

    for (int j = 0; j < (int)result.size(); ++j) {
        result[j].avg = static_cast<double>(result[j].sum) / result[j].count;
    }

    return result;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    // Массив int
    int arr1[] = {11, 22, 33, 44, 55, 51, 52};
    std::vector<GroupInfo<int, int, int>> res1 = groupStats(arr1, 7, 
        [](int x) { return x % 10; }, 
        [](int x) { return x; }
    );
    for (int i = 0; i < (int)res1.size(); ++i) {
        GroupInfo<int, int, int> g = res1[i];
        std::cout << g.key << ", "
                  << g.count << ", "
                  << g.minElem  << ", "
                  << g.maxElem  << ", "
                  << g.sum  << ", "
                  << g.avg << "\n";
    }
    std::cout << "\n";

    // Массив double
    double arr2[] = {-5.5, 5.0, 15.2, 7.3, -2.0, 12.0, -3.2};
    std::vector<GroupInfo<int, double, double>> res2 = groupStats(arr2, 7, 
        [](double x) { 
            if (x < 0) return 0;
            if (x <= 10) return 1;
            return 2;
        }, 
        [](double x) { return x; }
    );

    for (int i = 0; i < (int)res2.size(); ++i) {
        GroupInfo<int, double, double> g = res2[i];
        std::cout << g.key << ", "
                  << g.count << ", "
                  << g.minElem  << ", "
                  << g.maxElem  << ", "
                  << g.sum  << ", "
                  << g.avg << "\n";
    }
    std::cout << "\n";

    // Массив string
    std::string arr3[] = {"MIEM", "Mathematics", "Information", "templates", "IT"};
    
    std::vector<GroupInfo<char, std::string, int>> res3 = groupStats(arr3, 5,
        [](std::string x) { return x[0]; },
        [](std::string x) { return (int)x.length(); }
    );

    for (int i = 0; i < (int)res3.size(); ++i) {
        GroupInfo<char, std::string, int> g = res3[i];
        std::cout << g.key << ", "
                  << g.count << ", "
                  << g.minElem  << ", "
                  << g.maxElem  << ", "
                  << g.sum  << ", "
                  << g.avg << "\n";
    }

    return 0;
}