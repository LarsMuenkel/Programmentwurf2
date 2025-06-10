#include "juniordeveloper.hpp"
#include <iostream> // For std::cout

// Implementation of the constructor.
// Calls the constructor of the base class Developer.
JuniorDeveloper::JuniorDeveloper(const std::string& name, const std::string& alias)
    : Developer(name, alias) {
    // No additional initialization is required in the JuniorDeveloper constructor.
}

// Implementation of the method solve_problem for JuniorDeveloper.
void JuniorDeveloper::solve_problem() {
    std::cout << "Solving a problem:" << std::endl;
    // Use the overloaded stream operator of the base class to output name, alias, and logo.
    std::cout << *this << std::endl; 
    std::cout << "Puh, that was tough" << std::endl; // Specific message for JuniorDeveloper
    
    // Call the static method drink_coffee of the base class.
    Developer::drink_coffee(); 
}
