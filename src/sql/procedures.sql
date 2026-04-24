DELIMITER $$

-- Procedure: add_ingredient(IN p_label, IN p_amount)
CREATE PROCEDURE add_ingredient(
  IN p_label VARCHAR(255),
  IN p_amount DECIMAL(10,2)
)
BEGIN
  DECLARE existing_id INT;

  SELECT ingredient_id INTO existing_id
  FROM Ingredients
  WHERE label = LOWER(p_label)
  LIMIT 1;

  IF existing_id IS NOT NULL THEN
    -- update amount if desired
    UPDATE Ingredients 
    SET amount =  p_amount 
    WHERE ingredient_id = existing_id;
  ELSE
    INSERT INTO Ingredients(label, amount) VALUES (LOWER(p_label), p_amount);
  END IF;
END$$



-- Procedure: add_menu_item(IN p_title, IN p_price, IN p_ingredients_json)
-- p_ingredients_json example: '[{"label":"Flour","amount":100.0},{"label":"Sugar","amount":20.5}]'
CREATE PROCEDURE add_menu_item(
  IN p_title VARCHAR(255),
  IN p_price DECIMAL(5,2),
  IN p_ingredients_json JSON
)
BEGIN
  DECLARE idx INT DEFAULT 0;
  DECLARE cnt INT DEFAULT 0;
  DECLARE ing_label VARCHAR(255);
  DECLARE ing_amount DECIMAL(10,2);
  DECLARE ing_id INT;
  DECLARE it_id INT;

  -- Insert menu item
  INSERT INTO MenuItems(title, price) VALUES (LOWER(p_title), p_price);
  SET it_id = LAST_INSERT_ID();

  -- iterate JSON array
  SET cnt = JSON_LENGTH(p_ingredients_json);
  WHILE idx < cnt DO
    SET ing_label = JSON_UNQUOTE(JSON_EXTRACT(p_ingredients_json, CONCAT('$[', idx, '].label')));
    SET ing_amount = JSON_EXTRACT(p_ingredients_json, CONCAT('$[', idx, '].amount'));

    -- insert or get ingredient id (reuse add_ingredient)
    SELECT ingredient_id
    INTO ing_id
    FROM Ingredients
    WHERE label = LOWER(ing_label)
    LIMIT 1;

    -- insert junction row (if exists, update amount)
    IF ing_id IS NOT NULL THEN 
      INSERT INTO MenuItemIngredients(menu_item_id, ingredient_id, amount)
      VALUES (it_id, ing_id, ing_amount)
      ON DUPLICATE KEY UPDATE amount = VALUES(amount);
    END IF;

    SET idx = idx + 1;
  END WHILE;
END$$


CREATE PROCEDURE add_sale(
  IN p_menu_item VARCHAR(255),
  IN p_date DATE,
  IN p_customer_email VARCHAR(255),
  IN p_customer_phone VARCHAR(255),
  IN p_customer_name VARCHAR(255)
)
BEGIN

  DECLARE it_id INT;
  DECLARE c_id INT;
  DECLARE pts INT;

  -- get menu id number
  SELECT item_id
  INTO it_id
  FROM menuitems
  WHERE title = LOWER(p_menu_item)
  LIMIT 1;

  IF it_id IS NOT NULL THEN

    -- get sale points
    SELECT CEIL(price)
    INTO pts
    FROM menuitems
    WHERE item_id = it_id
    LIMIT 1;


    -- get customer id number
    SELECT customer_id
    INTO c_id
    FROM customers
    WHERE email = LOWER(p_customer_email)
    LIMIT 1;

    IF c_id IS NULL THEN -- customer not in database, add them
      INSERT INTO customers(name, email, phone_num, points)
      VALUES (LOWER(p_customer_name), LOWER(p_customer_email), LOWER(p_customer_phone), pts);
      SET c_id = LAST_INSERT_ID();
    ELSE -- customer exists, increment their points
      UPDATE customers 
      SET points = points + pts
      WHERE customer_id = c_id;
    END IF;

    INSERT INTO sales(item_id, date, customer_id)
    VALUES (it_id, p_date, c_id);


    -- subtract ingredient amounts used by the menu item
    UPDATE Ingredients I
    JOIN MenuItemIngredients m ON I.ingredient_id = m.ingredient_id
    SET I.amount = I.amount - m.amount
    WHERE m.menu_item_id = it_id;

  END IF;
END$$


DELIMITER ;