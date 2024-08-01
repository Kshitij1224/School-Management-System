#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
    int roll_number;
    float marks;
} Student;

void addStudent(Student* students, int* numStudents);
void displayStudents(Student* students, int numStudents);
void deleteStudent(Student* students, int* numStudents);
void deleteStudentFromFile();
void saveStudentsToFile(Student* students, int numStudents);
void loadStudentsFromFile(Student* students, int* numStudents);
void menu();

int main() {
    Student students[MAX_STUDENTS];
    int numStudents = 0;
    int choice;

    loadStudentsFromFile(students, &numStudents);
    do {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &numStudents);
                break;
            case 2:
                displayStudents(students, numStudents);
                break;
            case 3:
                deleteStudent(students, &numStudents);
                break;
            case 4:
                deleteStudentFromFile();
                break;
            case 5:
                saveStudentsToFile(students, numStudents);
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid choice.\n");
        }
    } while (choice != 6);
    return 0;
}

void menu() {
    printf("\nSchool Management System Menu\n");
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Delete Student\n");
    printf("4. Delete Student from File\n");
    printf("5. Save Students to File\n");
    printf("6. Exit\n");
}

void addStudent(Student* students, int* numStudents) {
    if (*numStudents < MAX_STUDENTS) {
        printf("Enter student name: ");
        scanf("%s", students[*numStudents].name);
        printf("Enter student age: ");
        scanf("%d", &students[*numStudents].age);
        printf("Enter student roll number: ");
        scanf("%d", &students[*numStudents].roll_number);
        printf("Enter student marks: ");
        scanf("%f", &students[*numStudents].marks);
        (*numStudents)++;
        printf("Student added successfully.\n");
    } else {
        printf("Maximum number of students reached.\n");
    }
}

void displayStudents(Student* students, int numStudents) {
    printf("\nList of Students:\n");
    printf("-----------------------------------------------------\n");
    printf("Name\t\tAge\tRoll Number\tMarks\n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < numStudents; ++i) {
        printf("%s\t\t%d\t%d\t\t%.2f\n", students[i].name, students[i].age,
               students[i].roll_number, students[i].marks);
    }
}

void deleteStudent(Student* students, int* numStudents) {
    int rollNumber;
    printf("Enter the roll number of the student to delete: ");
    scanf("%d", &rollNumber);
    int found = 0;
    for (int i = 0; i < *numStudents; ++i) {
        if (students[i].roll_number == rollNumber) {
            for (int j = i; j < *numStudents - 1; ++j) {
                students[j] = students[j + 1];
            }
            (*numStudents)--;
            found = 1;
            printf("Student with roll number %d deleted successfully.\n", rollNumber);
            break;
        }
    }
    if (!found) {
        printf("Student with roll number %d not found.\n", rollNumber);
    }
}

void deleteStudentFromFile() {
    int rollNumber;
    printf("Enter the roll number of the student to delete from file: ");
    scanf("%d", &rollNumber);
    FILE *tempFile;
    FILE *file;
    file = fopen("students.txt", "r");
    tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }
    int found = 0;
    Student student;
    while (fscanf(file, "%s %d %d %f", student.name, &student.age,
                  &student.roll_number, &student.marks) != EOF) {
        if (student.roll_number != rollNumber) {
            fprintf(tempFile, "%s %d %d %.2f\n", student.name, student.age,
                    student.roll_number, student.marks);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(tempFile);
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found) {
        printf("Student with roll number %d deleted successfully from file.\n", rollNumber);
    } else {
        printf("Student with roll number %d not found in file.\n", rollNumber);
    }
}

void saveStudentsToFile(Student* students, int numStudents) {
    FILE* file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < numStudents; ++i) {
        fprintf(file, "%s %d %d %.2f\n", students[i].name, students[i].age,
                students[i].roll_number, students[i].marks);
    }
    fclose(file);
    printf("Students saved to file successfully.\n");
}

void loadStudentsFromFile(Student* students, int* numStudents) {
    FILE* file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("No existing data found.\n");
        return;
    }
    while (fscanf(file, "%s %d %d %f", students[*numStudents].name, &students[*numStudents].age,
                  &students[*numStudents].roll_number, &students[*numStudents].marks) != EOF) {
        (*numStudents)++;
    }
    fclose(file);
    printf("Students loaded from file successfully.\n");
}
