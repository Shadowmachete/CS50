# Pokemon Stat Checker
#### Video Demo:  <URL HERE>
#### Description:
This project is a Flask website that allows users to search for and obtain simple data regarding pokemon from Generations 1 to 6.

In the **app.py** file, we have routes, _"/"_, _"/login"_, _"/logout"_, _"/register"_, _"/passwordChange"_, _"/search"_ and _"/data"_. The default route is set to redirect to _"/search"_ as there is no planned homepage for this project.

Firstly, we have _"/login"_, _"/logout"_, _"/register"_ and _"/passwordChange"_. As in the name, these routes allow the user to register an account and log in and out of the account to access the website. Registration adds the users username and password to a table named "users" in the database.db file. Both the login and register routes link the user to **login.html** and **register.html** which have a simple Sign In / Sign Up form with a link to the other route. The passwordChange route allows the user to change their password and will update the users table in the database according.

Next, on to _"/search"_. Upon clicking the "Search" in the navigation bar, the user will be shown the **search.html** template file. This file will first prompt the user to input various 