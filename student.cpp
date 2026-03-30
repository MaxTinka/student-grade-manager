#include "Student.h"
#include <fstream>
#include <iomanip>
#include <algorithm>

Student::Student() {
    name = "";
    id = 0;
}

Student::Student(std::string name, int id) {
    this->name = name;
    this->id = id;
}

std::string Student::getName() const { return name; }
int Student::getId() const { return id; }
std::vector<double> Student::getGrades() const { return grades; }
int Student::getGradeCount() const { return grades.size(); }

void Student::setName(std::string name) { this->name = name; }
void Student::setId(int id) { this->id = id; }

void Student::addGrade(double grade) {
    if (grade >= 0 && grade <= 100) {
        grades.push_back(grade);
        std::cout << "Grade added successfully!\n";
    } else {
        std::cout << "Invalid grade. Please enter a value between 0 and 100.\n";
    }
}

double Student::getAverage() const {
    if (grades.empty()) return 0.0;
    double sum = 0.0;
    for (double grade : grades) sum += grade;
    return sum / grades.size();
}

double Student::getHighest() const {
    if (grades.empty()) return 0.0;
    double highest = grades[0];
    for (double grade : grades) if (grade > highest) highest = grade;
    return highest;
}

double Student::getLowest() const {
    if (grades.empty()) return 0.0;
    double lowest = grades[0];
    for (double grade : grades) if (grade < lowest) lowest = grade;
    return lowest;
}

void Student::display() const {
    std::cout << "----------------------------------------\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Grade Count: " << grades.size() << "\n";
    if (!grades.empty()) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Average: " << getAverage() << "\n";
        std::cout << "Highest: " << getHighest() << "\n";
        std::cout << "Lowest: " << getLowest() << "\n";
    }
}

void Student::displayGrades() const {
    if (grades.empty()) {
        std::cout << "No grades recorded.\n";
        return;
    }
    std::cout << "Grades: ";
    for (size_t i = 0; i < grades.size(); i++) {
        std::cout << grades[i];
        if (i < grades.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}

void Student::saveToFile(std::ofstream& out) const {
    out << id << "\n";
    out << name << "\n";
    out << grades.size() << "\n";
    for (double grade : grades) out << grade << "\n";
}

void Student::loadFromFile(std::ifstream& in) {
    in >> id;
    in.ignore();
    std::getline(in, name);
    int gradeCount;
    in >> gradeCount;
    in.ignore();
    grades.clear();
    for (int i = 0; i < gradeCount; i++) {
        double grade;
        in >> grade;
        in.ignore();
        grades.push_back(grade);
    }
}
