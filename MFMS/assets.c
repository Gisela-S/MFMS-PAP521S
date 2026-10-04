#include <stdio.h>
#include <string.h>
#include "assets.h"

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

void addAsset(Asset assets[], int *count) {
    if (*count >= MAX_ASSETS) {
        printf("Asset list is full.\n");
        return;
    }

    Asset a;
    a.id[0] = '3';
    a.id[1] = '0';
    a.id[2] = '0';
    a.id[3] = '0' + (*count / 100) % 10;
    a.id[4] = '0' + (*count / 10) % 10;
    a.id[5] = '0' + (*count) % 10;
    a.id[6] = '\0';

    printf("Enter Asset Name: ");
    readLine(a.name, sizeof(a.name));

    printf("Enter Type (Vehicle/Computer/Building/Equipment/Furniture): ");
    readLine(a.type, sizeof(a.type));

    printf("Enter Purchase Value (N$): ");
    if (scanf("%lf", &a.value) != 1) {
        printf("Invalid value.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (a.value < 0) {
        printf("Asset value cannot be negative.\n");
        return;
    }

    printf("Enter Condition (New/Good/Fair/Poor): ");
    readLine(a.condition, sizeof(a.condition));

    assets[*count] = a;
    (*count)++;

    printf("Asset added successfully. ID: %s\n", a.id);
}

void displayAssets(const Asset assets[], int count) {
    if (count == 0) {
        printf("No assets recorded yet.\n");
        return;
    }

    printf("\n%-10s %-20s %-15s %-15s %-12s\n",
           "ID", "Name", "Type", "Value", "Condition");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-10s %-20s %-15s %-15.2f %-12s\n",
               assets[i].id,
               assets[i].name,
               assets[i].type,
               assets[i].value,
               assets[i].condition);
    }
}

void searchAsset(const Asset assets[], int count) {
    if (count == 0) {
        printf("No assets recorded yet.\n");
        return;
    }

    int option;
    int found = 0;

    printf("Search by (1) ID or (2) Name: ");
    scanf("%d", &option);
    clearInputBuffer();

    if (option == 1) {
        char searchId[20];
        printf("Enter Asset ID: ");
        readLine(searchId, sizeof(searchId));

        for (int i = 0; i < count; i++) {
            if (strcmp(assets[i].id, searchId) == 0) {
                printf("FOUND: %s | Type: %s | Value: N$%.2f | Condition: %s\n",
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

        for (int i = 0; i < count; i++) {
            if (strcmp(assets[i].name, searchName) == 0) {
                printf("FOUND: %s | Type: %s | Value: N$%.2f | Condition: %s\n",
                       assets[i].name, assets[i].type,
                       assets[i].value, assets[i].condition);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("Asset not found.\n");
    }
}

void assetMenu(Asset assets[], int *count) {
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
            case 1: addAsset(assets, count); break;
            case 2: displayAssets(assets, *count); break;
            case 3: searchAsset(assets, *count); break;
            case 4: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}