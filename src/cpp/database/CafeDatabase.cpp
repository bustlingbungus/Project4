#include "CafeDatabase.hpp"

#include <iostream>
#include <sstream>
#include <chrono>

#include "../sys/fileaccess.hpp"
#include "../sys/systemcall.hpp"


CafeDatabase cafeDatabase;



/**
 * Pulls the current date and time from user's computer to be stored internally.
 */
CafeDatabase::CafeDatabase()
: SQLDatabase("cafe_db")
{
    // get the date and time and convert it to date struct
    auto t = std::chrono::system_clock::now();
    curr_date = GetDate(std::chrono::system_clock::to_time_t(t));
}


CafeDatabase::~CafeDatabase()
{

}


// The current date on user's computer
Date CafeDatabase::CurrDate()
{
    return curr_date;
}


/**
 * Drops the entire database. Recreates the database tables and procedures. Uses sql files placed in the cwd
 * to do this.
 * 
 * Adds some generic data into database tables.
 */
void CafeDatabase::ResetSQLDatabase()
{
    // drops database and creates tables
    ExecSQL("\"SOURCE cafe_db.sql;\"");
    // create procedures
    ExecSQL("\"SOURCE add_procedures.sql;\"");
    ExecSQL("\"SOURCE remove_procedures.sql;\"");
    ExecSQL("\"SOURCE query_procedures.sql;\"");

    // add initial table entries

    // ingredients
    AddIngredient("Sugar", 10.00);
    AddIngredient("coffee_grounds", 15.00);
    AddIngredient("tea_leaves", 4.00);
    AddIngredient("milk", 16.00);
    AddIngredient("creamer", 8.00);
    AddIngredient("almond_milk", 8.00);

    // menu items
    AddMenuItem("Coffee", 2.50, {
        (Ingredient){"coffee_grounds",  0.25    },
        (Ingredient){"creamer",         0.5     },
        (Ingredient){"sugar",           0.1     }
    });
    
    AddMenuItem("espresso_shot", 1.00, {
        (Ingredient){"coffee_grounds",  0.25    },
    });

    AddMenuItem("sweet_tea", 3.00, {
        (Ingredient){"tea_leaves",      0.1     },
        (Ingredient){"sugar",           0.3     }
    });


    // customers
    AddCustomer("john_smith","jsm2323@yahoo.com","8131231234");
    AddCustomer("ben_steele","bens@usf.edu","8139879876");

    // employees
    AddEmployee("cafesteve", "mycafe43", "steven_tiras", 3);
    AddEmployee("dominic", "domf88", "dominic_fresno", 2);
    AddEmployee("stellaz", "cafejob9", "stella_azam", 1);
}


/**
 * Adds an ingredient to the inventory table. If the ingredient label already
 * exists in the database, the ingredient's amount will be updated.
 * Calls `add_ingredient` sql function.
 * 
 * \param label The name of the ingredient to add
 * \param amount The amount of the item in stock
 */
void CafeDatabase::AddIngredient(std::string label, float amount)
{
    ExecSQL("\"CALL add_ingredient(\'"+label+"\',"+std::to_string(amount)+");\"");
}


/**
 * Adds an item to the menu with a varying amount of ingredients. Formats the ingredients vector as 
 * a JSON string, and calls the `add_menu_item` sql function.
 * 
 * \param title Name of the menu item to add
 * \param price Price of the item
 * \param ingredients Vector of ingredients the menu item should use
 */
