#ifndef DATA_HANDLER_H__
#define DATA_HANDLER_H__

#include "StudentManager.h"
#include "FileManager.h"

/**
 * @brief Save student data to a file
 * @param manager Reference to the StudentManager instance
 * @param fileManager Reference to the FileManager instance
 * @details Saves all student data managed by the StudentManager to the file specified in FileManager
 */
void saveData(StudentManager& manager, FileManager& fileManager);

/**
 * @brief Load student data from a file
 * @param manager Reference to the StudentManager instance
 * @param fileManager Reference to the FileManager instance
 * @details Loads student data from the file specified in FileManager and populates the StudentManager
 */
void loadData(StudentManager& manager, FileManager& fileManager);

#endif // DATA_HANDLER_H__
