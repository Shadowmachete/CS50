import sqlite3
from flask import redirect, render_template, session
from functools import wraps

# Usage:
# 1. conn = connectDatabase()
# 2. conn.execute(SQL)
# 3a. (optional. For inputs) conn.commit()
# 3. conn.close()
def connectDatabase():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function