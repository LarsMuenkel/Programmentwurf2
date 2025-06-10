#ifndef SENIORDEVELOPER_HPP
#define SENIORDEVELOPER_HPP

#include "developer.hpp" // Basisklasse Developer einbinden

// Die Klasse SeniorDeveloper ist von Developer abgeleitet.
class SeniorDeveloper : public Developer {
public:
    // Konstruktor, der den Konstruktor der Basisklasse aufruft.
    SeniorDeveloper(const std::string& name, const std::string& alias);

    // Überschreiben der rein virtuellen Methode solve_problem.
    void solve_problem() override;
};

#endif // SENIORDEVELOPER_HPP
