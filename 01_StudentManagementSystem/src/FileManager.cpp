#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief Constructor for FileManager
 * @param filePath Path to the data file
 * @details Initializes the FileManager with the specified file path for storing student data
 */
FileManager::FileManager(const std::string& filePath) : dataFilePath(filePath) {}

/**
 * @brief Save student data to file
 * @param students Vector of Student objects to save
 * @return true if save operation was successful, false otherwise
 * @details Saves student data in CSV format with the following structure:
 *          ID,Name,Email,Age,Course1,Course2,...
 */
bool FileManager::saveStudents(const std::vector<Student>& students) {
    std::ofstream outFile(dataFilePath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing: " << dataFilePath << std::endl;
        return false;
    }
    
    for (const auto& student : students) {
        // Write student data in CSV format
        outFile << student.getStudentId() << ","
                << student.getName() << ","
                << student.getEmail() << ","
                << student.getAge();
        
        // Write courses
        const auto& courses = student.getCourses();
        for (const auto& course : courses) {
            outFile << "," << course;
        }
        
        outFile << std::endl;
    }
    
    outFile.close();
    return true;
}

/**
 * @brief Load student data from file
 * @return Vector of Student objects loaded from file
 * @details Reads CSV formatted student data and creates Student objects
 *          If file doesn't exist, creates an empty file and returns empty vector
 */
std::vector<Student> FileManager::loadStudents() {
    std::vector<Student> students;
    
    if (!fileExists()) {
        std::cerr << "Warning: Data file does not exist. Creating an empty file." << std::endl;
        createEmptyFile();
        return students;
    }
    
    std::ifstream inFile(dataFilePath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open file for reading: " << dataFilePath << std::endl;
        return students;
    }
    
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string token;
        
        // Parse student ID
        std::getline(ss, token, ',');
        int studentId = std::stoi(token);
        
        // Parse name
        std::getline(ss, token, ',');
        std::string name = token;
        
        // Parse email
        std::getline(ss, token, ',');
        std::string email = token;
        
        // Parse age
        std::getline(ss, token, ',');
        int age = std::stoi(token);
        
        // Create student object
        Student student(studentId, name, email, age);
        
        // Parse courses
        while (std::getline(ss, token, ',')) {
            student.addCourse(token);
        }
        
        students.push_back(student);
    }
    
    inFile.close();
    return students;
}

/**
 * @brief Check if the data file exists
 * @return true if file exists and is accessible, false otherwise
 */
bool FileManager::fileExists() const {
    std::ifstream file(dataFilePath);
    return file.good();
}

/**
 * @brief Create an empty data file
 * @details Creates a new empty file at the specified path
 */
void FileManager::createEmptyFile() const {
    std::ofstream file(dataFilePath);
    file.close();
}
