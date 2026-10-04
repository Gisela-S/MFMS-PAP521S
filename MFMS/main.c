// Contributed by Jona Kandume
#include <stdio.h>
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

static void displayMenu() {
    printf("\n========================================\n");
    printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM \n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
    printf("========================================\n");
}

static void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int main() {
    Employee employees[MAX_EMPLOYEES];
    int empCount = 0;

    Budget budgets[MAX_DEPARTMENTS];
    int budCount = 0;

    Supplier suppliers[MAX_SUPPLIERS];
    int supCount = 0;

    Asset assets[MAX_ASSETS];
    int astCount = 0;

    int choice;

    printf("\nWelcome to the Municipal Financial Management System\n");

    do {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            choice = 0;
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: employeeMenu(employees, &empCount); break;
            case 2: budgetMenu(budgets, &budCount); break;
            case 3: supplierMenu(suppliers, &supCount); break;
            case 4: assetMenu(assets, &astCount); break;
            case 5:
                generateReports(employees, empCount,
                                budgets, budCount,
                                suppliers, supCount,
                                assets, astCount);
                break;
            case 6:
                printf("\nExiting system. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please select 1-6.\n");
        }
    } while (choice != 6);

    return 0;
}
