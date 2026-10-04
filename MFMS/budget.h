#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 20

typedef struct {
    char department[50];
    double allocated;
    double expenditure;
} Budget;

void addBudget(Budget budgets[], int *count);
void enterExpenditure(Budget budgets[], int count);
void displayBudgets(const Budget budgets[], int count);
void budgetMenu(Budget budgets[], int *count);

#endif