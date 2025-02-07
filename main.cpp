#include "Kitchen.hpp"
#include <iostream>

int main() {
    // Provide the filename to the Kitchen constructor that reads the CSV
    std::string filename = "Dishes.csv";  // Ensure the file exists in the same directory

    // Create a Kitchen object using the parameterized constructor to load dishes from the CSV
    Kitchen kitchen(filename);

    // Test for dietaryAdjustment
    Dish::DietaryRequest dietary_request = {true, false, true, false, false, false};  // Vegetarian, gluten-free
    kitchen.dietaryAdjustment(dietary_request);

    // Test for displayMenu
    std::cout << "Displaying full menu: " << std::endl;
    kitchen.displayMenu();

    return 0;
}
