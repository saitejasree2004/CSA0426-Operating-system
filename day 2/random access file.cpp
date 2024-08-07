#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "employee_data.dat"
#define NAME_LENGTH 50

// Structure to represent an employee
typedef struct {
    int id;
    char name[NAME_LENGTH];
    int age;
    float salary;
} Employee;

// Function to add a new employee record
void add_employee(FILE *file, Employee emp) {
    fseek(file, (emp.id - 1) * sizeof(Employee), SEEK_SET);
    fwrite(&emp, sizeof(Employee), 1, file);
    printf("Employee record added/updated.\n");
}

// Function to display employee details
void display_employee(FILE *file, int id) {
    Employee emp;
    fseek(file, (id - 1) * sizeof(Employee), SEEK_SET);
    fread(&emp, sizeof(Employee), 1, file);
    
    if (feof(file)) {
        printf("Employee record not found.\n");
    } else {
        printf("Employee ID: %d\n", emp.id);
        printf("Name: %s\n", emp.name);
        printf("Age: %d\n", emp.age);
        printf("Salary: %.2f\n", emp.salary);
    }
}

// Function to initialize the employee file
void initialize_file(FILE *file) {
    Employee empty = {0, "", 0, 0.0};
    for (int i = 0; i < 100; i++) {
        fwrite(&empty, sizeof(Employee), 1, file);
    }
}

// Main function
int main() {
    FILE *file = fopen(FILE_NAME, "r+b");
    if (file == NULL) {
        file = fopen(FILE_NAME, "w+b");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
        initialize_file(file);
    }

    int choice, id;
    Employee emp;
    while (1) {
        printf("\nEmployee Record Management Menu:\n");
        printf("1. Add/Update Employee\n");
        printf("2. Display Employee\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

        switch (choice) {
            case 1:
                printf("Enter employee ID: ");
                scanf("%d", &emp.id);
                getchar(); // Consume newline character
                printf("Enter employee name: ");
                fgets(emp.name, NAME_LENGTH, stdin);
                emp.name[strcspn(emp.name, "\n")] = '\0'; // Remove newline character
                printf("Enter employee age: ");
                scanf("%d", &emp.age);
                printf("Enter employee salary: ");
                scanf("%f", &emp.salary);
                add_employee(file, emp);
                break;
            case 2:
                printf("Enter employee ID to display: ");
                scanf("%d", &id);
                display_employee(file, id);
                break;
            case 3:
                fclose(file);
                printf("Exiting.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

