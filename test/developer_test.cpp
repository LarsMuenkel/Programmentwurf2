#include "gtest/gtest.h"
#include "developer.hpp"
#include "juniordeveloper.hpp"
#include "seniordeveloper.hpp"
#include <fstream> // Für das Erstellen von Test-Logo-Dateien
#include <string>
#include <vector>

// Hilfsfunktion zum Erstellen einer temporären Logodatei für Tests
// Gibt den vollständigen Pfad zur erstellten Datei zurück
std::string create_test_logo_file(const std::string& filename, const std::string& content) {
    // LOGO_PATH wird durch die CMake-Definition bereitgestellt
    std::string full_path = std::string(LOGO_PATH) + "/" + filename;
    std::ofstream outfile(full_path);
    if (outfile.is_open()) {
        outfile << content;
        outfile.close();
    } else {
        // Im Fehlerfall einen leeren String zurückgeben oder eine Ausnahme werfen,
        // aber für Tests ist es oft besser, wenn der Test fehlschlägt, weil die Datei nicht erstellt wurde.
        throw std::runtime_error("Failed to create test logo file: " + full_path);
    }
    return full_path; // Obwohl wir im Test nur den Dateinamen verwenden
}

// Hilfsfunktion zum Löschen einer temporären Logodatei
void remove_test_logo_file(const std::string& filename) {
    std::string full_path = std::string(LOGO_PATH) + "/" + filename;
    std::remove(full_path.c_str());
}

// Testfixture für Developer-Tests
class DeveloperTest : public ::testing::Test {
protected:
    // Hier können SetUp- und TearDown-Methoden definiert werden, falls benötigt.
    // void SetUp() override {}
    // void TearDown() override {}

    // Test-Logo-Dateinamen
    const std::string correct_logo_filename = "test_logo_correct.txt";
    const std::string empty_logo_filename = "test_logo_empty.txt"; // Eine leere Datei
    const std::string invalid_logo_filename = "non_existent_logo.txt"; // Eine nicht existierende Datei

    const std::string logo_content_correct = "<test_logo>\nline2\nline3";
    const std::string logo_content_empty = "";


    void SetUp() override {
        // Erstelle die Test-Logo-Dateien vor jedem Test der load_logo_from_file Methode
        // (oder zumindest vor den Tests, die sie benötigen)
        try {
            create_test_logo_file(correct_logo_filename, logo_content_correct);
            create_test_logo_file(empty_logo_filename, logo_content_empty);
        } catch (const std::runtime_error& e) {
            // Wenn das Erstellen der Datei fehlschlägt, den Test fehlschlagen lassen.
            FAIL() << "Setup failed to create test logo files: " << e.what();
        }
    }

    void TearDown() override {
        // Entferne die Test-Logo-Dateien nach jedem Test
        remove_test_logo_file(correct_logo_filename);
        remove_test_logo_file(empty_logo_filename);
        // non_existent_logo.txt muss nicht entfernt werden, da es nicht erstellt wird.
    }
};

// Testet den Konstruktor und die Getter für JuniorDeveloper
TEST_F(DeveloperTest, JuniorDeveloperConstructorAndGetters) {
    const std::string name = "Johnny Junior";
    const std::string alias = "JJ";
    JuniorDeveloper jd(name, alias);

    EXPECT_EQ(jd.get_name(), name);
    EXPECT_EQ(jd.get_alias(), alias);
    EXPECT_EQ(jd.get_logo(), ""); // Logo sollte initial leer sein
}

// Testet den Konstruktor und die Getter für SeniorDeveloper
TEST_F(DeveloperTest, SeniorDeveloperConstructorAndGetters) {
    const std::string name = "Sarah Senior";
    const std::string alias = "SS";
    SeniorDeveloper sd(name, alias);

    EXPECT_EQ(sd.get_name(), name);
    EXPECT_EQ(sd.get_alias(), alias);
    EXPECT_EQ(sd.get_logo(), ""); // Logo sollte initial leer sein
}

// Testet load_logo_from_file: Logo ist leer vor dem Aufruf
TEST_F(DeveloperTest, LoadLogoFromFile_LogoEmptyBeforeLoad) {
    JuniorDeveloper dev("Test Dev", "TD");
    EXPECT_EQ(dev.get_logo(), ""); // Sicherstellen, dass das Logo vor dem Laden leer ist
}

// Testet load_logo_from_file: Korrektes Logo wird nach dem Laden geladen
TEST_F(DeveloperTest, LoadLogoFromFile_CorrectLogoLoaded) {
    JuniorDeveloper dev("Test Dev", "TD");
    // Die Datei test_logo_correct.txt wird im SetUp erstellt
    dev.load_logo_from_file(correct_logo_filename);
    EXPECT_EQ(dev.get_logo(), logo_content_correct);
}

// Testet load_logo_from_file: Korrektes Logo wird nach dem Laden geladen (mit SeniorDeveloper)
TEST_F(DeveloperTest, LoadLogoFromFile_CorrectLogoLoadedSenior) {
    SeniorDeveloper dev("Test Senior Dev", "TSD");
    dev.load_logo_from_file(correct_logo_filename);
    EXPECT_EQ(dev.get_logo(), logo_content_correct);
}


// Testet load_logo_from_file: Leere Datei führt zu leerem Logo-String
TEST_F(DeveloperTest, LoadLogoFromFile_EmptyFileLeadsToEmptyLogo) {
    JuniorDeveloper dev("Test Dev", "TD");
    // Die Datei test_logo_empty.txt wird im SetUp erstellt
    dev.load_logo_from_file(empty_logo_filename);
    EXPECT_EQ(dev.get_logo(), logo_content_empty);
}

// Testet load_logo_from_file: Exception wird bei ungültigem Dateinamen geworfen
TEST_F(DeveloperTest, LoadLogoFromFile_ThrowsExceptionOnInvalidFilename) {
    JuniorDeveloper dev("Test Dev", "TD");
    // non_existent_logo.txt existiert nicht
    EXPECT_THROW(dev.load_logo_from_file(invalid_logo_filename), std::runtime_error);
}

// Test für die solve_problem Methode (einfacher Test, um zu prüfen, ob sie ohne Fehler läuft)
// Eine genauere Prüfung der Ausgabe wäre komplexer und könnte Output-Capturing erfordern.
TEST_F(DeveloperTest, JuniorDeveloperSolveProblem) {
    JuniorDeveloper jd("Junior Test", "JT");
    // Um die Ausgabe zu testen, müsste man std::cout umleiten.
    // Hier testen wir nur, dass die Methode ohne Exceptions durchläuft.
    EXPECT_NO_THROW(jd.solve_problem());
}

TEST_F(DeveloperTest, SeniorDeveloperSolveProblem) {
    SeniorDeveloper sd("Senior Test", "ST");
    EXPECT_NO_THROW(sd.solve_problem());
}

// Hauptfunktion für die Tests wird von gtest_main bereitgestellt,
// daher ist keine main() Funktion in dieser Datei erforderlich,
// wenn wir gegen gtest_main linken.
