import sqlite3
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import connectDatabase, login_required

# Configure Application
app = Flask(__name__)

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

@app.route("/")
@login_required
def index():
    return render_template("index.html")

@app.route("/layout")
def layout():
    return render_template("layout.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        ...
    else:
        return render_template("login.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        ...
    else:
        return render_template("register.html")