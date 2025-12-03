#include <iostream>
#include <windows.h>
#include <iomanip>

void inputData(float* p, int n) {
    std::cout << "Введите значения: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> *(p + i);
    }
}

float average(const float* p, int n) {
    float summa = 0;
    for (int i = 0; i < n; ++i) {
        summa = summa + *(p + i);
    }
    return summa / n;
}

float minValue(const float* p, int n) {
    float min_value = *p;
    for (int i = 1; i < n; ++i) {
        min_value = std::min(min_value, *(p + i));
    }
    return min_value;
}

float maxValue(const float* p, int n) {
    float max_value = *p;
    for (int i = 1; i < n; ++i) {
        max_value = std::max(max_value, *(p + i));
    }
    return max_value;
}

float* filterAboveAverage(float* p, int n, int& newCount) {

    float aver = average(p, n);
    for (int i = 0; i < n; ++i) {
        if (*(p + i) > aver) {
            newCount++;
        }
    }

    float* new_data = new float[newCount];

    int j = 0;
    for (int i = 0; i < n; ++i) {
        if (*(p + i) > aver) {
            *(new_data + j) = *(p + i);
            j++;
        }
    }
    return new_data;
}

int main() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::cout << "=== Анализ сенсора ===\n";
    int n;

    std::cout << "Введите количество измерений: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Введено некорректное число измерений.";
        return 0;
    }

    float* data = new float[n];
    
    inputData(data, n);

    std::cout << std::fixed << std::setprecision(1);

    std::cout << "\nСреднее значение: " << average(data, n) << "\n";
    std::cout << "Минимум: " << minValue(data, n) << "\n";
    std::cout << "Максимум: " << maxValue(data, n) << "\n" << "\n";
    std::cout << "Значения выше среднего:\n";
    
    int newCount = 0;
    float* new_data = filterAboveAverage(data, n, newCount);
    for (int i = 0; i < newCount; ++i) {
        std::cout << *(new_data + i) << " ";
    }

    delete[] new_data;
    delete[] data;

    return 0;
}