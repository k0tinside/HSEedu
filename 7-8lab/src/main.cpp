#include <windows.h>
#include "ProcessList.h"

PCB makePCB(int id, const std::string& name, const std::string& status) {
    PCB p;
    p.processID = id;
    p.processName = name;
    p.processStatus = status;
    p.commandCounter = 0;
    return p;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::cout << "1. Инициализация списка процессов" << std::endl;
    ProcessList osManager;
    
    PCB p1 = makePCB(10, "Система", "Running");
    PCB p2 = makePCB(50, "Браузер", "Waiting");
    PCB p3 = makePCB(20, "Музыка", "Stopped");
    PCB p4 = makePCB(5, "Игра", "Running");
    PCB p5_dup = makePCB(50, "Браузер_дубликат", "Error");
    PCB p6 = makePCB(100, "Калькулятор", "Running");

    std::cout << "\n2. Добавление элементов (5, 10, 20, 50, 100)" << std::endl;
    osManager.insert(p1);
    osManager.insert(p2);
    osManager.insert(p3);
    osManager.insert(p4);
    osManager.insert(p6);

    std::cout << "\n3. Список после вставок" << std::endl;;
    osManager.printList();

    std::cout << "\n4. Удаление элементов" << std::endl;;
    
    if (osManager.remove(20)) {
        std::cout << "Процесс ID 20 удален" << std::endl;;
    }
    
    if (osManager.remove(5)) {
        std::cout << "Процесс ID 5 удален" << std::endl;;
    }

    std::cout << "\n5. Список после удалений (остались 10, 50, 100)" << std::endl;;
    osManager.printList();

    std::cout << "\n6. Проверка неудачных операций" << std::endl;;
    
    if (!osManager.insert(p5_dup)) {
        std::cout << "Попытка вставить дубликат ID 50: Отклонено" << std::endl;;
    }

    if (!osManager.remove(999)) {
        std::cout << "Попытка удалить ID 999: Не найден" << std::endl;;
    }

    std::cout << "\n7. Финальное состояние списка" << std::endl;;
    osManager.printList();

    return 0;
}