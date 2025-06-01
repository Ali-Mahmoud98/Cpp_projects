#ifndef CRUD_H__
#define CRUD_H__

#include "StudentManager.h"
#include <iostream>

/**
 * @brief Add a new student to the system
 * @param manager Reference to the StudentManager instance
 * @details Prompts user for student details (name, email, age) and
 *          attempts to add the student to the system
 */
void addStudent(StudentManager& manager);

/**
 * @brief Delete a student from the system
 * @param manager Reference to the StudentManager instance
 * @details Prompts user for student ID and attempts to remove
 *          the corresponding student from the system
 */
void deleteStudent(StudentManager& manager);

/**
 * @brief Search for a student using their ID
 * @param manager Reference to the StudentManager instance
 * @details Prompts user for student ID and displays the student's
 *          information if found
 */
void searchStudentById(StudentManager& manager);

/**
 * @brief Search for students by name
 * @param manager Reference to the StudentManager instance
 * @details Prompts user for a name or partial name and displays
 *          all matching students' information
 */
void searchStudentsByName(StudentManager& manager);

/**
 * @brief Display all students in the system
 * @param manager Reference to the StudentManager instance
 * @details Lists all students currently in the system with their
 *          complete information
 */
void listAllStudents(StudentManager& manager);

/**
 * @brief Enroll a student in a course
 * @param manager Reference to the StudentManager instance
 * @details Prompts user for student ID and course name, then
 *          attempts to enroll the student in the specified course
 */
void enrollStudentInCourse(StudentManager& manager);

/**
 * @brief Remove a student from a course
 * @param manager Reference to the StudentManager instance
 * @details Prompts user for student ID and course name, then
 *          attempts to remove the student from the specified course
 */
void removeStudentFromCourse(StudentManager& manager);

#endif // CRUD_H__
