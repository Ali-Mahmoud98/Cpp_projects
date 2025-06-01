#include "Student.h"
#include "StudentManager.h"
#include "FileManager.h"
#include "CRUD.h"
#include "DataHandler.h"
#include <iostream>
#include <limits>
#include <string>

#ifndef FILE_PATH
#define FILE_PATH ""
#endif

void displayMenu() {
    std::cout << "\n===== Student Management System =====\n";
    std::cout << "1. Add Student\n";
    std::cout << "2. Delete Student\n";
    std::cout << "3. Search Student by ID\n";
    std::cout << "4. Search Students by Name\n";
    std::cout << "5. List All Students\n";
    std::cout << "6. Enroll Student in Course\n";
    std::cout << "7. Remove Student from Course\n";
    std::cout << "8. Save Data\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    if (FILE_PATH == "") {
        std::cerr << "FILE_PATH is not defined" << std::endl;
        exit(-1);
    }
    // Initialize file manager with data file path
    FileManager fileManager(FILE_PATH);
    
    // Initialize student manager
    StudentManager studentManager;
    
    // Load existing data
    loadData(studentManager, fileManager);
    
    int choice;
    bool running = true;
    bool firstLoop = true;
    
    while (running) {
        if (firstLoop == true)
        {
            firstLoop = false;
        } else {
            std::cout << "Press any key to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        system("clear");
        displayMenu();
        std::cin >> choice;
        
        // Handle invalid input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                addStudent(studentManager);
                break;
            case 2:
                deleteStudent(studentManager);
                break;
            case 3:
                searchStudentById(studentManager);
                break;
            case 4:
                searchStudentsByName(studentManager);
                break;
            case 5:
                listAllStudents(studentManager);
                break;
            case 6:
                enrollStudentInCourse(studentManager);
                break;
            case 7:
                removeStudentFromCourse(studentManager);
                break;
            case 8:
                saveData(studentManager, fileManager);
                break;
            case 9:
                std::cout << "Saving data before exit...\n";
                saveData(studentManager, fileManager);
                std::cout << "Exiting program. Goodbye!\n";
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}
