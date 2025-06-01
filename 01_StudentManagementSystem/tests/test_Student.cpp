#include <gtest/gtest.h>
#include "Student.h"

// Test fixture for Student class
class StudentTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a student with test data
        testStudent = Student(1001, "John Doe", "john.doe@example.com", 20);
    }

    Student testStudent;
};

// Test constructor and getters
TEST_F(StudentTest, ConstructorAndGetters) {
    EXPECT_EQ(testStudent.getStudentId(), 1001);
    EXPECT_EQ(testStudent.getName(), "John Doe");
    EXPECT_EQ(testStudent.getEmail(), "john.doe@example.com");
    EXPECT_EQ(testStudent.getAge(), 20);
    EXPECT_TRUE(testStudent.getCourses().empty());
}

// Test setters
TEST_F(StudentTest, Setters) {
    testStudent.setStudentId(1002);
    EXPECT_EQ(testStudent.getStudentId(), 1002);
    
    testStudent.setName("Jane Smith");
    EXPECT_EQ(testStudent.getName(), "Jane Smith");
    
    testStudent.setEmail("jane.smith@example.com");
    EXPECT_EQ(testStudent.getEmail(), "jane.smith@example.com");
    
    testStudent.setAge(22);
    EXPECT_EQ(testStudent.getAge(), 22);
}

// Test course management
TEST_F(StudentTest, CourseManagement) {
    // Add a course
    testStudent.addCourse("CS101");
    EXPECT_EQ(testStudent.getCourses().size(), 1);
    EXPECT_TRUE(testStudent.isEnrolledIn("CS101"));
    
    // Add another course
    testStudent.addCourse("MATH202");
    EXPECT_EQ(testStudent.getCourses().size(), 2);
    EXPECT_TRUE(testStudent.isEnrolledIn("MATH202"));
    
    // Add a duplicate course (should not be added)
    testStudent.addCourse("CS101");
    EXPECT_EQ(testStudent.getCourses().size(), 2);
    
    // Remove a course
    testStudent.removeCourse("CS101");
    EXPECT_EQ(testStudent.getCourses().size(), 1);
    EXPECT_FALSE(testStudent.isEnrolledIn("CS101"));
    EXPECT_TRUE(testStudent.isEnrolledIn("MATH202"));
    
    // Remove a non-existent course (should have no effect)
    testStudent.removeCourse("HISTORY101");
    EXPECT_EQ(testStudent.getCourses().size(), 1);
}

// Test toString method
TEST_F(StudentTest, ToStringMethod) {
    std::string result = testStudent.toString();
    EXPECT_NE(result.find("Student ID: 1001"), std::string::npos);
    EXPECT_NE(result.find("Name: John Doe"), std::string::npos);
    EXPECT_NE(result.find("Email: john.doe@example.com"), std::string::npos);
    EXPECT_NE(result.find("Age: 20"), std::string::npos);
    EXPECT_NE(result.find("Courses: None"), std::string::npos);
    
    // Add a course and check that toString includes it
    testStudent.addCourse("CS101");
    result = testStudent.toString();
    EXPECT_NE(result.find("Courses: CS101"), std::string::npos);
    
    // Add another course and check that toString includes both
    testStudent.addCourse("MATH202");
    result = testStudent.toString();
    EXPECT_NE(result.find("Courses: CS101, MATH202"), std::string::npos);
}

// Test default constructor
TEST(StudentDefaultConstructorTest, DefaultValues) {
    Student defaultStudent;
    EXPECT_EQ(defaultStudent.getStudentId(), 0);
    EXPECT_EQ(defaultStudent.getName(), "");
    EXPECT_EQ(defaultStudent.getEmail(), "");
    EXPECT_EQ(defaultStudent.getAge(), 0);
    EXPECT_TRUE(defaultStudent.getCourses().empty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
