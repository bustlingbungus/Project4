DELIMITER $$

CREATE PROCEDURE remove_sale(
    IN p_sale_id VARCHAR(255)
)
BEGIN

    DECLARE cust_id INT;
    DECLARE it_id INT;
    DECLARE pts INT;

    SELECT item_id
    INTO it_id
    FROM sales
    WHERE sale_id = p_sale_id;

    -- decrement items sold counter
    IF it_id IS NOT NULL THEN
        UPDATE menuitems
        SET items_sold = items_sold - 1
        WHERE item_id = it_id;
    END IF;


    SELECT customer_id
    INTO cust_id
    FROM sales
    WHERE sale_id = p_sale_id;

    IF cust_id IS NOT NULL THEN -- subtract sale points from customer points
        -- get sale's points
        SELECT CEIL(price)
        INTO pts
        FROM sales
        JOIN menuitems
        ON sales.item_id = menuitems.item_id
        WHERE sales.sale_id = p_sale_id;

        -- subtract points from customer
        UPDATE customers
        SET points = points - pts
        WHERE customer_id = cust_id;
    END IF;

    DELETE FROM sales
    WHERE sale_id = p_sale_id;

END$$



CREATE PROCEDURE remove_ingredient(
    IN p_label VARCHAR(255)
)
BEGIN

    DECLARE ing_id INT;

    SELECT ingredient_id
    INTO ing_id
    FROM ingredients
    WHERE label = p_label
    LIMIT 1;

    IF ing_id IS NOT NULL THEN
        DELETE FROM menuitemingredients
        WHERE ingredient_id = ing_id;

        -- remove from ingredients table
        DELETE FROM ingredients
        WHERE ingredient_id = ing_id;
    END IF;
END$$


CREATE PROCEDURE remove_menu_item(
    IN p_title VARCHAR(255)
)
BEGIN

    DECLARE it_id INT;

    SELECT item_id
    INTO it_id
    FROM menuitems
    WHERE title = p_title
    LIMIT 1;

    IF it_id IS NOT NULL THEN

        -- remove from menuitemingredients
        DELETE FROM menuitemingredients
        WHERE menu_item_id = it_id;

        -- remove from menu items
        DELETE FROM menuitems
        WHERE item_id = it_id;
    END IF; 

END$$


CREATE PROCEDURE remove_customer(
    IN p_phone VARCHAR(255)
)
BEGIN
    DECLARE c_id INT;

    -- get customer id
    SELECT customer_id 
    INTO c_id
    FROM customers
    WHERE phone_num = p_phone
    LIMIT 1;

    IF c_id IS NOT NULL THEN
        -- edit affected sales
        UPDATE sales
        SET customer_id = NULL
        WHERE customer_id = c_id;

        -- remove from customers table
        DELETE FROM customers
        WHERE customer_id = c_id;
    END IF;
END$$


CREATE PROCEDURE remove_employee(
    IN p_username VARCHAR(255)
)
BEGIN
    DELETE FROM employees
    WHERE username = p_username;
END$$

DELIMITER ;