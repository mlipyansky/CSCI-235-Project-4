/**
 * @file Appetizer.cpp
 * @brief This file contains the implementation of the Appetizer class, which is a subclass of the Dish class.
 *
 * The Appetizer class includes methods to manage and present the Appetizer details such as ServingStyle, spiciness levels, and if vegetarian.
 * It provides constructors, accessor and mutator functions, and inherits the Dish class properties.
 *
 * @date 10/22/2024
 * @author Mitchell Lipyansky
 */

#include "Appetizer.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Appetizer::Appetizer()
    : Dish(), serving_style_(PLATED), spiciness_level_(0), vegetarian_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the appetizer.
 * @param ingredients The ingredients used in the appetizer.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the appetizer.
 * @param cuisine_type The cuisine type of the appetizer.
 * @param serving_style The serving style of the appetizer.
 * @param spiciness_level The spiciness level of the appetizer.
 * @param vegetarian Flag indicating if the appetizer is vegetarian.
 */
Appetizer::Appetizer(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const ServingStyle &serving_style, const int &spiciness_level, const bool &vegetarian)
    : Dish(name, ingredients, prep_time, price, cuisine_type), serving_style_(serving_style), spiciness_level_(spiciness_level), vegetarian_(vegetarian) {}

/**
 * Sets the serving style of the appetizer.
 * @param serving_style The new serving style.
 * @post Sets the private member `serving_style_` to the value of the parameter.
 */
void Appetizer::setServingStyle(const ServingStyle &serving_style) {
    serving_style_ = serving_style;
}

/**
 * @return The serving style of the appetizer.
 */
Appetizer::ServingStyle Appetizer::getServingStyle() const {
    return serving_style_;
}

/**
 * Sets the spiciness level of the appetizer.
 * @param spiciness_level An integer representing the spiciness level of the appetizer.
 * @post Sets the private member `spiciness_level_` to the value of the parameter.
 */
void Appetizer::setSpicinessLevel(const int &spiciness_level) {
    spiciness_level_ = spiciness_level;
}

/**
 * @return The spiciness level of the appetizer.
 */
int Appetizer::getSpicinessLevel() const {
    return spiciness_level_;
}

/**
 * Sets the vegetarian flag of the appetizer.
 * @param vegetarian A boolean indicating if the appetizer is vegetarian.
 * @post Sets the private member `vegetarian_` to the value of the parameter.
 */
void Appetizer::setVegetarian(const bool &vegetarian) {
    vegetarian_ = vegetarian;
}

/**
 * @return True if the appetizer is vegetarian, false otherwise.
 */
bool Appetizer::isVegetarian() const {
    return vegetarian_;
}

/**
    * Displays the appetizer's details.
    * @post Outputs the appetizer's details, including name, ingredients,
    preparation time, price, cuisine type, serving style, spiciness level, and
    vegetarian status, to the standard output.
    * The information must be displayed in the following format:
    *
    * Dish Name: [Name of the dish]
    * Ingredients: [Comma-separated list of ingredients]
    * Preparation Time: [Preparation time] minutes
    * Price: $[Price, formatted to two decimal places]
    * Cuisine Type: [Cuisine type]
    * Serving Style: [Serving style: Plated, Family Style, or Buffet]
    * Spiciness Level: [Spiciness level]
    * Vegetarian: [Yes/No]
    */
void Appetizer::display() const {
    std::cout << "Dish Name: " << getName() << std::endl;

    std::cout << "Ingredients: ";
    for (size_t i = 0; i < getIngredients().size(); ++i) {
        std::cout << getIngredients()[i];
        if (i != getIngredients().size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    std::cout << "Preparation Time: " << getPrepTime() << " minutes" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Price: $" << getPrice() << std::endl;
    std::cout << "Cuisine Type: " << getCuisineType() << std::endl;

    // Display Appetizer-specific attributes
    std::cout << "Serving Style: ";
    switch (serving_style_) {
        case PLATED: std::cout << "Plated"; break;
        case FAMILY_STYLE: std::cout << "Family Style"; break;
        case BUFFET: std::cout << "Buffet"; break;
    }
    std::cout << std::endl;

    std::cout << "Spiciness Level: " << spiciness_level_ << std::endl;
    std::cout << "Vegetarian: " << (vegetarian_ ? "Yes" : "No") << std::endl;
}

/**
    * Modifies the appetizer based on dietary accommodations.
    * @param request A DietaryRequest structure specifying the dietary
    accommodations.
    * @post Adjusts the appetizer's attributes to meet the specified
    dietary needs.
    * * *
    - If `request.vegetarian` is true:
    - Sets `vegetarian_` to true.
    - Searches `ingredients_` for any non-vegetarian
    ingredients and replaces the first occurrence with "Beans". If there are
    other non-vegetarian ingredients, the next non-vegetarian ingredient is
    replaced with "Mushrooms".  If there are more, they will be removed
    without substitution.
    *             Non-vegetarian ingredients are: "Meat", "Chicken",
    "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
    * * * *
    - If `request.low_sodium` is true:
    - Reduces `spiciness_level_` by 2 (minimum of 0).
    - If `request.gluten_free` is true:
    - Removes gluten-containing ingredients from
    `ingredients_`.
    *             Gluten-containing ingredients are: "Wheat", "Flour",
    "Bread", "Pasta", "Barley", "Rye", "Oats", "Crust".
*/
void Appetizer::dietaryAccommodations(const DietaryRequest& request) {
    std::vector<std::string> ingredients = getIngredients();

    // Handle vegetarian request
    if (request.vegetarian) {
        vegetarian_ = true;

        std::vector<std::string> non_veg_ingredients = {"Meat", "Chicken", "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon"};
        int replacement_count = 0;
        for (auto& ingredient : ingredients) {
            if (std::find(non_veg_ingredients.begin(), non_veg_ingredients.end(), ingredient) != non_veg_ingredients.end()) {
                if (replacement_count == 0) {
                    ingredient = "Beans";  // First replacement
                } else if (replacement_count == 1) {
                    ingredient = "Mushrooms";  // Second replacement
                } else {
                    ingredient = "";  // Remove additional non-veg ingredients
                }
                replacement_count++;
            }
        }
        ingredients.erase(std::remove(ingredients.begin(), ingredients.end(), ""), ingredients.end());
    }

    // Handle low sodium request
    if (request.low_sodium) {
        spiciness_level_ = std::max(spiciness_level_ - 2, 0);  // Reduce spiciness, minimum 0
    }

    // Handle gluten-free request
    if (request.gluten_free) {
        std::vector<std::string> gluten_ingredients = {"Wheat", "Flour", "Bread", "Pasta", "Barley", "Rye", "Oats", "Crust"};
        for (auto& ingredient : ingredients) {
            if (std::find(gluten_ingredients.begin(), gluten_ingredients.end(), ingredient) != gluten_ingredients.end()) {
                ingredient = "";  // Remove gluten ingredients
            }
        }
        ingredients.erase(std::remove(ingredients.begin(), ingredients.end(), ""), ingredients.end());
    }

    // Set the updated ingredients
    setIngredients(ingredients);
}
