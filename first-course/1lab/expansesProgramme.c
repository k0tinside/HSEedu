#include <stdio.h>
#include <windows.h>

#define MAX_EXPENSES 1000

struct Expense {
    char date[11];
    char category[30];
    float amount;
};

struct Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

void loadExpenses(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return;

    char line[100];
    while (fgets(line, sizeof(line), file) && expenseCount < MAX_EXPENSES) {
        struct Expense e;
        if (sscanf(line, "%10s %29s %f", e.date, e.category, &e.amount) == 3) {
            expenses[expenseCount++] = e;
        }
    }
    fclose(file);
}

void saveExpenseToFile(const char *filename, struct Expense e) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        printf("Ошибка открытия файла!\n");
        return;
    }
    fprintf(file, "%s %s %f\n", e.date, e.category, e.amount);
    fclose(file);
}

void addExpense() {
    if (expenseCount >= MAX_EXPENSES) {
        printf("Превышен лимит расходов!\n");
        return;
    }

    struct Expense e;
    printf("Введите дату (дд.мм.гггг): ");
    scanf("%s", e.date);
    printf("Введите категорию: ");
    scanf("%s", e.category);
    printf("Введите сумму: ");
    scanf("%f", &e.amount);

    expenses[expenseCount++] = e;
    saveExpenseToFile("expenses.txt", e);

    printf("Расход добавлен!\n");
}

void showAllExpenses() {
    if (expenseCount == 0) {
        printf("Нет данных о расходах.\n");
        return;
    }

    printf("\n--- Все расходы ---\n");
    printf("%12s %15s %12s\n", "Дата", "Категория", "Сумма");
    printf("-------------------------------------------\n");

    for (int i = 0; i < expenseCount; i++) {
        printf("%12s%15s%10.2f руб.\n", expenses[i].date, expenses[i].category, expenses[i].amount);
    }
}

void showStats() {
    if (expenseCount == 0) {
        printf("Нет данных для анализа.\n");
        return;
    }

    float total = 0;
    float max = expenses[0].amount;

    for (int i = 0; i < expenseCount; i++) {
        total += expenses[i].amount;
        if (expenses[i].amount > max) {
            max = expenses[i].amount;
        }
    }

    float average = total / expenseCount;

    printf("\n--- Статистика ---\n");
    printf("Всего потрачено: %.2f руб.\n", total);
    printf("Средняя трата: %.2f руб.\n", average);
    printf("Максимальная трата: %.2f руб.\n", max);
}

void showMenu() {
    printf("\n--- Статистика ---\n");
    printf("1. Добавить расход\n");
    printf("2. Показать все расходы\n");
    printf("3. Показать статистику\n");
    printf("4. Выход\n");
    printf("Выберите пункт: ");
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    loadExpenses("expenses.txt");

    int choice;
    do {
        showMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: addExpense(); break;
            case 2: showAllExpenses(); break;
            case 3: showStats(); break;
            case 4: printf("Выход из программы.\n"); break;
            default: printf("Некорректный выбор.\n");
        }
    } while (choice != 4);

    return 0;
}