#include <stdio.h>
#include <string.h>

#define MAX 100

/* ============================================================
   DATA STRUCTURES
   ============================================================ */

typedef struct {
    char id[20];
    char name[50];
    char department[30];
    double basic_salary;
    double housing_allowance;
    double transport_allowance;
} Employee;

typedef struct {
    char department[30];
    double allocated;
    double expenditure;
} Budget;

typedef struct {
    char id[20];
    char name[50];
    char email[50];
    char phone[20];
    char town[30];
} Supplier;

typedef struct {
    char id[20];
    char name[50];
    char type[30];
    double value;
    char condition[20];
} Asset;

/* ============================================================
   GLOBAL STORAGE
   ============================================================ */

Employee employees[MAX];
int emp_count = 0;

Budget budgets[MAX];
int budget_count = 0;

Supplier suppliers[MAX];
int supplier_count = 0;

Asset assets[MAX];
int asset_count = 0;

/* ============================================================
   FUNCTION PROTOTYPES
   ============================================================ */

void displayMenu();
void employeeManagement();
void budgetManagement();
void supplierManagement();
void assetManagement();
void generateReports();

void clearInputBuffer();
void readLine(char *buffer, int size);

void addEmployee();
void displayEmployees();
void searchEmployee();

void addBudget();
void displayBudgets();
void enterExpenditure();

void addSupplier();
void displaySuppliers();
void searchSupplier();

void addAsset();
void displayAssets();
void searchAsset();

/* ============================================================
   MAIN
   ============================================================ */

int main() {
    int choice;

    printf("\nWelcome to the Municipal Financial Management System\n");

    do {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid numeric input!\n");
            clearInputBuffer();
            choice = 0;
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: employeeManagement(); break;
            case 2: budgetManagement();   break;
            case 3: supplierManagement(); break;
            case 4: assetManagement();    break;
            case 5: generateReports();    break;
            case 6: printf("\nExiting system. Goodbye!\n"); break;
            default: printf("\nInvalid choice! Please select 1-6.\n");
        }
    } while (choice != 6);

    return 0;
}

/* ============================================================
   HELPER FUNCTIONS
   ============================================================ */

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

/* ============================================================
   MAIN MENU
   ============================================================ */

void displayMenu() {
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

/* ============================================================
   EMPLOYEE MANAGEMENT
   ============================================================ */

void employeeManagement() {
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
            case 1: addEmployee();       break;
            case 2: displayEmployees();  break;
            case 3: searchEmployee();    break;
            case 4: printf("\nReturning to main menu...\n"); break;
            default: printf("\nInvalid choice!\n");
        }
    } while (choice != 4);
}

