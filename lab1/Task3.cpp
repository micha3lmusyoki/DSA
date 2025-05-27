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
        grade = calculateGrade();
        calculated = true;
        return true;
    }

    int getMark() const { return mark; }
    char getGrade() const { return grade; }
    bool isCalculated() const { return calculated; }

private:
    char calculateGrade() {
        if (mark > 69) return 'A';
        if (mark > 59) return 'B';
        if (mark > 49) return 'C';
        if (mark > 39) return 'D';
        return 'E';
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

// Student
class Student {
private:
    string regNo;
    string name;
    int age;
    Course course;
    Grade grade;

public:
    Student() : regNo(""), name(""), age(0) {}
    Student(string rn, string n, int a, Course c) :
        regNo(rn), name(n), age(a), course(c) {}

    void setRegNo(string rn) { regNo = rn; }
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setCourse(Course c) { course = c; }
    void setGrade(Grade g) { grade = g; }

    string getRegNo() const { return regNo; }
    string getName() const { return name; }
    int getAge() const { return age; }
    Course getCourse() const { return course; }
    Grade getGrade() const { return grade; }

    bool setMark(int m) { return grade.setMark(m); }
};

// Array-based List ADT with dynamic resizing
class StudentList {
private:
    Student* students;
    int capacity;
    int size;

    void resize(int newCapacity) {
        Student* newStudents = new Student[newCapacity];
        for (int i = 0; i < size; i++) {
            newStudents[i] = students[i];
        }
        delete[] students;
        students = newStudents;
        capacity = newCapacity;
    }

public:
    // Constructors
    StudentList() : capacity(10), size(0) {
        students = new Student[capacity];
    }

    StudentList(Student s) : capacity(10), size(1) {
        students = new Student[capacity];
        students[0] = s;
    }

    StudentList(const StudentList& other) : capacity(other.capacity), size(other.size) {
        students = new Student[capacity];
        for (int i = 0; i < size; i++) {
            students[i] = other.students[i];
        }
    }

    ~StudentList() {
        delete[] students;
    }
    StudentList& operator=(const StudentList& other) {
        if (this != &other) {
            delete[] students;
            capacity = other.capacity;
            size = other.size;
            students = new Student[capacity];
            for (int i = 0; i < size; i++) {
                students[i] = other.students[i];
            }
        }
        return *this;
    }

    // List operations
    bool addStudent(Student s) {
        if (size >= capacity) {
            resize(capacity * 2);
        }
        students[size++] = s;
        return true;
    }

    bool addStudentAt(Student s, int pos) {
        if (pos < 0 || pos > size) return false;

        if (size >= capacity) {
            resize(capacity * 2);
        }
        for (int i = size; i > pos; i--) {
            students[i] = students[i-1];
        }
        students[pos] = s;
        size++;
        return true;
    }

    bool removeStudent(Student s) {
        for (int i = 0; i < size; i++) {
            if (students[i].getRegNo() == s.getRegNo()) {
                // Shift elements to fill gap
                for (int j = i; j < size-1; j++) {
                    students[j] = students[j+1];
                }
                size--;
                if (size < capacity / 4 && capacity > 10) {
                    resize(capacity / 2);
                }
                return true;
            }
        }
        return false;
    }

    bool removeStudentAt(int pos) {
        if (pos < 0 || pos >= size) return false;
        for (int i = pos; i < size-1; i++) {
            students[i] = students[i+1];
        }
        size--;
        if (size < capacity / 4 && capacity > 10) {
            resize(capacity / 2);
        }
        return true;
    }

    int getSize() const { return size; }
    int getCapacity() const { return capacity; }

    Student getStudent(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return students[index];
    }
};

int main() {
    Course c1("ICS 105", "Introduction to Programming");
    Course c2("STA 2200", "Discrete Mathematics");
    Course c3("EEE 208", "Physics for Engineers");

    Student s1("S001", "John Doe", 20, c1);
    s1.setMark(85);

    StudentList list1(s1);

    // Add more students
    for (int i = 2; i <= 15; i++) {
        string regNo = "S" + string(i < 10 ? "00" : "0") + to_string(i);
        string name = "Student " + to_string(i);
        int age = 18 + (i % 5);
        Course course = (i % 3 == 0) ? c1 : (i % 3 == 1) ? c2 : c3;
        int mark = 40 + (i * 3) % 61;  // Marks between 40-100

        Student s(regNo, name, age, course);
        s.setMark(mark);
        list1.addStudent(s);
    }

    // Display all students
    cout << "Student List (" << list1.getSize() << " students, capacity: "
         << list1.getCapacity() << "):\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < list1.getSize(); i++) {
        Student s = list1.getStudent(i);
        cout << "Reg No: " << s.getRegNo() << endl;
        cout << "Name: " << s.getName() << endl;
        cout << "Age: " << s.getAge() << endl;
        cout << "Course: " << s.getCourse().getCode() << " - "
             << s.getCourse().getName() << endl;
        cout << "Mark: " << s.getGrade().getMark() << endl;
        cout << "Grade: " << s.getGrade().getGrade() << endl;
        cout << "------------------------------------------------\n";
    }

    // Test other operations
    Student newStudent("S016", "New Student", 21, c2);
    list1.addStudentAt(newStudent, 5);  // Insert at position 5

    Student toRemove = list1.getStudent(7);
    list1.removeStudent(toRemove);

    list1.removeStudentAt(3);  // Remove student at position 3

    cout << "\nAfter modifications (" << list1.getSize() << " students, capacity: "
         << list1.getCapacity() << "):\n";

    return 0;
}
