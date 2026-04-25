#pragma once

#include "SQLDatabase.hpp"

#include <vector>

#include "Ingredient.hpp"
#include "Date.hpp"
#include "Customer.hpp"



class CafeDatabase : public SQLDatabase
{
    public:

        CafeDatabase();
        ~CafeDatabase();

        void ResetSQLDatabase();

        void AddIngredient(std::string label, float amount);

        void AddMenuItem(std::string title, float price, std::vector<Ingredient> ingredients);

        void AddSale(std::string item_sold, Date date, Customer* customer = nullptr);
};

extern CafeDatabase cafeDatabase;