void addEmployee() {
    if (emp_count >= MAX) {
        printf("Database full!\n");
        return;
    }

    Employee e;

    printf("Enter ID: ");
    readLine(e.id, sizeof(e.id));

    printf("Enter Name: ");
    readLine(e.name, sizeof(e.name));

    printf("Enter Department: ");
    readLine(e.department, sizeof(e.department));

    printf("Enter Basic Salary (N$): ");
    if (scanf("%lf", &e.basic_salary) != 1) {
        printf("Invalid salary input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (e.basic_salary < 0) {
        printf("Invalid negative salary!\n");
        return;
    }

    e.housing_allowance = e.basic_salary * 0.15;
    e.transport_allowance = e.basic_salary * 0.05;

    employees[emp_count++] = e;
    printf("Employee added successfully!\n");
}

void displayEmployees() {
    if (emp_count == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    printf("\n%-10s %-20s %-15s %-12s %-12s %-12s %-12s\n",
           "ID", "Name", "Department", "Basic",
           "Housing", "Transport", "Total");
    printf("---------------------------------------------------------------------------------------\n");

    for (int i = 0; i < emp_count; i++) {
        double gross = employees[i].basic_salary
                     + employees[i].housing_allowance
                     + employees[i].transport_allowance;
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

void searchEmployee() {
    if (emp_count == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    int option;
    int found = 0;

    printf("\nSearch by (1) ID or (2) Name: ");
    scanf("%d", &option);
    clearInputBuffer();

    if (option == 1) {
        char searchId[20];
        printf("Enter Employee ID: ");
        readLine(searchId, sizeof(searchId));

        for (int i = 0; i < emp_count; i++) {
            if (strcmp(employees[i].id, searchId) == 0) {
                double gross = employees[i].basic_salary
                             + employees[i].housing_allowance
                             + employees[i].transport_allowance;
                printf("\n[FOUND] ID: %s | Name: %s | Dept: %s | Total: N$%.2f\n",
                       employees[i].id, employees[i].name,
                       employees[i].department, gross);
                found = 1;
                break;
            }
        }
    }
    else if (option == 2) {
        char searchName[50];
        printf("Enter Employee Name: ");
        readLine(searchName, sizeof(searchName));

        for (int i = 0; i < emp_count; i++) {
            if (strcmp(employees[i].name, searchName) == 0) {
                double gross = employees[i].basic_salary
                             + employees[i].housing_allowance
                             + employees[i].transport_allowance;
                printf("\n[FOUND] ID: %s | Name: %s | Dept: %s | Total: N$%.2f\n",
                       employees[i].id, employees[i].name,
                       employees[i].department, gross);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("\nEmployee not found.\n");
    }
}

/* ============================================================
   BUDGET MANAGEMENT
   ============================================================ */

void budgetManagement() {
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
            case 1: addBudget();          break;
            case 2: enterExpenditure();   break;
            case 3: displayBudgets();     break;
            case 4: printf("\nReturning to main menu...\n"); break;
            default: printf("\nInvalid choice!\n");
        }
    } while (choice != 4);
}

void addBudget() {
    if (budget_count >= MAX) {
        printf("Database full!\n");
        return;
    }

    Budget b;

    printf("Enter Department Name: ");
    readLine(b.department, sizeof(b.department));

    printf("Enter Allocated Budget (N$): ");
    if (scanf("%lf", &b.allocated) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (b.allocated < 0) {
        printf("Budget cannot be negative!\n");
        return;
    }

    b.expenditure = 0.0;
    budgets[budget_count++] = b;

    printf("Budget for '%s' added successfully.\n", b.department);
}

void enterExpenditure() {
    if (budget_count == 0) {
        printf("No budgets recorded yet.\n");
        return;
    }

    char name[30];
    int found = 0;

    printf("Enter Department Name: ");
    readLine(name, sizeof(name));

    for (int i = 0; i < budget_count; i++) {
        if (strcmp(budgets[i].department, name) == 0) {
            double amount;
            printf("Enter Expenditure Amount (N$): ");
            if (scanf("%lf", &amount) != 1) {
                printf("Invalid amount!\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();

            if (amount < 0) {
                printf("Expenditure cannot be negative!\n");
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

void displayBudgets() {
    if (budget_count == 0) {
        printf("No budgets recorded yet.\n");
        return;
    }

    printf("\n%-20s %-15s %-15s %-15s %-15s\n",
           "Department", "Allocated", "Expenditure",
           "Remaining", "Status");
    printf("---------------------------------------------------------------------------------\n");

    for (int i = 0; i < budget_count; i++) {
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

/* ============================================================
   SUPPLIER MANAGEMENT
   ============================================================ */

void supplierManagement() {
    int choice;
    do {
        printf("\n--- Supplier Management ---\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back to Main Menu\n");
        printf("Select option: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: addSupplier();       break;
            case 2: displaySuppliers();  break;
            case 3: searchSupplier();    break;
            case 4: printf("\nReturning to main menu...\n"); break;
            default: printf("\nInvalid choice!\n");
        }
    } while (choice != 4);
}

void addSupplier() {
    if (supplier_count >= MAX) {
        printf("Database full!\n");
        return;
    }

    Supplier s;

    printf("Enter Supplier ID: ");
    readLine(s.id, sizeof(s.id));

    printf("Enter Supplier Name: ");
    readLine(s.name, sizeof(s.name));

    printf("Enter Email: ");
    readLine(s.email, sizeof(s.email));

    printf("Enter Phone: ");
    readLine(s.phone, sizeof(s.phone));

    printf("Enter Town/Location: ");
    readLine(s.town, sizeof(s.town));

    suppliers[supplier_count++] = s;
    printf("Supplier registered successfully.\n");
}

void displaySuppliers() {
    if (supplier_count == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    printf("\n%-10s %-20s %-25s %-15s %-15s\n",
           "ID", "Name", "Email", "Phone", "Town");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < supplier_count; i++) {
        printf("%-10s %-20s %-25s %-15s %-15s\n",
               suppliers[i].id, suppliers[i].name,
               suppliers[i].email, suppliers[i].phone,
               suppliers[i].town);
    }
}

void searchSupplier() {
    if (supplier_count == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    int option;
    int found = 0;

    printf("\nSearch by (1) ID or (2) Name: ");
    scanf("%d", &option);
    clearInputBuffer();

    if (option == 1) {
        char searchId[20];
        printf("Enter Supplier ID: ");
        readLine(searchId, sizeof(searchId));

        for (int i = 0; i < supplier_count; i++) {
            if (strcmp(suppliers[i].id, searchId) == 0) {
                printf("\n[FOUND] %s | %s | %s | %s\n",
                       suppliers[i].name, suppliers[i].email,
                       suppliers[i].phone, suppliers[i].town);
                found = 1;
                break;
            }
        }
    }
    else if (option == 2) {
        char searchName[50];
        printf("Enter Supplier Name: ");
        readLine(searchName, sizeof(searchName));

        for (int i = 0; i < supplier_count; i++) {
            if (strcmp(suppliers[i].name, searchName) == 0) {
                printf("\n[FOUND] %s | %s | %s | %s\n",
                       suppliers[i].name, suppliers[i].email,
                       suppliers[i].phone, suppliers[i].town);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("\nSupplier not found.\n");
    }
}

/* ============================================================
   ASSET MANAGEMENT
   ============================================================ */

void assetManagement() {
    int choice;
    do {
        printf("\n--- Asset Management ---\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back to Main Menu\n");
        printf("Select option: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: addAsset();       break;
            case 2: displayAssets();  break;
            case 3: searchAsset();    break;
            case 4: printf("\nReturning to main menu...\n"); break;
            default: printf("\nInvalid choice!\n");
        }
    } while (choice != 4);
}

void addAsset() {
    if (asset_count >= MAX) {
        printf("Database full!\n");
        return;
    }

    Asset a;

    printf("Enter Asset ID: ");
    readLine(a.id, sizeof(a.id));

    printf("Enter Asset Name: ");
    readLine(a.name, sizeof(a.name));

    printf("Enter Type (Vehicle/Computer/Building/Equipment/Furniture): ");
    readLine(a.type, sizeof(a.type));

    printf("Enter Purchase Value (N$): ");
    if (scanf("%lf", &a.value) != 1) {
        printf("Invalid value!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (a.value < 0) {
        printf("Asset value cannot be negative!\n");
        return;
    }

    printf("Enter Condition (New/Good/Fair/Poor): ");
    readLine(a.condition, sizeof(a.condition));

    assets[asset_count++] = a;
    printf("Asset logged successfully.\n");
}

void displayAssets() {
    if (asset_count == 0) {
        printf("No assets registered yet.\n");
        return;
    }

    printf("\n%-10s %-20s %-15s %-15s %-12s\n",
           "ID", "Name", "Type", "Value", "Condition");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < asset_count; i++) {
        printf("%-10s %-20s %-15s %-15.2f %-12s\n",
               assets[i].id, assets[i].name,
               assets[i].type, assets[i].value,
               assets[i].condition);
    }
}

void searchAsset() {
    if (asset_count == 0) {
        printf("No assets registered yet.\n");
        return;
    }

    int option;
    int found = 0;

    printf("\nSearch by (1) ID or (2) Name: ");
    scanf("%d", &option);
    clearInputBuffer();

    if (option == 1) {
        char searchId[20];
        printf("Enter Asset ID: ");
        readLine(searchId, sizeof(searchId));

        for (int i = 0; i < asset_count; i++) {
            if (strcmp(assets[i].id, searchId) == 0) {
                printf("\n[FOUND] %s | Type: %s | Value: N$%.2f | Condition: %s\n",
                       assets[i].name, assets[i].type,
                       assets[i].value, assets[i].condition);
                found = 1;
                break;
            }
        }
    }
    else if (option == 2) {
        char searchName[50];
        printf("Enter Asset Name: ");
        readLine(searchName, sizeof(searchName));

        for (int i = 0; i < asset_count; i++) {
            if (strcmp(assets[i].name, searchName) == 0) {
                printf("\n[FOUND] %s | Type: %s | Value: N$%.2f | Condition: %s\n",
                       assets[i].name, assets[i].type,
                       assets[i].value, assets[i].condition);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("\nAsset not found.\n");
    }
}

/* ============================================================
   REPORTS
   ============================================================ */

void generateReports() {
    printf("\n========================================\n");
    printf("       MUNICIPAL FINANCIAL REPORTS       \n");
    printf("========================================\n");

    /* ----- EMPLOYEE REPORT ----- */
    printf("\n===== EMPLOYEE REPORT =====\n");
    printf("Total Employees: %d\n", emp_count);

    if (emp_count > 0) {
        double total = 0.0;
        double highest = 0.0;
        double lowest = -1.0;
        int first = 1;

        for (int i = 0; i < emp_count; i++) {
            double gross = employees[i].basic_salary
                         + employees[i].housing_allowance
                         + employees[i].transport_allowance;
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

        printf("Average Salary: N$%.2f\n", total / emp_count);
        printf("Highest Salary: N$%.2f\n", highest);
        printf("Lowest Salary:  N$%.2f\n", lowest);
    }

    /* ----- BUDGET REPORT ----- */
    printf("\n===== BUDGET REPORT =====\n");

    if (budget_count == 0) {
        printf("No department budgets recorded yet.\n");
    } else {
        double totalAlloc = 0.0;
        double totalExp = 0.0;
        int overBudget = 0;

        for (int i = 0; i < budget_count; i++) {
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
            for (int i = 0; i < budget_count; i++) {
                if (budgets[i].expenditure > budgets[i].allocated) {
                    double over = budgets[i].expenditure - budgets[i].allocated;
                    printf(" - %s (Over by N$%.2f)\n",
                           budgets[i].department, over);
                }
            }
        }
    }

    /* ----- SUPPLIER REPORT ----- */
    printf("\n===== SUPPLIER REPORT =====\n");
    printf("Total Suppliers: %d\n", supplier_count);

    for (int i = 0; i < supplier_count; i++) {
        printf(" - %s (%s), %s\n",
               suppliers[i].name, suppliers[i].town, suppliers[i].phone);
    }

    /* ----- ASSET REPORT ----- */
    printf("\n===== ASSET REPORT =====\n");
    printf("Total Assets: %d\n", asset_count);

    double totalAssetValue = 0.0;
    for (int i = 0; i < asset_count; i++) {
        totalAssetValue += assets[i].value;
    }
    printf("Total Asset Value: N$%.2f\n", totalAssetValue);

    for (int i = 0; i < asset_count; i++) {
        printf(" - %s (%s), Condition: %s\n",
               assets[i].name, assets[i].type, assets[i].condition);
    }

    printf("\n========================================\n");
    printf("           END OF REPORTS               \n");
    printf("========================================\n");
}