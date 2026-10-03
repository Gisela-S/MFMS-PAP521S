Municipal Financial Management System (MFMS)

Course: PAP521S - Programming in Practice
Project: Project A - Foundation System

Group Members

| # | Name                    | Student Number |
|---|------                   |----------------|
| 1 | Kandume Jona            | 220106657      |
| 2 | Mutilifa Lovisa         | 220049386
| 3 | Gabriel Iipnge          | 224020455 
| 4 | Abigail Angula          | 224020633
| 5 | Victor Shikomba         | 201022303
| 6 | Gisela Shigwedha        | 222130520
| 7 |                         | 

Project Description

MFMS is a menu driven console application written in ANSI C (C99). It
allows municipal staff to record and manage employees, departmental
budgets, suppliers and assets. The system also produces basic reports
across all four areas. This is the foundation version of the system
(Project A), which will be extended in Project B.

System Features

Employee Management: add, display and search employees;
  calculates gross salary (basic + housing allowance + transport allowance)
Budget Management: record departmental budgets and expenditure,
  calculate remaining budget, flag departments over budget
Supplier Management: add, display and search suppliers by ID or name
Asset Management: add, display and search assets
Reports: employee, budget, supplier and asset reports
Input validation: rejects negative amounts, empty names and invalid
  menu choices

Compilation Instructions

Using GCC:

```bash
gcc -Wall -Wextra -std=c99 main.c -o mfms.exe