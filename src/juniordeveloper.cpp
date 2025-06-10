#include "juniordeveloper.hpp"
#include <iostream> // Für std::cout

// Implementierung des Konstruktors.
// Ruft den Konstruktor der Basisklasse Developer auf.
JuniorDeveloper::JuniorDeveloper(const std::string& name, const std::string& alias)
    : Developer(name, alias) {
    // Keine zusätzliche Initialisierung im JuniorDeveloper Konstruktor notwendig.
}

// Implementierung der Methode solve_problem für JuniorDeveloper.
void JuniorDeveloper::solve_problem() {
    std::cout << "Solving a problem:" << std::endl;
    // Den überladenen Stream-Operator der Basisklasse verwenden, um Name, Alias und Logo auszugeben.
    std::cout << *this << std::endl; 
    std::cout << "Puh, that was tough" << std::endl; // Spezifische Nachricht für JuniorDeveloper
    
    // Die statische Methode drink_coffee der Basisklasse aufrufen.
    Developer::drink_coffee(); 
}
