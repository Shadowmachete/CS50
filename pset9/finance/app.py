import os
import datetime
import pytz

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
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
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute(
        "SELECT stock, SUM(shares) as shares, Date FROM transactions WHERE user_id = ? GROUP BY stock", session["user_id"])
    prices = {stock['stock']: lookup(stock['stock'])['price'] for stock in stocks}
    userData = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    totalHolding = 0
    for i in stocks:
        totalHolding += prices[i['stock']] * i['shares']
    return render_template("index.html", name=userData[0]["username"], cash=userData[0]["cash"], holding=totalHolding, stocks=stocks, prices=prices)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol of stock", 400)

        elif not request.form.get("shares"):
            return apology("must provide a number of shares", 400)

        try:
            numberOfShares = int(request.form.get("shares"))
            if numberOfShares < 0:
                return apology("must provide a positive number of shares", 400)

        except:
            return apology("must provide a number of shares", 400)

        data = lookup(request.form.get("symbol"))
        if data == None:
            return apology("incorrect symbol", 400)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        if cash < float(data["price"] * numberOfShares):
            return apology("insufficient balance", 400)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - float(data["price"] * numberOfShares),
                    session["user_id"])
        db.execute("INSERT INTO transactions (user_id, stock, shares, date) VALUES (?, ?, ?, ?)", session["user_id"], data["symbol"], numberOfShares, datetime.datetime.now(pytz.timezone("US/Eastern")))
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT stock, shares, Date FROM transactions WHERE user_id = ? ORDER BY Date ASC", session["user_id"])
    prices = {stock['stock']: lookup(stock['stock'])['price'] for stock in stocks}
    return render_template("history.html", stocks=stocks, prices=prices)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol of stock", 400)

        data = lookup(request.form.get("symbol"))
        if data == None:
            return apology("incorrect symbol", 400)

        return render_template("quoted.html", data=data)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password was repeated properly
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("must repeat password properly", 400)

        names = db.execute("SELECT username FROM users")
        nameList = []
        for name in names:
            nameList.append(name['username'])

        if request.form.get("username") in nameList:
            return apology("user already registered", 400)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get(
            "username"), generate_password_hash(request.form.get("password")))
        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide stock to sell", 400)

        elif not request.form.get("shares"):
            return apology("must provide number of stocks to sell", 400)

        try:
            numberOfShares = int(request.form.get("shares"))
            if numberOfShares < 0:
                return apology("must provide a positive number of shares", 400)

        except:
            return apology("must provide a number of shares", 400)

        stocks = db.execute("SELECT DISTINCT(stock) FROM transactions WHERE user_id = ?", session["user_id"])
        stocklist = []
        for i in stocks:
            stocklist.append(i['stock'])
        print(stocks)
        if request.form.get("symbol") not in stocklist:
            return apology("shares not purchased", 400)

        numShares = db.execute("SELECT sum(shares) as shares FROM transactions WHERE user_id = ? AND stock = ?",
                                session["user_id"], request.form.get("symbol"))
        if numberOfShares > numShares[0]['shares']:
            return apology("not enough shares purchased", 400)

        data = lookup(request.form.get("symbol"))
        if data == None:
            return apology("incorrect symbol", 400)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + float(data["price"] * numberOfShares), session["user_id"])
        db.execute("INSERT INTO transactions (user_id, stock, shares, date) VALUES (?, ?, ?, ?)",
                    session["user_id"], data["symbol"], -numberOfShares, datetime.datetime.now(pytz.timezone("US/Eastern")))

        return redirect("/")
    else:
        stocks = db.execute("SELECT DISTINCT(stock) FROM transactions WHERE user_id = ?", session["user_id"])
        return render_template("sell.html", stocks=stocks)


@app.route("/passwordChange", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        if not request.form.get("password"):
            return apology("must provide password", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("must repeat password properly", 400)

        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(
            request.form.get("password")), session["user_id"])
        return redirect("/")
    else:
        return render_template("change_password.html")