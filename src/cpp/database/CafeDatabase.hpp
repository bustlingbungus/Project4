#pragma once

#include "SQLDatabase.hpp"

class CafeDatabase : public SQLDatabase
{
    public:

        CafeDatabase();
        ~CafeDatabase();

        void ResetSQLDatabase();

        void AddIngredient(std::string label, float amount);
};

extern CafeDatabase cafeDatabase;