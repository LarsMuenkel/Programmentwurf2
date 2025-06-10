#ifndef SENIORDEVELOPER_HPP_grtjkösfsghfg
#define SENIORDEVELOPER_HPP_grtjkösfsghfg

#include "developer.hpp"  // Include base class Developer

// The SeniorDeveloper class is derived from Developer.
class SeniorDeveloper : public Developer
{
   public:
    // Constructor that calls the base class constructor.
    SeniorDeveloper(const std::string& name, const std::string& alias);

    // Override of the pure virtual method solve_problem.
    void solve_problem() override;
};

#endif  // SENIORDEVELOPER_HPP
