-- Refactor the schema of roster.db, with three tables

-- Table only for students
CREATE TABLE students (
    id INTEGER NOT NULL,
    student_name TEXT NOT NULL,
    PRIMARY KEY(id)
);

-- Table only for houses
CREATE TABLE houses (
    id INTEGER NOT NULL,
    house_name TEXT NOT NULL,
    head_name TEXT NOT NULL,
    PRIMARY KEY(id)
);

-- Table only for assignments, relationships between students and houses
CREATE TABLE assignments (
    student_id INTEGER NOT NULL,
    house_id INTEGER NOT NULL,
    FOREIGN KEY(student_id) REFERENCES students(id),
    FOREIGN KEY(house_id) REFERENCES houses(id),
    -- Compound key, since this combination will always be unique
    PRIMARY KEY(student_id, house_id)
);
