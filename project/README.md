# Pokemon Stat Checker
#### Video Demo:  <URL HERE>
#### Description:
This project is a Flask website that allows users to search for and obtain simple data regarding pokemon from Generations 1 to 6.

In the app.py file, we have routes, "/", "/login", "/logout", "/register", "/passwordChange", "/search" and "/data". The default route is set to redirect to "/search" as there is no planned homepage for this project.

Firstly, we have "/login", "/logout", "/register" and "/passwordChange". As in the name, these routes allow the user to register an account and log in and out of the account to access the website. Registration adds the users username and password to a table named "users" in the database.db file.