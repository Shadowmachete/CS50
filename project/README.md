# Pokemon Stat Checker
#### Video Demo:  <URL HERE>
## Description:
### Introduction
This project is a Flask website that allows users to search for and obtain simple data regarding pokemon from Generations 1 to 6.

In the **app.py** file, we have routes, _"/"_, _"/login"_, _"/logout"_, _"/register"_, _"/passwordChange"_, _"/search"_ and _"/data"_. The default route is set to redirect to _"/search"_ as there is no planned homepage for this project.

### Admin
Firstly, we have _"/login"_, _"/logout"_, _"/register"_ and _"/passwordChange"_. As in the name, these routes allow the user to register an account and log in and out of the account to access the website. Registration adds the users username and password to a table named "users" in the database.db file. Both the login and register routes link the user to **login.html** and **register.html** which have a simple Sign In / Sign Up form with a link to the other route. The passwordChange route allows the user to change their password and will update the users table in the database according.

### Searching
Next, on to _"/search"_. Upon clicking the "Search" in the navigation bar, the user will be shown the **search.html** template file. This file will first prompt the user to fill up various fields to narrow the search. The user can choose to provide
- id
- name
- primary type
- secondary type
- generation number
- whether or not the pokemon is a legendary

Additionally, the user can choose to order the search results in either Ascending or Descending order by
- name
- type
- total stat points
- respective stat points
- generation number

After the user submits their inputted values, the form will then submit all the data to execute a `SELECT` statement to the pokemon table in the database. This pokemon table was obtained from a pokemon.csv file from [Github user Armgilles](https://gist.github.com/armgilles/194bcff35001e7eb53a2a8b441e8b2c6) which contains data regarding pokemon from Generation 1 to 6 of pokemon. The data returned from the `SELECT` statement was then used to populate the table which has rows ***Id, Name, Typing, Total, HP, Attack, Defense, Sp. Atk, Sp. Def, Speed, Generation, Legendary*** and ***Data***. The ***Typing*** column has 2 columns for dual typed pokemon. Pokemon with only 1 type will have their typing populate both columns allocated to ***Typing***.

Some things to note are that Mega pokemon have a mega icon next to their name along with a different text colour being Dark Magenta. The colours for the ***Typings*** are obtained from [Bulbapedia](https://bulbapedia.bulbagarden.net/wiki/Main_Page). The ***Legendary*** column has either a tick or a cross to represent either *Yes* or *No* to the question *"Is this pokemon a legendary?"*. Lastly, under the ***Data*** column, there is a button which will send the user to the _"/data"_ route with the corresponding ***Id*** of the pokemon to display the data of. Mega pokemon will not have this button as outside of battle they are equivalent to the base pokemon.

### Data
Finally, on to _"/data"_. 