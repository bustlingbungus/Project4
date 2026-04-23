-- Procedure: add_menu_item(IN p_title, IN p_price, IN p_ingredients_json, OUT p_item_id)
-- p_ingredients_json example: '[{"label":"Flour","amount":100.0},{"label":"Sugar","amount":20.5}]'
CREATE PROCEDURE add_menu_item(
  IN p_title VARCHAR(255),
  IN p_price DECIMAL(5,2),
  IN p_ingredients_json JSON,
  OUT p_item_id INT
)
BEGIN
  DECLARE idx INT DEFAULT 0;
  DECLARE cnt INT DEFAULT 0;
  DECLARE ing_label VARCHAR(255);
  DECLARE ing_amount DECIMAL(10,2);
  DECLARE ing_id INT;

  -- Insert menu item
  INSERT INTO MenuItems(title, price) VALUES (p_title, p_price);
  SET p_item_id = LAST_INSERT_ID();

  -- iterate JSON array
  SET cnt = JSON_LENGTH(p_ingredients_json);
  WHILE idx < cnt DO
    SET ing_label = JSON_UNQUOTE(JSON_EXTRACT(p_ingredients_json, CONCAT('$[', idx, '].label')));
    SET ing_amount = JSON_EXTRACT(p_ingredients_json, CONCAT('$[', idx, '].amount'));

    -- insert or get ingredient id (reuse add_ingredient)
    CALL add_ingredient(ing_label, ing_amount, ing_id);

    -- insert junction row (if exists, update amount)
    INSERT INTO MenuItemIngredients(menu_item_id, ingredient_id, amount)
    VALUES (p_item_id, ing_id, ing_amount)
    ON DUPLICATE KEY UPDATE amount = VALUES(amount);

    SET idx = idx + 1;
  END WHILE;
END$$