void CafeDatabase::AddMenuItem(std::string title, float price, std::vector<Ingredient> ingredients)
{
    // convert ingredients vector to JSON string
    std::string ingredients_json = "[";
    for (int i = 0; i < ingredients.size(); ++i)
    {
        if (i > 0) ingredients_json += ",";
        // format each ingredient as {"label":"ing_label","amount":ing_amount}
        ingredients_json += "{\"label\":\""+ingredients[i].label+"\",\"amount\":"+std::to_string(ingredients[i].amount)+"}";
    }
    ingredients_json += "]";


    // to conform with formatting on the command line, the JSON double quotes need to be 
    // formatted as another character 
    std::string json = ingredients_json;
    size_t pos = 0;
    while ((pos = json.find('"', pos)) != std::string::npos) {
        json.insert(pos, "\\"); // insert '\\' character where the double quotes were
        pos += 2; // increment position past hte fixed quote
    }
    json = "CAST(\'"+json+"\' AS JSON)"; // format to SQL cast


    // format sql call
    ExecSQL("\"CALL add_menu_item(\'"+title+"\',"+std::to_string(price)+","+json+");\"");
}


/**
 * Formats internally stored date to string. Adds a sale using date and arguents passed 
 * here. If the optional `customer_phone` arg is entered, the sale's price is rounded 
 * up to the nearest integer, and added to the customer's points. Call's `add_sale`
 * SQL procedure.
 * 
 * \param item_sold Name of the menu item that was sold
 * \param customer_phone [Optional] Phone number of the customer buying.
 */
void CafeDatabase::AddSale(std::string item_sold, std::string customer_phone)
{
    // format date as string
    std::string date_arg = "\'"+curr_date.to_string(DATEFORMAT_YYYYMMDD)+"\'";
    // add quotes to custoemr phone if not null
    if (customer_phone != "NULL") customer_phone = "\'"+customer_phone+"\'";

    ExecSQL("\"CALL add_sale(\'"+item_sold+"\',"+date_arg+","+customer_phone+");\"");
}


/**
 * Adds a customer to the database. They will initially have 0 points. Calls
 * `add_customer` SQL Proceudre.
 * 
 * \param name Customer's name
 * \param email Customer's email
 * \param phone Customer's phone number (just the numbers, no spaces or anything!)
 */
void CafeDatabase::AddCustomer(std::string name, std::string email, std::string phone)
{
    // normalize phone number
    std::string p = "";
    for (char& ch : phone) if (isdigit(ch)) p += ch;

    ExecSQL("\"CALL add_customer(\'"+name+"\',\'"+email+"\',\'"+p+"\');\"");
}


/**
 * Adds an ingredient to an existing menu item. Calls `add_menuitemingredient` SQL procedure.
 * 
 * \param item_name Name of the menu item the ingredient is being added to
 * \param ingredient Name of the ingredient to add
 * \param amount Amount of the ingredient used by the menu item
 */
void CafeDatabase::AddIngredient(std::string item_name, std::string ingredient, float amount)
{
    ExecSQL("\"CALL add_menuitemingredient(\'"+item_name+"\',\'"+ingredient+"\',"+std::to_string(amount)+");\"");
}


/**
 * Adds an employee to the employees table. Calls `add_employee` SQL procedure.
 * 
 * \param username Employee's username used for login
 * \param password Employee's password used for login
 * \param name Employee's actual name
 * \param access the access level the account should have. 1 for register, 2 for inventory, 3 for owner
 */
void CafeDatabase::AddEmployee(std::string username, std::string password, std::string name, int access)
{
    ExecSQL("\"CALL add_employee(\'"+username+"\',\'"+password+"\',\'"+name+"\',"+std::to_string(access)+");\"");
}


/**
 * Removes a sale form the sales record. Decrements 'items sold' for the menu item on the
 * sale, and, if there was a customer on the sale, removes the appropriate number of
 * points from that customer. Calls the `refund_sale` SQL procedure.
 * 
 * \param sale_id id number of the sale to remove
 */
void CafeDatabase::RefundSale(int sale_id)
{
    ExecSQL("\"CALL remove_sale("+std::to_string(sale_id)+");\"");
}


/**
 * Removes an ingredient from the inventory. Removes the ingredient from all menu items,
 * without removing those menu items. Calls `remove_ingredient` SQL procedure
 * 
 * \param ing_name name of the ingredient to remove
 */
