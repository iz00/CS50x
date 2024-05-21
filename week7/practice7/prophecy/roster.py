# Update the data in roster.db, with the new schema

from cs50 import SQL
from csv import DictReader

db = SQL("sqlite:///roster.db")

# Clean all data previously inserted on tables of roster
db.execute("DELETE FROM students")
db.execute("DELETE FROM houses")
db.execute("DELETE FROM assignments")

old_db = SQL("sqlite:///roster_old.db")

# Get the four houses
houses = old_db.execute("SELECT DISTINCT(house), head FROM students ORDER BY house")

# Insert each house in the houses table
for house in houses:
    db.execute(
        "INSERT INTO houses (house_name, head_name) VALUES (?, ?)",
        house["house"],
        house["head"],
    )

# Read csv file to know the student-house relationships
with open("students.csv") as file:
    file_reader = DictReader(file)
    for student in file_reader:
        # Insert each student in students table
        db.execute(
            "INSERT INTO students (student_name) VALUES (?)", student["student_name"]
        )

        # Get id from current student
        student_id = db.execute(
            "SELECT id FROM students WHERE student_name = ?", student["student_name"]
        )[0]["id"]
        # Get id from current student's house
        house_id = db.execute(
            "SELECT id FROM houses WHERE house_name = ?", student["house"]
        )[0]["id"]

        # Insert into assignments corresponding student's and house's id
        db.execute(
            "INSERT INTO assignments (student_id, house_id) VALUES (?, ?)",
            student_id,
            house_id,
        )
