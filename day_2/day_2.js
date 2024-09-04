const { readFileSync } = require("fs");

const redCubes = 12;
const greenCubes = 13;
const blueCubes = 14;

const file = readFileSync("./input.txt", "utf-8");

let sumPossibleIds = 0;
let lines = file.split("\n");
lines.pop();
lines.forEach((line) => {
  let split = line.split(": ");
  let id = parseInt(split[0].split(" ")[1]);

  line = split[1];

  // split at ;
  const handfuls = line.split("; ");
  if (isPossible(handfuls)) sumPossibleIds += id;
});

function isPossible(handfuls) {
  for (let handful of handfuls) {
    for (const numAndColor of handful.split(", ")) {
      const num = numAndColor.split(" ")[0];
      const color = numAndColor.split(" ")[1];

      if (color[0] == "r" && num > redCubes) return false;
      if (color[0] == "g" && num > greenCubes) return false;
      if (color[0] == "b" && num > blueCubes) return false;
    }
  }

  return true;
}

console.log(sumPossibleIds);
