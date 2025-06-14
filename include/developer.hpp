#ifndef DEVELOPER_HPP_grtjkösfsghfg
#define DEVELOPER_HPP_grtjkösfsghfg

#include <fstream>  // For file access in load_logo_from_file
#include <iostream>
#include <stdexcept>  // For std::runtime_error
#include <string>
#include <vector>  // Needed for reading the logo

// The Developer class serves as a base class for JuniorDeveloper and SeniorDeveloper.
class Developer
{
   protected:
    std::string name;   // Name of the developer
    std::string alias;  // Alias name of the developer
    std::string logo;   // Logo of the developer (can be multiline)

   public:
    // Constructor to initialize name and alias.
    Developer(const std::string& name, const std::string& alias);

    // Virtual destructor, important for base classes with virtual methods.
    virtual ~Developer() = default;

    // Static method that outputs that coffee was drunk.
    static void drink_coffee();

    // Non-virtual method for loading a logo from a file.
    void load_logo_from_file(const std::string& filename);

    // Getter methods for all member variables.
    const std::string& get_name() const;
    const std::string& get_alias() const;
    const std::string& get_logo() const;

    // Pure virtual method "solve_problem", which must be implemented in derived classes.
    virtual void solve_problem() = 0;

    // Friend function for overloading the stream operator (<<) for std::cout.
    friend std::ostream& operator<<(std::ostream& os, const Developer& dev);
};

#endif  // DEVELOPER_HPP
