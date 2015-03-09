-- setup
CREATE TABLE department (
    id INTEGER NOT NULL UNIQUE,
    name TEXT NOT NULL UNIQUE
);

CREATE TABLE employee (
    name TEXT NOT NULL,
    department_id INTEGER NOT NULL,
    FOREIGN KEY (department_id) REFERENCES department (id)
);

INSERT INTO department VALUES(31, 'Sales');
INSERT INTO department VALUES(33, 'Engineering');
INSERT INTO department VALUES(34, 'Clerical');
INSERT INTO department VALUES(35, 'Marketing');

INSERT INTO employee VALUES('Rafferty', 31);
INSERT INTO employee VALUES('Jones', 33);
INSERT INTO employee VALUES('Heisenberg', 33);
INSERT INTO employee VALUES('Robinson', 34);
INSERT INTO employee VALUES('Smith', 34);
INSERT INTO employee VALUES('Williams', 35);

SELECT * FROM employee e INNER JOIN department d WHERE e.department_id = d.id;

-- main
DELETE
FROM
    employee
WHERE
    department_id IN (
        SELECT
            id
        FROM
            department
        WHERE
            id = 34
    );

SELECT
    e.name,
    d.name
FROM
    employee e INNER JOIN department d
WHERE
    e.department_id = d.id;
