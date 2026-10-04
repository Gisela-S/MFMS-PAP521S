#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100

typedef struct {
    char id[20];
    char name[50];
    char email[50];
    char phone[20];
    char town[30];
} Supplier;

void addSupplier(Supplier suppliers[], int *count);
void displaySuppliers(const Supplier suppliers[], int count);
void searchSupplier(const Supplier suppliers[], int count);
void supplierMenu(Supplier suppliers[], int *count);

#endif