#include <gtest/gtest.h>
#include "FileManager.h"
#include <fstream>
#include <cstdio>  // for remove()

// Test fixture for FileManager class
class FileManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Use a temporary test file
        testFilePath = "test_students.dat";
        
        // Create test students
        testStudents.push_back(Student(1001, "John Doe", "john.doe@example.com", 20));
        testStudents.push_back(Student(1002, "Jane Smith", "jane.smith@example.com", 22));
        
        // Add courses to students
        testStudents[0].addCourse("CS101");
        testStudents[0].addCourse("MATH202");
        testStudents[1].addCourse("PHYSICS101");
        
        // Initialize FileManager with test file
        fileManager = new FileManager(testFilePath);
    }

    void TearDown() override {
        delete fileManager;
        
        // Clean up temporary test file
        std::remove(testFilePath.c_str());
    }

    std::string testFilePath;
    std::vector<Student> testStudents;
    FileManager* fileManager;
};

// Test file existence check
TEST_F(FileManagerTest, FileExists) {
    // File should not exist initially
    EXPECT_FALSE(fileManager->fileExists());
    
    // Create the file
    fileManager->createEmptyFile();
    
    // Now file should exist
    EXPECT_TRUE(fileManager->fileExists());
}

// Test creating empty file
TEST_F(FileManagerTest, CreateEmptyFile) {
    fileManager->createEmptyFile();
    
    // Verify file was created
    std::ifstream file(testFilePath);
    EXPECT_TRUE(file.good());
    
    // Verify file is empty
    std::string content;
    std::getline(file, content);
    EXPECT_TRUE(content.empty());
}

// Test saving and loading students
TEST_F(FileManagerTest, SaveAndLoadStudents) {
    // Save test students
    bool saveResult = fileManager->saveStudents(testStudents);
    EXPECT_TRUE(saveResult);
    
    // Load saved students
    std::vector<Student> loadedStudents = fileManager->loadStudents();
    
    // Verify correct number of students loaded
    ASSERT_EQ(loadedStudents.size(), 2);
    
    // Verify student data was preserved
    EXPECT_EQ(loadedStudents[0].getStudentId(), 1001);
    EXPECT_EQ(loadedStudents[0].getName(), "John Doe");
    EXPECT_EQ(loadedStudents[0].getEmail(), "john.doe@example.com");
    EXPECT_EQ(loadedStudents[0].getAge(), 20);
    EXPECT_EQ(loadedStudents[0].getCourses().size(), 2);
    EXPECT_TRUE(loadedStudents[0].isEnrolledIn("CS101"));
    EXPECT_TRUE(loadedStudents[0].isEnrolledIn("MATH202"));
    
    EXPECT_EQ(loadedStudents[1].getStudentId(), 1002);
    EXPECT_EQ(loadedStudents[1].getName(), "Jane Smith");
    EXPECT_EQ(loadedStudents[1].getEmail(), "jane.smith@example.com");
    EXPECT_EQ(loadedStudents[1].getAge(), 22);
    EXPECT_EQ(loadedStudents[1].getCourses().size(), 1);
    EXPECT_TRUE(loadedStudents[1].isEnrolledIn("PHYSICS101"));
}

// Test loading from non-existent file
TEST_F(FileManagerTest, LoadFromNonExistentFile) {
    // File does not exist yet
    std::vector<Student> loadedStudents = fileManager->loadStudents();
    
    // Should return an empty vector and create an empty file
    EXPECT_TRUE(loadedStudents.empty());
    EXPECT_TRUE(fileManager->fileExists());
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
