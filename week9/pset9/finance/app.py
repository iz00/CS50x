from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from re import search
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
# Ensure responses aren't cached
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
# Show portfolio of stocks
def index():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        return apology("method not allowed", 405)

    # Else, user reached route via GET (as by clicking a link or via redirect)

    # Get the user's id
    user_id = session["user_id"]

    # Query stocks table to get all stocks the user owns
    stocks = db.execute(
        "SELECT symbol, shares FROM stocks WHERE user_id = ? ORDER BY symbol", user_id
    )

    # Initialize the user's cash in stocks to 0
    stocks_cash = 0

    # For every stock the user has, get its current price and the total price the user has with their shares
    for stock in stocks:
        stock["price"] = lookup(stock["symbol"])["price"]
        stock["total_price"] = stock["price"] * stock["shares"]
        stocks_cash += stock["total_price"]

    # Query users table to get the amount of cash the user has
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Render the template with the stocks's and the user's infos
    return render_template(
        "index.html", stocks=stocks, cash=user_cash, total_cash=user_cash + stocks_cash
    )


@app.route("/add", methods=["GET", "POST"])
@login_required
# Add additional cash to user's account
def add():
    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("add.html")

    # Else, user reached route via POST (as by submitting a form via POST)

    # Ensure cash was submitted
    cash = request.form.get("cash")
    if not cash:
        return apology("missing cash")

    # Ensure cash is valid
    try:
        cash = float(cash)
    except ValueError:
        return apology("invalid cash")
    if cash <= 0:
        return apology("invalid cash")

    # Get the user's id
    user_id = session["user_id"]

    # Query users table to get the amount of cash the user has
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Update user's cash on the users table
    db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash + cash, user_id)

    flash(f"{usd(cash)} added to acount!")

    # Redirect user to home page
    return redirect("/")


@app.route("/buy", methods=["GET", "POST"])
@login_required
# Buy shares of stock
def buy():
    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("buy.html")

    # Else, user reached route via POST (as by submitting a form via POST)

    # Ensure symbol was submitted
    symbol = request.form.get("symbol")
    if not symbol:
        return apology("missing symbol")

    # Ensure shares were submitted
    shares = request.form.get("shares")
    if not shares:
        return apology("missing shares")

    # Lookup symbol for its infos
    symbol_info = lookup(symbol)

    # Ensure symbol is valid
    if not symbol_info:
        return apology("invalid symbol")

    # Ensure shares are valid
    try:
        shares = int(shares)
    except ValueError:
        return apology("invalid shares")
    if shares < 1:
        return apology("invalid shares")

    # Get id of user trying to buy
    user_id = session["user_id"]

    # Get the total price of the shares to be bought and query users table to get the amount of cash the user has
    share_price = symbol_info["price"]
    total_price = share_price * shares
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Ensure user has enough money
    if user_cash < total_price:
        return apology("can't afford")

    symbol = symbol_info["symbol"]

    # Add the transaction to transactions table
    db.execute(
        "INSERT INTO transactions (user_id, transaction_type, symbol, shares, price) VALUES (?, ?, ?, ?, ?)",
        user_id,
        "buy",
        symbol,
        shares,
        share_price,
    )

    # Check if user already has shares of that symbol
    user_shares = db.execute(
        "SELECT shares FROM stocks WHERE user_id = ? AND symbol = ?", user_id, symbol
    )
    # If they don't, add the shares to the user on the stocks table
    if len(user_shares) == 0:
        db.execute(
            "INSERT INTO stocks (user_id, symbol, shares) VALUES (?, ?, ?)",
            user_id,
            symbol,
            shares,
        )
    # It they do, update the user's shares on the stocks table
    else:
        new_shares = user_shares[0]["shares"] + shares
        db.execute(
            "UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?",
            new_shares,
            user_id,
            symbol,
        )

    # Update user's cash on the users table
    db.execute(
        "UPDATE users SET cash = ? WHERE id = ?", user_cash - total_price, user_id
    )

    flash(f"Bought {shares} shares of {symbol} for {usd(total_price)}!")

    # Redirect user to home page
    return redirect("/")


@app.route("/change", methods=["GET", "POST"])
@login_required
# Change user's password
def change():
    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("change.html")

    # Else, user reached route via POST (as by submitting a form via POST)

    # Ensure current password was submitted
    current_password = request.form.get("current_password")
    if not current_password:
        return apology("missing current password")

    # Ensure new password was submitted
    new_password = request.form.get("new_password")
    if not new_password:
        return apology("missing new password")

    # Ensure new password is valid
    if search("^(.{0,7}|[^0-9]*|[^A-Z]*|[^a-z]*|[a-zA-Z0-9]*)$", new_password):
        return apology("invalid new password")

    # Ensure confirmation was submitted
    confirmation = request.form.get("confirmation")
    if not confirmation:
        return apology("missing confirmation")

    # Get the user's id
    user_id = session["user_id"]

    # Query users table to get the user's password
    user_password = db.execute("SELECT hash FROM users WHERE id = ?", user_id)[0]["hash"]

    # Ensure password is correct
    if not check_password_hash(user_password, current_password):
        return apology("invalid current password")

    # Update user's password on the users table
    db.execute(
        "UPDATE users SET hash = ? WHERE id = ?",
        generate_password_hash(new_password),
        user_id,
    )

    flash("Password successfully changed!")

    # Redirect user to home page
    return redirect("/")


