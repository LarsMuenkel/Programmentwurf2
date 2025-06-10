#include "developer.hpp"

// Implementation of the constructor
Developer::Developer(const std::string& name, const std::string& alias)
    : name(name), alias(alias) {}


// Implementation of the static method drink_coffee
void Developer::drink_coffee() {
    std::cout << "Ahhhh, I needed that coffee!!!" << std::endl;
}

// Implementation of the method load_logo_from_file
void Developer::load_logo_from_file(const std::string& filename) {
    // The LOGO_PATH is provided through the compiler definition in CMakeLists.txt.
    // It is important to ensure that LOGO_PATH is correctly defined.
    // If LOGO_PATH is not defined, this will result in a compiler error.
    // The macro name LOGO_PATH is used directly here.
    std::string full_path = std::string(LOGO_PATH) + "/" + filename;
    
    std::ifstream logo_file(full_path);
    if (!logo_file.is_open()) {
        // Error if the file cannot be opened.
        throw std::runtime_error("Error: Could not open logo file: " + full_path);
    }

    std::string line;
    std::vector<std::string> logo_lines;
    while (std::getline(logo_file, line)) {
        logo_lines.push_back(line);
    }
    logo_file.close();

    // Save the logo as a single string with line breaks
    this->logo = ""; // Clear the old logo
    for (size_t i = 0; i < logo_lines.size(); ++i) {
        this->logo += logo_lines[i];
        if (i < logo_lines.size() - 1) {
            this->logo += "\n"; // Add line break, except for the last line
        }
    }

    if (this->logo.empty() && !logo_lines.empty()) {
        // Fallback if the logo is empty but lines were read (e.g., only blank lines)
        // In this case, one could decide to consider the logo as "empty" or
        // keep the read blank lines. Here we keep it.
    } else if (logo_lines.empty()) {
        // If the file was empty, the logo remains an empty string.
        // One could also issue a warning or throw an error here, depending on the requirement.
    }
}

// Implementation of the getter methods
const std::string& Developer::get_name() const {
    return this->name;
}

const std::string& Developer::get_alias() const {
    return this->alias;
}

const std::string& Developer::get_logo() const {
    return this->logo;
}

// Implementation of the overloaded stream operator
std::ostream& operator<<(std::ostream& os, const Developer& dev) {
    // If a logo has been loaded, it is output first.
    if (!dev.get_logo().empty()) {
        os << dev.get_logo() << std::endl;
    }
    os << "Name: " << dev.get_name() << std::endl;
    os << "Alias: " << dev.get_alias(); // No std::endl here, so it fits in solve_problem
    return os;
}