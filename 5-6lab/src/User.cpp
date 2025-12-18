#include "User.h"
 
User::User(std::string name,
           std::string userId,
           int maxBooksAllowed)
    : name(name),
    userId(userId),
    borrowedBooks(),
    maxBooksAllowed(maxBooksAllowed) {
        if (name == "") {
            throw std::invalid_argument("Имя пользователя не может быть пустым");
        }
        if (userId == "") {
            throw std::invalid_argument("ID пользователя не может быть пустым");
        }
    }

std::string User::getName() const {
    return name;
}

std::string User::getUserId() const {
    return userId;
}

std::vector<std::string> User::getBorrowedBooks() const {
    return borrowedBooks;
}
int User::getMaxBooksAllowed() const {
    return maxBooksAllowed;
}

bool User::canBorrowMore() const {
    return borrowedBooks.size() < maxBooksAllowed;
}

void User::addBook(const std::string& isbn) {
    if (canBorrowMore() == false) {
        throw std::runtime_error("У пользователя максимальное количество взятых книг");
    }
    if (isbn == "") {
        throw std::invalid_argument("ISBN не может быть пустым");
    }
    borrowedBooks.push_back(isbn);
}

void User::removeBook(const std::string& isbn) {
    if (borrowedBooks.empty()) {
        throw std::runtime_error("У пользователя нет книг");
    }
    for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
        if (*it == isbn) {
            borrowedBooks.erase(it);
            return;
        }
    }
    throw std::runtime_error("ISBN не найден в списке выданных книг");
}

void User::displayProfile() const {
    std::cout << "Имя: " << name << std::endl;
    std::cout << "ID: " << userId << std::endl;
    if (!borrowedBooks.empty()) {
        int count = 1;
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            std::cout << "Книга№" << count << *it << std::endl;
            ++count;
        }
    } else {
        std::cout << "На данный момент пользователь не брал книг." << std::endl;
    }
    std::cout << "Максимальное количество книг для выдачи: " << maxBooksAllowed << std::endl;
}