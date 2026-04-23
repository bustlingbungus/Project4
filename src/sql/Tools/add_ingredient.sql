-- Procedure: add_ingredient(IN p_label, IN p_amount, OUT p_ingredient_id)
CREATE PROCEDURE add_ingredient(
  IN p_label VARCHAR(255),
  IN p_amount DECIMAL(10,2),
  OUT p_ingredient_id INT
)
BEGIN
  DECLARE existing_id INT;

  SELECT ingredient_id INTO existing_id
  FROM Ingredients
  WHERE label = p_label
  LIMIT 1;

  IF existing_id IS NOT NULL THEN
    -- update amount if desired (commented out). Uncomment to add to existing amount:
    -- UPDATE Ingredients SET amount = amount + p_amount WHERE ingredient_id = existing_id;
    SET p_ingredient_id = existing_id;
  ELSE
    INSERT INTO Ingredients(label, amount) VALUES (p_label, p_amount);
    SET p_ingredient_id = LAST_INSERT_ID();
  END IF;
END$$