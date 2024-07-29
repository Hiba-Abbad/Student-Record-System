#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 300

typedef struct StudentInformation {
    int rollNo;
    char name[100];
    char fatherName[100];
    int age; 
    int joiningClass;
    int joiningYear;
} Student;

void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;
    printf("                             Student Record System\n");

    while (1) {
        printf("\n1. Add student\n2. View students\n3. Search student\n4. Update student\n5. Delete student\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void addStudent() {
    Student student;
    FILE *file = fopen("Students.txt", "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Roll no: ");
    scanf("%d", &student.rollNo);

    printf("Enter name: ");
    scanf("%s", student.name);
    printf("Enter father's name: ");
    scanf("%s", student.fatherName);
    printf("Enter age: ");
    scanf("%d", &student.age);
    
    printf("Enter joining year: ");
    scanf("%d", &student.joiningYear);
    printf("Enter Class: ");
    scanf("%d", &student.joiningClass);

    fprintf(file, "Roll no: %d\n", student.rollNo);
    fprintf(file, "Student name: %s\n", student.name);
    fprintf(file, "Father's name: %s\n", student.fatherName);
    fprintf(file, "Age: %d\n", student.age);
    fprintf(file, "Joining year: %d\n", student.joiningYear);
    fprintf(file, "Class: %d\n", student.joiningClass);
    fprintf(file, "<------------------------------------>\n");
    fclose(file);
    printf("Student record added successfully.\n");
}

void viewStudents() {
    char line[256];
    FILE *file = fopen("Students.txt", "r");

    if (file == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\nStudents Details:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

void searchStudent() {
    int rollNo;
    char line[256];
    Student student;
    FILE *file = fopen("Students.txt", "r");

    if (file == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter roll no to search: ");
    scanf("%d", &rollNo);

    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "Roll no: %d", &student.rollNo) == 1 && student.rollNo == rollNo) {
            found = 1;
            printf("\nStudent Details:\n");
            printf("%s", line);
            while (fgets(line, sizeof(line), file) && strncmp(line, "<------------------------------------>", 37) != 0) {
                printf("%s", line);
            }
            printf("%s", line); // Print the final separator line
            break;
        }
    }
    if (!found) {
        printf("Student not found!\n");
    }
    fclose(file);
}

void updateStudent() {
    int rollNo, found = 0;
    Student student;
    Student students[MAX_STUDENTS];
    int count = 0;
    char line[256];

    FILE *file = fopen("Students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter roll no to update: ");
    scanf("%d", &rollNo);

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "Roll no: %d", &students[count].rollNo) == 1) {
            if (students[count].rollNo == rollNo) {
                found = 1;
                printf("Enter new name: ");
                scanf("%s", students[count].name);
                printf("Enter new father's name: ");
                scanf("%s", students[count].fatherName);
                printf("Enter new age: ");
                scanf("%d", &students[count].age);
                printf("Enter new roll no: ");
                scanf("%d", &students[count].rollNo);
                printf("Enter new joining year: ");
                scanf("%d", &students[count].joiningYear);
                printf("Enter new class: ");
                scanf("%d", &students[count].joiningClass);
            }
            fprintf(temp, "Student name: %s\n", students[count].name);
            fprintf(temp, "Father's name: %s\n", students[count].fatherName);
            fprintf(temp, "Age: %d\n", students[count].age);
            fprintf(temp, "Roll no: %d\n", students[count].rollNo);
            fprintf(temp, "Joining year: %d\n", students[count].joiningYear);
            fprintf(temp, "Class: %d\n", students[count].joiningClass);
            fprintf(temp, "<------------------------------------>\n");
            count++;
        } else {
            fprintf(temp, "%s", line);
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("Students.txt");
        rename("temp.txt", "Students.txt");
        printf("Student record updated successfully.\n");
    } else {
        printf("Student not found.\n");
        remove("temp.txt");
    }
}

void deleteStudent() {
    int rollNo, found = 0;
    Student student;
    char line[256];

    FILE *file = fopen("Students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter roll no to delete: ");
    scanf("%d", &rollNo);

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "Roll no: %d", &student.rollNo) == 1 && student.rollNo == rollNo) {
            found = 1;
            while (fgets(line, sizeof(line), file) && strncmp(line, "<------------------------------------>", 37) != 0);
        } else {
            fprintf(temp, "%s", line);
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("Students.txt");
        rename("temp.txt", "Students.txt");
        printf("Student record deleted successfully.\n");
    } else {
        printf("Student not found.\n");
        remove("temp.txt");
    }
}
