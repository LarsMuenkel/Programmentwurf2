#ifndef JUNIORDEVELOPER_HPP_grtjkösfsghfg
#define JUNIORDEVELOPER_HPP_grtjkösfsghfg

#include "developer.hpp"  // Include base class Developer

// The JuniorDeveloper class is derived from Developer.
class JuniorDeveloper : public Developer
{
   public:
    // Constructor that calls the base class constructor.
    JuniorDeveloper(const std::string& name, const std::string& alias);

    // Override of the pure virtual method solve_problem.
    void solve_problem() override;
};

#endif  // JUNIORDEVELOPER_HPP
