#include <gtest/gtest.h>
#include "DataHandler.h"
#include "StudentManager.h"
#include "FileManager.h"
#include <fstream>
#include <cstdio>  // for remove()

// Test fixture for DataHandler functions
class DataHandlerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Use a temporary test file
        testFilePath = "test_data_handler.dat";
        
        // Initialize managers
        fileManager = new FileManager(testFilePath);
        studentManager = new StudentManager();
        
        // Add some test students to the manager
        studentManager->addStudent("John Doe", "john.doe@example.com", 20);
        studentManager->addStudent("Jane Smith", "jane.smith@example.com", 22);
        
        // Get student IDs for later use
        std::vector<Student> students = studentManager->getAllStudents();
        if (!students.empty()) {
            testStudentId = students[0].getStudentId();
        }
        
        // Enroll students in courses
        studentManager->enrollStudentInCourse(testStudentId, "CS101");
        studentManager->enrollStudentInCourse(testStudentId, "MATH202");
    }

    void TearDown() override {
        delete fileManager;
        delete studentManager;
        
        // Clean up temporary test file
        std::remove(testFilePath.c_str());
    }

    std::string testFilePath;
    FileManager* fileManager;
    StudentManager* studentManager;
    uint32_t testStudentId;
};

// Test saving data
TEST_F(DataHandlerTest, SaveData) {
    // Save data
    ::testing::internal::CaptureStdout();  // Capture console output
    saveData(*studentManager, *fileManager);
    std::string output = ::testing::internal::GetCapturedStdout();
    
    // Check output message
    EXPECT_NE(output.find("Data saved successfully"), std::string::npos);
    
    // Verify file exists
    EXPECT_TRUE(fileManager->fileExists());
    
    // Verify file contains data
    std::ifstream file(testFilePath);
    std::string line;
    int lineCount = 0;
    while (std::getline(file, line)) {
        lineCount++;
    }
    EXPECT_EQ(lineCount, 2);  // Should have 2 students
}

// Test loading data
TEST_F(DataHandlerTest, LoadData) {
    // First save some data
    saveData(*studentManager, *fileManager);
    
    // Create a new student manager to load data into
    StudentManager newManager;
    
    // Load data into the new manager
    ::testing::internal::CaptureStdout();  // Capture console output
    loadData(newManager, *fileManager);
    std::string output = ::testing::internal::GetCapturedStdout();
    
    // Check output message
    EXPECT_NE(output.find("Loaded 2 students"), std::string::npos);
    
    // Verify students were loaded correctly
    EXPECT_EQ(newManager.getStudentCount(), 2);
    
    // Verify course enrollments were preserved
    std::vector<Student*> students = newManager.searchStudentsByName("John");
    ASSERT_EQ(students.size(), 1);
    EXPECT_TRUE(students[0]->isEnrolledIn("CS101"));
    EXPECT_TRUE(students[0]->isEnrolledIn("MATH202"));
}

// Test data persistence
TEST_F(DataHandlerTest, DataPersistence) {
    // Save initial data
    saveData(*studentManager, *fileManager);
    
    // Create a new student manager
    StudentManager manager1;
    
    // Load data into manager1
    loadData(manager1, *fileManager);
    
    // Add a new student and save again
    manager1.addStudent("Alice Brown", "alice.brown@example.com", 21);
    saveData(manager1, *fileManager);
    
    // Create another manager
    StudentManager manager2;
    
    // Load data into manager2
    loadData(manager2, *fileManager);
    
    // Verify all students are present
    EXPECT_EQ(manager2.getStudentCount(), 3);
    
    // Verify the new student is present
    std::vector<Student*> students = manager2.searchStudentsByName("Alice");
    ASSERT_EQ(students.size(), 1);
    EXPECT_EQ(students[0]->getName(), "Alice Brown");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
