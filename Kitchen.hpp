/**
 * @file Kitchen.hpp
 * @brief This file contains the declaration of the Kitchen class, which is a subclass of ArrayBag.
 *
 * The Kitchen class includes attributes to represent the sum of prep times and the number of elaborate dishes.
 * It provides a constructor and several unique methods for kitchen calculations and related Dish functions.
 *
 * @date 10/22/2024
 * @author Mitchell Lipyansky
 */

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "ArrayBag.hpp"
#include "Dish.hpp"
// for round
#include <cmath>
#include <string>
#include <vector>

class Kitchen : public ArrayBag<Dish*> {
    public:
        Kitchen();
        /**
        * Parameterized constructor.
        * @param filename The name of the input CSV file containing dish
        information.
        * @pre The CSV file must be properly formatted.
        * @post Initializes the kitchen by reading dishes from the CSV file and
        storing them as `Dish*`.
        */
        Kitchen(const std::string& filename);
        bool newOrder(Dish* new_dish);
        bool serveDish(Dish* dish_to_remove);
        int getPrepTimeSum() const;
        int calculateAvgPrepTime() const;
        int elaborateDishCount() const;
        double calculateElaboratePercentage() const;
        int tallyCuisineTypes(const std::string& cuisine_type) const;
        int releaseDishesBelowPrepTime(const int& prep_time);
        int releaseDishesOfCuisineType(const std::string& cuisine_type);
        void kitchenReport() const;
        /**
        * Adjusts all dishes in the kitchen based on the specified dietary
        accommodation.
        * @param request A DietaryRequest structure specifying the dietary
        accommodations.
        * @post Calls the `dietaryAccommodations()` method on each dish in the
        kitchen to adjust them accordingly.
        */
        void dietaryAdjustment(const Dish::DietaryRequest& request);
        /**
        * Displays all dishes currently in the kitchen.
        * @post Calls the `display()` method of each dish.
        */
        void displayMenu() const;
        /**
        * Destructor.
        * @post Deallocates all dynamically allocated dishes to prevent memory
        leaks. */
        ~Kitchen();

    private:
        int total_prep_time_;
        int count_elaborate_;
    
};

#endif // KITCHEN_HPP