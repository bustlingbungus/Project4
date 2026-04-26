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
        void AddSale(std::string item_sold, Date date, std::string customer_phone = "NULL");
        void AddCustomer(std::string name, std::string email, std::string phone);
        void AddIngredient(std::string item_name, std::string ingredient, float amount);

        void RefundSale(int sale_id);
        void RemoveIngredient(std::string ing_name);
        void RemoveMenuItem(std::string item_name);
        void RemoveCustomer(std::string phone_number);

        void QueryIngredients();
        void QueryMenu();
        void QueryCustomers();
        void QuerySales();
        void QueryMenuItemIngredients();
        void QuerySaleTotal();

    protected:

        void CallFunctionWithoutArgs(std::string function);

        bool validDate(Date date);
};

extern CafeDatabase cafeDatabase;