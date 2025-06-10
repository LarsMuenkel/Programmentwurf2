# CMake Mindestversion festlegen
cmake_minimum_required(VERSION 3.20)

# Projektname und Sprache definieren
project(DeveloperExercise LANGUAGES CXX)

# C++ Standard auf C++14 setzen
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Keine GNU-Erweiterungen verwenden

# Compiler-Flags setzen (gemäß Vorgabe)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Pfad für Header-Dateien der Bibliothek hinzufügen
include_directories(include)

# Definition für den Pfad zu den Logo-Dateien
# Dieser Pfad wird relativ zum Quellverzeichnis des Projekts sein
# Angenommen, die Logos befinden sich in einem Ordner "logos" im Projekt-Stammverzeichnis
set(LOGO_FILES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/logos")
# Überprüfen, ob der LOGO_PATH als String übergeben wird, ggf. Anführungszeichen hinzufügen
# Dies ist wichtig, damit der Pfad im C++ Code korrekt als String interpretiert wird.
add_definitions("-DLOGO_PATH=\"${LOGO_FILES_PATH}\"")


# Bibliothek "developer_lib" erstellen
# Sie besteht aus den Klassen Developer, JuniorDeveloper und SeniorDeveloper
add_library(developer_lib
    src/developer.cpp
    src/juniordeveloper.cpp
    src/seniordeveloper.cpp
)

# Die Header-Dateien der Bibliothek als öffentlich deklarieren
target_include_directories(developer_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Hauptanwendung "main_app" erstellen
add_executable(main_app src/main.cpp)

# Die Hauptanwendung gegen die "developer_lib" linken
target_link_libraries(main_app PRIVATE developer_lib)

# --- GoogleTest Integration ---
# Testingsystem aktivieren
enable_testing()

# GoogleTest über FetchContent herunterladen und konfigurieren
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main # oder eine spezifische Version wie release-1.14.0
)
# Damit gtest und gtest_main verfügbar sind, aber nicht standardmäßig gebaut werden,
# wenn sie nicht von einem Test benötigt werden.
FetchContent_MakeAvailable(googletest)

# Test-Executable erstellen
# Annahme: Die Testdateien befinden sich im Verzeichnis "test"
add_executable(run_tests
    test/developer_test.cpp
    # Fügen Sie hier weitere Testdateien hinzu, falls vorhanden
)

# Die Test-Executable gegen developer_lib und googletest linken
target_link_libraries(run_tests PRIVATE developer_lib gtest_main)

# Die Tests zum CTest-Framework hinzufügen
include(GoogleTest)
gtest_discover_tests(run_tests)

# Ausgabe zur Information
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler Flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "Logo path definition: -DLOGO_PATH=\"${LOGO_FILES_PATH}\"")
message(STATUS "GoogleTest integration enabled.")
