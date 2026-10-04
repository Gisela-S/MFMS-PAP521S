
#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include "common.h"

#define MAX_SUPPLIERS 50

typedef struct {
    int  supplierId;
    char name[NAME_LEN];
    char email[STR_LEN];
    char phone[PHONE_LEN];
    char town[NAME_LEN];
} Supplier;

void addSupplier(Supplier suppliers[], int *count);

void displaySuppliers(const Supplier suppliers[], int count);

void searchSupplier(const Supplier suppliers[], int count);

void supplierMenu(Supplier suppliers[], int *count);

#endif 