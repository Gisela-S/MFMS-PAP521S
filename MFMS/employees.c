#include <stdio.h>
#include <string.h>
#include "employees.h"

static void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

void addEmployee(Employee employees[], int *count) {
    if (*count >= MAX_EMPLOYEES) {
        printf("Employee list is full.\n");
        return;
    }

    Employee e;
    e.id[0] = '1';
    e.id[1] = '0';
    e.id[2] = '0';
    e.id[3] = '0' + (*count / 100) % 10;
    e.id[4] = '0' + (*count / 10) % 10;
    e.id[5] = '0' + (*count) % 10;
    e.id[6] = '\0';

    printf("Enter Employee Name: ");
    readLine(e.name, sizeof(e.name));

    printf("Enter Department: ");
    readLine(e.department, sizeof(e.department));

    printf("Enter Basic Salary (N$): ");
    if (scanf("%lf", &e.basic_salary) != 1) {
        printf("Invalid salary input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (e.basic_salary < 0) {
        printf("Salary cannot be negative.\n");
        return;
    }

    e.housing_allowance = e.basic_salary * 0.15;
    e.transport_allowance = e.basic_salary * 0.05;

    employees[*count] = e;
    (*count)++;

    printf("Employee added successfully. ID: %s\n", e.id);
}

void displayEmployees(const Employee employees[], int count) {
    if (count == 0) {
        printf("No employees recorded yet.\n");
        return;
    }

    printf("\n%-10s %-20s %-15s %-12s %-12s %-12s %-12s\n",
           "ID", "Name", "Department", "Basic",
           "Housing", "Transport", "Total");
    printf("---------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        double gross = calculateGrossSalary(&employees[i]);
        printf("%-10s %-20s %-15s %-12.2f %-12.2f %-12.2f %-12.2f\n",
               employees[i].id,
               employees[i].name,
               employees[i].department,
               employees[i].basic_salary,
               employees[i].housing_allowance,
               employees[i].transport_allowance,
               gross);
    }
}

void searchEmployee(const Employee employees[], int count) {
    if (count == 0) {
        printf("No employees recorded yet.\n");
        return;
    }

    int option;
    int found = 0;

    printf("Search by (1) ID or (2) Name: ");
    scanf("%d", &option);
    clearInputBuffer();

    if (option == 1) {
        char searchId[20];
        printf("Enter Employee ID: ");
        readLine(searchId, sizeof(searchId));

        for (int i = 0; i < count; i++) {
            if (strcmp(employees[i].id, searchId) == 0) {
                double gross = calculateGrossSalary(&employees[i]);
                printf("FOUND: ID %s | Name: %s | Dept: %s | Total: N$%.2f\n",
                       employees[i].id, employees[i].name,
                       employees[i].department, gross);
                found = 1;
                break;
            }
        }
    }
    else if (option == 2) {
        char searchName[NAME_LEN];
        printf("Enter Employee Name: ");
        readLine(searchName, sizeof(searchName));

        for (int i = 0; i < count; i++) {
            if (strcmp(employees[i].name, searchName) == 0) {
                double gross = calculateGrossSalary(&employees[i]);
                printf("FOUND: ID %s | Name: %s | Dept: %s | Total: N$%.2f\n",
                       employees[i].id, employees[i].name,
                       employees[i].department, gross);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("Employee not found.\n");
    }
}

double calculateGrossSalary(const Employee *e) {
    return e->basic_salary + e->housing_allowance + e->transport_allowance;
}

void employeeMenu(Employee employees[], int *count) {
    int choice;
    do {
        printf("\n--- Employee Management ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Back to Main Menu\n");
        printf("Select option: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: addEmployee(employees, count); break;
            case 2: displayEmployees(employees, *count); break;
            case 3: searchEmployee(employees, *count); break;
            case 4: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}