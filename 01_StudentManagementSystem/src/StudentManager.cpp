#include "StudentManager.h"
#include <algorithm>

/**
 * @brief Default constructor
 * @details Initializes the student management system with starting ID of 1000
 */
StudentManager::StudentManager() : nextStudentId(1000) {}

/**
 * @brief Add a new student to the management system
 * @param name Student's full name
 * @param email Student's email address
 * @param age Student's age
 * @return true if student was successfully added
 * @details Creates a new student with the next available ID and adds them to the system
 */
bool StudentManager::addStudent(const std::string& name, const std::string& email, uint8_t age) {
    // Create a new student with the next available ID
    Student newStudent(nextStudentId, name, email, age);
    
    // Add the student to the map
    students[nextStudentId] = newStudent;
    
    // Increment the next available ID
    nextStudentId++;
    
    return true;
}

/**
 * @brief Remove a student from the management system
 * @param studentId ID of the student to remove
 * @return true if student was found and removed, false otherwise
 */
bool StudentManager::deleteStudent(uint32_t studentId) {
    auto it = students.find(studentId);
    if (it != students.end()) {
        students.erase(it);
        return true;
    }
    return false;
}

/**
 * @brief Retrieve a student by their ID
 * @param studentId ID of the student to find
 * @return Pointer to the Student object if found, nullptr otherwise
 */
Student* StudentManager::getStudent(uint32_t studentId) {
    auto it = students.find(studentId);
    if (it != students.end()) {
        return &(it->second);
    }
    return nullptr;
}

/**
 * @brief Search for students by name
 * @param name Full or partial name to search for
 * @return Vector of pointers to matching Student objects
 * @details Performs a case-insensitive search of student names
 */
std::vector<Student*> StudentManager::searchStudentsByName(const std::string& name) {
    std::vector<Student*> result;
    
    for (auto& pair : students) {
        // Case-insensitive search
        std::string studentName = pair.second.getName();
        std::string searchName = name;
        
        // Convert both strings to lowercase for case-insensitive comparison
        std::transform(studentName.begin(), studentName.end(), studentName.begin(), ::tolower);
        std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
        
        if (studentName.find(searchName) != std::string::npos) {
            result.push_back(&pair.second);
        }
    }
    
    return result;
}

/**
 * @brief Enroll a student in a course
 * @param studentId ID of the student to enroll
 * @param course Name of the course
 * @return true if student was found and enrolled, false otherwise
 */
bool StudentManager::enrollStudentInCourse(uint32_t studentId, const std::string& course) {
    Student* student = getStudent(studentId);
    if (student) {
        student->addCourse(course);
        return true;
    }
    return false;
}

/**
 * @brief Remove a student from a course
 * @param studentId ID of the student
 * @param course Name of the course
 * @return true if student was found and removed from course, false otherwise
 */
bool StudentManager::removeStudentFromCourse(uint32_t studentId, const std::string& course) {
    Student* student = getStudent(studentId);
    if (student && student->isEnrolledIn(course)) {
        student->removeCourse(course);
        return true;
    }
    return false;
}

/**
 * @brief Get the total number of students in the system
 * @return Number of students currently managed
 */
uint32_t StudentManager::getStudentCount() const {
    return students.size();
}

/**
 * @brief Get all students in the system
 * @return Vector containing copies of all Student objects
 */
std::vector<Student> StudentManager::getAllStudents() const {
    std::vector<Student> result;
    for (const auto& pair : students) {
        result.push_back(pair.second);
    }
    return result;
}
