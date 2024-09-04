const { readFileSync } = require('fs')

const file = readFileSync('./input.txt', 'utf-8')

let numStrings = {
  o: [['one', 1]],
  t: [
    ['two', 2],
    ['three', 3]
  ],
  f: [
    ['four', 4],
    ['five', 5]
  ],
  s: [
    ['six', 6],
    ['seven', 7]
  ],
  e: [['eight', 8]],
  n: [['nine', 9]]
}

function getNumFromIdx(line, idx) {
  let currentChar = line[idx]
  if (numStrings[currentChar] != undefined) {
    for (let numString of numStrings[currentChar]) {
      // optimize by starting with the substring 0, 0+min(length, 5) then doing sliding window
      if (line.substring(idx, idx + 5).startsWith(numString[0])) {
	return numString[1]
      }
    }
  }

  return parseInt(line[idx])
}

let sum = 0
file.split('\n').forEach((line) => {
  let l = 0
  let r = 0
  let firstNum = 0
  let secondNum = 0

  for (l = 0; l < line.length; l++) {
    firstNum = getNumFromIdx(line, l)
    if (!isNaN(firstNum)) {
      break
    }
  }

  for (r = line.length - 1; r >= l; r--) {
    secondNum = getNumFromIdx(line, r)
    if (!isNaN(secondNum)) break
  }

  sum += firstNum * 10 + secondNum
})

console.log(sum)
