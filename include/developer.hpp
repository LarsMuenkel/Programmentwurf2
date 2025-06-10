#ifndef DEVELOPER_HPP
#define DEVELOPER_HPP

#include <string>
#include <iostream>
#include <fstream> // Für Dateizugriff in load_logo_from_file
#include <stdexcept> // Für std::runtime_error
#include <vector>    // Wird für das Einlesen des Logos benötigt

// Die Klasse Developer dient als Basisklasse für JuniorDeveloper und SeniorDeveloper.
class Developer {
protected:
    std::string name;         // Name des Entwicklers
    std::string alias;        // Alias-Name des Entwicklers
    std::string logo;         // Logo des Entwicklers (kann mehrzeilig sein)

public:
    // Konstruktor zur Initialisierung von Name und Alias.
    // Das Logo ist nicht Teil des Konstruktors.
    Developer(const std::string& name, const std::string& alias);

    // Virtueller Destruktor, wichtig für Basisklassen mit virtuellen Methoden.
    virtual ~Developer() = default;

    // Statische Methode, die ausgibt, dass Kaffee getrunken wurde.
    static void drink_coffee();

    // Nicht-virtuelle Methode zum Laden eines Logos aus einer Datei.
    // Wirft eine std::runtime_error, wenn der Dateiname ungültig ist oder die Datei nicht geöffnet werden kann.
    void load_logo_from_file(const std::string& filename);

    // Getter-Methoden für alle Membervariablen.
    const std::string& get_name() const;
    const std::string& get_alias() const;
    const std::string& get_logo() const;

    // Rein virtuelle Methode "solve_problem", die in abgeleiteten Klassen implementiert werden muss.
    virtual void solve_problem() = 0;

    // Freund-Funktion zur Überladung des Stream-Operators (<<) für std::cout.
    friend std::ostream& operator<<(std::ostream& os, const Developer& dev);
};

#endif // DEVELOPER_HPP
