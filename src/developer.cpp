#include "developer.hpp"

// Implementierung des Konstruktors
Developer::Developer(const std::string& name, const std::string& alias)
    : name(name), alias(alias) {}


// Implementierung der statischen Methode drink_coffee
void Developer::drink_coffee() {
    std::cout << "Ahhhh, I needed that coffee!!!" << std::endl;
}

// Implementierung der Methode load_logo_from_file
void Developer::load_logo_from_file(const std::string& filename) {
    // Der LOGO_PATH wird durch die Compiler-Definition in CMakeLists.txt bereitgestellt.
    // Es ist wichtig sicherzustellen, dass LOGO_PATH korrekt definiert ist.
    // Wenn LOGO_PATH nicht definiert ist, wird dies zu einem Compiler-Fehler führen.
    // Der Makro-Name LOGO_PATH wird hier direkt verwendet.
    std::string full_path = std::string(LOGO_PATH) + "/" + filename;
    
    std::ifstream logo_file(full_path);
    if (!logo_file.is_open()) {
        // Fehler, wenn die Datei nicht geöffnet werden kann.
        throw std::runtime_error("Error: Could not open logo file: " + full_path);
    }

    std::string line;
    std::vector<std::string> logo_lines;
    while (std::getline(logo_file, line)) {
        logo_lines.push_back(line);
    }
    logo_file.close();

    // Das Logo als einzelner String mit Zeilenumbrüchen speichern
    this->logo = ""; // Altes Logo löschen
    for (size_t i = 0; i < logo_lines.size(); ++i) {
        this->logo += logo_lines[i];
        if (i < logo_lines.size() - 1) {
            this->logo += "\n"; // Zeilenumbruch hinzufügen, außer bei der letzten Zeile
        }
    }

    if (this->logo.empty() && !logo_lines.empty()) {
        // Fallback, falls das Logo leer ist, aber Zeilen gelesen wurden (z.B. nur Leerzeilen)
        // In diesem Fall könnte man entscheiden, das Logo als "leer" zu betrachten oder
        // die gelesenen Leerzeilen zu behalten. Hier behalten wir es.
    } else if (logo_lines.empty()) {
        // Wenn die Datei leer war, bleibt das Logo ein leerer String.
        // Man könnte hier auch eine Warnung ausgeben oder einen Fehler werfen, je nach Anforderung.
    }
}

// Implementierung der Getter-Methoden
const std::string& Developer::get_name() const {
    return this->name;
}

const std::string& Developer::get_alias() const {
    return this->alias;
}

const std::string& Developer::get_logo() const {
    return this->logo;
}

// Implementierung des überladenen Stream-Operators
std::ostream& operator<<(std::ostream& os, const Developer& dev) {
    // Wenn ein Logo geladen wurde, wird es zuerst ausgegeben.
    if (!dev.get_logo().empty()) {
        os << dev.get_logo() << std::endl;
    }
    os << "Name: " << dev.get_name() << std::endl;
    os << "Alias: " << dev.get_alias(); // Kein std::endl hier, damit es in solve_problem passt
    return os;
}