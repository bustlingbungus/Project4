#pragma once

#include "SQLDatabase.hpp"

#include <vector>
#include <ctime>

#include "Ingredient.hpp"
#include "Date.hpp"



/**
 * Main interface for interacting with the SQL cafe database.
 * Contains the current date on user's computer.
 */
class CafeDatabase : public SQLDatabase
{
    public:

        CafeDatabase();
        ~CafeDatabase();

        Date CurrDate();
        
        void ResetSQLDatabase();

        void AddIngredient(std::string label, float amount);
        void AddMenuItem(std::string title, float price, std::vector<Ingredient> ingredients);
        void AddSale(std::string item_sold, std::string customer_phone = "NULL");
        void AddCustomer(std::string name, std::string email, std::string phone);
        void AddIngredient(std::string item_name, std::string ingredient, float amount);
        void AddEmployee(std::string username, std::string password, std::string name, int access_type);

        void RefundSale(int sale_id);
        void RemoveIngredient(std::string ing_name);
        void RemoveMenuItem(std::string item_name);
        void RemoveCustomer(std::string phone_number);
        void RemoveEmployee(std::string username);

        void QueryIngredients();
        void QueryMenu();
        void QueryCustomers();
        void QuerySales();
        void QueryMenuItemIngredients();
        void QuerySaleTotal();
        void QueryEmployees();

    protected:

        Date GetDate(std::time_t date);

        /** The current date on the user's computer */
        Date curr_date;
};

/** Main interface for interacting with the SQL cafe database */
extern CafeDatabase cafeDatabase;