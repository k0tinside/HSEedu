#include <iostream>
#include <windows.h>
#include <limits>
#include "Book.h"
#include "User.h"
#include "Library.h"

void showMenu() {
    std::cout << "\n=== БИБЛИОТЕКА ===" << std::endl;
    std::cout << "1. Просмотреть все книги" << std::endl;
    std::cout << "2. Просмотреть всех пользователей" << std::endl;
    std::cout << "3. Добавить новую книгу" << std::endl;
    std::cout << "4. Зарегистрировать пользователя" << std::endl;
    std::cout << "5. Выдать книгу пользователю" << std::endl;
    std::cout << "6. Принять книгу от пользователя" << std::endl;
    std::cout << "7. Поиск книги по ISBN" << std::endl;
    std::cout << "8. Просмотреть профиль пользователя" << std::endl;
    std::cout << "9. Сохранить данные в файл" << std::endl;
    std::cout << "10. Выход" << std::endl;
    std::cout << "Ваш выбор: _";
}

int getValidChoice() {
    int choice;
   while (true) {
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите число от 1 до 10: ";
            continue;
        }
        
        if (choice < 1 || choice > 10) {
            std::cout << "Ошибка: выберите пункт от 1 до 10: ";
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }
}

void showBooks(Library &lib) {
    std::cout << "\n-----Список всех книг-----" << std::endl;
    lib.displayAllBooks();
}

void showUsers(Library &lib) {
    std::cout << "\n-----Список всех пользователей-----" << std::endl;
    lib.displayAllUsers();
}

void addBook(Library &lib) {
    std::cout << "\n-----Добавление новой книги-----" << std::endl;
    std::string title, author, isbn;
    int year;
    
    try {
        std::cout << "Название: ";
        std::getline(std::cin, title);
        
        std::cout << "Автор: ";
        std::getline(std::cin, author);
        
        std::cout << "Год: ";
        std::cin >> year;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "ISBN: ";
        std::getline(std::cin, isbn);
        
        Book book(title, author, year, isbn);
        lib.addBook(book);
        std::cout << "Книга добавлена" << std::endl;
        
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка ввода: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void addUser(Library& lib) {
    std::cout << "\n-----Регистрация пользователя-----" << std::endl;
    std::string name, userId;
    int maxBooksAllowed;
    
    try {
        std::cout << "Имя пользователя: ";
        std::getline(std::cin, name);
        
        std::cout << "ID пользователя: ";
        std::getline(std::cin, userId);
        
        std::cout << "Максимальное количество книг для выдачи: ";
        std::cin >> maxBooksAllowed;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        User user(name, userId, maxBooksAllowed);
        lib.addUser(user);
        std::cout << "Пользователь зарегистрирован" << std::endl;
        
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка ввода: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void borrowBook(Library& lib) {
    std::cout << "\n-----Выдача книги пользователю-----" << std::endl;
    std::string userName, isbn;
    
    try {
        std::cout << "Имя пользователя: ";
        std::getline(std::cin, userName);
        
        std::cout << "ISBN книги: ";
        std::getline(std::cin, isbn);
        
        lib.borrowBook(userName, isbn);
        std::cout << "Книга выдана" << std::endl;
        
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка ввода: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void returnBook(Library& lib) {
    std::cout << "\n-----Принятие книги от пользователя-----" << std::endl;
    std::string isbn;
    
    try {
        std::cout << "ISBN книги: ";
        std::getline(std::cin, isbn);
        
        lib.returnBook(isbn);
        std::cout << "Книга принята" << std::endl;
        
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка ввода: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void findBook(Library& lib) {
    std::cout << "\n-----Поиск книги по ISBN-----" << std::endl;
    std::string isbn;
    
    try {
        std::cout << "ISBN: ";
        std::getline(std::cin, isbn);
        
        Book* book = lib.findBookByISBN(isbn);
        if (book != nullptr) {
            book->displayInfo();
        } else {
            std::cout << "Книга не найдена" << std::endl;
        }
        
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка ввода: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void showUserProfile(Library& lib) {
    std::cout << "\n-----Поиск профиля пользователя-----" << std::endl;
    std::string userName;
    
    try {
        std::cout << "ID пользователя: ";
        std::getline(std::cin, userName);
        
        User* user = lib.findUserByName(userName);
        if (user != nullptr) {
            user->displayProfile();
        } else {
            std::cout << "Пользователь не найден" << std::endl;
        }
        
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка ввода: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void save(Library &lib) {
    try {
        lib.saveToFile();
        std::cout << "Данные сохранены" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка сохранения: " << e.what() << std::endl;
    }
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    try {
        Library lib("data/library_data.txt");
        lib.loadFromFile();
        int choice;
        do {
            showMenu();
            choice = getValidChoice();
            switch (choice) {
                case 1:
                    showBooks(lib);
                    break;
                case 2:
                    showUsers(lib);
                    break;
                case 3:
                    addBook(lib);
                    break;
                case 4:
                    addUser(lib);
                    break;
                case 5:
                    borrowBook(lib);
                    break;
                case 6:
                    returnBook(lib);
                    break;
                case 7:
                    findBook(lib);
                    break;
                case 8:
                    showUserProfile(lib);
                    break;
                case 9:
                    save(lib);
                    break;
                case 10:
                    std::cout << "Выход из программы..." << std::endl;                
                default:
                    break;
            }
        } while (choice != 10);

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка ввода: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}