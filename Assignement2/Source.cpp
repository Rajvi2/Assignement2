#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct STUDENT_DATA {
    std::string first_name;
    std::string last_name;
    std::string email;
};

int main() {
    // Vector to store student objects
    std::vector<STUDENT_DATA> students;

    // Print application mode
#ifdef PRE_RELEASE
    std::cout << "Running Pre-Release Version" << std::endl;
#else
    std::cout << "Running Standard Version" << std::endl;
#endif

    // Relative path to the StudentData.txt file
    std::string file_path = "StudentData.txt";

    // Open the StudentData.txt file
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file at path: " << file_path << std::endl;
        std::cerr << "Make sure the file is located in the correct directory." << std::endl;
        return 1;
    }

    std::string line;

    // Read each line from the file
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string first_name, last_name;

        // Parse the line (assuming first and last names are separated by a comma)
        if (std::getline(ss, first_name, ',') && std::getline(ss, last_name)) {
            STUDENT_DATA student = { first_name, last_name, "" };  // email will be added later in pre-release
            students.push_back(student);
        }
        else {
            std::cerr << "Warning: Skipping malformed line: " << line << std::endl;
        }
    }

    file.close();

#ifdef PRE_RELEASE
    // Add email addresses in Pre-Release mode
    std::ifstream email_file("StudentData_Emails.txt");

    if (!email_file.is_open()) {
        std::cerr << "Error: Unable to open the email file." << std::endl;
        return 1;
    }

    // Read the email data and assign to students
    while (std::getline(email_file, line)) {
        std::stringstream ss(line);
        std::string first_name, last_name, email;

        // Parse the line (assuming first name, last name, and email are separated by commas)
        if (std::getline(ss, first_name, ',') && std::getline(ss, last_name, ',') && std::getline(ss, email)) {
            for (auto& student : students) {
                if (student.first_name == first_name && student.last_name == last_name) {
                    student.email = email;
                    break;
                }
            }
        }
        else {
            std::cerr << "Warning: Skipping malformed email line: " << line << std::endl;
        }
    }

    email_file.close();

    // Print out the students with emails
    std::cout << "Students with Emails Loaded:" << std::endl;
    for (const auto& student : students) {
        std::cout << "First Name: " << student.first_name << ", Last Name: " << student.last_name
            << ", Email: " << student.email << std::endl;
    }
#endif

    return 0;
}
