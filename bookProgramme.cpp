#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>

using namespace std;

const int MAX_BOOKS = 1000;

struct Book {
    char name[100];
    char author[50];
    int year;
    float rating;
};

Book books[MAX_BOOKS];
int bookCount = 0;

void loadBooks(const char *filename) {
    ifstream fin(filename);
    if (!fin) return;

    while (fin >> books[bookCount].name >> books[bookCount].author >> books[bookCount].year >> books[bookCount].rating) {
        bookCount++;
    }

    fin.close();
}

void saveBookToFile(const char *filename, Book b) {
    ofstream fout(filename, ios::app);
    if (!fout) {
        cout << "Ошибка при сохранении файла!" << endl;
        return;
    }

    fout << b.name << " " << b.author << " " << b.year << " " << b.rating << endl;
    fout.close();
}

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        cout << "Превышен лимит книг!" << endl;
        return;
    }

    Book b;
    cout << "Введите название книги: ";
    cin >> b.name;

    cout << "Введите автора книги: ";
    cin >> b.author;

    cout << "Введите год прочтения: ";
    cin >> b.year;

    cout << "Введите оценку: ";
    cin >> b.rating;

    books[bookCount++] = b;
    saveBookToFile("books.txt", b);

    cout << "Книга добавлена!\n";
}

void showAllBooks() {
    if (bookCount == 0) {
        cout << "Нет данных о книгах.\n";
        return;
    }

    cout << "\n--- Все книги ---\n";
    cout << left << setw(32) << "Название"
         << setw(30) << "Автор"
         << setw(27) << "Год"
         << "Оценка\n";
    cout << "-----------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < bookCount; i++) {
        cout << left << setw(25) << books[i].name
             << setw(25) << books[i].author
             << setw(25) << books[i].year
             << books[i].rating << "\n";
    }
}

void showStats() {
    if (bookCount == 0) {
        cout << "Нет данных для анализа.\n";
        return;
    }

    float total = 0;
    float max = books[0].rating;
    const char *nameBook = books[0].name;

    for (int i = 0; i < bookCount; i++) {
        total += books[i].rating;
        if (books[i].rating > max) {
            max = books[i].rating;
            nameBook = books[i].name;
        }
    }

    float average = total / bookCount;

    cout << "\n--- Статистика ---\n";
    cout << "Количество прочитанных книг: " << bookCount << " книг(и)\n";
    cout << "Средняя оценка: " << average << "\n";
    cout << "Самая высоко оценённая книга: " << nameBook << "\n";
}

void showmenu() {
    cout << "\n=== Трекер книг ===\n";
    cout << "1. Добавить книгу\n";
    cout << "2. Показать все книги\n";
    cout << "3. Показать статистику\n";
    cout << "4. Выход\n";
    cout << "Выберите пункт: ";
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    loadBooks("books.txt");
    int choice;

    do {
        showmenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                showAllBooks();
                break;
            case 3:
                showStats();
                break;
            case 4:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор.\n";
        }
    } while (choice != 4);

    return 0;
}
