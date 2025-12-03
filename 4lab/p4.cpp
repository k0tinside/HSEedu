#include <iostream>
#include <windows.h>
#include <iomanip>

float dayAverage(float* row, int h) {
    float summa = 0;
    for (int j = 0; j < h; ++j) {
        summa = summa + *(row + j);
    }
    return summa / h;
}

float overallAverage(float** p, int d, int h) {
    float summa = 0;
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < h; ++j) {
            summa = summa + *(*(p + i) + j);
        }
    }
    return summa / (d * h);
}

void showHotDays(float** p, int d, int h) {
    float avg = overallAverage(p, d, h);
    std::cout << "Теплые дни:\n";
    for (int i = 0; i < d; ++i) {
        float dayAvg = dayAverage(*(p + i), h);
        if (dayAvg > avg) {
            std::cout << "День " << i + 1 << " (среднее = " << dayAvg << ")\n";
        }
    }
}

int main() {
    
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::cout << std::fixed << std::setprecision(1);

    int d, h;
    
    std::cout << "Введите количество дней: ";
    std::cin >> d;

    std::cout << "Введите количество измерений в дне: ";
    std::cin >> h;

    if (d <= 0 || h <= 0) {
        std::cout << "Введено некорректное число измерений.";
        return 0;
    }

    float** data = new float*[d];
    for (int i = 0; i < d; ++i) {
        *(data + i) = new float[h];
        std::cout << "День " << i + 1 << ": ";
        for (int j = 0; j < h; ++j) {
            std::cin >> *(*(data + i) + j);
        }
    }
    
    std::cout << "\nОбщая средняя температура: " << overallAverage(data, d, h) << "\n";

    showHotDays(data, d, h);

    for (int i = 0; i < d; ++i) {
        delete[] *(data + i);
    }
    delete[] data;

    return 0;
}