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

        void RefundSale(int sale_id);

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