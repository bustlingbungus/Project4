# Cafe Management System
### COP 4710 — Database Management Systems, Spring 2026

A terminal-based enterprise management system for a cafe, built with **C++17** and **MySQL**. Employees log in with role-based credentials and interact with a live MySQL database to manage the menu, inventory, sales, customers, and staff.

---

## What This Project Does

The system simulates a real cafe's back-office operations:

- **Register staff** can ring up sales, add customers to the loyalty program, and issue refunds
- **Inventory staff** can view and restock ingredients
- **Owners** have full control — managing menu items, employees, viewing revenue, and everything above

All data is stored in a MySQL database (`cafe_db`) and accessed through stored procedures. The app connects to MySQL directly via the CLI using `execvp`, so no external driver library is needed.

---

## Requirements (macOS)

- **macOS** (this branch is macOS-specific)
- **CMake** 3.15 or later
- **Xcode Command Line Tools** (provides `clang++`)
  ```bash
  xcode-select --install
  ```
- **MySQL 8.0+** installed and running locally
  ```bash
  brew install mysql
  brew services start mysql
  ```
- **MySQL** must be accessible from your terminal as the `mysql` command:
  ```bash
  mysql --version
  ```

---

## Installation & Setup

### 1. Clone the repository (oomat-macos branch)

```bash
git clone -b oomat-macos https://github.com/bustlingbungus/Project4.git
cd Project4
```

### 2. Create your MySQL credentials file

The app reads your MySQL login from a `my.cnf` file in the **same directory you run the app from** (the project root). This file is gitignored for security.

Create it:
```bash
cat > my.cnf << EOF
[client]
user     = root
password = your_mysql_password
host     = 127.0.0.1
EOF
```

Replace `root` and `your_mysql_password` with your actual MySQL username and password.

> **Note:** If your MySQL root account has no password (common on fresh installs), leave the `password` line blank or omit it.

### 3. Copy the SQL files to the project root

The app sources SQL files from the current working directory. Make sure these four files are in the project root (they're already in `src/sql/` — just copy them):

```bash
cp src/sql/cafe_db.sql .
cp src/sql/add_procedures.sql .
cp src/sql/remove_procedures.sql .
cp src/sql/query_procedures.sql .
```

### 4. Build the project

```bash
cmake -S . -B build
cmake --build build
```

The compiled binary will be at `build/bin/Project4`.

### 5. Initialize the database

This creates the `cafe_db` database, all tables, stored procedures, and loads sample data (menu items, ingredients, employees, customers):

```bash
./build/bin/Project4 init
```

You only need to run this once. **Running it again will wipe and recreate the database.**

---

## Running the App

```bash
./build/bin/Project4
```

You will be greeted with a login prompt. Use one of the pre-loaded employee accounts:

| Username    | Password   | Role      | Access Level |
|-------------|------------|-----------|--------------|
| `cafesteve` | `mycafe43` | Owner     | Full access  |
| `dominic`   | `domf88`   | Inventory | Inventory + Register |
| `stellaz`   | `cafejob9` | Register  | Register only |

---

## Navigating the System

After logging in you land on the **Home Page**. Type `help` on any page to see available commands.

### Pages

| Page      | How to reach it          | Who can use it     |
|-----------|--------------------------|--------------------|
| Home      | Automatic after login    | Everyone           |
| Register  | `goto register`          | All staff          |
| Inventory | `goto inventory`         | Inventory + Owner  |
| Owner     | `goto owner`             | Owner only         |

### Common Commands

**Register page** — for ringing up sales:
```
addsale coffee                    # anonymous sale
addsale coffee 8131231234         # sale linked to loyalty customer
addcustomer alice a@b.com 8135550001
viewsales
refundsale 3
viewmenu
```

**Inventory page** — for managing stock:
```
inventory                         # view all ingredient amounts
setamount milk 20.00              # restock an ingredient
viewmenu
viewingredients
```

**Owner page** — full control:
```
viewbalance                       # total revenue
employees                         # list all staff
addemployee janed pass123 jane_doe 2
removeemployee janed
addmenu latte 4.50 milk 0.8 coffee_grounds 0.25
removemenu latte
removecustomer 8135550001
```

Type `exit` on any page to quit the application.
Type `logout` to return to the login screen.

---

## Project Structure

```
Project4/
├── CMakeLists.txt
├── my.cnf                  # your credentials (gitignored, you create this)
├── cafe_db.sql             # copy from src/sql/
├── add_procedures.sql      # copy from src/sql/
├── remove_procedures.sql   # copy from src/sql/
├── query_procedures.sql    # copy from src/sql/
├── src/
│   ├── cpp/
│   │   ├── main.cpp
│   │   ├── Init.hpp
│   │   ├── database/
│   │   │   ├── CafeDatabase.cpp / .hpp   # high-level DB operations
│   │   │   ├── SQLDatabase.cpp / .hpp    # MySQL CLI connector
│   │   │   ├── Date.cpp / .hpp
│   │   │   └── Ingredient.hpp
│   │   ├── terminal/
│   │   │   ├── Terminal.cpp / .hpp       # base class
│   │   │   ├── Login.cpp / .hpp
│   │   │   ├── HomePage.cpp / .hpp
│   │   │   ├── RegisterPage.cpp / .hpp
│   │   │   ├── InventoryPage.cpp / .hpp
│   │   │   └── OwnerPage.cpp / .hpp
│   │   └── sys/
│   │       ├── systemcall.cpp / .hpp     # execvp / fork wrappers
│   │       └── fileaccess.cpp / .hpp
│   └── sql/
│       ├── cafe_db.sql
│       ├── add_procedures.sql
│       ├── remove_procedures.sql
│       └── query_procedures.sql
└── build/
    └── bin/
        └── Project4                      # compiled binary
```

---

## Troubleshooting

**`mysql: command not found`**
MySQL is not on your PATH. If installed via Homebrew: `export PATH="/usr/local/opt/mysql/bin:$PATH"` (add to your `~/.zshrc`).

**`Access denied for user`**
Your `my.cnf` credentials are wrong. Test with: `mysql --defaults-extra-file=my.cnf`

**`Can't open file: cafe_db.sql`**
You must run the binary from the project root (where the `.sql` files are), not from inside `build/bin/`.

**`ERROR 1305: PROCEDURE cafe_db.add_ingredient does not exist`**
The procedures weren't loaded. Run `./build/bin/Project4 init` again to reinitialize.
