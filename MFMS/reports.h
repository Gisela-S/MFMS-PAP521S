#ifndef REPORTS_H
#define REPORTS_H

#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

void generateReports(const Employee employees[], int empCount,
                     const Budget budgets[], int budCount,
                     const Supplier suppliers[], int supCount,
                     const Asset assets[], int astCount);

#endif