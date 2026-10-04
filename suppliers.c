/* ========================================================================
 * suppliers.c
 * Supplier Management module (Student 3 responsibility).
 *
 * Demonstrates: arrays, strings (strcmp for search/duplicate checks),
 * functions and loops.
 * ======================================================================== */

#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "utils.h"

void addSupplier(Supplier suppliers[], int *count) {
    if (*count >= MAX_SUPPLIERS) {
        printf("\nError: Supplier list is full (maximum %d).\n", MAX_SUPPLIERS);
        return;
    }

    Supplier newSup;
    newSup.supplierId = getValidatedInt("Enter Supplier ID: ", 1, 999999);

    for (int i = 0; i < *count; i++) {
        if (suppliers[i].supplierId == newSup.supplierId) {
            printf("Error: Supplier ID %d already exists.\n", newSup.supplierId);
            return;
        }
    }

    getValidatedString("Enter Supplier Name: ", newSup.name, NAME_LEN);
    getValidatedString("Enter Email Address: ", newSup.email, STR_LEN);
    getValidatedString("Enter Telephone Number: ", newSup.phone, PHONE_LEN);
    getValidatedString("Enter Town/Location: ", newSup.town, NAME_LEN);

    suppliers[*count] = newSup;
    (*count)++;

    printf("\nSupplier '%s' added successfully.\n", newSup.name);
}

void displaySuppliers(const Supplier suppliers[], int count) {
    if (count == 0) {
        printf("\nNo suppliers recorded yet.\n");
        return;
    }

    printf("\n%-6s %-20s %-25s %-15s %-15s\n",
           "ID", "Name", "Email", "Phone", "Town");
    for (int i = 0; i < 85; i++) putchar('-');
    putchar('\n');

    for (int i = 0; i < count; i++) {
        printf("%-6d %-20s %-25s %-15s %-15s\n",
               suppliers[i].supplierId,
               suppliers[i].name,
               suppliers[i].email,
               suppliers[i].phone,
               suppliers[i].town);
    }
}

void searchSupplier(const Supplier suppliers[], int count) {
    if (count == 0) {
        printf("\nNo suppliers recorded yet.\n");
        return;
    }

    int searchChoice = getValidatedInt("Search by (1) Supplier ID or (2) Name: ", 1, 2);
    int found = 0;

    if (searchChoice == 1) {
        int id = getValidatedInt("Enter Supplier ID to search: ", 1, 999999);
        for (int i = 0; i < count; i++) {
            if (suppliers[i].supplierId == id) {
                found = 1;
                printf("\n--- Supplier Found ---\n");
                printf("ID:    %d\n", suppliers[i].supplierId);
                printf("Name:  %s\n", suppliers[i].name);
                printf("Email: %s\n", suppliers[i].email);
                printf("Phone: %s\n", suppliers[i].phone);
                printf("Town:  %s\n", suppliers[i].town);
                break;
            }
        }
    } else {
        char name[NAME_LEN];
        getValidatedString("Enter Supplier Name to search: ", name, NAME_LEN);
        for (int i = 0; i < count; i++) {
            if (strcmp(suppliers[i].name, name) == 0) {
                found = 1;
                printf("\n--- Supplier Found ---\n");
                printf("ID:    %d\n", suppliers[i].supplierId);
                printf("Name:  %s\n", suppliers[i].name);
                printf("Email: %s\n", suppliers[i].email);
                printf("Phone: %s\n", suppliers[i].phone);
                printf("Town:  %s\n", suppliers[i].town);
                break;
            }
        }
    }

    if (!found) {
        printf("\nNo supplier matched your search.\n");
    }
}

void supplierMenu(Supplier suppliers[], int *count) {
    int choice;

    do {
        printf("\n---- SUPPLIER MANAGEMENT ----\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back to Main Menu\n");
        choice = getValidatedInt("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1:
                addSupplier(suppliers, count);
                break;
            case 2:
                displaySuppliers(suppliers, *count);
                break;
            case 3:
                searchSupplier(suppliers, *count);
                break;
            case 4:
                printf("Returning to main menu...\n");
                break;
        }
    } while (choice != 4);
}