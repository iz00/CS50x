import os

from calendar import month_name
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

# Global list of months, skip first element which is empty
MONTHS = list(month_name)[1:]


@app.after_request
# Ensure responses aren't cached
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
# Show birthdays and add new entries to database
def index():
    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        # Query database to get all birthdays ordered by name
        birthdays = db.execute("SELECT * FROM birthdays ORDER BY name")

        # Render the template with the birthdays
        return render_template("index.html", months=MONTHS, birthdays=birthdays)

    # Else, user reached route via POST (as by submitting a form via POST)

    # Ensure name was submitted
    name = request.form.get("name").strip()
    if not name:
        return redirect("/")

    # Ensure month was submitted and is valid
    month = request.form.get("month")
    if month not in MONTHS:
        return redirect("/")

    day = request.form.get("day")

    # Ensure day is valid
    try:
        day = int(day)
    except (TypeError, ValueError):
        return redirect("/")
    # Ensure month and day are valid birth dates
    if (
        day < 1
        or day > 31
        or (month == "February" and day > 28)
        or (month in ["April", "June", "September", "November"] and day > 30)
    ):
        return redirect("/")

    # Add the birthday to the database, converting the month to its number equivalent
    db.execute(
        "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)",
        name,
        MONTHS.index(month) + 1,
        day,
    )

    # Reload homepage, via GET
    return redirect("/")


@app.route("/delete", methods=["POST"])
# Delete a birthday
def delete():
    # Get the id of the birthday to be deleted
    id = request.form.get("id")

    # Delete the birthday from the database
    if id:
        db.execute("DELETE FROM birthdays WHERE id = ?", id)

    # Reload homepage, via GET
    return redirect("/")


@app.route("/edit", methods=["POST"])
# Edit a birthday
def edit():
    # Ensure name was submitted
    name = request.form.get("name").strip()
    if not name:
        return redirect("/")

    # Ensure month was submitted and is valid
    month = request.form.get("month")
    if month not in MONTHS:
        return redirect("/")

    day = request.form.get("day")

    # Ensure day is valid
    try:
        day = int(day)
    except (TypeError, ValueError):
        return redirect("/")
    # Ensure month and day are valid birth dates
    if (
        day < 1
        or day > 31
        or (month == "February" and day > 28)
        or (month in ["April", "June", "September", "November"] and day > 30)
    ):
        return redirect("/")

    # Get the id of the birthday to be edited
    id = request.form.get("id")

    # Update the birthday on the database
    if id:
        db.execute(
            "UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?",
            name,
            MONTHS.index(month) + 1,
            day,
            id,
        )

    # Reload homepage, via GET
    return redirect("/")
