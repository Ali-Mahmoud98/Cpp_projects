# Student Management System

A comprehensive C++ console application for managing student records and academic information.

## Features

- Add, view, update, and delete student records
- Search for students by ID, name, or other criteria
- Manage course enrollments
- Data persistence through file handling

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/Ali-Mahmoud98/Cpp_projects.git
    cd 01_StudentManagementSystem
    ```
2. Build the project:
    ```bash
    cmake . -B build
    cmake --build build --config Debug --target all -j 10 --
    ```
3. Run the application:
    ```bash
    ./build/StudentManagementSystem
    ```
4. Run the tests:
    ```bash
    cmake --build build --config Debug --target runStudentTests # Run student class tests
    cmake --build build --config Debug --target runStudentManagerTests # Run student manager class tests
    cmake --build build --config Debug --target runFileManagerTests # Run file manager class tests
    cmake --build build --config Debug --target runCRUDTests # Run CRUD class tests
    cmake --build build --config Debug --target runDataHandlerTests # Run data handler class tests
    ```

## Usage

The application provides a menu-driven interface:

1. **Student Management**:
   - Add new students
   - Update student information
   - View student details
   - Delete student records

2. **Course Management**:
   - Add new courses
   - Assign students to courses

## Project Structure

```
01_StudentManagementSystem/
├── include/             # Header files
├── src/                 # Source files
├── data/                # Data storage
├── docs/                # Documentation
└── README.md            # This file
```

## Technologies

- C++ (Standard: C++11/14/17)
- File I/O for data persistence
- OOP principles for system design
