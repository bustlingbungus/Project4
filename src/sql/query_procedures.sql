USE cafe_db;

DELIMITER $$

CREATE PROCEDURE query_ingredients(

)
BEGIN
    SELECT label, amount FROM ingredients;
END$$


CREATE PROCEDURE query_menu(

)
BEGIN
    SELECT title, price, items_sold FROM menuitems;
END$$



CREATE PROCEDURE query_customers(

)
BEGIN
    SELECT * FROM customers;
END$$


CREATE PROCEDURE query_sales(

)
BEGIN
    SELECT sale_id, title, date, customer_id, price
    FROM sales
    JOIN menuitems
    WHERE sales.item_id = menuitems.item_id;
END$$

DELIMITER ;