@app.route("/history", methods=["GET", "POST"])
@login_required
# Show history of transactions
def history():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        return apology("method not allowed", 405)

    # Else, user reached route via GET (as by clicking a link or via redirect)

    # Get the user's id
    user_id = session["user_id"]

    # Query transactions table to get all transactions made by the user
    transactions = db.execute(
        "SELECT transaction_type, symbol, shares, price, timestamp FROM transactions WHERE user_id = ?",
        user_id,
    )

    # Render the template with the transactions's infos
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
# Log user in
def login():
    # Forget any user_id
    session.clear()

    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("login.html")

    # Else, user reached route via POST (as by submitting a form via POST)

    # Ensure username was submitted
    username = request.form.get("username")
    if not username:
        return apology("must provide username", 403)

    # Ensure password was submitted
    password = request.form.get("password")
    if not password:
        return apology("must provide password", 403)

    # Query users table to get the user through their username
    user = db.execute("SELECT * FROM users WHERE username = ?", username)

    # Ensure username exists and password is correct
    if len(user) != 1 or not check_password_hash(user[0]["hash"], password):
        return apology("invalid username and/or password", 403)

    # Remember which user has logged in
    session["user_id"] = user[0]["id"]

    # Redirect user to home page
    return redirect("/")


@app.route("/logout")
# Log user out
def logout():
    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
# Get stock quote
def quote():
    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("quote.html")

    # Else, user reached route via POST (as by submitting a form via POST)

    # Ensure symbol was submitted
    symbol = request.form.get("symbol")
    if not symbol:
        return apology("missing symbol")

    # Lookup symbol for its infos
    symbol_info = lookup(symbol)

    # Ensure symbol is valid
    if not symbol_info:
        return apology("invalid symbol")

    # Render the template with the symbol's infos
    return render_template(
        "quoted.html", price=symbol_info["price"], symbol=symbol_info["symbol"]
    )


@app.route("/register", methods=["GET", "POST"])
# Register user
def register():
    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("register.html")

    # Else, user reached route via POST (as by submitting a form via POST)

    # Ensure username was submitted
    username = request.form.get("username")
    if not username:
        return apology("missing username")

    # Query users table to get a user through the username
    user = db.execute("SELECT * FROM users WHERE username = ?", username)

    # Ensure username is available
    if len(user) != 0:
        return apology("username is not available")

    # Ensure password was submitted
    password = request.form.get("password")
    if not password:
        return apology("missing password")

    # Ensure password is valid
    if search("^(.{0,7}|[^0-9]*|[^A-Z]*|[^a-z]*|[a-zA-Z0-9]*)$", password):
        return apology("invalid password")

    # Ensure confirmation was submitted
    confirmation = request.form.get("confirmation")
    if not confirmation:
        return apology("missing confirmation")

    # Ensure equality between password and confirmation
    if password != confirmation:
        return apology("passwords don't match")

    # Add the new user on the users table and remember the user logged in
    session["user_id"] = db.execute(
        "INSERT INTO users (username, hash) VALUES (?, ?)",
        username,
        generate_password_hash(password),
    )

    flash("Registered!")

    # Redirect user to home page
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
# Sell shares of stock
def sell():
    # Get the user's id
    user_id = session["user_id"]

    # Query stocks table to get all stocks the user owns
    stocks = db.execute(
        "SELECT symbol, shares FROM stocks WHERE user_id = ? ORDER BY symbol", user_id
    )
    symbols_owned = [stock["symbol"] for stock in stocks]

    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        # Render the template with the symbols
        return render_template("sell.html", symbols=symbols_owned)

    # Else, user reached route via POST (as by submitting a form via POST)

    # Ensure symbol was submitted
    symbol = request.form.get("symbol")
    if not symbol:
        return apology("missing symbol")

    # Ensure shares were submitted
    shares = request.form.get("shares")
    if not shares:
        return apology("missing shares")

    # Ensure shares are valid
    try:
        shares = int(shares)
    except ValueError:
        return apology("invalid shares")
    if shares < 1:
        return apology("shares must be positive")

    symbol_info = lookup(symbol)

    # Ensure symbol exists and user owns shares of it
    if not symbol_info or symbol not in symbols_owned:
        return apology("symbol not owned")

    # Ensure user has enough shares
    shares_owned = [stock["shares"] for stock in stocks if stock["symbol"] == symbol][0]
    if shares_owned < shares:
        return apology("too many shares")

    # Get the price of a share
    share_price = symbol_info["price"]

    # Add the transaction to transactions table
    db.execute(
        "INSERT INTO transactions (user_id, transaction_type, symbol, shares, price) VALUES (?, ?, ?, ?, ?)",
        user_id,
        "sell",
        symbol,
        shares,
        share_price,
    )

    # Check if user will have any shares of that symbol left
    new_shares = shares_owned - shares
    # If they don't, delete the row of that symbol and that user from the stocks table
    if new_shares == 0:
        db.execute(
            "DELETE FROM stocks WHERE user_id = ? AND symbol = ?", user_id, symbol
        )
    # It they do, update the user's shares on the stocks table
    else:
        db.execute(
            "UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?",
            new_shares,
            user_id,
            symbol,
        )

    # Get the total price of the shares to be sold and query users table to get the amount of cash the user has
    total_price = share_price * shares
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Update user's cash on the users table
    db.execute(
        "UPDATE users SET cash = ? WHERE id = ?", user_cash + total_price, user_id
    )

    flash(f"Sold {shares} shares of {symbol} for {usd(total_price)}!")

    # Redirect user to home page
    return redirect("/")
