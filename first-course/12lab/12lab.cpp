#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iterator>

using TimePoint = std::chrono::system_clock::time_point;

struct LogEvent {
    TimePoint timestamp;
    std::string message;
};

class LogIterator {
    std::vector<LogEvent>::const_iterator m_current;
    std::vector<LogEvent>::const_iterator m_end;
    TimePoint m_start;
    TimePoint m_finish;

    void skip_invalid() {
        while (m_current != m_end) {
            if (m_current->timestamp >= m_start && m_current->timestamp <= m_finish) {
                break; 
            }
            ++m_current;
        }
    }

public:
    LogIterator(std::vector<LogEvent>::const_iterator start_it, 
                std::vector<LogEvent>::const_iterator end_it, 
                TimePoint start, TimePoint finish)
        : m_current(start_it), m_end(end_it), m_start(start), m_finish(finish) 
    {
        skip_invalid();
    }

    const LogEvent& operator*() const { return *m_current; }
    
    LogIterator& operator++() {
        if (m_current != m_end) {
            ++m_current;
            skip_invalid();
        }
        return *this;
    }

    bool operator!=(const LogIterator& other) const {
        return m_current != other.m_current;
    }
};

int main() {
    system("chcp 65001 > nul");

    std::vector<LogEvent> logs;
    std::string choice;

    std::cout << "--- СИСТЕМА ЛОГИРОВАНИЯ ---" << std::endl;
    std::cout << "Выберите действие: " << std::endl;
    std::cout << "1) Добавить запись (добавить)" << std::endl 
              << "2) Фильтр за 10 мин (фильтр)" << std::endl 
              << "3) Выход из программы (выход)" << std::endl;

    while (true) {
        std::cout << "Введите ключевое слово в скобках: " << std::endl;
        std::cin >> choice;

        if (choice == "добавить") {
            std::string msg;
            std::cout << std::endl << "Введите текст лога: ";
            std::getline(std::cin >> std::ws, msg);

            logs.push_back({ std::chrono::system_clock::now(), msg });
            
            std::cout << "Запись была добавлена в систему" << std::endl;
            std::cout << "------------" << std::endl;

        } else if (choice == "фильтр") {
            std::cout << "===================" << std::endl;
            
            if (logs.empty()) {
                std::cout << "Журнал логов пуст" << std::endl;
            } else {
                auto now = std::chrono::system_clock::now();
                auto ten_mins_ago = now - std::chrono::minutes(10);

                LogIterator it(logs.begin(), logs.end(), ten_mins_ago, now);
                LogIterator end_it(logs.end(), logs.end(), ten_mins_ago, now);

                bool found = false;
                std::cout << "События за последние 10 минут: " << std::endl;

                for (; it != end_it; ++it) {
                    std::cout << " - '" << (*it).message << "'" << std::endl;
                    found = true;
                }

                if (!found) {
                    std::cout << "Подходящих записей не найдено" << std::endl;
                }
            }
            
            std::cout << "===================" << std::endl;

        } else if (choice == "выход") {
            break;
        }
    }

    return 0;
}