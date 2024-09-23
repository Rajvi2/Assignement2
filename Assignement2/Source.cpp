#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip> // For std::setw

// Struct to hold student data
struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
    std::string email; // Store email
};

int main() {
    std::vector<STUDENT_DATA> students;

    // Step #3: Read StudentData.txt
    std::ifstream inputFile("StudentData.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file StudentData.txt" << std::endl;
        return 1; // Exit if file can't be opened
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string firstName, lastName;
        std::getline(iss, firstName, ','); // Read first name
        std::getline(iss, lastName);        // Read last name
        students.push_back({ firstName, lastName, "" }); // Initialize with empty email
    }

    inputFile.close();

    // Step #4: Print student information
#ifdef _DEBUG
#ifdef PRE_RELEASE
    // In Debug Pre-Release Mode: Read emails and print names with emails
    std::cout << "Debug Pre-Release Mode: Student List with Emails:" << std::endl;
    std::cout << std::left << std::setw(20) << "First Name"
        << std::setw(20) << "Last Name"
        << "Email Address" << std::endl;
    std::cout << std::string(60, '-') << std::endl; // Separator line

    std::ifstream emailFile("StudentData_Emails.txt");
    if (!emailFile) {
        std::cerr << "Unable to open file StudentData_Emails.txt" << std::endl;
        return 1; // Exit if file can't be opened
    }

    size_t index = 0;
    while (std::getline(emailFile, line) && index < students.size()) {
        // Directly assign only the email address from the file to the student email field
        students[index].email = line; // Store only the email
        ++index;
    }

    emailFile.close();

    // Print names with emails correctly formatted
    for (const auto& student : students) {
        std::cout <<student.email << std::endl; // Correctly show only email
    }

#else
    // In Debug Mode (without PRE_RELEASE): Just print student names
    std::cout << "Debug Mode: Student List:" << std::endl;
    std::cout << std::left << std::setw(20) << "First Name"
        << std::setw(20) << "Last Name" << std::endl;
    std::cout << std::string(40, '-') << std::endl; // Separator line

    for (const auto& student : students) {
        std::cout << std::left << std::setw(20) << student.firstName
            << std::setw(20) << student.lastName << std::endl;
    }
#endif // PRE_RELEASE

#else
    // Non-debug messages
#ifdef PRE_RELEASE
    std::cout << "Running in Pre-Release Mode" << std::endl;
#else
    std::cout << "Running in Standard Mode" << std::endl;
#endif
#endif // _DEBUG

    return 0;
}
