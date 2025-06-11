#include <iostream>
#include <memory>  // For std::shared_ptr and std::make_shared
#include <vector>

#include "developer.hpp"
#include "juniordeveloper.hpp"
#include "seniordeveloper.hpp"

int main()
{
    // 1. Create a vector of shared_ptr to Developer objects.
    std::vector<std::shared_ptr<Developer>> developers;

    // 2. Instantiate at least one object of the classes SeniorDeveloper and JuniorDeveloper
    //    using dynamic memory allocation (std::make_shared).
    auto senior_dev = std::make_shared<SeniorDeveloper>("Tony Stark", "Iron Man");
    auto junior_dev = std::make_shared<JuniorDeveloper>("Peter Parker", "Spiderman");

    try
    {
        senior_dev->load_logo_from_file("iron_man_logo.txt");
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error loading logo for Senior Developer: " << e.what() << std::endl;
    }

    try
    {
        junior_dev->load_logo_from_file("spiderman_logo.txt");
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error loading logo for Junior Developer: " << e.what() << std::endl;
    }

    // 3. Add all created Developer objects to the vector.
    developers.push_back(senior_dev);
    developers.push_back(junior_dev);

    // 4. Use a loop and an iterator to iterate over the vector,
    //    letting each Developer in the vector "solve a problem".
    for (auto it = developers.begin(); it != developers.end(); ++it)
    {
        (*it)->solve_problem();  // Polymorphic call of solve_problem()
        if (std::next(it) != developers.end())
        {  // Adds a blank line between outputs, except after the last element
            std::cout << std::endl;
        }
    }

    return 0;
}