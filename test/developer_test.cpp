#include "gtest/gtest.h"
#include "developer.hpp"
#include "juniordeveloper.hpp"
#include "seniordeveloper.hpp"
#include <fstream> // For creating test logo files
#include <string>
#include <vector>

// Helper function to create a temporary logo file for tests
// Returns the full path to the created file
std::string create_test_logo_file(const std::string& filename, const std::string& content) {
    // LOGO_PATH is provided through the CMake definition
    std::string full_path = std::string(LOGO_PATH) + "/" + filename;
    std::ofstream outfile(full_path);
    if (outfile.is_open()) {
        outfile << content;
        outfile.close();
    } else {
        // In case of an error, return an empty string or throw an exception,
        // but for tests, it is often better if the test fails because the file was not created.
        throw std::runtime_error("Failed to create test logo file: " + full_path);
    }
    return full_path; // Although we only use the filename in the test
}

// Helper function to delete a temporary logo file
void remove_test_logo_file(const std::string& filename) {
    std::string full_path = std::string(LOGO_PATH) + "/" + filename;
    std::remove(full_path.c_str());
}

// Test fixture for Developer tests
class DeveloperTest : public ::testing::Test {
protected:
    // SetUp and TearDown methods can be defined here if needed.
    // void SetUp() override {}
    // void TearDown() override {}

    // Test logo filenames
    const std::string correct_logo_filename = "test_logo_correct.txt";
    const std::string empty_logo_filename = "test_logo_empty.txt"; // An empty file
    const std::string invalid_logo_filename = "non_existent_logo.txt"; // A non-existent file

    const std::string logo_content_correct = "<test_logo>\nline2\nline3";
    const std::string logo_content_empty = "";


    void SetUp() override {
        // Create the test logo files before each test of the load_logo_from_file method
        // (or at least before the tests that need them)
        try {
            create_test_logo_file(correct_logo_filename, logo_content_correct);
            create_test_logo_file(empty_logo_filename, logo_content_empty);
        } catch (const std::runtime_error& e) {
            // If creating the file fails, let the test fail.
            FAIL() << "Setup failed to create test logo files: " << e.what();
        }
    }

    void TearDown() override {
        // Remove the test logo files after each test
        remove_test_logo_file(correct_logo_filename);
        remove_test_logo_file(empty_logo_filename);
        // non_existent_logo.txt does not need to be removed as it is not created.
    }
};

// Tests the constructor and getters for JuniorDeveloper
TEST_F(DeveloperTest, JuniorDeveloperConstructorAndGetters) {
    const std::string name = "Johnny Junior";
    const std::string alias = "JJ";
    JuniorDeveloper jd(name, alias);

    EXPECT_EQ(jd.get_name(), name);
    EXPECT_EQ(jd.get_alias(), alias);
    EXPECT_EQ(jd.get_logo(), ""); // Logo should be empty initially
}

// Tests the constructor and getters for SeniorDeveloper
TEST_F(DeveloperTest, SeniorDeveloperConstructorAndGetters) {
    const std::string name = "Sarah Senior";
    const std::string alias = "SS";
    SeniorDeveloper sd(name, alias);

    EXPECT_EQ(sd.get_name(), name);
    EXPECT_EQ(sd.get_alias(), alias);
    EXPECT_EQ(sd.get_logo(), ""); // Logo should be empty initially
}

// Tests load_logo_from_file: Logo is empty before the call
TEST_F(DeveloperTest, LoadLogoFromFile_LogoEmptyBeforeLoad) {
    JuniorDeveloper dev("Test Dev", "TD");
    EXPECT_EQ(dev.get_logo(), ""); // Ensure the logo is empty before loading
}

// Tests load_logo_from_file: Correct logo is loaded after loading
TEST_F(DeveloperTest, LoadLogoFromFile_CorrectLogoLoaded) {
    JuniorDeveloper dev("Test Dev", "TD");
    // The file test_logo_correct.txt is created in SetUp
    dev.load_logo_from_file(correct_logo_filename);
    EXPECT_EQ(dev.get_logo(), logo_content_correct);
}

// Tests load_logo_from_file: Correct logo is loaded after loading (with SeniorDeveloper)
TEST_F(DeveloperTest, LoadLogoFromFile_CorrectLogoLoadedSenior) {
    SeniorDeveloper dev("Test Senior Dev", "TSD");
    dev.load_logo_from_file(correct_logo_filename);
    EXPECT_EQ(dev.get_logo(), logo_content_correct);
}


// Tests load_logo_from_file: Empty file leads to empty logo string
TEST_F(DeveloperTest, LoadLogoFromFile_EmptyFileLeadsToEmptyLogo) {
    JuniorDeveloper dev("Test Dev", "TD");
    // The file test_logo_empty.txt is created in SetUp
    dev.load_logo_from_file(empty_logo_filename);
    EXPECT_EQ(dev.get_logo(), logo_content_empty);
}

// Tests load_logo_from_file: Exception is thrown on invalid filename
TEST_F(DeveloperTest, LoadLogoFromFile_ThrowsExceptionOnInvalidFilename) {
    JuniorDeveloper dev("Test Dev", "TD");
    // non_existent_logo.txt does not exist
    EXPECT_THROW(dev.load_logo_from_file(invalid_logo_filename), std::runtime_error);
}

// Test for the solve_problem method (simple test to check if it runs without errors)
// A more detailed check of the output would be more complex and might require output capturing.
TEST_F(DeveloperTest, JuniorDeveloperSolveProblem) {
    JuniorDeveloper jd("Junior Test", "JT");
    // To test the output, one would need to redirect std::cout.
    // Here we only test that the method runs without exceptions.
    EXPECT_NO_THROW(jd.solve_problem());
}

TEST_F(DeveloperTest, SeniorDeveloperSolveProblem) {
    SeniorDeveloper sd("Senior Test", "ST");
    EXPECT_NO_THROW(sd.solve_problem());
}

// Main function for the tests is provided by gtest_main,
// so no main() function is required in this file,
// if we link against gtest_main.
