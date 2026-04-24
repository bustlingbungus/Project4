#pragma once

#include "SQLDatabase.hpp"

#include <vector>

#include "Ingredient.hpp"

class CafeDatabase : public SQLDatabase
{
    public:

        CafeDatabase();
        ~CafeDatabase();

        void ResetSQLDatabase();

        void AddIngredient(std::string label, float amount);

        void AddMenuItem(std::string title, float price, std::vector<Ingredient> ingredients);
};

extern CafeDatabase cafeDatabase;