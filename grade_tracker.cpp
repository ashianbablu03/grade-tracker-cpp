// ============================================================
//  Student Grade Tracker — C++
//  Concepts: OOP, File I/O, GPA Calculation, Vectors, Classes
// ============================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>

// ── Course class: stores one course's data ──────────────────
class Course {
private:
    std::string name;
    double grade;       // numeric grade 0–100
    int    creditHours;

public:
    // Constructor
    Course(std::string n, double g, int ch)
        : name(n), grade(g), creditHours(ch) {}

    // Getters
    std::string getName()    const { return name; }
    double      getGrade()   const { return grade; }
    int         getCredits() const { return creditHours; }

    // Convert numeric grade to letter grade
    std::string getLetterGrade() const {
        if (grade >= 90) return "A";
        if (grade >= 80) return "B";
        if (grade >= 70) return "C";
        if (grade >= 60) return "D";
        return "F";
    }

    // Convert numeric grade to GPA points (4.0 scale)
    double getGPAPoints() const {
        if (grade >= 90) return 4.0;
        if (grade >= 80) return 3.0;
        if (grade >= 70) return 2.0;
        if (grade >= 60) return 1.0;
        return 0.0;
    }

    // Format course as a CSV line for file saving
    std::string toCSV() const {
        return name + "," + std::to_string(grade) + "," + std::to_string(creditHours);
    }
};

// ── Student class: manages a student's list of courses ──────
class Student {
private:
    std::string       studentName;
    std::vector<Course> courses;

public:
    Student(std::string name) : studentName(name) {}

    std::string getName() const { return studentName; }

    // Add a course to the student's record
    void addCourse(const Course& c) {
        courses.push_back(c);
    }

    // Remove a course by name (returns true if found & removed)
    bool removeCourse(const std::string& name) {
        for (auto it = courses.begin(); it != courses.end(); ++it) {
            if (it->getName() == name) {
                courses.erase(it);
                return true;
            }
        }
        return false;
    }

    // Calculate cumulative GPA using weighted average
    double calculateGPA() const {
        if (courses.empty()) return 0.0;

        double totalPoints  = 0.0;
        int    totalCredits = 0;

        for (const auto& c : courses) {
            totalPoints  += c->getGPAPoints() * c.getCredits();
            totalCredits += c.getCredits();
        }

        return (totalCredits == 0) ? 0.0 : totalPoints / totalCredits;
    }

    // Print a formatted grade report to the console
    void printReport() const {
        std::cout << "\n========================================\n";
        std::cout << "  Grade Report for: " << studentName << "\n";
        std::cout << "========================================\n";
        std::cout << std::left
                  << std::setw(22) << "Course"
                  << std::setw(10) << "Grade"
                  << std::setw(8)  << "Letter"
                  << std::setw(8)  << "Credits"
                  << "\n";
        std::cout << "----------------------------------------\n";

        for (const auto& c : courses) {
            std::cout << std::left
                      << std::setw(22) << c.getName()
                      << std::setw(10) << std::fixed << std::setprecision(1) << c.getGrade()
                      << std::setw(8)  << c.getLetterGrade()
                      << std::setw(8)  << c.getCredits()
                      << "\n";
        }

        std::cout << "----------------------------------------\n";
        std::cout << "  Cumulative GPA: " << std::fixed << std::setprecision(2)
                  << calculateGPA() << " / 4.00\n";
        std::cout << "========================================\n\n";
    }

    // Save student record to a .txt file
    void saveToFile() const {
        std::string filename = studentName + "_grades.txt";
        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file for saving.\n";
            return;
        }

        file << "Student: " << studentName << "\n";
        file << "GPA: " << std::fixed << std::setprecision(2) << calculateGPA() << "\n";
        file << "Courses:\n";

        for (const auto& c : courses) {
            file << "  " << c.toCSV() << "\n";
        }

        file.close();
        std::cout << "Record saved to " << filename << "\n";
    }

    // Load student record from file
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Could not open file: " << filename << "\n";
            return;
        }

        courses.clear();
        std::string line;

        // Skip header lines
        std::getline(file, line); // "Student: ..."
        std::getline(file, line); // "GPA: ..."
        std::getline(file, line); // "Courses:"

        // Parse each course line (CSV format)
        while (std::getline(file, line)) {
            if (line.empty() || line[0] != ' ') continue;
            line = line.substr(2); // remove leading spaces

            std::stringstream ss(line);
            std::string name, gradeStr, creditStr;

            if (std::getline(ss, name, ',') &&
                std::getline(ss, gradeStr, ',') &&
                std::getline(ss, creditStr)) {
                courses.push_back(Course(name, std::stod(gradeStr), std::stoi(creditStr)));
            }
        }

        file.close();
        std::cout << "Record loaded from " << filename << "\n";
    }

    bool hasCourses() const { return !courses.empty(); }
};

// ── Helper: get a valid numeric input from user ──────────────
double getValidGrade() {
    double grade;
    while (true) {
        std::cin >> grade;
        if (std::cin.fail() || grade < 0 || grade > 100) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "  Please enter a grade between 0 and 100: ";
        } else {
            std::cin.ignore(1000, '\n');
            return grade;
        }
    }
}

// ── Main menu ────────────────────────────────────────────────
int main() {
    std::cout << "====================================\n";
    std::cout << "   Student Grade Tracker — C++\n";
    std::cout << "====================================\n";
    std::cout << "Enter your name: ";

    std::string name;
    std::getline(std::cin, name);

    Student student(name);

    int choice = 0;
    while (choice != 5) {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Add a course\n";
        std::cout << "2. Remove a course\n";
        std::cout << "3. View grade report\n";
        std::cout << "4. Save record to file\n";
        std::cout << "5. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');

        if (choice == 1) {
            // Add course
            std::string courseName;
            int credits;

            std::cout << "  Course name: ";
            std::getline(std::cin, courseName);

            std::cout << "  Grade (0–100): ";
            double grade = getValidGrade();

            std::cout << "  Credit hours: ";
            std::cin >> credits;
            std::cin.ignore(1000, '\n');

            student.addCourse(Course(courseName, grade, credits));
            std::cout << "  ✓ Course added.\n";

        } else if (choice == 2) {
            // Remove course
            std::string courseName;
            std::cout << "  Course name to remove: ";
            std::getline(std::cin, courseName);

            if (student.removeCourse(courseName))
                std::cout << "  ✓ Course removed.\n";
            else
                std::cout << "  Course not found.\n";

        } else if (choice == 3) {
            // Print report
            if (!student.hasCourses())
                std::cout << "  No courses added yet.\n";
            else
                student.printReport();

        } else if (choice == 4) {
            // Save to file
            student.saveToFile();

        } else if (choice != 5) {
            std::cout << "  Invalid option. Try again.\n";
        }
    }

    std::cout << "\nGoodbye, " << name << "!\n";
    return 0;
}
