#include "CafeDatabase.hpp"

#include <iostream>

#include "../sys/fileaccess.hpp"
#include "../sys/systemcall.hpp"



CafeDatabase cafeDatabase;



CafeDatabase::CafeDatabase()
: SQLDatabase("cafe_db")
{

}


CafeDatabase::~CafeDatabase()
{

}


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
}


void CafeDatabase::AddIngredient(std::string label, float amount)
{
    ExecSQL("\"CALL add_ingredient(\'"+label+"\',"+std::to_string(amount)+");\"");
}


void CafeDatabase::AddMenuItem(std::string title, float price, std::vector<Ingredient> ingredients)
{
    std::string ingredients_json = "[";
    for (int i = 0; i < ingredients.size(); ++i)
    {
        if (i > 0) ingredients_json += ",";

        ingredients_json += "{\"label\":\""+ingredients[i].label+"\",\"amount\":"+std::to_string(ingredients[i].amount)+"}";
    }
    ingredients_json += "]";


    std::string sql = "CALL add_menu_item(";
    sql += "'" + title + "', ";
    sql += std::to_string(price) + ", ";
    // escape double quotes for shell double-quoted argument
    std::string escaped_json = ingredients_json;
    size_t pos = 0;
    while ((pos = escaped_json.find('"', pos)) != std::string::npos) {
        escaped_json.insert(pos, "\\");
        pos += 2;
    }
    sql += "CAST('" + escaped_json + "' AS JSON));";

    std::string sqlValue = "\"" + sql + "\"";
    ExecSQL(sqlValue);
}


void CafeDatabase::AddSale(std::string item_sold, Date date, std::string customer_phone)
{
    // format date as string
    std::string yr = std::to_string(date.year);
    while (yr.size() < 4) yr = "0" + yr;
    std::string mo = std::to_string(date.month);
    while (mo.size() < 2) mo = "0" + mo;
    std::string dy = std::to_string(date.day);
    while (dy.size() < 2) dy = "0" + dy;
    std::string date_arg = "\'"+yr+"-"+mo+"-"+dy+"\'";

    if (customer_phone != "NULL") customer_phone = "\'"+customer_phone+"\'";

    std::string func_str = "\"CALL add_sale(\'"+item_sold+"\',"+date_arg+","+customer_phone+");\"";

    ExecSQL(func_str);
}


void CafeDatabase::AddIngredient(std::string item_name, std::string ingredient, float amount)
{
    ExecSQL("\"CALL add_menuitemingredient(\'"+item_name+"\',\'"+ingredient+"\',"+std::to_string(amount)+");\"");
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


void CafeDatabase::CallFunctionWithoutArgs(std::string function)
{
    ExecSQL("\"CALL "+function+"();\"");
}


bool CafeDatabase::validDate(Date date)
{
    if (date.month > 12 || date.month <= 0) {
        std::cerr << "Invalid month\n";
        return false;
    } 
    unsigned int max_day;  
    // this system does not account for leap years or anything like that.... I really dgaf
    switch (date.month) {
        case 1: max_day = 31; // jan
        case 2: max_day = 28; // feb
        case 3: max_day = 31; // mar
        case 4: max_day = 30; // apr
        case 5: max_day = 31; // may
        case 6: max_day = 30; // jun
        case 7: max_day = 31; // jul
        case 8: max_day = 31; // aug
        case 9: max_day = 30; // sep
        case 10: max_day = 31; // oct
        case 11: max_day = 30; // nov
        case 12: max_day = 31; // dec
    }
    if (date.day > max_day || date.day <= 0) {
        std::cerr << "Invalid day\n";
        return false;
    }

    return true;
}