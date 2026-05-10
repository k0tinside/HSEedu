#include <iostream>
#include <vector>
#include <string>
#include <iterator> 

int main() {

    system("chcp 65001 > nul");

    std::vector<std::string> inventory;
    std::string choice;

    std::cout << "--- ИНВЕНТАРЬ ---" << std::endl;
    std::cout << "Выберите действие: " << std::endl;
    std::cout << "1) Добавить предмет (добавить)" << std::endl <<"2) Удалить предмет (удалить)" << std::endl << "3) Показать инвентарь (показать)" << std::endl << "4) Выход из программы (выход)" << std::endl;

    while (true) {
        std::cout << "Введите ключевое слово в скобках: " << std::endl;
        std::cin >> choice;

        if (choice == "добавить") {
            std::string item;
            std::cout << std::endl << "Введите название добавляемого предмета: ";
            std::getline(std::cin >> std::ws, item);

            auto it = std::back_inserter(inventory);
            *it = item; 
            
            std::cout << "Предмет был добавлен в инвентарь" << std::endl;
            std::cout << "------------" << std::endl;

        } else if (choice == "удалить") {
            std::string item;
            std::cout << "Введите название удаляемого предмета: ";
            std::getline(std::cin >> std::ws, item);

            bool wasDeleted = false;

            for (auto it = inventory.begin(); it != inventory.end(); ) {
                if (*it == item) {
                    it = inventory.erase(it); 
                    std::cout << "Предмет '" << item << "' был удален" << std::endl;
                    wasDeleted = true;
                    break;
                } else {
                    ++it;
                }
            }

            if (!wasDeleted) {
                std::cout << "Данный предмет не был найден в инвентаре" << std::endl;
            }
            std::cout << "------------" << std::endl;
            
        } else if (choice == "показать") {
            std::cout << "===================" << std::endl; 
            std::cout << "Содержимое инвентаря: ";

            for (auto it = inventory.begin(); it != inventory.end(); ++it) {
                std::cout << "'" << *it << "' ";
            }
            std::cout << std::endl << "===================" << std::endl; 

        } else if (choice == "выход") {
            break;
        }
    }
    return 0;
}