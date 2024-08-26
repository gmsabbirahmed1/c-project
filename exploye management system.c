#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define FILE_NAME "employees.dat"

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float salary;
} Employee;

// Function prototypes
void addEmployee();
void displayEmployees();
void searchEmployee();
void deleteEmployee();
int getNewEmployeeID();

int main() {
    int choice;

    while(1) {
        printf("\n*** Employee Management System ***\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                deleteEmployee();
                break;
            case 5:
                printf("Exiting the system...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to add a new employee
void addEmployee() {
    FILE *file;
    Employee emp;

    file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    emp.id = getNewEmployeeID();

    printf("Enter Employee Name: ");
    getchar(); // to consume the newline left by previous input
    fgets(emp.name, MAX_NAME_LEN, stdin);
    emp.name[strcspn(emp.name, "\n")] = '\0';  // Remove newline character from string

    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(Employee), 1, file);

    fclose(file);

    printf("Employee added successfully.\n");
}

// Function to display all employees
void displayEmployees() {
    FILE *file;
    Employee emp;

    file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No employees found.\n");
        return;
    }

    printf("\nEmployee Details:\n");
    printf("ID\tName\t\tSalary\n");
    printf("---------------------------------\n");

    while (fread(&emp, sizeof(Employee), 1, file)) {
        printf("%d\t%s\t\t%.2f\n", emp.id, emp.name, emp.salary);
    }

    fclose(file);
}

// Function to search for an employee by ID
void searchEmployee() {
    FILE *file;
    Employee emp;
    int id, found = 0;

    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No employees found.\n");
        return;
    }

    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            printf("\nEmployee Details:\n");
            printf("ID: %d\n", emp.id);
            printf("Name: %s\n", emp.name);
            printf("Salary: %.2f\n", emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }

    fclose(file);
}

// Function to delete an employee by ID
void deleteEmployee() {
    FILE *file, *tempFile;
    Employee emp;
    int id, found = 0;

    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No employees found.\n");
        return;
    }

    tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        printf("Unable to open temporary file.\n");
        fclose(file);
        return;
    }

    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id != id) {
            fwrite(&emp, sizeof(Employee), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) {
        printf("Employee with ID %d deleted successfully.\n", id);
    } else {
        printf("Employee with ID %d not found.\n", id);
    }
}

// Function to generate a new employee ID
int getNewEmployeeID() {
    FILE *file;
    Employee emp;
    int id = 1;

    file = fopen(FILE_NAME, "rb");
    if (file != NULL) {
        while (fread(&emp, sizeof(Employee), 1, file)) {
            id = emp.id + 1;
        }
        fclose(file);
    }

    return id;
}
