import sqlite3


# Usage:
# 1. conn = connectDatabase()
# 2. conn.execute(SQL)
# 3a. (optional. For selections) conn.commit()
# 3. conn.close()
def connectDatabase():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn