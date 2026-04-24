DROP DATABASE IF EXISTS cafe_db; -- drop any existing database so that this file initializes cafe_db
CREATE DATABASE IF NOT EXISTS cafe_db CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE cafe_db;

CREATE TABLE IF NOT EXISTS Ingredients (
  ingredient_id INT AUTO_INCREMENT PRIMARY KEY,
  label VARCHAR(255) NOT NULL UNIQUE,
  amount DECIMAL(10,2)
);

CREATE TABLE IF NOT EXISTS MenuItems (
  item_id INT AUTO_INCREMENT PRIMARY KEY,
  title VARCHAR(255) NOT NULL UNIQUE,
  price DECIMAL(5,2),
  items_sold INT DEFAULT 0
);

CREATE TABLE IF NOT EXISTS MenuItemIngredients (
  menu_item_id INT NOT NULL,
  ingredient_id INT NOT NULL,
  amount DECIMAL(10,2),
  PRIMARY KEY (menu_item_id, ingredient_id),
  FOREIGN KEY (menu_item_id) REFERENCES MenuItems(item_id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (ingredient_id) REFERENCES Ingredients(ingredient_id) ON DELETE RESTRICT ON UPDATE CASCADE
);


CREATE TABLE IF NOT EXISTS Customers (
  customer_id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(255) NOT NULL,
  points INT NOT NULL DEFAULT 0,
  email VARCHAR(255) NOT NULL UNIQUE,
  phone_num VARCHAR(30) UNIQUE
);

CREATE TABLE IF NOT EXISTS Sales (
  sale_id INT AUTO_INCREMENT PRIMARY KEY,
  date DATE NOT NULL,
  amount DECIMAL(5,2),
  customer_id INT,
  item_id INT NOT NULL,
  FOREIGN KEY (item_id) REFERENCES MenuItems(item_id),
  FOREIGN KEY (customer_id) REFERENCES Customers(customer_id)
);
