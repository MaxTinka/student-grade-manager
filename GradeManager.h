#ifndef GRADEMANAGER_H
#define GRADEMANAGER_H

#include <vector>
#include "Student.h"

class GradeManager {
private:
    std::vector<Student> students;
    Student* findStudentById(int id);
    
public:
    GradeManager();
    void addStudent();
    void removeStudent();
    void searchStudent();
    void displayAllStudents();
    void addGradeToStudent();
    void viewStudentGrades();
    void displayClassStatistics();
    void loadData();
    void saveData();
    void run();
};

#endif
