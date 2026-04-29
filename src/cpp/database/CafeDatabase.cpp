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
    auto t = std::chrono::system_clock::now();
    curr_date = GetDate(std::chrono::system_clock::to_time_t(t));
}


CafeDatabase::~CafeDatabase()
{

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
 * Adds an ingredient to the inventory table. Calls `add_ingredient` sql function.
 */
void CafeDatabase::AddIngredient(std::string label, float amount)
{
    ExecSQL("\"CALL add_ingredient(\'"+label+"\',"+std::to_string(amount)+");\"");
}


/**
 * Adds an item to the menu with a varying amount of ingredients. Formats the ingredients vector as 
 * a JSON string, and calls the `add_menu_item` sql function.
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
 * up to the nearest integer, and added to the customer's points. Call's  
 */
void CafeDatabase::AddSale(std::string item_sold, std::string customer_phone)
{
    // format date as string
    std::string date_arg = "\'"+std::to_string(curr_date.year)+"-"+std::to_string(curr_date.month)+"-"+std::to_string(curr_date.day)+"\'";

    if (customer_phone != "NULL") customer_phone = "\'"+customer_phone+"\'";

    std::string func_str = "\"CALL add_sale(\'"+item_sold+"\',"+date_arg+","+customer_phone+");\"";

    ExecSQL(func_str);
}


void CafeDatabase::AddIngredient(std::string item_name, std::string ingredient, float amount)
{
    ExecSQL("\"CALL add_menuitemingredient(\'"+item_name+"\',\'"+ingredient+"\',"+std::to_string(amount)+");\"");
}


void CafeDatabase::AddEmployee(std::string username, std::string password, std::string name, int access)
{
    ExecSQL("\"CALL add_employee(\'"+username+"\',\'"+password+"\',\'"+name+"\',"+std::to_string(access)+");\"");
}


void CafeDatabase::RefundSale(int sale_id)
{
    ExecSQL("\"CALL remove_sale("+std::to_string(sale_id)+");\"");
}


void CafeDatabase::RemoveIngredient(std::string ing_name)
{
    ExecSQL("\"CALL remove_ingredient(\'"+ing_name+"\');\"");
}

void CafeDatabase::RemoveMenuItem(std::string item_name)
{
    ExecSQL("\"CALL remove_menu_item(\'"+item_name+"\');\"");
}

void CafeDatabase::RemoveCustomer(std::string phone_number)
{
    ExecSQL("\"CALL remove_customer(\'"+phone_number+"\');\"");
}


void CafeDatabase::RemoveEmployee(std::string username)
{
    ExecSQL("\"CALL remove_employee(\'"+username+"\');\"");
}


void CafeDatabase::AddCustomer(std::string name, std::string email, std::string phone)
{
    // normalize phone number
    std::string p = "";
    for (char& ch : phone) if (isdigit(ch)) p += ch;

    ExecSQL("\"CALL add_customer(\'"+name+"\',\'"+email+"\',\'"+p+"\');\"");
}


void CafeDatabase::QueryIngredients()
{
    CallFunctionWithoutArgs("query_ingredients");
}


void CafeDatabase::QueryMenu()
{
    CallFunctionWithoutArgs("query_menu");
}


void CafeDatabase::QueryCustomers()
{
    CallFunctionWithoutArgs("query_customers");
}


void CafeDatabase::QuerySales()
{
    CallFunctionWithoutArgs("query_sales");
}


void CafeDatabase::QueryMenuItemIngredients()
{
    CallFunctionWithoutArgs("query_menuingredients");
}


void CafeDatabase::QuerySaleTotal()
{
    CallFunctionWithoutArgs("query_sale_total");
}


void CafeDatabase::QueryEmployees()
{
    CallFunctionWithoutArgs("view_employees");
}


void CafeDatabase::CallFunctionWithoutArgs(std::string function)
{
    ExecSQL("\"CALL "+function+"();\"");
}


Date CafeDatabase::GetDate(std::time_t date)
{
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

    return (Date){month, day, year};
}