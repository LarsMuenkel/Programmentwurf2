#include "seniordeveloper.hpp"
#include <iostream> // Für std::cout

// Implementierung des Konstruktors.
// Ruft den Konstruktor der Basisklasse Developer auf.
SeniorDeveloper::SeniorDeveloper(const std::string& name, const std::string& alias)
    : Developer(name, alias) {
    // Keine zusätzliche Initialisierung im SeniorDeveloper Konstruktor notwendig.
}

// Implementierung der Methode solve_problem für SeniorDeveloper.
void SeniorDeveloper::solve_problem() {
    std::cout << "Solving a problem:" << std::endl;
    // Den überladenen Stream-Operator der Basisklasse verwenden, um Name, Alias und Logo auszugeben.
    std::cout << *this << std::endl; 
    std::cout << "Ha, that was EZ!" << std::endl; // Spezifische Nachricht für SeniorDeveloper
    
    // Die statische Methode drink_coffee der Basisklasse aufrufen.
    Developer::drink_coffee();
}