/**
 * @file Dessert.hpp
 * @brief This file contains the declaration of the Dessert class, which is a subclass of the Dish class.
 *
 * The Dessert class includes attributes such as flavor profile, sweetness level, and if it contains nuts.
 * and if gluten free.
 * It provides constructors, accessor and mutator functions, and inherits the Dish class properties.
 *
 * @date 10/22/2024
 * @author Mitchell Lipyansky
 */

#ifndef DESSERT_HPP
#define DESSERT_HPP

#include "Dish.hpp"
#include <string>
#include <vector>

/**
 * @class Dessert
 * @brief Represents a dessert dish, inheriting from Dish.
 */
class Dessert : public Dish {
public:
    /**
     * @enum FlavorProfile
     * @brief Describes the dominant flavor of the dessert.
     */
    enum FlavorProfile { SWEET, BITTER, SOUR, SALTY, UMAMI };

    /**
     * Default constructor.
     * Initializes all private members with default values.
     */
    Dessert();

    /**
     * Parameterized constructor.
     * @param name The name of the dessert.
     * @param ingredients The ingredients used in the dessert.
     * @param prep_time The preparation time in minutes.
     * @param price The price of the dessert.
     * @param cuisine_type The cuisine type of the dessert.
     * @param flavor_profile The flavor profile of the dessert.
     * @param sweetness_level The sweetness level of the dessert.
     * @param contains_nuts Flag indicating if the dessert contains nuts.
     */
    Dessert(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const FlavorProfile &flavor_profile, const int &sweetness_level, const bool &contains_nuts);

    /**
     * Sets the flavor profile of the dessert.
     * @param flavor_profile The new flavor profile.
     * @post Sets the private member `flavor_profile_` to the value of the parameter.
     */
    void setFlavorProfile(const FlavorProfile &flavor_profile);

    /**
     * @return The flavor profile of the dessert.
     */
    FlavorProfile getFlavorProfile() const;

    /**
     * Sets the sweetness level of the dessert.
     * @param sweetness_level An integer representing the sweetness level of the dessert.
     * @post Sets the private member `sweetness_level_` to the value of the parameter.
     */
    void setSweetnessLevel(const int &sweetness_level);

    /**
     * @return The sweetness level of the dessert.
     */
    int getSweetnessLevel() const;

    /**
     * Sets the contains_nuts flag of the dessert.
     * @param contains_nuts A boolean indicating if the dessert contains nuts.
     * @post Sets the private member `contains_nuts_` to the value of the parameter.
     */
    void setContainsNuts(const bool &contains_nuts);

    /**
     * @return True if the dessert contains nuts, false otherwise.
     */
    bool containsNuts() const;

    /**
     * Displays the dessert's details.
    * @post Outputs the dessert's details, including name, ingredients,
    preparation time, price, cuisine type, flavor profile, sweetness level, and
    whether it contains nuts.
    * The information must be displayed in the following format:
    *
    * Dish Name: [Name of the dish]
    * Ingredients: [Comma-separated list of ingredients]
    * Preparation Time: [Preparation time] minutes
    * Price: $[Price, formatted to two decimal places]
    * Cuisine Type: [Cuisine type]
    * Flavor Profile: [Flavor profile: Sweet, Bitter, Sour, Salty, or Umami]
    * Sweetness Level: [Sweetness level]
    * Contains Nuts: [Yes/No]
    */
    void display() const override;

    /**
    * Modifies the dessert based on dietary accommodations.
    * @param request A DietaryRequest structure specifying the dietary
    accommodations.
    * @post Adjusts the dessert's attributes to meet the specified dietary
    needs. *
    * * *
    * * * * *

    - If `request.nut_free` is true:
    - Sets `contains_nuts_` to false.
    - Removes nuts from `ingredients_`.
               Nuts are: "Almonds", "Walnuts", "Pecans", "Hazelnuts",
"Peanuts", "Cashews", "Pistachios".
- If `request.low_sugar` is true:
    - Reduces `sweetness_level_` by 3 (minimum of 0).
- If `request.vegan` is true:
    - Removes dairy and egg ingredients from `ingredients_`.
               Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
"Butter", "Cream", "Yogurt".
    */
    void dietaryAccommodations(const DietaryRequest& request) override;

private:
    FlavorProfile flavor_profile_; ///< The flavor profile of the dessert.
    int sweetness_level_; ///< The sweetness level of the dessert.
    bool contains_nuts_; ///< Flag indicating if the dessert contains nuts.
};

#endif // DESSERT_HPP