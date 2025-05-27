#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 40

// Course structure
typedef struct {
    char course_code[20];
    char course_name[50];
} Course;

// Grade structure
typedef struct {
    int mark;
    char the_grade;
    int grade_locked;  // flag to prevent editing once calculated
} Grade;

// Student structure
typedef struct {
    char reg_no[20];
    char name[50];
    int age;
    Course course;
    Grade grade;
} Student;

// Global students array
Student students[MAX_STUDENTS];
int student_count = 0;

// Function to calculate grade
char calculate_grade(int mark) {
    if (mark > 69) return 'A';
    if (mark > 59) return 'B';
    if (mark > 49) return 'C';
    if (mark > 39) return 'D';
    return 'E';
}

// Add student
void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("Student limit reached.\n");
        return;
    }

    Student s;

    printf("Enter registration number: ");
    scanf("%s", s.reg_no);
    printf("Enter name: ");
    scanf(" %[^\n]", s.name);  // read full line
    printf("Enter age: ");
    scanf("%d", &s.age);
    printf("Enter course code: ");
    scanf("%s", s.course.course_code);
    printf("Enter course name: ");
    scanf(" %[^\n]", s.course.course_name);

    s.grade.grade_locked = 0;  // grade can be added later
    students[student_count++] = s;

    printf("Student added successfully.\n");
}

// Edit student
void edit_student() {
    char reg[20];
    printf("Enter registration number to edit: ");
    scanf("%s", reg);

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].reg_no, reg) == 0) {
            printf("Editing student: %s\n", students[i].name);
            printf("Enter new name: ");
            scanf(" %[^\n]", students[i].name);
            printf("Enter new age: ");
            scanf("%d", &students[i].age);
            printf("Enter new course code: ");
            scanf("%s", students[i].course.course_code);
            printf("Enter new course name: ");
            scanf(" %[^\n]", students[i].course.course_name);
            printf("Student details updated.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

// Add marks and calculate grade
void add_mark() {
    char reg[20];
    int mark;
    printf("Enter registration number: ");
    scanf("%s", reg);

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].reg_no, reg) == 0) {
            if (students[i].grade.grade_locked) {
                printf("Grade already assigned and locked. Cannot edit.\n");
                return;
            }
            printf("Enter mark (0–100): ");
            scanf("%d", &mark);
            if (mark < 0 || mark > 100) {
                printf("Invalid mark.\n");
                return;
            }
            students[i].grade.mark = mark;
            students[i].grade.the_grade = calculate_grade(mark);
            students[i].grade.grade_locked = 1;
            printf("Grade calculated: %c\n", students[i].grade.the_grade);
            return;
        }
    }

    printf("Student not found.\n");
}

// View all students
void view_students() {
    for (int i = 0; i < student_count; i++) {
        printf("\nStudent %d:\n", i + 1);
        printf("Reg No: %s\n", students[i].reg_no);
        printf("Name: %s\n", students[i].name);
        printf("Age: %d\n", students[i].age);
        printf("Course Code: %s\n", students[i].course.course_code);
        printf("Course Name: %s\n", students[i].course.course_name);
        if (students[i].grade.grade_locked)
            printf("Mark: %d | Grade: %c\n", students[i].grade.mark, students[i].grade.the_grade);
        else
            printf("Grade not assigned.\n");
    }
}

// Menu
void menu() {
    int choice;
    do {
        printf("\n---- Student Management Menu ----\n");
        printf("1. Add Student\n");
        printf("2. Edit Student\n");
        printf("3. Add Mark & Calculate Grade\n");
        printf("4. View All Students\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_student(); break;
            case 2: edit_student(); break;
            case 3: add_mark(); break;
            case 4: view_students(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
}

// Main
int main() {
    menu();
    return 0;
}
