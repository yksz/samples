-- setup
CREATE TABLE product (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL UNIQUE,
    price INTEGER NOT NULL
);

INSERT INTO product (name, price) VALUES ('apple', 50);
INSERT INTO product (name, price) VALUES ('orange', 100);
INSERT INTO product (name, price) VALUES ('coffee', 150);

SELECT
    id,
    name,
    price
FROM
    product;

-- main
SELECT
    CASE WHEN name = 'apple' THEN 'fruit'
         WHEN name = 'orange' THEN 'fruit'
         WHEN name = 'coffee' THEN 'drink'
    ELSE 'other' END AS kind,
    COUNT(*) AS count
FROM
    product
GROUP BY
    CASE WHEN name = 'apple' THEN 'fruit'
         WHEN name = 'orange' THEN 'fruit'
         WHEN name = 'coffee' THEN 'drink'
    ELSE 'other' END;
