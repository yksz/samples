-- setup
CREATE TABLE product (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL UNIQUE,
    price INTEGER NOT NULL
);

INSERT INTO product (name, price) VALUES ('apple', 50);
INSERT INTO product (name, price) VALUES ('orange', 100);
INSERT INTO product (name, price) VALUES ('coffee', 150);

SELECT * FROM product;

-- main
CREATE VIEW price100
AS SELECT
    id,
    name,
    price
FROM
    product
WHERE
    price <= 100;

SELECT
    name,
    price
FROM
    price100;
