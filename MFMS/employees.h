#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES   100
#define NAME_LEN        50

typedef struct {
    char id[20];
    char name[NAME_LEN];
    char department[NAME_LEN];
    double basic_salary;
    double housing_allowance;
    double transport_allowance;
} Employee;

void addEmployee(Employee employees[], int *count);
void displayEmployees(const Employee employees[], int count);
void searchEmployee(const Employee employees[], int count);
double calculateGrossSalary(const Employee *e);
void employeeMenu(Employee employees[], int *count);

#endif