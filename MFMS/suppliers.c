#include <stdio.h>
#include <string.h>
#include "suppliers.h"

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

void addSupplier(Supplier suppliers[], int *count) {
    if (*count >= MAX_SUPPLIERS) {
        printf("Supplier list is full.\n");
        return;
    }

    Supplier s;
    s.id[0] = '2';
    s.id[1] = '0';
    s.id[2] = '0';
    s.id[3] = '0' + (*count / 100) % 10;
    s.id[4] = '0' + (*count / 10) % 10;
    s.id[5] = '0' + (*count) % 10;
    s.id[6] = '\0';

    printf("Enter Supplier Name: ");
    readLine(s.name, sizeof(s.name));

    printf("Enter Email: ");
    readLine(s.email, sizeof(s.email));

    printf("Enter Phone: ");
    readLine(s.phone, sizeof(s.phone));

    printf("Enter Town: ");
    readLine(s.town, sizeof(s.town));

    suppliers[*count] = s;
    (*count)++;

    printf("Supplier added successfully. ID: %s\n", s.id);
}

void displaySuppliers(const Supplier suppliers[], int count) {
    if (count == 0) {
        printf("No suppliers recorded yet.\n");
        return;
    }

    printf("\n%-10s %-20s %-25s %-15s %-15s\n",
           "ID", "Name", "Email", "Phone", "Town");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-10s %-20s %-25s %-15s %-15s\n",
               suppliers[i].id,
               suppliers[i].name,
               suppliers[i].email,
               suppliers[i].phone,
               suppliers[i].town);
    }
}

void searchSupplier(const Supplier suppliers[], int count) {
    if (count == 0) {
        printf("No suppliers recorded yet.\n");
        return;
    }

    int option;
    int found = 0;

    printf("Search by (1) ID or (2) Name: ");
    scanf("%d", &option);
    clearInputBuffer();

    if (option == 1) {
        char searchId[20];
        printf("Enter Supplier ID: ");
        readLine(searchId, sizeof(searchId));

        for (int i = 0; i < count; i++) {
            if (strcmp(suppliers[i].id, searchId) == 0) {
                printf("FOUND: %s | %s | %s | %s\n",
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

        for (int i = 0; i < count; i++) {
            if (strcmp(suppliers[i].name, searchName) == 0) {
                printf("FOUND: %s | %s | %s | %s\n",
                       suppliers[i].name, suppliers[i].email,
                       suppliers[i].phone, suppliers[i].town);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("Supplier not found.\n");
    }
}

void supplierMenu(Supplier suppliers[], int *count) {
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
            case 1: addSupplier(suppliers, count); break;
            case 2: displaySuppliers(suppliers, *count); break;
            case 3: searchSupplier(suppliers, *count); break;
            case 4: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}