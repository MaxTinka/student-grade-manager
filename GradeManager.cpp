#include "GradeManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <limits>

GradeManager::GradeManager() {
    loadData();
}

Student* GradeManager::findStudentById(int id) {
    for (auto& student : students) {
        if (student.getId() == id) return &student;
    }
    return nullptr;
}

void GradeManager::addStudent() {
    std::string name;
    int id;
    std::cin.ignore();
    std::cout << "Enter student name: ";
    std::getline(std::cin, name);
    std::cout << "Enter student ID: ";
    std::cin >> id;
    if (findStudentById(id) != nullptr) {
        std::cout << "Student ID already exists.\n";
        return;
    }
    students.push_back(Student(name, id));
    std::cout << "Student added!\n";
    saveData();
}

void GradeManager::removeStudent() {
    int id;
    std::cout << "Enter student ID: ";
    std::cin >> id;
    auto it = std::find_if(students.begin(), students.end(),
        [id](const Student& s) { return s.getId() == id; });
    if (it == students.end()) {
        std::cout << "Student not found.\n";
        return;
    }
    students.erase(it);
    std::cout << "Student removed!\n";
    saveData();
}

void GradeManager::searchStudent() {
    int id;
    std::cout << "Enter student ID: ";
    std::cin >> id;
    Student* s = findStudentById(id);
    if (s) s->display();
    else std::cout << "Student not found.\n";
}

void GradeManager::displayAllStudents() {
    if (students.empty()) {
        std::cout << "No students.\n";
        return;
    }
    for (const auto& s : students) s.display();
    displayClassStatistics();
}

void GradeManager::addGradeToStudent() {
    int id;
    double grade;
    std::cout << "Enter student ID: ";
    std::cin >> id;
    Student* s = findStudentById(id);
    if (!s) {
        std::cout << "Student not found.\n";
        return;
    }
    std::cout << "Enter grade (0-100): ";
    std::cin >> grade;
    s->addGrade(grade);
    saveData();
}

void GradeManager::viewStudentGrades() {
    int id;
    std::cout << "Enter student ID: ";
    std::cin >> id;
    Student* s = findStudentById(id);
    if (!s) {
        std::cout << "Student not found.\n";
        return;
    }
    s->display();
    s->displayGrades();
}

void GradeManager::displayClassStatistics() {
    if (students.empty()) return;
    double classTotal = 0;
    int studentsWithGrades = 0;
    double highest = 0, lowest = 100;
    int a=0,b=0,c=0,d=0,f=0;
    for (const auto& s : students) {
        if (s.getGradeCount() > 0) {
            double avg = s.getAverage();
            classTotal += avg;
            studentsWithGrades++;
            if (s.getHighest() > highest) highest = s.getHighest();
            if (s.getLowest() < lowest) lowest = s.getLowest();
            if (avg >= 90) a++;
            else if (avg >= 80) b++;
            else if (avg >= 70) c++;
            else if (avg >= 60) d++;
            else f++;
        }
    }
    std::cout << "\n=== CLASS STATISTICS ===\n";
    std::cout << "Students: " << students.size() << "\n";
    if (studentsWithGrades > 0) {
        std::cout << "Class Avg: " << std::fixed << std::setprecision(2) 
                  << (classTotal / studentsWithGrades) << "\n";
        std::cout << "Highest Grade: " << highest << "\n";
        std::cout << "Lowest Grade: " << lowest << "\n";
        std::cout << "A: " << a << " B: " << b << " C: " << c << " D: " << d << " F: " << f << "\n";
    }
}

void GradeManager::loadData() {
    std::ifstream file("students.txt");
    if (!file.is_open()) return;
    int count;
    file >> count;
    file.ignore();
    students.clear();
    for (int i = 0; i < count; i++) {
        Student s;
        s.loadFromFile(file);
        students.push_back(s);
    }
    file.close();
}

void GradeManager::saveData() {
    std::ofstream file("students.txt");
    file << students.size() << "\n";
    for (const auto& s : students) s.saveToFile(file);
    file.close();
}

void GradeManager::run() {
    int choice;
    do {
        std::cout << "\n=== STUDENT GRADE MANAGER ===\n";
        std::cout << "1. Add Student\n2. Remove Student\n3. Search Student\n";
        std::cout << "4. Display All Students\n5. Add Grade\n6. View Grades\n";
        std::cout << "7. Class Statistics\n0. Exit\nChoice: ";
        std::cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: removeStudent(); break;
            case 3: searchStudent(); break;
            case 4: displayAllStudents(); break;
            case 5: addGradeToStudent(); break;
            case 6: viewStudentGrades(); break;
            case 7: displayClassStatistics(); break;
            case 0: saveData(); std::cout << "Goodbye!\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}
