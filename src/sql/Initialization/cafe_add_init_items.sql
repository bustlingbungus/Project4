USE cafe_db;

CALL add_ingredient('Sugar', 10.00, @unused);
CALL add_ingredient('Coffee Grounds', 15.00, @unused);
CALL add_ingredient('Tea Leaves', 4.00, @unused);
CALL add_ingredient('Whole Milk', 16.00, @unused);
CALL add_ingredient('Creamer', 8.00, @unused);
CALL add_ingredient('Almond Milk', 8.00, @unused);


CALL add_menu_item('Coffee', 2.50, '[
    {"label":"coffee grounds",  "amount":0.25   },
    {"label":"creamer",         "amount":0.5    },
    {"label":"sugar",           "amount":0.1    }
]', @unused);

CALL add_menu_item('espresso shot', 1.00, '[
    {"label":"coffee grounds",  "amount":0.25   }
]', @unused);

-- CALL add_menu_item('Green tea', 2.50, '[
--     {"label":"coffee grounds",  "amount":0.25   },
--     {"label":"creamer",         "amount":0.5    },
--     {"label":"sugar",           "amount":0.1    }
-- ]', @unused);