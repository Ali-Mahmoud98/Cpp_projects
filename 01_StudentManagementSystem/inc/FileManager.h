#ifndef FILE_MANAGER_H__
#define FILE_MANAGER_H__

#include "Student.h"
#include <vector>
#include <string>

/**
 * @class FileManager
 * @brief Manages file operations for student data persistence
 * 
 * @details This class handles reading and writing student data to a file
 *          in CSV format. It provides functionality for:
 *          - Saving student records to file
 *          - Loading student records from file
 *          - Basic file management operations
 */
class FileManager {
private:
    std::string dataFilePath;    ///< Path to the data storage file

public:
    /**
     * @brief Constructor for FileManager
     * @param filePath Path to the data file
     */
    FileManager(const std::string& filePath);
    
    /**
     * @brief Save student data to file
     * @param students Vector of Student objects to save
     * @return true if save operation was successful, false otherwise
     */
    bool saveStudents(const std::vector<Student>& students);

    /**
     * @brief Load student data from file
     * @return Vector of Student objects loaded from file
     */
    std::vector<Student> loadStudents();
    
    /**
     * @brief Check if the data file exists
     * @return true if file exists and is accessible, false otherwise
     */
    bool fileExists() const;

    /**
     * @brief Create an empty data file
     * @details Creates a new empty file at the specified path if it doesn't exist
     */
    void createEmptyFile() const;
};

#endif // FILE_MANAGER_H__
