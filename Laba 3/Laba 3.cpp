#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>


#define FILE_NAME "employees.dat"
#define MAX_EMPLOYEES 500

typedef struct {
    char surname[80];
    char name[80];
    char patronymic[80];
    char position[120];
    double salary;
}Employee;

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

void addEmployee(void);
void saveEmployees(void);
void loadEmployees(void);
void showEmployees(void);
void searchEmployee(void);
void changeSalary(void);
void changePosition(void);
void sortEmployees(void);
void deleteEmployee(void);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    loadEmployees();

    printf("===================База данных сотрудников==================\n\n");
    int choice = 1, key;
    while (choice) {
        printf("1 - Добавить сотрудника\n");
        printf("2 - Показать всех сотрудников\n");
        printf("3 - Найти сотрудника по ФИО\n");
        printf("4 - Изменить оклад сотрудника\n");
        printf("5 - Изменить должность сотрудника\n");
        printf("6 - Упорядочить сотрудников по фамилии\n");
        printf("7 - Удалить сотрудника\n");
        printf("0 - Выход\n");
        if (scanf("%d", &key) != 1) {
            printf("Выберите функцию программы: ");
            while (getchar() != '\n' && !feof(stdin)) {}
        }
        while (getchar() != '\n' && !feof(stdin)) {}
        switch (key)
        {
        case 1: 
            addEmployee();
            break;
        case 2:
            showEmployees();
            break;
        case 3:
            searchEmployee();
            break;
        case 4:
            changeSalary();
            break;
        case 5:
            changePosition();
            break;
        case 6:
            sortEmployees();
            break;
        case 7:
            deleteEmployee();
            break;
        case 0:
            choice = 0;
            break;
        default:
            printf("Вы выбрали несуществующую функцию, попробуйте снова\n");
            break;
        }
    }
    printf("Работа программы завершена");
    return 0;
}
//Сохранение всех сотрудников в базу данных
void saveEmployees(void) {
    FILE* file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Не удалось сохранить базу данных.\n");
        return;
    }
    fwrite(employees, sizeof(Employee), employeeCount, file);
    fclose(file);
}
//Выгрузка всех сотрудников из базы данных
void loadEmployees(void) {
    FILE* file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        employeeCount = 0;
        return;
    }
    employeeCount = (int)fread(employees, sizeof(Employee), MAX_EMPLOYEES, file);
    fclose(file);
}
//Добавление нового сотрудника (1)
void addEmployee(void)
{
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("База данных заполнена.\n");
        return;
    }

    Employee newEmployee;

    printf("Фамилия: ");
    fgets(newEmployee.surname, sizeof(newEmployee.surname), stdin);
    newEmployee.surname[strcspn(newEmployee.surname, "\n")] = '\0';

    printf("Имя: ");
    fgets(newEmployee.name, sizeof(newEmployee.name), stdin);
    newEmployee.name[strcspn(newEmployee.name, "\n")] = '\0';

    printf("Отчество: ");
    fgets(newEmployee.patronymic, sizeof(newEmployee.patronymic), stdin);
    newEmployee.patronymic[strcspn(newEmployee.patronymic, "\n")] = '\0';

    printf("Должность: ");
    fgets(newEmployee.position, sizeof(newEmployee.position), stdin);
    newEmployee.position[strcspn(newEmployee.position, "\n")] = '\0';

    printf("Оклад: ");
    if (scanf("%lf", &newEmployee.salary) != 1 || newEmployee.salary < 0) {
        printf("Некорректный оклад. Запись не добавлена.\n");
        while (getchar() != '\n' && !feof(stdin)) {}
        return;
    }
    while (getchar() != '\n' && !feof(stdin)) {}

    employees[employeeCount] = newEmployee;
    employeeCount++;
    saveEmployees();
    printf("Сотрудник добавлен.\n");
}
//Показать всех сотрудников (2)
void showEmployees(void) {
    if (employeeCount == 0) {
        printf("База данных пуста.\n");
        return;
    }
    for (int i = 0; i < employeeCount; i++) {
        printf("\nСотрудник №%d\n", i + 1);
        printf("ФИО: %s %s %s\n", employees[i].surname, employees[i].name, employees[i].patronymic);
        printf("Должность: %s\n", employees[i].position);
        printf("Оклад: %.2f\n", employees[i].salary);
    }
}
//Поиск пользователя по ФИО (3)
void searchEmployee(void)
{
    char surname[80], name[80], patronymic[80];
    int found = 0;

    printf("Фамилия: ");
    fgets(surname, sizeof(surname), stdin);
    surname[strcspn(surname, "\n")] = '\0';

    printf("Имя: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Отчество: ");
    fgets(patronymic, sizeof(patronymic), stdin);
    patronymic[strcspn(patronymic, "\n")] = '\0';

    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].surname, surname) == 0 &&
            strcmp(employees[i].name, name) == 0 &&
            strcmp(employees[i].patronymic, patronymic) == 0) {
            printf("\nНайден сотрудник:\n");
            printf("\nСотрудник №%d\n", i + 1);
            printf("%s %s %s\n", employees[i].surname, employees[i].name, employees[i].patronymic);
            printf("Должность: %s\n", employees[i].position);
            printf("Оклад: %.2f\n", employees[i].salary);
            found = 1;
        }
    }
    if (!found) printf("Сотрудник не найден.\n");
}
//Изменение оклада сотрудника (4)
void changeSalary(void)
{
    int number;
    showEmployees();
    if (employeeCount == 0) return;

    printf("Номер сотрудника в списке: ");
    if (scanf("%d", &number) != 1) {
        printf("Некорректный номер.\n");
        while (getchar() != '\n' && !feof(stdin)) {}
        return;
    }
    while (getchar() != '\n' && !feof(stdin)) {}

    if (number < 1 || number > employeeCount) {
        printf("Такого номера нет.\n");
        return;
    }

    printf("Новый оклад: ");
    if (scanf("%lf", &employees[number - 1].salary) != 1 ||
        employees[number - 1].salary < 0) {
        printf("Некорректный оклад. Изменение отменено.\n");
        while (getchar() != '\n' && !feof(stdin)) {}
        return;
    }
    while (getchar() != '\n' && !feof(stdin)) {}

    saveEmployees();
    printf("Оклад изменён.\n");
}
//Изменение должности сотрудника (5)
void changePosition(void)
{
    int number;
    showEmployees();
    if (employeeCount == 0) return;

    printf("Номер сотрудника в списке: ");
    if (scanf("%d", &number) != 1) {
        printf("Некорректный номер.\n");
        while (getchar() != '\n' && !feof(stdin)) {}
        return;
    }
    while (getchar() != '\n' && !feof(stdin)) {}

    if (number < 1 || number > employeeCount) {
        printf("Такого номера нет.\n");
        return;
    }

    printf("Новая должность: ");
    fgets(employees[number - 1].position,
        sizeof(employees[number - 1].position), stdin);
    employees[number - 1].position[strcspn(employees[number - 1].position, "\n")] = '\0';

    saveEmployees();
    printf("Должность изменена.\n");
}
//Сортировка по фамилии (6)
void sortEmployees(void)
{
    Employee temp;

    for (int i = 0; i < employeeCount; i++) {
        for (int j = 0; j < employeeCount - 1; j++) {
            if (strcoll(employees[j].surname, employees[j + 1].surname) > 0) {
                temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
    saveEmployees();
    printf("Сортировка по фамилии выполнена.\n");
}
//Удаление пользователя (7)
void deleteEmployee(void)
{
    int number;
    showEmployees();
    if (employeeCount == 0) return;

    printf("Номер сотрудника для удаления: ");
    if (scanf("%d", &number) != 1) {
        printf("Некорректный номер.\n");
        while (getchar() != '\n' && !feof(stdin)) {}
        return;
    }
    while (getchar() != '\n' && !feof(stdin)) {}

    if (number < 1 || number > employeeCount) {
        printf("Такого номера нет.\n");
        return;
    }

    for (int i = number - 1; i < employeeCount - 1; i++) {
        employees[i] = employees[i + 1];
    }
    employeeCount--;
    saveEmployees();
    printf("Сотрудник удалён.\n");
}