#ifndef JUNIORDEVELOPER_HPP
#define JUNIORDEVELOPER_HPP

#include "developer.hpp" // Basisklasse Developer einbinden

// Die Klasse JuniorDeveloper ist von Developer abgeleitet.
class JuniorDeveloper : public Developer {
public:
    // Konstruktor, der den Konstruktor der Basisklasse aufruft.
    JuniorDeveloper(const std::string& name, const std::string& alias);

    // Überschreiben der rein virtuellen Methode solve_problem.
    void solve_problem() override;
};

#endif // JUNIORDEVELOPER_HPP
