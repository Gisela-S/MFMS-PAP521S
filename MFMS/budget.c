#include <stdio.h>
#include <string.h>
#include "budget.h"

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

void addBudget(Budget budgets[], int *count) {
    if (*count >= MAX_DEPARTMENTS) {
        printf("Budget list is full.\n");
        return;
    }

    Budget b;

    printf("Enter Department Name: ");
    readLine(b.department, sizeof(b.department));

    printf("Enter Allocated Budget (N$): ");
    if (scanf("%lf", &b.allocated) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (b.allocated < 0) {
        printf("Budget cannot be negative.\n");
        return;
    }

    b.expenditure = 0.0;
    budgets[*count] = b;
    (*count)++;

    printf("Budget for '%s' added successfully.\n", b.department);
}

void enterExpenditure(Budget budgets[], int count) {
    if (count == 0) {
        printf("No budgets recorded yet.\n");
        return;
    }

    char name[50];
    int found = 0;

    printf("Enter Department Name: ");
    readLine(name, sizeof(name));

    for (int i = 0; i < count; i++) {
        if (strcmp(budgets[i].department, name) == 0) {
            double amount;
            printf("Enter Expenditure Amount (N$): ");
            if (scanf("%lf", &amount) != 1) {
                printf("Invalid amount.\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();

            if (amount < 0) {
                printf("Expenditure cannot be negative.\n");
                return;
            }

            budgets[i].expenditure += amount;
            printf("Expenditure recorded for '%s'.\n", budgets[i].department);

            if (budgets[i].expenditure > budgets[i].allocated) {
                printf("WARNING: '%s' has EXCEEDED its budget!\n",
                       budgets[i].department);
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Department '%s' not found.\n", name);
    }
}

void displayBudgets(const Budget budgets[], int count) {
    if (count == 0) {
        printf("No budgets recorded yet.\n");
        return;
    }

    printf("\n%-20s %-15s %-15s %-15s %-15s\n",
           "Department", "Allocated", "Expenditure",
           "Remaining", "Status");
    printf("---------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        double remaining = budgets[i].allocated - budgets[i].expenditure;
        const char *status;

        if (remaining >= 0) {
            status = "WITHIN BUDGET";
        } else {
            status = "EXCEEDED";
        }

        printf("%-20s %-15.2f %-15.2f %-15.2f %-15s\n",
               budgets[i].department,
               budgets[i].allocated,
               budgets[i].expenditure,
               remaining,
               status);
    }
}

void budgetMenu(Budget budgets[], int *count) {
    int choice;
    do {
        printf("\n--- Budget Management ---\n");
        printf("1. Add Department Budget\n");
        printf("2. Enter Expenditure\n");
        printf("3. Display Budgets\n");
        printf("4. Back to Main Menu\n");
        printf("Select option: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: addBudget(budgets, count); break;
            case 2: enterExpenditure(budgets, *count); break;
            case 3: displayBudgets(budgets, *count); break;
            case 4: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}