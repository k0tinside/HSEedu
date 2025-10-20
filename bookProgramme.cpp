#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

const int MAX_BOOKS = 1000;


struct Book
{
    char name[100];
    char author[50];
    int year; 
    float rating;
};

// Глобальный массив для хранения всех расходов
Book books[MAX_BOOKS];
int bookCount = 0; // Текущее количество записей расходов



void loadBooks(const char *filename)
{
    ifstream fin(filename);

    if (!fin)
        return;

    while (fin >> books[bookCount].name >> books[bookCount].author >> books[bookCount].year >> books[bookCount].rating)
    {
        bookCount++;
    }

    fin.close();
}


void saveBookToFile(const char *filename, Book b)
{
    ofstream fout(filename, ios::app);

    if (!fout)
    {
        cout << "Ошибка при сохранении файла!" << endl;
        return;
    }

    fout << b.name << " " << b.author << " " << b.year << b.rating << endl;
    fout.close(); 
}



void addBook()
{
    // Проверяем, не превышен ли лимит
    if (bookCount >= MAX_BOOKS)
    {
        cout << "Превышен лимит расходов!" << endl;
        return;
    }

    Book b; // Создаём новую переменную для расхода

    // Считываем данные от пользователя
    cout << "Введите название книги: ";
    cin >> b.name;

    cout << "Введите автора книги: ";
    cin >> b.author;

    cout << "Введите год прочтения: ";
    cin >> b.year;

    cout << "Введите оценку: ";
    cin >> b.rating;

    // Добавляем в массив и сохраняем в файл
    books[bookCount++] = b;
    saveBookToFile("expenses.txt", b);

    cout << "Книга добавлена!\n";
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

    int choice;

    do {
        showmenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
            case 2:
            case 3:
            case 4:
            default:
                cout << "Неверный выбор.\n";
        }
    }

    return 0;
}