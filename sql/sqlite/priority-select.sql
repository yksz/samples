-- setup
CREATE TABLE account (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    first_name TEXT,
    last_name TEXT
);

INSERT INTO account (id) VALUES (1);
INSERT INTO account (first_name) VALUES ('John');
INSERT INTO account (first_name, last_name) VALUES ('John', 'Smith');

SELECT * FROM account;

-- main
SELECT
    id,
    CASE WHEN last_name IS NOT NULL THEN last_name
    ELSE (
        CASE WHEN first_name IS NOT NULL THEN first_name
        ELSE 'Anonymous' END
    ) END AS name
FROM
    account;
