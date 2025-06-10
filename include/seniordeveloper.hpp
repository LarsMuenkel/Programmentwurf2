#ifndef SENIORDEVELOPER_HPP
#define SENIORDEVELOPER_HPP

#include "developer.hpp" // Include base class Developer

// The SeniorDeveloper class is derived from Developer.
class SeniorDeveloper : public Developer {
public:
    // Constructor that calls the base class constructor.
    SeniorDeveloper(const std::string& name, const std::string& alias);

    // Override of the pure virtual method solve_problem.
    void solve_problem() override;
};

#endif // SENIORDEVELOPER_HPP
