id = document.querySelector("#id").innerHTML;
generations = {1: [1,2], 2: [3,4], 3: [5,6,7], 4: [8,9,10], 5: [11, 12, 13, 14], 6: [15, 16], 7: [17, 18, 19], 8: [20, 23]};
async function getData(id) {
    await fetch('https://pokeapi.co/api/v2/pokemon/' + id)
    .then(resp => resp.json())
    .then(data => {
        levelUp = [];
        egg = [];
        other = [];
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
    return [name, levelUp, egg, other]
}
async function renderData(gen=1, learn_by="level-up") {
    data = await getData(id);
    box = document.querySelector(".learnset");
    box.innerHTML = ``;
    document.querySelector("#gen").innerHTML = gen;
    document.querySelector("#learn_by").innerHTML = learn_by;
    document.querySelector(".leftbox").innerHTML = name;
    learnBy = {"level-up": 1, "egg": 2, "other": 3}
    for (move of data[learnBy[learn_by]]) {
        versionGroup = move[1].version_group.url.split('version-group/')[1].split("/")[0]
        moveName = move[0].split("-").join(" ")
        version = move[1].version_group.name.split("-").join(" ")
        if (/*generations[gen].some((version) => version == versionGroup)*/ generations[gen][0] == versionGroup) {
            if (learn_by == "level-up") {
                box.innerHTML += `${moveName} learnt at ${move[1].level_learned_at} in gen ${gen}<br>`;
            } else {
                box.innerHTML += `${moveName} learnt via ${learn_by} in gen ${gen}<br>`;
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