void CafeDatabase::RemoveIngredient(std::string ing_name)
{
    ExecSQL("\"CALL remove_ingredient(\'"+ing_name+"\');\"");
}


/**
 * Removes an item from the menu. Removes any sales made with this menu item 
 * (without deducing customer points). Calls `remove_menu_item` SQL procedure.
 * 
 * \param item_name Name of the menu item to remove
 */
void CafeDatabase::RemoveMenuItem(std::string item_name)
{
    ExecSQL("\"CALL remove_menu_item(\'"+item_name+"\');\"");
}


/**
 * Removes a customer from the database. Calls `remove_customer` SQL procedure.
 * 
 * \param phone_number Phone number of the customer to remove 
 */
void CafeDatabase::RemoveCustomer(std::string phone_number)
{
    // normalize phone number
    std::string p = "";
    for (char& ch : phone_number) if (isdigit(ch)) p += ch;

    ExecSQL("\"CALL remove_customer(\'"+p+"\');\"");
}


/**
 * Removes an employee from the database. Calls `remove_employee` SQL procedure.
 * 
 * \param username Username of the employee to remove
 */
void CafeDatabase::RemoveEmployee(std::string username)
{
    ExecSQL("\"CALL remove_employee(\'"+username+"\');\"");
}


/**
 * Shows ingredients in the cafe inventory. Calls `query_ingredients` SQL procedure.
 */
void CafeDatabase::QueryIngredients()
{
    ExecSQL("\"CALL query_ingredients();\"");
}


/**
 * Shows menu items. Calls `query_menu` SQL procedure.
 */
void CafeDatabase::QueryMenu()
{
    ExecSQL("\"CALL query_menu();\"");
}


/**
 * Shows all customers. Calls `query_customers` SQL procedure.
 */
void CafeDatabase::QueryCustomers()
{
    ExecSQL("\"CALL query_customers();\"");
}


/**
 * Shows all sales. Calls `query_sales` SQL procedure.
 */
void CafeDatabase::QuerySales()
{
    ExecSQL("\"CALL query_sales();\"");
}


/**
 * Shows ingredients used in all menu items. Calls `query_menuitemingredients` SQL procedure.
 */
void CafeDatabase::QueryMenuItemIngredients()
{
    ExecSQL("\"CALL query_menuingredients();\"");
}


/**
 * Shows the sum of all sale prices. Calls `query_sale_total` SQL procedure.
 */
void CafeDatabase::QuerySaleTotal()
{
    ExecSQL("\"CALL query_sale_total();\"");
}


/**
 * Shows all employees. Calls `view_employees` SQL procedure
 */
void CafeDatabase::QueryEmployees()
{
    ExecSQL("\"CALL view_employees();\"");
}


/**
 * Converts `time_t` produced from `to_time_t` function into a `Date` struct.
 * 
 * \param date `time_t` object representing a date and time. 
 */
Date CafeDatabase::GetDate(std::time_t date)
{
    // get time in a format used for input
    std::istringstream iss(std::ctime(&date));
    
    std::string str;
    int month;
    int day;
    int year;

    // get month
    iss >> str >> str;
    if (str == "Jan") month = 1;
    else if (str == "Feb") month = 2;
    else if (str == "Mar") month = 3;
    else if (str == "Apr") month = 4;
    else if (str == "May") month = 5;
    else if (str == "Jun") month = 6;
    else if (str == "Jul") month = 7;
    else if (str == "Aug") month = 8;
    else if (str == "Sep") month = 9;
    else if (str == "Oct") month = 10;
    else if (str == "Nov") month = 11;
    else if (str == "Dec") month = 12;
    else month = -1;

    // get day
    iss >> str;
    day = std::stoi(str);

    // get year
    iss >> str >> str;
    year = std::stoi(str);

    // format as struct
    return (Date){month, day, year};
}