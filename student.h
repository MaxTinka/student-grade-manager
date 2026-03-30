#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>

class Student {
private:
    std::string name;
    int id;
    std::vector<double> grades;

public:
    Student();
    Student(std::string name, int id);

    std::string getName() const;
    int getId() const;
    std::vector<double> getGrades() const;
    int getGradeCount() const;

    void setName(std::string name);
    void setId(int id);

    void addGrade(double grade);
    double getAverage() const;
    double getHighest() const;
    double getLowest() const;
    
    void display() const;
    void displayGrades() const;
    
    void saveToFile(std::ofstream& out) const;
    void loadFromFile(std::ifstream& in);
};

#endif
