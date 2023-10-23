from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import login_required

# Configure Application
app = Flask(__name__)


app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

db = SQL("sqlite:///database.db")

@app.route("/")
@login_required
def index():
    return redirect("/search")

@app.route("/login", methods=["GET", "POST"])
def login():
    session.clear()

    if request.method == "POST":
        if not request.form.get("username"):
            return render_template("login.html", error="No username")

        elif not request.form.get("password"):
            return render_template("login.html", error="No password")

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return render_template("login.html", error="Invalid username")

        session["user_id"] = rows[0]["id"]
        return redirect("/")
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    session.clear()

    return redirect("/")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        if not request.form.get("username"):
            return render_template("register.html", error="No username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return render_template("register.html", error="No password")

        # Ensure password was repeated properly
        elif request.form.get("password") != request.form.get("confirmation"):
            return render_template("register.html", error="Password repeated incorrectly")

        names = db.execute("SELECT username FROM users")
        nameList = []
        for name in names:
            nameList.append(name['username'])

        if request.form.get("username") in nameList:
            return render_template("register.html", error="User already registered")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))
        return redirect("/login")
    else:
        return render_template("register.html")

@app.route("/passwordChange", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        if not request.form.get("password"):
            return render_template("change_password.html", error="No password")

        elif request.form.get("password") != request.form.get("confirmation"):
            return render_template("change_password.html", error="Password repeated incorrectly")

        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(request.form.get("password")), session["user_id"])
        return redirect("/")
    else:
        return render_template("change_password.html")

@login_required
@app.route("/search", methods=["GET", "POST"])
def search():
    if request.method == "POST":
        id, name, type1, type2, gen, isLegend, order, orderdir = request.form.get("id", ""), request.form.get("name", ""), request.form.get("type1", ""), request.form.get("type2", ""), request.form.get("gen", ""), request.form.get("isLegend", ""), request.form.get("order", ""), request.form.get("orderdir", "")
        if order != '':
            if orderdir != '':
                data = db.execute("SELECT * FROM pokemon WHERE id LIKE ? AND Name LIKE ? AND `Type 1` LIKE ? AND `Type 2` LIKE ? AND Generation LIKE ? AND Legendary LIKE ? ORDER BY ? ?", "%" + id + "%", "%" + name + "%", "%" + type1 + "%", "%" + type2 + "%", "%" + gen + "%", "%" + isLegend + "%", order, orderdir)
            else:
                data = db.execute("SELECT * FROM pokemon WHERE id LIKE ? AND Name LIKE ? AND `Type 1` LIKE ? AND `Type 2` LIKE ? AND Generation LIKE ? AND Legendary LIKE ? ORDER BY ?", "%" + id + "%", "%" + name + "%", "%" + type1 + "%", "%" + type2 + "%", "%" + gen + "%", "%" + isLegend + "%", order)
        else:
            data = db.execute("SELECT * FROM pokemon WHERE id LIKE ? AND Name LIKE ? AND `Type 1` LIKE ? AND `Type 2` LIKE ? AND Generation LIKE ? AND Legendary LIKE ?", "%" + id + "%", "%" + name + "%", "%" + type1 + "%", "%" + type2 + "%", "%" + gen + "%", "%" + isLegend + "%")
        return render_template("search.html", data=data)
    else:
        return render_template("search.html")

@login_required
@app.route("/data", methods=["GET", "POST"])
def pokemonData():
    if request.method == "POST":
        id = request.form.get("id")
        if id == None:
            return render_template("search.html", error="Please choose")
        return render_template("data.html", id=id)
    else:
        return render_template("search.html", error="Please select the pokemon you would like to see the data of.")