#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "students.dat"
#define MAX_NAME 50

typedef struct {
    int id;
    char name[MAX_NAME];
    int age;
    float marks;
} Student;

// Function prototypes
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void updateStudent();

int main() {
    int choice;
    while (1) {
        printf("\n--- Student Record Management ---\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

void addStudent() {
    FILE *fp = fopen(FILENAME, "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }
    Student s;
    printf("Enter ID: "); scanf("%d", &s.id);
    getchar();
    printf("Enter Name: "); fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    printf("Enter Age: "); scanf("%d", &s.age);
    printf("Enter Marks: "); scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Student added successfully.\n");
}

void displayStudents() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        printf("No records found.\n");
        return;
    }
    Student s;
    printf("\n%-5s %-20s %-5s %-6s\n", "ID", "Name", "Age", "Marks");
    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("%-5d %-20s %-5d %-6.2f\n", s.id, s.name, s.age, s.marks);
    }
    fclose(fp);
}

void searchStudent() {
    int id, found = 0;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        printf("No records found.\n");
        return;
    }
    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            printf("Record Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nMarks: %.2f\n", s.id, s.name, s.age, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) printf("Student not found.\n");
    fclose(fp);
}

void deleteStudent() {
    int id, found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp || !temp) {
        printf("Error opening file.\n");
        return;
    }
    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(Student), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found)
        printf("Student deleted successfully.\n");
    else
        printf("Student not found.\n");
}

void updateStudent() {
    int id, found = 0;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp || !temp) {
        printf("Error opening file.\n");
        return;
    }
    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            found = 1;
            printf("Enter new Name: "); getchar(); fgets(s.name, MAX_NAME, stdin);
            s.name[strcspn(s.name, "\n")] = 0;
            printf("Enter new Age: "); scanf("%d", &s.age);
            printf("Enter new Marks: "); scanf("%f", &s.marks);
        }
        fwrite(&s, sizeof(Student), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found)
        printf("Student updated successfully.\n");
    else
        printf("Student not found.\n");
}