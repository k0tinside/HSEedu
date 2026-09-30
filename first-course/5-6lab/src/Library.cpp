#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Library.h"

Library::Library(const std::string& dataFile)
    : books(),
      users(),
      dataFile(dataFile) {}

void Library::addBook(const Book& book) {
    std::string isbn = book.getIsbn();
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getIsbn() == isbn) {
            throw std::invalid_argument("ISBN должен быть уникальным");
        }
    }
    books.push_back(book);
}

void Library::addUser(const User& user) {
    std::string idUser = user.getUserId();
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->getUserId() == idUser) {
            throw std::invalid_argument("ID пользователя должен быть уникальным");
        }
    }
    users.push_back(user);
}

void Library::borrowBook(const std::string& name, const std::string& isbn) {
    if (isbn.empty()) {
        throw std::invalid_argument("ISBN должен быть не пустым");
    }
    if (name.empty()) {
        throw std::invalid_argument("Имя пользователя не может быть пустым");
    }

    Book* book = findBookByISBN(isbn); 
    User* user = findUserByName(name);

    if (book == nullptr) {
        throw std::runtime_error("Книга не найдена");
    }
    if (user == nullptr) {
        throw std::runtime_error("Пользователь не найден");
    }

    if (user->canBorrowMore() && book->getIsAvailable()) {
        user->addBook(isbn);
        book->borrowBook(name);
    } else if (!user->canBorrowMore()) {
        throw std::runtime_error("У пользователя максимальное количество книг");
    } else {
        throw std::runtime_error("Книга уже взята");
    }
}

void Library::returnBook(const std::string& isbn) {
    if (isbn.empty()) {
        throw std::invalid_argument("ISBN должен быть не пустым");
    }

    Book* book = findBookByISBN(isbn);
    if (book == nullptr) {
        throw std::runtime_error("Книга не найдена");
    }

    std::string borrower = book->getBorrowedBy();
    if (borrower.empty()) {
        throw std::runtime_error("Книга не была взята");
    }

    User* user = findUserByName(borrower);
    if (user == nullptr) {
        throw std::runtime_error("Пользователь не найден");
    }

    user->removeBook(isbn);
    book->returnBook();
}

Book* Library::findBookByISBN(const std::string& isbn) {
    if (isbn.empty()) {
        throw std::invalid_argument("ISBN должен быть не пустым");
    }
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getIsbn() == isbn) {
            return &(*it);
        }
    }
    return nullptr;
}

User* Library::findUserByName(const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument("Имя пользователя не может быть пустым");
    }
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->getName() == name) {
            return &(*it);
        }
    }
    return nullptr;
}

void Library::displayAllBooks() {
    for (auto it = books.begin(); it != books.end(); ++it) {
        it->displayInfo();
        std::cout << "-----------------------\n";
    }
}

void Library::displayAllUsers() {
    for (auto it = users.begin(); it != users.end(); ++it) {
        it->displayProfile();
        std::cout << "-----------------------\n";
    }
}

void Library::saveToFile() {
    std::ofstream file(dataFile);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи");
    }

    file << "---BOOKS---" << std::endl;
    for (auto it = books.begin(); it != books.end(); ++it) {
        file << "BOOK" << std::endl;
        file << "Title: " << it->getTitle() << std::endl;
        file << "Author: " << it->getAuthor() << std::endl;
        file << "Year: " << it->getYear() << std::endl;
        file << "ISBN: " << it->getIsbn() << std::endl;
        if (it->getIsAvailable()) {
            file << "Available: " << "yes" << std::endl;
        } else {
            file << "Available: " << "no" << std::endl;
        }
        file << "BorrowedBy: " << it->getBorrowedBy() << std::endl;
    }

    file << "---USERS---" << std::endl;
    for (auto uit = users.begin(); uit != users.end(); ++uit) {
        file << "USER" << std::endl;
        file << "Name: " << uit->getName() << std::endl;
        file << "UserID: " << uit->getUserId() << std::endl;
        file << "MaxBooks: " << uit->getMaxBooksAllowed() << std::endl;

        const std::vector<std::string>& borrowed = uit->getBorrowedBooks();
        file << "BorrowedBooks: ";
        int i = 0;
        for (auto it = borrowed.begin(); it != borrowed.end(); ++it) {
            file << *it;
            ++i;
            if (i < borrowed.size()) {
                file << "|";
            }
        }
        file << std::endl;
    }

    file.close();
}

void Library::loadFromFile() {
    std::ifstream file(dataFile);
    if (!file.is_open()) {
        return;
    }

    books.clear();
    users.clear();

    std::string line;

    while (std::getline(file, line)) {
        if (line == "---BOOKS---") {
            break;
        }
    }

    while (std::getline(file, line)) {
        if (line == "---USERS---") {
            break;
        }
        if (line != "BOOK") {
            continue;
        }

        std::string title, author, isbn, isAvailableStr, borrowedBy;
        int year = 0;

        std::getline(file, line); 
        title = line.substr(std::string("Title: ").size());

        std::getline(file, line); 
        author = line.substr(std::string("Author: ").size());

        std::getline(file, line); 
        year = std::stoi(line.substr(std::string("Year: ").size()));

        std::getline(file, line); 
        isbn = line.substr(std::string("ISBN: ").size());

        std::getline(file, line); 
        isAvailableStr = line.substr(std::string("Available: ").size());

        std::getline(file, line); 
        borrowedBy = line.substr(std::string("BorrowedBy: ").size());

        try {
            Book book(title, author, year, isbn);
            if (isAvailableStr == "no") {
                if (!borrowedBy.empty()) {
                    book.borrowBook(borrowedBy);
                }
            }
            books.push_back(book);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при загрузке книги: " << e.what() << std::endl;
        }
    }

    while (std::getline(file, line)) {
        if (line != "USER") {
            continue;
        }

        std::string name, userId, borrowedStr;
        int maxBooksAllowed = 0;

        std::getline(file, line); 
        name = line.substr(std::string("Name: ").size());

        std::getline(file, line); 
        userId = line.substr(std::string("UserID: ").size());

        std::getline(file, line); 
        maxBooksAllowed = std::stoi(line.substr(std::string("MaxBooks: ").size()));

        std::getline(file, line); 
        borrowedStr = line.substr(std::string("BorrowedBooks: ").size());

        try {
            User user(name, userId, maxBooksAllowed);

            if (!borrowedStr.empty()) {
                std::size_t start = 0;
                while (start < borrowedStr.size()) {
                    std::size_t pos = borrowedStr.find('|', start);

                    std::string isbn;
                    if (pos == std::string::npos) {
                        isbn = borrowedStr.substr(start);
                    } else {
                        isbn = borrowedStr.substr(start, pos - start);
                    }

                    if (!isbn.empty()) {
                        user.addBook(isbn);
                    }

                    if (pos == std::string::npos) {
                        break;
                    }

                    start = pos + 1;
                }
            }

            users.push_back(user);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при загрузке пользователя: " << e.what() << std::endl;
        }
    }

    file.close();
}
