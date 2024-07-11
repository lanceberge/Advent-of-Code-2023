const { readFileSync } = require('fs');

const file = readFileSync('./input.txt', 'utf-8');

let sumProducts = 0;
let lines = file.split('\n');
lines.pop();

lines.forEach(line => {
  const split = line.split(': ');
  const id = parseInt(split[0].split(' ')[1]);
  line = split[1];

  let minRed = 0;
  let minGreen = 0;
  let minBlue = 0;
  for (const game of line.split('; ')) {
    for (const numAndColor of game.split(', ')) {
      const num = numAndColor.split(' ')[0];
      const color = numAndColor.split(' ')[1];

      // largest r,g,b num - multiply then add to sumProducts
      if (color[0] == 'r') minRed   = Math.max(minRed, num);
      if (color[0] == 'g') minGreen = Math.max(minGreen, num);
      if (color[0] == 'b') minBlue  = Math.max(minBlue, num);
    }
  }

  sumProducts += minRed * minGreen * minBlue;
});

console.log(sumProducts);
