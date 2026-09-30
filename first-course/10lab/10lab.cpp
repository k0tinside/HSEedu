#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>
#include <windows.h>

template <class T>
class MyPipeline {
private:
    struct Step {
        std::string name;
        std::function<T(T)> func;
    };

    std::vector<Step> steps;

public:
    MyPipeline() = default;

    size_t size() const {
        return steps.size();
    }

    bool empty() const {
        return steps.empty();
    }

    void clear() {
        steps.clear();
    }

    template <class F>
    void addStep(const std::string& name, F func) {
        if (name.empty()) {
            throw std::invalid_argument("пустое имя шага");
        }
        steps.push_back({name, std::function<T(T)>(func)});
    }

    void removeStep(size_t index) {
        if (index >= steps.size()) {
            throw std::out_of_range("выход за пределы конвейера индекса");
        }
        steps.erase(steps.begin() + index);
    }

    T run(T value) const {
        T current = value;
        for (const auto& step : steps) {
            current = step.func(current);
        }
        return current;
    }

    std::vector<T> trace(T value) const {
        std::vector<T> results;
        if (steps.empty()) {
            return results;
        }
        
        T current = value;
        for (const auto& step : steps) {
            current = step.func(current);
            results.push_back(current);
        }
        return results;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyPipeline<T>& pipeline) {
        os << "количество шагов: " << pipeline.size() << "\n";
        for (size_t i = 0; i < pipeline.size(); ++i) {
            os << i << ") " << pipeline.steps[i].name << "\n";
        }
        return os;
    }
};

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::cout << "Демонстрация MyPipeline<int>\n";
    MyPipeline<int> mathPipe;
    
    mathPipe.addStep("умножить на 5", [](int x) { return x * 5; });
    mathPipe.addStep("прибавить 52", [](int x) { return x + 52; });
    mathPipe.addStep("вычесть 2", [](int x) { return x - 2; });

    std::cout << mathPipe << "\n";

    int start_int = 5;
    std::cout << "входное значение: " << start_int << "\n";
    
    std::cout << "результат run: " << mathPipe.run(start_int) << "\n\n";

    std::cout << "результаты trace:\n";
    std::vector<int> traces = mathPipe.trace(start_int);
    for (size_t i = 0; i < traces.size(); ++i) {
        std::cout << "после шага " << i << ": " << traces[i] << "\n";
    }
    std::cout << "\n";

    std::cout << "Демонстрация MyPipeline<std::string>\n";
    MyPipeline<std::string> strPipe;
    
    strPipe.addStep("лучший вуз", [](std::string s) { return s + ": МИЭМ"; });
    strPipe.addStep("любимый предмет", [](std::string s) { return s + " обожает ЯПы"; });
    strPipe.addStep("сделать дубликат", [](std::string s) { return s + " " + s; });

    std::string start_str = "студент СКБ252";
    std::cout << "входное значение: " << start_str << "\n";
    std::cout << "результат run: " << strPipe.run(start_str) << "\n\n";

    std::cout << "Демонстрация исключения\n";
    
    std::cout << "попытка удалить несуществующий шаг:\n";
    try {
        mathPipe.removeStep(100);
    } catch (const std::out_of_range& e) {
        std::cout << "поймано исключение out_of_range: " << e.what() << "\n";
    }

    return 0;
}