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

    DECLARE ing_id;


    SELECT ingredient_id
    INTO ing_id
    FROM ingredients
    WHERE label = p_label
    LIMIT 1;

    DELETE FROM menuitems
    JOIN menuitemingredients
    ON menuitems.item_id = menuitemingredients.menu_item_id
    WHERE menuitemingredients.ingredientIid = ing_id;


END$$

DELIMITER ;