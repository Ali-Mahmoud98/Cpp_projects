#include "DataHandler.h"
#include <iostream>

/**
 * @brief Save student data to a file
 * @param manager Reference to the StudentManager instance
 * @param fileManager Reference to the FileManager instance
 */
void saveData(StudentManager& manager, FileManager& fileManager) {
    std::cout << "\n----- Saving Data -----\n";
    
    if (fileManager.saveStudents(manager.getAllStudents())) {
        std::cout << "Data saved successfully!\n";
    } else {
        std::cout << "Failed to save data.\n";
    }
}

/**
 * @brief Load student data from a file
 * @param manager Reference to the StudentManager instance
 * @param fileManager Reference to the FileManager instance
 */
void loadData(StudentManager& manager, FileManager& fileManager) {
    std::cout << "Loading data...\n";
    
    std::vector<Student> loadedStudents = fileManager.loadStudents();
    for (const auto& student : loadedStudents) {
        // Add each loaded student to the manager
        manager.addStudent(student.getName(), student.getEmail(), student.getAge());
        
        // Add courses
        for (const auto& course : student.getCourses()) {
            manager.enrollStudentInCourse(student.getStudentId(), course);
        }
    }
    
    std::cout << "Loaded " << loadedStudents.size() << " students.\n";
}
