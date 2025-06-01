#include <gtest/gtest.h>
#include "StudentManager.h"

// Test fixture for StudentManager class
class StudentManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Add some test students
        manager.addStudent("John Doe", "john.doe@example.com", 20);
        manager.addStudent("Jane Smith", "jane.smith@example.com", 22);
        manager.addStudent("Bob Johnson", "bob.johnson@example.com", 19);
    }

    StudentManager manager;
};

// Test adding students
TEST_F(StudentManagerTest, AddStudent) {
    // Check initial count
    EXPECT_EQ(manager.getStudentCount(), 3);
    
    // Add another student
    bool result = manager.addStudent("Alice Brown", "alice.brown@example.com", 21);
    EXPECT_TRUE(result);
    EXPECT_EQ(manager.getStudentCount(), 4);
    
    // Verify student was added correctly
    std::vector<Student*> students = manager.searchStudentsByName("Alice");
    ASSERT_EQ(students.size(), 1);
    EXPECT_EQ(students[0]->getName(), "Alice Brown");
    EXPECT_EQ(students[0]->getEmail(), "alice.brown@example.com");
    EXPECT_EQ(students[0]->getAge(), 21);
}

// Test deleting students
TEST_F(StudentManagerTest, DeleteStudent) {
    // Get a student to delete
    std::vector<Student*> students = manager.searchStudentsByName("John");
    ASSERT_EQ(students.size(), 1);
    int studentId = students[0]->getStudentId();
    
    // Delete the student
    bool result = manager.deleteStudent(studentId);
    EXPECT_TRUE(result);
    EXPECT_EQ(manager.getStudentCount(), 2);
    
    // Verify student was deleted
    Student* deletedStudent = manager.getStudent(studentId);
    EXPECT_EQ(deletedStudent, nullptr);
    
    // Try to delete a non-existent student
    result = manager.deleteStudent(9999);
    EXPECT_FALSE(result);
    EXPECT_EQ(manager.getStudentCount(), 2);
}

// Test searching students by name
TEST_F(StudentManagerTest, SearchStudentsByName) {
    // Search for a specific student
    std::vector<Student*> students = manager.searchStudentsByName("Jane");
    ASSERT_EQ(students.size(), 1);
    EXPECT_EQ(students[0]->getName(), "Jane Smith");
    
    // Search for a partial name that should match multiple students
    students = manager.searchStudentsByName("o");
    ASSERT_EQ(students.size(), 2); // Should match "John Doe" and "Bob Johnson"
    
    // Search for a name that doesn't exist
    students = manager.searchStudentsByName("Xavier");
    EXPECT_TRUE(students.empty());
    
    // Case-insensitive search
    students = manager.searchStudentsByName("jane");
    ASSERT_EQ(students.size(), 1);
    EXPECT_EQ(students[0]->getName(), "Jane Smith");
}

// Test getting a student by ID
TEST_F(StudentManagerTest, GetStudent) {
    // Get a student ID to use
    std::vector<Student*> students = manager.searchStudentsByName("Jane");
    ASSERT_EQ(students.size(), 1);
    int studentId = students[0]->getStudentId();
    
    // Get the student by ID
    Student* student = manager.getStudent(studentId);
    ASSERT_NE(student, nullptr);
    EXPECT_EQ(student->getName(), "Jane Smith");
    EXPECT_EQ(student->getEmail(), "jane.smith@example.com");
    
    // Try to get a non-existent student
    student = manager.getStudent(9999);
    EXPECT_EQ(student, nullptr);
}

// Test enrolling students in courses
TEST_F(StudentManagerTest, EnrollStudentInCourse) {
    // Get a student ID to use
    std::vector<Student*> students = manager.searchStudentsByName("John");
    ASSERT_EQ(students.size(), 1);
    int studentId = students[0]->getStudentId();
    
    // Enroll the student in a course
    bool result = manager.enrollStudentInCourse(studentId, "CS101");
    EXPECT_TRUE(result);
    
    // Verify enrollment
    Student* student = manager.getStudent(studentId);
    ASSERT_NE(student, nullptr);
    EXPECT_TRUE(student->isEnrolledIn("CS101"));
    
    // Enroll in another course
    result = manager.enrollStudentInCourse(studentId, "MATH202");
    EXPECT_TRUE(result);
    EXPECT_TRUE(student->isEnrolledIn("MATH202"));
    
    // Try to enroll a non-existent student
    result = manager.enrollStudentInCourse(9999, "CS101");
    EXPECT_FALSE(result);
}

// Test removing students from courses
TEST_F(StudentManagerTest, RemoveStudentFromCourse) {
    // Get a student ID to use
    std::vector<Student*> students = manager.searchStudentsByName("John");
    ASSERT_EQ(students.size(), 1);
    int studentId = students[0]->getStudentId();
    
    // Enroll the student in courses
    manager.enrollStudentInCourse(studentId, "CS101");
    manager.enrollStudentInCourse(studentId, "MATH202");
    
    // Remove from one course
    bool result = manager.removeStudentFromCourse(studentId, "CS101");
    EXPECT_TRUE(result);
    
    // Verify removal
    Student* student = manager.getStudent(studentId);
    ASSERT_NE(student, nullptr);
    EXPECT_FALSE(student->isEnrolledIn("CS101"));
    EXPECT_TRUE(student->isEnrolledIn("MATH202"));
    
    // Try to remove from a course the student isn't enrolled in
    result = manager.removeStudentFromCourse(studentId, "HISTORY101");
    EXPECT_FALSE(result);
    
    // Try to remove a non-existent student from a course
    result = manager.removeStudentFromCourse(9999, "MATH202");
    EXPECT_FALSE(result);
}

// Test getting all students
TEST_F(StudentManagerTest, GetAllStudents) {
    std::vector<Student> allStudents = manager.getAllStudents();
    EXPECT_EQ(allStudents.size(), 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
