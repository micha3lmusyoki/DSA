#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Grade
typedef struct {
    int mark;
    char grade;
    bool calculated;
} Grade;

// Course
typedef struct {
    char code[20];
    char name[50];
} Course;

// Student
typedef struct Student {
    char regNo[20];
    char name[50];
    int age;
    Course course;
    Grade grade;
    struct Student* next;
} Student;
void calculateGrade(Grade* grade) {
    if (grade->mark > 69) grade->grade = 'A';
    else if (grade->mark > 59) grade->grade = 'B';
    else if (grade->mark > 49) grade->grade = 'C';
    else if (grade->mark > 39) grade->grade = 'D';
    else grade->grade = 'E';
    grade->calculated = true;
}

//Create a new student
Student* createStudent(const char* regNo, const char* name, int age,
                      const char* courseCode, const char* courseName) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    strcpy(newStudent->regNo, regNo);
    strcpy(newStudent->name, name);
    newStudent->age = age;
    strcpy(newStudent->course.code, courseCode);
    strcpy(newStudent->course.name, courseName);
    newStudent->grade.mark = 0;
    newStudent->grade.calculated = false;
    newStudent->next = NULL;
    return newStudent;
}

//Add a student to the end of the list
void addStudent(Student** head, Student* newStudent) {
    if (*head == NULL) {
        *head = newStudent;
    } else {
        Student* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }
}

//Insert a student at a specific position
bool insertStudent(Student** head, Student* newStudent, int position) {
    if (position < 0) return false;

    if (position == 0) {
        newStudent->next = *head;
        *head = newStudent;
        return true;
    }

    Student* current = *head;
    for (int i = 0; current != NULL && i < position - 1; i++) {
        current = current->next;
    }

    if (current == NULL) return false;

    newStudent->next = current->next;
    current->next = newStudent;
    return true;
}

// Function to remove a student by registration number
bool removeStudent(Student** head, const char* regNo) {
    Student* temp = *head;
    Student* prev = NULL;

    if (temp != NULL && strcmp(temp->regNo, regNo) == 0) {
        *head = temp->next;
        free(temp);
        return true;
    }

    while (temp != NULL && strcmp(temp->regNo, regNo) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return false;

    prev->next = temp->next;
    free(temp);
    return true;
}

bool removeStudentAt(Student** head, int position) {
    if (*head == NULL || position < 0) return false;

    Student* temp = *head;

    if (position == 0) {
        *head = temp->next;
        free(temp);
        return true;
    }
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) return false;

    Student* next = temp->next->next;
    free(temp->next);
    temp->next = next;
    return true;
}
bool setStudentMark(Student* head, const char* regNo, int mark) {
    Student* current = head;
    while (current != NULL) {
        if (strcmp(current->regNo, regNo) == 0) {
            if (current->grade.calculated) {
                return false;
            }
            if (mark < 0 || mark > 100) {
                return false;
            }
            current->grade.mark = mark;
            calculateGrade(&(current->grade));
            return true;
        }
        current = current->next;
    }
    return false;
}
void displayStudents(Student* head) {
    Student* current = head;
    printf("\n--- Student List ---\n");
    while (current != NULL) {
        printf("Reg No: %s\n", current->regNo);
        printf("Name: %s\n", current->name);
        printf("Age: %d\n", current->age);
        printf("Course: %s - %s\n", current->course.code, current->course.name);
        if (current->grade.calculated) {
            printf("Mark: %d\n", current->grade.mark);
            printf("Grade: %c\n", current->grade.grade);
        } else {
            printf("Grade: Not yet set\n");
        }
        printf("-----------------------\n");
        current = current->next;
    }
}
void freeList(Student** head) {
    Student* current = *head;
    Student* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

int main() {
    Student* studentList = NULL;

    Course c1 = {"ICS 105", "Introduction to Programming"};
    Course c2 = {"STA 2200", "Discrete Mathematics"};
    Course c3 = {"EEE 208", "Physics for Engineers"};

    // Add students
    Student* s1 = createStudent("S001", "John Doe", 20, c1.code, c1.name);
    addStudent(&studentList, s1);

    for (int i = 2; i <= 15; i++) {
        char regNo[20];
        sprintf(regNo, "S%03d", i);

        char name[50];
        sprintf(name, "Student %d", i);

        int age = 18 + (i % 5);
        Course course = (i % 3 == 0) ? c1 : (i % 3 == 1) ? c2 : c3;

        Student* s = createStudent(regNo, name, age, course.code, course.name);
        addStudent(&studentList, s);
        if (i % 2 == 0) {
            int mark = 40 + (i * 3) % 61;
            setStudentMark(studentList, regNo, mark);
        }
    }
    displayStudents(studentList);

    Student* newStudent = createStudent("S016", "New Student", 21, c2.code, c2.name);
    insertStudent(&studentList, newStudent, 5);

    removeStudent(&studentList, "S007");
    removeStudentAt(&studentList, 3);

    printf("\nAfter modifications:\n");
    displayStudents(studentList);

    freeList(&studentList);

    return 0;
}
