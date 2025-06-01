#include "Student.h"
#include <sstream>

/**
 * @brief Default constructor
 *
 * @details Initializes a student with:
 *          - ID set to 0
 *          - Empty name and email strings
 *          - Age set to 0
 *          - Empty courses vector
 */
Student::Student() : studentId(0), name(""), email(""), age(0) {}

/**
 * @brief Parameterized constructor
 * @param id The student's ID number
 * @param name The student's full name
 * @param email The student's email address
 * @param age The student's age
 */
Student::Student(int id, const std::string& name, const std::string& email, int age)
    : studentId(id), name(name), email(email), age(age) {}

/**
 * @brief Get the student's ID
 * @return The student's ID number
 */
int Student::getStudentId() const {
    return studentId;
}

/**
 * @brief Get the student's name
 * @return The student's full name
 */
std::string Student::getName() const {
    return name;
}

/**
 * @brief Get the student's email
 * @return The student's email address
 */
std::string Student::getEmail() const {
    return email;
}

/**
 * @brief Get the student's age
 * @return The student's age
 */
int Student::getAge() const {
    return age;
}

/**
 * @brief Get the list of courses the student is enrolled in
 * @return Vector containing course names
 */
std::vector<std::string> Student::getCourses() const {
    return courses;
}

/**
 * @brief Set the student's ID
 * @param id New ID number to assign
 */
void Student::setStudentId(int id) {
    studentId = id;
}

/**
 * @brief Set the student's name
 * @param name New name to assign
 */
void Student::setName(const std::string& name) {
    this->name = name;
}

/**
 * @brief Set the student's email
 * @param email New email address to assign
 */
void Student::setEmail(const std::string& email) {
    this->email = email;
}

/**
 * @brief Set the student's age
 * @param age New age to assign
 */
void Student::setAge(int age) {
    this->age = age;
}

/**
 * @brief Add a course to student's enrollment list
 * @param course Name of the course to add
 * @details Adds a course only if the student is not already enrolled in it
 */
void Student::addCourse(const std::string& course) {
    if (!isEnrolledIn(course)) {
        courses.push_back(course);
    }
}

/**
 * @brief Remove a course from student's enrollment list
 * @param course Name of the course to remove
 */
void Student::removeCourse(const std::string& course) {
    for (auto it = courses.begin(); it != courses.end(); ++it) {
        if (*it == course) {
            courses.erase(it);
            break;
        }
    }
}

/**
 * @brief Check if student is enrolled in a specific course
 * @param course Name of the course to check
 * @return true if student is enrolled, false otherwise
 */
bool Student::isEnrolledIn(const std::string& course) const {
    for (const auto& c : courses) {
        if (c == course) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Convert student information to string format
 * @return Formatted string containing all student details
 * @details Returns a string containing:
 *          - Student ID
 *          - Name
 *          - Email
 *          - Age
 *          - List of enrolled courses
 */
std::string Student::toString() const {
    std::stringstream ss;
    ss << "Student ID: " << studentId << "\n"
       << "Name: " << name << "\n"
       << "Email: " << email << "\n"
       << "Age: " << age << "\n"
       << "Courses: ";
    
    if (courses.empty()) {
        ss << "None";
    } else {
        for (size_t i = 0; i < courses.size(); ++i) {
            ss << courses[i];
            if (i < courses.size() - 1) {
                ss << ", ";
            }
        }
    }
    
    return ss.str();
}
