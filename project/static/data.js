id = document.querySelector("#id").innerHTML;
generations = {1: [1,2], 2: [3,4], 3: [5,6,7], 4: [8,9,10], 5: [11, 12, 13, 14], 6: [15, 16], 7: [17, 18, 19], 8: [20, 23]};
async function getData(id) {
    await fetch('https://pokeapi.co/api/v2/pokemon/' + id)
    .then(resp => resp.json())
    .then(data => {
        levelUp = [];
        egg = [];
        other = [];
        abilities = data.abilities;
        stats = data.stats;
        types = data.types;
        moves = data.moves;
        name = data.name;
        moves.forEach((move) => {
            moveName = move.move.name;
            for (i of move.version_group_details) {
                if (i.move_learn_method.name == "level-up") {
                    levelUp.push([moveName, i]);
                } else if (i.move_learn_method.name == "egg") {
                    egg.push([moveName, i]);
                } else {
                    other.push([moveName, i]);
                }
            }
        })
    })
    levelUp.sort((a,b) => {return a[1].level_learned_at - b[1].level_learned_at});
    return [name, levelUp, egg, other, abilities, stats, types]
}
async function renderData(gen=1, learn_by="level-up") {
    data = await getData(id);
    box = document.querySelector(".learnset");
    lbox = document.querySelector(".leftbox");
    lbox.innerHTML = ``;
    box.innerHTML = ``;

    document.querySelector("#gen").innerHTML = gen;
    document.querySelector("#learn_by").innerHTML = learn_by;
    lbox.innerHTML += `<h1 class="title">${data[0]}</h1>`;
    lbox.innerHTML += `<div id="types" class="flex"></div>`;
    for (i of data[6])
    {
        document.querySelector("#types").innerHTML += `<p class="Typing ${i.type.name[0].toUpperCase() + i.type.name.substring(1)}">${i.type.name}</p>`;
    }
    lbox.innerHTML += `<div id="abilities" class="flex"></div>`;
    for (i of data[4])
    {
        document.querySelector("#abilities").innerHTML += `<p class="Ability">${i.ability.name}</p>`;
    }
    lbox.innerHTML += `<div id="stats" class="flex"></div>`;
    EVs = [];
    for (i of data[5])
    {
        if (i.effort != 0)
        {
            EVs.push([i.stat.name,i.effort])
        }
        document.querySelector("#stats").innerHTML += `<p class="Stat">${i.stat.name.split('-').join(" ")} : ${i.base_stat}</p>`;
    }
    document.querySelector("#stats").innerHTML += `<hr><p class="Stat" id="EV">Effort Values</p>`;
    for (i of EVs)
    {
        document.querySelector("#stats").innerHTML += `<p class="Stat">${i[0].split('-').join(" ")} : ${i[1]}</p>`;
    }
    learnBy = {"level-up": 1, "egg": 2, "other": 3}
    document.querySelectorAll(".title")[1].innerHTML = learn_by.split('-').join(" ");
    for (move of data[learnBy[learn_by]]) {
        versionGroup = move[1].version_group.url.split('version-group/')[1].split("/")[0]
        moveName = move[0].split("-").join(" ")
        version = move[1].version_group.name.split("-").join(" ")
        if (/*generations[gen].some((version) => version == versionGroup)*/ generations[gen][0] == versionGroup) {
            if (learn_by == "level-up") {
                box.innerHTML += `<td>${moveName}</td><td>${move[1].level_learned_at}</td><br>`;
            } else {
                box.innerHTML += `<td>${moveName}</td><td>N.A.</td><br>`;
            }
        }
    }
}
renderData();
document.querySelectorAll("button").forEach((btn) => {
    btn.addEventListener('click', (e) => {
        if (e.target.name == "gen") {
            e.target.classList.add("selected");
            document.querySelectorAll("button").forEach((button) => {
                if (button.name == "gen" && button.classList.contains("selected") && button != e.target) {
                    button.classList.remove("selected")
                }
            })
            renderData(gen = e.target.value, learn_by = document.querySelector("#learn_by").innerHTML)
        } else {
            e.target.classList.add("selected");
            document.querySelectorAll("button").forEach((button) => {
                if (button.name == "learn_by" && button.classList.contains("selected") && button != e.target) {
                    button.classList.remove("selected")
                }
            })
            renderData(gen = document.querySelector("#gen").innerHTML, learn_by = e.target.value)
        }
    })
})