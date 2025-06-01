#ifndef STUDENT_H__
#define STUDENT_H__

#include <string>
#include <vector>

/**
 * @class Student
 * @brief Represents a student in the school system.
 *
 * @details This class encapsulates the details of a student such as their ID, name, email,
 * age, and enrolled courses.
 */
class Student {
private:
    int studentId;           ///< Unique identifier for the student
    std::string name;        ///< Full name of the student
    std::string email;       ///< Email address of the student
    int age;                 ///< Age of the student
    std::vector<std::string> courses;  ///< List of courses the student is enrolled in

public:
    /**
     * @brief Default constructor
     */
    Student();

    /**
     * @brief Parameterized constructor
     * @param id The student's ID number
     * @param name The student's full name
     * @param email The student's email address
     * @param age The student's age
     */
    Student(int id, const std::string& name, const std::string& email, int age);
    
    // Getters
    /**
     * @brief Get the student's ID
     * @return The student's ID number
     */
    int getStudentId() const;

    /**
     * @brief Get the student's name
     * @return The student's full name
     */
    std::string getName() const;

    /**
     * @brief Get the student's email
     * @return The student's email address
     */
    std::string getEmail() const;

    /**
     * @brief Get the student's age
     * @return The student's age
     */
    int getAge() const;

    /**
     * @brief Get the list of courses
     * @return Vector containing all enrolled courses
     */
    std::vector<std::string> getCourses() const;
    
    // Setters
    /**
     * @brief Set the student's ID
     * @param id New ID number to assign
     */
    void setStudentId(int id);

    /**
     * @brief Set the student's name
     * @param name New name to assign
     */
    void setName(const std::string& name);

    /**
     * @brief Set the student's email
     * @param email New email address to assign
     */
    void setEmail(const std::string& email);

    /**
     * @brief Set the student's age
     * @param age New age to assign
     */
    void setAge(int age);
    
    // Course management
    /**
     * @brief Add a course to student's enrollment list
     * @param course Name of the course to add
     */
    void addCourse(const std::string& course);

    /**
     * @brief Remove a course from student's enrollment list
     * @param course Name of the course to remove
     */
    void removeCourse(const std::string& course);

    /**
     * @brief Check if student is enrolled in a specific course
     * @param course Name of the course to check
     * @return true if student is enrolled, false otherwise
     */
    bool isEnrolledIn(const std::string& course) const;
    
    /**
     * @brief Convert student information to string format
     * @return Formatted string containing all student details
     */
    std::string toString() const;
};

#endif // STUDENT_H__
