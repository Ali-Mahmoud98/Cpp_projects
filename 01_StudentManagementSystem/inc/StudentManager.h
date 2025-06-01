#ifndef STUDENT_MANAGER_H__
#define STUDENT_MANAGER_H__

#include "Student.h"
#include <map>
#include <vector>
#include <string>

/**
 * @class StudentManager
 * @brief Manages student records and their course enrollments
 * 
 * @details This class provides functionality to:
 *          - Add and remove students
 *          - Search for students
 *          - Manage course enrollments
 *          - Track student information
 */
class StudentManager {
private:
    std::map<uint32_t, Student> students; ///< Map of student ID to Student object
    uint32_t nextStudentId;               ///< Counter for generating unique student IDs

public:
    /**
     * @brief Default constructor
     * @details Initializes an empty student management system
     */
    StudentManager();
    
    // Student management operations
    /**
     * @brief Adds a new student to the system
     * @param name The student's full name
     * @param email The student's email address
     * @param age The student's age
     * @return true if student was successfully added, false otherwise
     */
    bool addStudent(const std::string& name, const std::string& email, uint8_t age);

    /**
     * @brief Removes a student from the system
     * @param studentId The ID of the student to remove
     * @return true if student was successfully removed, false if student wasn't found
     */
    bool deleteStudent(uint32_t studentId);

    /**
     * @brief Retrieves a student by their ID
     * @param studentId The ID of the student to find
     * @return Pointer to the Student object if found, nullptr otherwise
     */
    Student* getStudent(uint32_t studentId);

    /**
     * @brief Searches for students by their name
     * @param name Full or partial name to search for
     * @return Vector of pointers to matching Student objects
     */
    std::vector<Student*> searchStudentsByName(const std::string& name);
    
    // Course management operations
    /**
     * @brief Enrolls a student in a course
     * @param studentId The ID of the student to enroll
     * @param course The name of the course
     * @return true if enrollment was successful, false otherwise
     */
    bool enrollStudentInCourse(uint32_t studentId, const std::string& course);

    /**
     * @brief Removes a student from a course
     * @param studentId The ID of the student
     * @param course The name of the course
     * @return true if removal was successful, false otherwise
     */
    bool removeStudentFromCourse(uint32_t studentId, const std::string& course);
    
    // Utility functions
    /**
     * @brief Gets the total number of students in the system
     * @return Number of enrolled students
     */
    uint32_t getStudentCount() const;

    /**
     * @brief Retrieves all students in the system
     * @return Vector containing all Student objects
     */
    std::vector<Student> getAllStudents() const;
};

#endif // STUDENT_MANAGER_H__