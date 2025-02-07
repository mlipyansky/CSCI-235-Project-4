/**
 * @file Kitchen.cpp
 * @brief This file contains the implementation of the Kitchen class, which is a subclass of ArrayBag.
 *
 * The Kitchen class includes attributes to represent the sum of prep times and the number of elaborate dishes.
 * It provides a constructor and several unique methods for kitchen calculations and related Dish functions.
 *
 * @date 10/22/2024
 * @author Mitchell Lipyansky
 */

#include "Kitchen.hpp"
#include "Appetizer.hpp"
#include "MainCourse.hpp"
#include "Dessert.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

Kitchen::Kitchen() : total_prep_time_(0), count_elaborate_(0) {}

/**
* Parameterized constructor.
* @param filename The name of the input CSV file containing dish
information.
* @pre The CSV file must be properly formatted.
* @post Initializes the kitchen by reading dishes from the CSV file and
storing them as `Dish*`.
*/
Kitchen::Kitchen(const std::string& filename) {
    std::ifstream file(filename);

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string dish_type, name, ingredients_str, prep_time_str, price_str, cuisine_type_str, additional_attributes;

        // Extract all parts of the CSV row
        std::getline(ss, dish_type, ',');
        std::getline(ss, name, ',');
        std::getline(ss, ingredients_str, ',');
        std::getline(ss, prep_time_str, ',');
        std::getline(ss, price_str, ',');
        std::getline(ss, cuisine_type_str, ',');
        std::getline(ss, additional_attributes);

        // Convert numeric fields
        int prep_time = std::stoi(prep_time_str);
        double price = std::stod(price_str);

        // Parse ingredients
        std::vector<std::string> ingredients;
        std::stringstream ingredients_ss(ingredients_str);
        std::string ingredient;
        while (std::getline(ingredients_ss, ingredient, ';')) {
            ingredients.push_back(ingredient);
        }

        // Determine the CuisineType
        Dish::CuisineType cuisine_type;
        if (cuisine_type_str == "ITALIAN") cuisine_type = Dish::CuisineType::ITALIAN;
        else if (cuisine_type_str == "MEXICAN") cuisine_type = Dish::CuisineType::MEXICAN;
        else if (cuisine_type_str == "CHINESE") cuisine_type = Dish::CuisineType::CHINESE;
        else if (cuisine_type_str == "INDIAN") cuisine_type = Dish::CuisineType::INDIAN;
        else if (cuisine_type_str == "AMERICAN") cuisine_type = Dish::CuisineType::AMERICAN;
        else if (cuisine_type_str == "FRENCH") cuisine_type = Dish::CuisineType::FRENCH;
        else cuisine_type = Dish::CuisineType::OTHER;

        // Create the appropriate dish object based on DishType
        if (dish_type == "APPETIZER") {
            std::stringstream additional_ss(additional_attributes);
            std::string serving_style_str, spiciness_str, vegetarian_str;
            std::getline(additional_ss, serving_style_str, ';');
            std::getline(additional_ss, spiciness_str, ';');
            std::getline(additional_ss, vegetarian_str, ';');

            Appetizer::ServingStyle serving_style;
            if (serving_style_str == "PLATED") {
                serving_style = Appetizer::ServingStyle::PLATED;
            } else if (serving_style_str == "FAMILY_STYLE") {
                serving_style = Appetizer::ServingStyle::FAMILY_STYLE;
            } else if (serving_style_str == "BUFFET") {
                serving_style = Appetizer::ServingStyle::BUFFET;
            } else {
                serving_style = Appetizer::ServingStyle::PLATED;
            }
            int spiciness_level = std::stoi(spiciness_str);
            bool vegetarian = (vegetarian_str == "true");

            Dish* appetizer = new Appetizer(name, ingredients, prep_time, price, cuisine_type, serving_style, spiciness_level, vegetarian);
            add(appetizer);
        } else if (dish_type == "MAINCOURSE") {
            std::stringstream additional_ss(additional_attributes);
            std::string cooking_method_str, protein_type, side_dishes_str, gluten_free_str;

            std::getline(additional_ss, cooking_method_str, ';');
            std::getline(additional_ss, protein_type, ';');
            std::getline(additional_ss, side_dishes_str, ';');
            std::getline(additional_ss, gluten_free_str, ';');

            MainCourse::CookingMethod cooking_method;
            if (cooking_method_str == "GRILLED") {
                cooking_method = MainCourse::CookingMethod::GRILLED;
            } else if (cooking_method_str == "BAKED") {
                cooking_method = MainCourse::CookingMethod::BAKED;
            } else if (cooking_method_str == "BOILED") {
                cooking_method = MainCourse::CookingMethod::BOILED;
            } else if (cooking_method_str == "FRIED") {
                cooking_method = MainCourse::CookingMethod::FRIED;
            } else if (cooking_method_str == "STEAMED") {
                cooking_method = MainCourse::CookingMethod::STEAMED;
            } else if (cooking_method_str == "RAW") {
                cooking_method = MainCourse::CookingMethod::RAW;
            } else {
                cooking_method = MainCourse::CookingMethod::GRILLED;
            }
            bool gluten_free = (gluten_free_str == "true");

            std::vector<MainCourse::SideDish> side_dishes;
            std::stringstream side_dishes_ss(side_dishes_str);
            std::string side_dish_str;
            while (std::getline(side_dishes_ss, side_dish_str, '|')) {
                std::string side_name, category_str;
                std::stringstream side_ss(side_dish_str);
                std::getline(side_ss, side_name, ':');
                std::getline(side_ss, category_str, ':');
                MainCourse::Category category;
                if (category_str == "GRAIN") {
                    category = MainCourse::Category::GRAIN;
                } else if (category_str == "PASTA") {
                    category = MainCourse::Category::PASTA;
                } else if (category_str == "LEGUME") {
                    category = MainCourse::Category::LEGUME;
                } else if (category_str == "BREAD") {
                    category = MainCourse::Category::BREAD;
                } else if (category_str == "SALAD") {
                    category = MainCourse::Category::SALAD;
                } else if (category_str == "SOUP") {
                    category = MainCourse::Category::SOUP;
                } else if (category_str == "STARCHES") {
                    category = MainCourse::Category::STARCHES;
                } else if (category_str == "VEGETABLE") {
                    category = MainCourse::Category::VEGETABLE;
                } else {
                    category = MainCourse::Category::GRAIN;
                }
                side_dishes.push_back({side_name, category});
            }

            Dish* main_course = new MainCourse(name, ingredients, prep_time, price, cuisine_type, cooking_method, protein_type, side_dishes, gluten_free);
            add(main_course);
        } else if (dish_type == "DESSERT") {
            std::stringstream additional_ss(additional_attributes);
            std::string flavor_profile_str, sweetness_level_str, contains_nuts_str;

            std::getline(additional_ss, flavor_profile_str, ';');
            std::getline(additional_ss, sweetness_level_str, ';');
            std::getline(additional_ss, contains_nuts_str, ';');

            Dessert::FlavorProfile flavor_profile;
            if (flavor_profile_str == "SWEET") {
                flavor_profile = Dessert::FlavorProfile::SWEET;
            } else if (flavor_profile_str == "BITTER") {
                flavor_profile = Dessert::FlavorProfile::BITTER;
            } else if (flavor_profile_str == "SOUR") {
                flavor_profile = Dessert::FlavorProfile::SOUR;
            } else if (flavor_profile_str == "SALTY") {
                flavor_profile = Dessert::FlavorProfile::SALTY;
            } else if (flavor_profile_str == "UMAMI") {
                flavor_profile = Dessert::FlavorProfile::UMAMI;
            } else {
                flavor_profile = Dessert::FlavorProfile::SWEET;
            }
            int sweetness_level = std::stoi(sweetness_level_str);
            bool contains_nuts = (contains_nuts_str == "true");

            Dish* dessert = new Dessert(name, ingredients, prep_time, price, cuisine_type, flavor_profile, sweetness_level, contains_nuts);
            add(dessert);
        }
    }

    file.close();
}

