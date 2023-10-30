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
Finally, on to _"/data"_. Initially, if the user clicks the "Pokemon Data" in the navigation bar or manually visits the _"/data"_ route in the url of the site, they will be displayed with the **search.html** template file and prompted to select the pokemon they wish to view the data of.

Once the user has selected the pokemon to view the data of via clicking on the Data button, they will be shown the **data.html** file with relevant information. The **data.html** file has 2 sections. On the left, in order from top to bottom we have the pokemon's
- Name
- Typing
- Abilities
- Stats
- EVs (Effort Values) gained upon kill

Next, on the right we have 8 buttons on top which allow the user to choose from Generation 1 to 8. Below that the user can choose either Level Up, Egg or Other. These 3 options represent the method that the pokemon learns the moves displayed below.

Below the buttons, there is a table which states the method that the pokemon learns the moves by, followed by the move name and the level that the pokemon learns the move at, if applicable.

Learnset data is all obtained via Javascript API fetch from [PokéAPI](https://pokeapi.co/) in the **data.js** file.

Firstly, the Javascript file extracts the pokemon id from the HTML of the **data.html** page. The function getData is then defined to take in the id as an argument and to use `fetch` to fetch the data from the API via `fetch('https://pokeapi.co/api/v2/pokemon/' + id)`. The response is converted to JSON and data is extracted from the JSON to populate the _levelUp_, _egg_ and _other_ arrays, along with _abilities_, _stats_, _types_ and _pokemonName_ variables. The data is then returned as the array, `[pokemonName, levelUp, egg, other, abilities, stats, types]` with the _levelUp_ array being sorted by _Level Learnt_.

Next, the renderData function is defined with arguments *gen* and *learn_by* which has default values of *1* and *"level-up"* respectively. This function first gets the data by calling getData with the id of the pokemon. Then it populates the left box with the name, typing, abilities, stats and EVs of the pokemon, all from the data returned by the getData function.

For the right box, the renderData function loops through all moves which are in array corresponding to the *learn_by* argument inputted into the function. Then, the generation that the pokemon learns the move in is compared against the *gen* argument inputted before adding the new row into the table.

Lastly, at the end of the **data.js** file, Event Listeners are added to each of the buttons. If the button is used to change the generation of moves viewed, the renderData function will be called with the new generation number which is in the value of the button along with the previous method via which the pokemon learnt the moves. Similarly for the buttons controlling method used, the new method will be provided along with the previous generation of moves being viewed.