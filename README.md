# IVS Project 1 - Testing

## Author

- **Name:** Maksim Kalutski
- **Login:** xkalut00

## Description

This project is focused on practical verification of software testing skills using unit tests. The project is divided into three main parts:

1. Black box tests - testing unknown code.
2. White box tests - testing known code.
3. Test Driven Development - implementation of code based on tests.

## Project Structure

- **System of translation (CMake):** Generation of scripts for translation.
- `black_box_tests.cpp` Testing of unknown code.
- `white_box_tests.cpp` Testing of known code.
- `tdd_code.cpp` Implementation of code based on tests.

## Prerequisites and Compilation

- **Tools:** GCC 5.4+, GCOV, LCOV v1.14, CMake 3.16+, GoogleTest, Git client.
- **Platform:** Linux/GCC.

### Compilation and Execution

- Unpack the files into a directory, compile using CMake, and run the tests via ctest or directly.