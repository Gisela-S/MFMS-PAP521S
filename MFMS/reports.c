#include <stdio.h>
#include "reports.h"

void generateReports(const Employee employees[], int empCount,
                     const Budget budgets[], int budCount,
                     const Supplier suppliers[], int supCount,
                     const Asset assets[], int astCount) {

    printf("\n========================================\n");
    printf("       MUNICIPAL FINANCIAL REPORTS       \n");
    printf("========================================\n");

    printf("\n===== EMPLOYEE REPORT =====\n");
    printf("Total Employees: %d\n", empCount);

    if (empCount > 0) {
        double total = 0.0;
        double highest = 0.0;
        double lowest = -1.0;
        int first = 1;

        for (int i = 0; i < empCount; i++) {
            double gross = calculateGrossSalary(&employees[i]);
            total += gross;

            if (first) {
                highest = gross;
                lowest = gross;
                first = 0;
            } else {
                if (gross > highest) highest = gross;
                if (gross < lowest)  lowest = gross;
            }
        }

        printf("Average Salary: N$%.2f\n", total / empCount);
        printf("Highest Salary: N$%.2f\n", highest);
        printf("Lowest Salary:  N$%.2f\n", lowest);
    }

    printf("\n===== BUDGET REPORT =====\n");

    if (budCount == 0) {
        printf("No department budgets recorded yet.\n");
    } else {
        double totalAlloc = 0.0;
        double totalExp = 0.0;
        int overBudget = 0;

        for (int i = 0; i < budCount; i++) {
            totalAlloc += budgets[i].allocated;
            totalExp   += budgets[i].expenditure;
            if (budgets[i].expenditure > budgets[i].allocated) {
                overBudget++;
            }
        }

        printf("Total Allocated Budget: N$%.2f\n", totalAlloc);
        printf("Total Expenditure:      N$%.2f\n", totalExp);
        printf("Remaining Budget:       N$%.2f\n", totalAlloc - totalExp);
        printf("Departments Exceeding Budget: %d\n", overBudget);

        if (overBudget > 0) {
            printf("\nDepartments over budget:\n");
            for (int i = 0; i < budCount; i++) {
                if (budgets[i].expenditure > budgets[i].allocated) {
                    double over = budgets[i].expenditure - budgets[i].allocated;
                    printf(" - %s (Over by N$%.2f)\n",
                           budgets[i].department, over);
                }
            }
        }
    }

    printf("\n===== SUPPLIER REPORT =====\n");
    printf("Total Suppliers: %d\n", supCount);

    for (int i = 0; i < supCount; i++) {
        printf(" - %s (%s), %s\n",
               suppliers[i].name, suppliers[i].town, suppliers[i].phone);
    }

    printf("\n===== ASSET REPORT =====\n");
    printf("Total Assets: %d\n", astCount);

    double totalAssetValue = 0.0;
    for (int i = 0; i < astCount; i++) {
        totalAssetValue += assets[i].value;
    }
    printf("Total Asset Value: N$%.2f\n", totalAssetValue);

    for (int i = 0; i < astCount; i++) {
        printf(" - %s (%s), Condition: %s\n",
               assets[i].name, assets[i].type, assets[i].condition);
    }

    printf("\n========================================\n");
    printf("           END OF REPORTS               \n");
    printf("========================================\n");
}