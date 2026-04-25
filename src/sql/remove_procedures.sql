DELIMITER $$

CREATE PROCEDURE remove_sale(
    IN p_sale_id VARCHAR(255)
)
BEGIN

    DECLARE cust_id INT;
    DECLARE pts INT;

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

DELIMITER ;