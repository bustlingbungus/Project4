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
    RunSQLFile("cafe_db.sql");
    // create procedures
    RunSQLFile("add_procedures.sql");
    RunSQLFile("query_procedures.sql");

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
    std::string cmd = "mysql";
    std::vector<std::string> cmdarr = {
        cmd,
        "-u",
        sql_username,
        "-p",
        "cafe_db",
        "-e",
        "\"CALL add_ingredient(\'"+label+"\',"+std::to_string(amount)+");\"",
        "--password="+sql_password
    };

    RunCommands(cmd ,cmdarr);
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

    std::vector<std::string> cmdarr = {
        "mysql",
        "-u", 
        sql_username,
        "-p",
        "cafe_db",
        "-e",
        sqlValue,
        "--password=" + sql_password
    };

    RunCommands("mysql", cmdarr);
}


void CafeDatabase::AddSale(std::string item_sold, Date date, std::string customer_phone)
{
    std::string date_arg = "\'"+std::to_string(date.year)+"-"+std::to_string(date.month)+"-"+std::to_string(date.day)+"\'";
    if (customer_phone != "NULL") customer_phone = "\'"+customer_phone+"\'";

    std::string func_str = "\"CALL add_sale(\'"+item_sold+"\',"+date_arg+","+customer_phone+");\"";


    std::string cmd = "mysql";
    std::vector<std::string> cmdarr = {
        cmd,
        "-u",
        sql_username,
        "-p",
        "cafe_db",
        "-e",
        func_str,
        "--password="+sql_password
    };

    RunCommands(cmd ,cmdarr);
}


void CafeDatabase::AddCustomer(std::string name, std::string email, std::string phone)
{
    // normalize phone number
    std::string p = "";
    for (char& ch : phone) if (isdigit(ch)) p += ch;

    std::string cmd = "mysql";
    std::vector<std::string> cmdarr = {
        cmd,
        "-u",
        sql_username,
        "-p",
        "cafe_db",
        "-e",
        "\"CALL add_customer(\'"+name+"\',\'"+email+"\',\'"+p+"\');\"",
        "--password="+sql_password
    };

    RunCommands(cmd ,cmdarr);
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


void CafeDatabase::CallFunctionWithoutArgs(std::string function)
{
    std::string cmd = "mysql";
    std::vector<std::string> cmdarr = {
        cmd,
        "-u",
        sql_username,
        "-p",
        database,
        "-e",
        "\"CALL "+function+"();\"",
        "--password="+sql_password
    };

    RunCommands(cmd ,cmdarr);
}