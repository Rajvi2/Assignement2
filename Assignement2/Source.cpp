#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct STUDENT_DATA {
    std::string first_name;
    std::string last_name;
};

int main() {
    // Vector to store student objects
    std::vector<STUDENT_DATA> students;

    // Open the StudentData.txt file
    std::ifstream file("StudentData.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening StudentData.txt file!" << std::endl;
        return 1;
    }

    std::string line;
    // Read each line from the file
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string first_name, last_name;

        // Parse the line (assuming first and last names are separated by a comma)
        if (std::getline(ss, first_name, ',') && std::getline(ss, last_name)) {
            // Create a student object and add it to the vector
            STUDENT_DATA student = { first_name, last_name };
            students.push_back(student);
        }
    }

    file.close();

    // Print out the students stored in the vector
    for (const auto& student : students) {
        std::cout << "First Name: " << student.first_name << ", Last Name: " << student.last_name << std::endl;
    }

    return 0;
}
