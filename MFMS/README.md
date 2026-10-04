Municipal Financial Management System (MFMS)

Course: PAP521S - Programming in Practice
Project: Project A - Foundation System
Group Number: [YOUR GROUP NUMBER]

Group Members

1. [Iipinge Gabriel]     [224020455]
2. [Kandume Jona]        [220106657]
3. [Abigail Angula]      [224020633]
4. [Mutilifa Lovisa]     [220049386]
5. [Victor Shikomba]     [201022303]
6. [Gisela Shigwedhsa]   [222130520]
7. [Petrus Kapembe]      [224009818]


Project Description

MFMS is a menu-driven console application written in ANSI C (C99). It allows
municipal staff to record and manage employees, departmental budgets,
suppliers and assets, and produces summary reports across all four areas.

System Features

Employee Management: add, display, and search employees; calculates
gross salary (basic + housing allowance + transport allowance)

Budget Management: record departmental budgets and expenditure,
calculate remaining budget, flag departments over budget

Supplier Management: add, display, and search suppliers

Asset Management: add, display, and search assets

Reports: employee, budget, supplier, and asset reports
Input validation: rejects negative amounts, empty names, and invalid
menu choices

Project Structure

    MFMS/
    main.c              Entry point and main menu
    employees.h         Employee struct and prototypes
    employees.c         Employee functions
    budget.h            Budget struct and prototypes
    budget.c            Budget functions
    suppliers.h         Supplier struct and prototypes
    suppliers.c         Supplier functions
    assets.h            Asset struct and prototypes
    assets.c            Asset functions
    reports.h           Reports prototype
    reports.c           Reports implementation
    README.md           This file

Compilation Instructions

Using GCC:

    gcc -Wall -Wextra -std=c99 main.c employees.c budget.c suppliers.c assets.c reports.c -o mfms.exe

How to Run the System

On Windows:

    .\mfms.exe

On Linux/Mac:

    ./mfms

Individual Responsibilities

| Member                       | Primary Responsibility                      |
|------------------------------|---------------------------------------------|
| Kandume Jona 220106657       | Employee Management                         |
| Mutilifa Lovisa 220049386    | Budget Management                           |
| Gisela Shigwedhsa 222130520  | Supplier Management                         |
| Abigail Angula 224020633     | Asset Management                            |
| Victor Shikomba 201022303    | Reports                                     |
| Petrus Kapembe               | Functions, integration and validation       |
| Iipinge Gabriel 224020455    | Testing, documentation and Git coordination |