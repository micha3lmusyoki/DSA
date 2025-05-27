#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// Grade
class Grade {
private:
    int mark;
    char grade;
    bool calculated;

public:
    Grade() : mark(0), grade(' '), calculated(false) {}

    bool setMark(int m) {
        if (calculated) return false;
        if (m < 0 || m > 100) return false;
        mark = m;
        calculateGrade();
        calculated = true;
        return true;
    }

    int getMark() const { return mark; }
    char getGrade() const { return grade; }
    bool isCalculated() const { return calculated; }

private:
    void calculateGrade() {
        if (mark > 69) grade = 'A';
        else if (mark > 59) grade = 'B';
        else if (mark > 49) grade = 'C';
        else if (mark > 39) grade = 'D';
        else grade = 'E';
    }
};

// Course
class Course {
private:
    string code;
    string name;

public:
    Course() : code(""), name("") {}
    Course(string c, string n) : code(c), name(n) {}

    void setCode(string c) { code = c; }
    void setName(string n) { name = n; }
    string getCode() const { return code; }
    string getName() const { return name; }
};

// Student node
class StudentNode {
public:
    string regNo;
    string name;
    int age;
    Course course;
    Grade grade;
    StudentNode* next;

    StudentNode(string rn, string n, int a, Course c)
        : regNo(rn), name(n), age(a), course(c), next(nullptr) {}
};

// Linked List class for Students
class StudentLinkedList {
private:
    StudentNode* head;
    int size;

public:
    StudentLinkedList() : head(nullptr), size(0) {}

    ~StudentLinkedList() {
        clear();
    }

    // Add student to end of list
    void addStudent(string regNo, string name, int age, Course course) {
        StudentNode* newNode = new StudentNode(regNo, name, age, course);
        if (head == nullptr) {
            head = newNode;
        } else {
            StudentNode* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    // Insert student at specific position
    bool insertStudent(string regNo, string name, int age, Course course, int position) {
        if (position < 0 || position > size) return false;

        StudentNode* newNode = new StudentNode(regNo, name, age, course);
        if (position == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            StudentNode* current = head;
            for (int i = 0; i < position - 1; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
        return true;
    }
//remove student
    bool removeStudent(string regNo) {
        if (head == nullptr) return false;

        if (head->regNo == regNo) {
            StudentNode* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }

        StudentNode* current = head;
        while (current->next != nullptr && current->next->regNo != regNo) {
            current = current->next;
        }

        if (current->next == nullptr) return false;

        StudentNode* temp = current->next;
        current->next = temp->next;
        delete temp;
        size--;
        return true;
    }
    bool removeStudentAt(int position) {
        if (position < 0 || position >= size) return false;

        if (position == 0) {
            StudentNode* temp = head;
            head = head->next;
            delete temp;
        } else {
            StudentNode* current = head;
            for (int i = 0; i < position - 1; i++) {
                current = current->next;
            }
            StudentNode* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
        size--;
        return true;
    }
    bool setStudentMark(string regNo, int mark) {
        StudentNode* current = head;
        while (current != nullptr) {
            if (current->regNo == regNo) {
                return current->grade.setMark(mark);
            }
            current = current->next;
        }
        return false;
    }
    void displayStudents() const {
        cout << "\n--- Student List (" << size << " students) ---\n";
        StudentNode* current = head;
        while (current != nullptr) {
            cout << "Reg No: " << current->regNo << endl;
            cout << "Name: " << current->name << endl;
            cout << "Age: " << current->age << endl;
            cout << "Course: " << current->course.getCode()
                 << " - " << current->course.getName() << endl;
            if (current->grade.isCalculated()) {
                cout << "Mark: " << current->grade.getMark() << endl;
                cout << "Grade: " << current->grade.getGrade() << endl;
            } else {
                cout << "Grade: Not yet set" << endl;
            }
            cout << "-----------------------\n";
            current = current->next;
        }
    }
    void clear() {
        while (head != nullptr) {
            StudentNode* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    int getSize() const { return size; }
};

int main() {
    StudentLinkedList studentList;

    Course c1("ICS 105", "Introduction to Programming");
    Course c2("STA 2200", "Discrete Mathematics");
    Course c3("EEE 208", "Physics for Engineers");

    // Add students
    studentList.addStudent("S001", "John Doe", 20, c1);

    for (int i = 2; i <= 15; i++) {
        string regNo = "S" + string(i < 10 ? "00" : "0") + to_string(i);
        string name = "Student " + to_string(i);
        int age = 18 + (i % 5);
        Course course = (i % 3 == 0) ? c1 : (i % 3 == 1) ? c2 : c3;

        studentList.addStudent(regNo, name, age, course);

        if (i % 2 == 0) {
            int mark = 40 + (i * 3) % 61;
            studentList.setStudentMark(regNo, mark);
        }
    }

    studentList.displayStudents();

    studentList.insertStudent("S016", "New Student", 21, c2, 5);
    studentList.removeStudent("S007");
    studentList.removeStudentAt(3);

    cout << "\nAfter modifications:\n";
    studentList.displayStudents();

    return 0;
}
