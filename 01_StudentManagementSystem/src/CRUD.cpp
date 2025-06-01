#include "CRUD.h"

/**
 * @brief Add a new student to the system
 * @param manager Reference to the StudentManager instance
 * @details Prompts user for student details (name, email, age) and
 *          attempts to add the student to the system
 */
void addStudent(StudentManager& manager) {
    std::string name, email;
    int age;
    
    std::cout << "\n----- Add Student -----\n";
    
    std::cout << "Enter name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    
    std::cout << "Enter email: ";
    std::getline(std::cin, email);
    
    std::cout << "Enter age: ";
    std::cin >> age;
    
    if (manager.addStudent(name, email, age)) {
        std::cout << "Student added successfully!\n";
    } else {
        std::cout << "Failed to add student.\n";
    }
}

/**
 * @brief Delete a student from the system
 * @param manager Reference to the StudentManager instance
 * @details Prompts user for student ID and attempts to remove
 *          the corresponding student from the system
 */
void deleteStudent(StudentManager& manager) {
    int studentId;
    
    std::cout << "\n----- Delete Student -----\n";
    std::cout << "Enter student ID: ";
    std::cin >> studentId;
    
    if (manager.deleteStudent(studentId)) {
        std::cout << "Student deleted successfully!\n";
    } else {
        std::cout << "Student not found or failed to delete.\n";
    }
}

/**
 * @brief Search for a student using their ID
 * @param manager Reference to the StudentManager instance
 * @details Prompts user for student ID and displays the student's
 *          information if found
 */
void searchStudentById(StudentManager& manager) {
    int studentId;
    
    std::cout << "\n----- Search Student by ID -----\n";
    std::cout << "Enter student ID: ";
    std::cin >> studentId;
    
    Student* student = manager.getStudent(studentId);
    if (student) {
        std::cout << "\nStudent found:\n";
        std::cout << student->toString() << std::endl;
    } else {
        std::cout << "Student not found.\n";
    }
}

/**
 * @brief Search for students by name
 * @param manager Reference to the StudentManager instance
 * @details Prompts user for a name or partial name and displays
 *          all matching students' information
 */
void searchStudentsByName(StudentManager& manager) {
    std::string name;
    
    std::cout << "\n----- Search Students by Name -----\n";
    std::cout << "Enter name (or part of name): ";
    std::cin.ignore();
    std::getline(std::cin, name);
    
    std::vector<Student*> students = manager.searchStudentsByName(name);
    if (students.empty()) {
        std::cout << "No students found.\n";
    } else {
        std::cout << "\nFound " << students.size() << " student(s):\n";
        for (const auto& student : students) {
            std::cout << "\n" << student->toString() << std::endl;
        }
    }
}

/**
 * @brief Display all students in the system
 * @param manager Reference to the StudentManager instance
 * @details Lists all students currently in the system with their
 *          complete information
 */
void listAllStudents(StudentManager& manager) {
    std::cout << "\n----- All Students -----\n";
    
    std::vector<Student> students = manager.getAllStudents();
    if (students.empty()) {
        std::cout << "No students in the system.\n";
    } else {
        std::cout << "Total students: " << students.size() << std::endl;
        for (const auto& student : students) {
            std::cout << "\n" << student.toString() << std::endl;
        }
    }
}

/**
 * @brief Enroll a student in a course
 * @param manager Reference to the StudentManager instance
 * @details Prompts user for student ID and course name, then
 *          attempts to enroll the student in the specified course
 */
void enrollStudentInCourse(StudentManager& manager) {
    int studentId;
    std::string course;
    
    std::cout << "\n----- Enroll Student in Course -----\n";
    std::cout << "Enter student ID: ";
    std::cin >> studentId;
    
    Student* student = manager.getStudent(studentId);
    if (!student) {
        std::cout << "Student not found.\n";
        return;
    }
    
    std::cout << "Enter course name: ";
    std::cin.ignore();
    std::getline(std::cin, course);
    
    if (manager.enrollStudentInCourse(studentId, course)) {
        std::cout << "Student enrolled in course successfully!\n";
    } else {
        std::cout << "Failed to enroll student in course.\n";
    }
}

/**
 * @brief Remove a student from a course
 * @param manager Reference to the StudentManager instance
 * @details Prompts user for student ID and course name, then
 *          attempts to remove the student from the specified course
 */
void removeStudentFromCourse(StudentManager& manager) {
    int studentId;
    std::string course;
    
    std::cout << "\n----- Remove Student from Course -----\n";
    std::cout << "Enter student ID: ";
    std::cin >> studentId;
    
    Student* student = manager.getStudent(studentId);
    if (!student) {
        std::cout << "Student not found.\n";
        return;
    }
    
    std::cout << "Enter course name: ";
    std::cin.ignore();
    std::getline(std::cin, course);
    
    if (manager.removeStudentFromCourse(studentId, course)) {
        std::cout << "Student removed from course successfully!\n";
    } else {
        std::cout << "Student is not enrolled in this course or failed to remove.\n";
    }
}