bool Kitchen::newOrder(Dish* new_dish)
{
    if (add(new_dish))
    {
        total_prep_time_ += new_dish->getPrepTime();
        //std::cout<< "Dish added: "<<new_dish.getName() << std::endl;
        //if the new dish has 5 or more ingredients AND takes an hour or more to prepare, increment count_elaborate_
        if (new_dish->getIngredients().size() >= 5 && new_dish->getPrepTime() >= 60)
        {
            //std::cout << "Elaborate dish added: "<<new_dish.getName() << std::endl;
            count_elaborate_++;
        }
        return true;
    }
    return false;
}
bool Kitchen::serveDish(Dish* dish_to_remove)
{
    if (getCurrentSize() == 0)
    {
        return false;
    }
    if (remove(dish_to_remove))
    {
        total_prep_time_ -= dish_to_remove->getPrepTime();
        if (dish_to_remove->getIngredients().size() >= 5 && dish_to_remove->getPrepTime() >= 60)
        {
            count_elaborate_--;
        }
        return true;
    }
    return false;
}
int Kitchen::getPrepTimeSum() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    return total_prep_time_;
}
int Kitchen::calculateAvgPrepTime() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    double total_prep_time_ = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        total_prep_time_ += items_[i]->getPrepTime();
    }
    total_prep_time_ = total_prep_time_ / getCurrentSize();
    // std::cout<< "Total prep time: "<<total_prep_time_ << std::endl;
    // std::cout<<"rounded: "<<round(total_prep_time_)<<std::endl;
    return round(total_prep_time_);
}
int Kitchen::elaborateDishCount() const
{
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return count_elaborate_;
}
double Kitchen::calculateElaboratePercentage() const
{
    // //Computes the percentage of vegetarian dishes in the kitchen rounded up to 2 decimal places.
    // double elaborate_dish = count_elaborate_;
    // std::cout << elaborate_dish << std::endl;

    // double total_dish = getCurrentSize();
    // std::cout << total_dish << std::endl;

    // double percentage = (elaborate_dish / total_dish) * 10000;
    // std::cout << percentage << std::endl;
    // percentage = round(percentage);
    // std::cout << percentage << std::endl;
    // percentage = percentage / 100;
    // std::cout << percentage << std::endl;

    // return percentage;
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return round(double(count_elaborate_) / double(getCurrentSize()) * 10000)/100;

    //return count_elaborate_ / getCurrentSize();
}
int Kitchen::tallyCuisineTypes(const std::string& cuisine_type) const{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
        }
    }
    return count;
}
int Kitchen::releaseDishesBelowPrepTime(const int& prep_time)
{
    int count = 0;
    int num= getCurrentSize();
    for (int i = 0; i < num; i++)
    {
        if (items_[i]->getPrepTime() < prep_time)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}

int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine_type)
{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}
void Kitchen::kitchenReport() const
{
    std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << std::endl;
    std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << std::endl;
    std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << std::endl;
    std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << std::endl;
    std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << std::endl;
    std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << std::endl;
    std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << std::endl<<std::endl;
    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;
    std::cout << "ELABORATE DISHES: " << calculateElaboratePercentage() << "%" << std::endl;
}

/**
 * Adjusts all dishes in the kitchen based on the specified dietary
accommodation.
 * @param request A DietaryRequest structure specifying the dietary
accommodations.
 * @post Calls the `dietaryAccommodations()` method on each dish in the
kitchen to adjust them accordingly.
*/
void Kitchen::dietaryAdjustment(const Dish::DietaryRequest& request) {
    for (int i = 0; i < getCurrentSize(); ++i) {
            items_[i]->dietaryAccommodations(request);
        }
}


/**
 * Displays all dishes currently in the kitchen.
 * @post Calls the `display()` method of each dish.
*/
void Kitchen::displayMenu() const {
    for (int i = 0; i < getCurrentSize(); ++i) {
        items_[i]->display();
    }
}

/**
 * Destructor.
 * @post Deallocates all dynamically allocated dishes to prevent memory
leaks. */
Kitchen::~Kitchen() {
    for (int i = 0; i < getCurrentSize(); ++i) {
        delete items_[i];  // Deallocate memory
    }
}

