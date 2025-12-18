#include "Book.h"

Book::Book(const std::string title, 
        const std::string author,
        int year,
        const std::string isbn) 
    : title(title),
    author(author),
    year(year),
    isbn(isbn),
    isAvailable(true),
    borrowedBy("") {
        int cur_year = 2025;
        if (year < 1450 || year > cur_year) {
            throw std::invalid_argument("Год должен быть корректным");
        }
        if (isbn == "") { 
            throw std::invalid_argument("ISBN должен быть не пустым");
        }
    }

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

int Book::getYear() const {
    return year;
}

std::string Book::getIsbn() const {
    return isbn;
}

bool Book::getIsAvailable() const {
    return isAvailable;
}

std::string Book::getBorrowedBy() const {
    return borrowedBy;
}

void Book::borrowBook(std::string userId) {
    if (isAvailable == false) {
        throw std::runtime_error("Книга уже взята");
    } 
    if (userId == "") {
        throw std::invalid_argument("Пустое ID пользователя");
    }
    isAvailable = false;
    borrowedBy = userId;
}

void Book::returnBook() {
    if (isAvailable == true) {
        throw std::runtime_error("Книгу не забирали");
    }
    isAvailable = true;
    borrowedBy.clear();
}

void Book::displayInfo() const {
    std::cout << "Название: " << title << std::endl;
    std::cout << "Автор: " << author << std::endl;
    std::cout << "Год: " << year << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    if (isAvailable) {
        std::cout << "Книга доступна" << std::endl;
    } else {
        std::cout << "Книга не доступна" << std::endl;
        std::cout << "Книга взята: " << borrowedBy << std::endl;
    }
}