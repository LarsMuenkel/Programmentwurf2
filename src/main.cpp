#include <iostream>
#include <vector>
#include <memory> // Für std::shared_ptr und std::make_shared
#include "developer.hpp"
#include "juniordeveloper.hpp"
#include "seniordeveloper.hpp"

int main() {
    // 1. Ein Vector von shared_ptr auf Developer-Objekte anlegen.
    std::vector<std::shared_ptr<Developer>> developers;

    // 2. Mindestens je ein Objekt der Klassen SeniorDeveloper und JuniorDeveloper instanziieren
    //    unter Verwendung dynamischer Speicherallokation (std::make_shared).
    auto senior_dev = std::make_shared<SeniorDeveloper>("Diana Prince", "Wonder Woman");
    auto junior_dev = std::make_shared<JuniorDeveloper>("Peter Parker", "Spiderman");

    // Optional: Logos laden. Die Dateinamen müssen im "logos" Ordner existieren.
    // Der Pfad wird durch die Compiler-Definition LOGO_PATH in CMakeLists.txt bestimmt.
    try {
        senior_dev->load_logo_from_file("wonder_woman_logo.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error loading logo for Senior Developer: " << e.what() << std::endl;
    }

    try {
        junior_dev->load_logo_from_file("spiderman_logo.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error loading logo for Junior Developer: " << e.what() << std::endl;
    }
    
    // Testfall für ungültigen Dateinamen (optional, zum Demonstrieren der Exception)
    /*
    try {
        auto temp_dev = std::make_shared<JuniorDeveloper>("Test User", "Test Alias");
        temp_dev->load_logo_from_file("non_existent_logo.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught expected error: " << e.what() << std::endl;
    }
    */


    // 3. Alle angelegten Developer-Objekte dem Vector hinzufügen.
    developers.push_back(senior_dev);
    developers.push_back(junior_dev);

    // 4. Unter Verwendung einer Schleife und eines Iterators über den Vector gehen,
    //    um die Developer des Vectors ein "Problem lösen" zu lassen.
    for (auto it = developers.begin(); it != developers.end(); ++it) {
        (*it)->solve_problem(); // Polymorpher Aufruf von solve_problem()
        if (std::next(it) != developers.end()) { // Fügt eine Leerzeile zwischen den Ausgaben hinzu, außer nach dem letzten Element
            std::cout << std::endl;
        }
    }

    return 0;
}