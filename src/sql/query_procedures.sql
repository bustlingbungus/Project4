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


CREATE PROCEDURE query_menuingredients(

)
BEGIN
    SELECT title, label, menuitemingredients.amount
    FROM menuitemingredients
    JOIN menuitems 
    ON menuitems.item_id = menuitemingredients.menu_item_id
    JOIN ingredients
    ON ingredients.ingredient_id = menuitemingredients.ingredient_id;
END$$


CREATE PROCEDURE query_sale_total(

)
BEGIN
    SELECT SUM(price)
    FROM Sales
    JOIN menuitems
    ON menuitems.item_id = sales.item_id;
END$$


CREATE PROCEDURE view_employees(

)
BEGIN
    SELECT * FROM employees;
END$$


CREATE PROCEDURE user_exists(
    IN p_username VARCHAR(255)
)
BEGIN
    DECLARE cnt INT;

    SELECT COUNT(*)
    INTO cnt
    FROM employees
    WHERE username = p_username;

    IF cnt > 0 THEN
        SELECT TRUE AS exists_flag;
    ELSE
        SELECT FALSE AS exists_flag;
    END IF;

END$$


CREATE PROCEDURE valid_password(
    IN p_username VARCHAR(255),
    IN p_password VARCHAR(255)
)
BEGIN
    DECLARE correct_password VARCHAR(255);

    SELECT password
    INTO correct_password
    FROM employees
    WHERE username = p_username
    LIMIT 1;

    IF correct_password IS NOT NULL THEN
        IF correct_password = p_password THEN
            SELECT TRUE AS exists_flag;
        ELSE
            SELECT FALSE AS exists_flag;
        END IF;
    END IF;

END$$


CREATE PROCEDURE get_access(
    IN p_username VARCHAR(255)
)
BEGIN
    SELECT access_type
    FROM employees
    WHERE username = p_username
    LIMIT 1;
END$$

DELIMITER ;