#include <gtest/gtest.h>
#include "CRUD.h"
#include "StudentManager.h"
#include <sstream>

// Mock for std::cin to test input functions
class CinMock {
public:
    CinMock(const std::string& input) {
        // Save the original cin buffer
        oldCin = std::cin.rdbuf();
        
        // Set the input buffer to our stringstream
        inputStream.str(input);
        std::cin.rdbuf(inputStream.rdbuf());
    }
    
    ~CinMock() {
        // Restore the original cin buffer
        std::cin.rdbuf(oldCin);
    }
    
private:
    std::stringstream inputStream;
    std::streambuf* oldCin;
};

// Test fixture for CRUD functions
class CRUDTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a student manager with some test data
        manager = new StudentManager();
        manager->addStudent("John Doe", "john.doe@example.com", 20);
        
        // Get student ID for testing
        std::vector<Student> students = manager->getAllStudents();
        if (!students.empty()) {
            testStudentId = students[0].getStudentId();
        }
    }

    void TearDown() override {
        delete manager;
    }

    StudentManager* manager;
    uint32_t testStudentId;
};

// Test addStudent function
TEST_F(CRUDTest, AddStudent) {
    // Set up mock input for addStudent
    std::string mockInput = "\nJane Smith\njane.smith@example.com\n22\n"; // first \n simulated the enter before entering the name
    CinMock cinMock(mockInput);
    
    // Capture stdout for testing output
    ::testing::internal::CaptureStdout();
    
    // Call addStudent
    addStudent(*manager);
    
    // Get captured output
    std::string output = ::testing::internal::GetCapturedStdout();
    
    // Verify success message
    EXPECT_NE(output.find("Student added successfully"), std::string::npos);
    
    // Verify student was added
    EXPECT_EQ(manager->getStudentCount(), 2);
    
    // // Verify student data is correct
    std::vector<Student*> students = manager->searchStudentsByName("Jane");
    ASSERT_EQ(students.size(), 1);
    EXPECT_EQ(students[0]->getName(), "Jane Smith");
    EXPECT_EQ(students[0]->getEmail(), "jane.smith@example.com");
    EXPECT_EQ(students[0]->getAge(), 22);
}

// Test deleteStudent function
TEST_F(CRUDTest, DeleteStudent) {
    // Set up mock input for deleteStudent
    std::string mockInput = std::to_string(testStudentId) + "\n";
    CinMock cinMock(mockInput);
    
    // Capture stdout for testing output
    ::testing::internal::CaptureStdout();
    
    // Call deleteStudent
    deleteStudent(*manager);
    
    // Get captured output
    std::string output = ::testing::internal::GetCapturedStdout();
    
    // Verify success message
    EXPECT_NE(output.find("Student deleted successfully"), std::string::npos);
    
    // Verify student was deleted
    EXPECT_EQ(manager->getStudentCount(), 0);
}

// Test searchStudentById function
TEST_F(CRUDTest, SearchStudentById) {
    // Set up mock input for searchStudentById
    std::string mockInput = std::to_string(testStudentId) + "\n";
    CinMock cinMock(mockInput);
    
    // Capture stdout for testing output
    ::testing::internal::CaptureStdout();
    
    // Call searchStudentById
    searchStudentById(*manager);
    
    // Get captured output
    std::string output = ::testing::internal::GetCapturedStdout();
    
    // Verify output contains student info
    EXPECT_NE(output.find("Student found"), std::string::npos);
    EXPECT_NE(output.find("John Doe"), std::string::npos);
    EXPECT_NE(output.find("john.doe@example.com"), std::string::npos);
}

// Test searchStudentsByName function
TEST_F(CRUDTest, SearchStudentsByName) {
    // Set up mock input for searchStudentsByName
    std::string mockInput = "John\n";
    CinMock cinMock(mockInput);
    
    // Capture stdout for testing output
    ::testing::internal::CaptureStdout();
    
    // Call searchStudentsByName
    searchStudentsByName(*manager);
    
    // Get captured output
    std::string output = ::testing::internal::GetCapturedStdout();
    
    // Verify output contains student info
    EXPECT_NE(output.find("Found 1 student"), std::string::npos);
    EXPECT_NE(output.find("John Doe"), std::string::npos);
    EXPECT_NE(output.find("john.doe@example.com"), std::string::npos);
}

// Test listAllStudents function
TEST_F(CRUDTest, ListAllStudents) {
    // Capture stdout for testing output
    ::testing::internal::CaptureStdout();
    
    // Call listAllStudents
    listAllStudents(*manager);
    
    // Get captured output
    std::string output = ::testing::internal::GetCapturedStdout();
    
    // Verify output contains student info
    EXPECT_NE(output.find("Total students: 1"), std::string::npos);
    EXPECT_NE(output.find("John Doe"), std::string::npos);
    EXPECT_NE(output.find("john.doe@example.com"), std::string::npos);
}

// Test enrollStudentInCourse function
TEST_F(CRUDTest, EnrollStudentInCourse) {
    // Set up mock input for enrollStudentInCourse
    std::string mockInput = std::to_string(testStudentId) + "\nCS101\n";
    CinMock cinMock(mockInput);
    
    // Capture stdout for testing output
    ::testing::internal::CaptureStdout();
    
    // Call enrollStudentInCourse
    enrollStudentInCourse(*manager);
    
    // Get captured output
    std::string output = ::testing::internal::GetCapturedStdout();
    
    // Verify success message
    EXPECT_NE(output.find("Student enrolled in course successfully"), std::string::npos);
    
    // Verify student was enrolled
    Student* student = manager->getStudent(testStudentId);
    ASSERT_NE(student, nullptr);
    EXPECT_TRUE(student->isEnrolledIn("CS101"));
}

// Test removeStudentFromCourse function
TEST_F(CRUDTest, RemoveStudentFromCourse) {
    // First enroll student in a course
    manager->enrollStudentInCourse(testStudentId, "CS101");
    
    // Set up mock input for removeStudentFromCourse
    std::string mockInput = std::to_string(testStudentId) + "\nCS101\n";
    CinMock cinMock(mockInput);
    
    // Capture stdout for testing output
    ::testing::internal::CaptureStdout();
    
    // Call removeStudentFromCourse
    removeStudentFromCourse(*manager);
    
    // Get captured output
    std::string output = ::testing::internal::GetCapturedStdout();
    
    // Verify success message
    EXPECT_NE(output.find("Student removed from course successfully"), std::string::npos);
    
    // Verify student was removed from course
    Student* student = manager->getStudent(testStudentId);
    ASSERT_NE(student, nullptr);
    EXPECT_FALSE(student->isEnrolledIn("CS101"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
