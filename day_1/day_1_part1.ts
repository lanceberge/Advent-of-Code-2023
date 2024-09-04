import { readFileSync } from 'fs'

const file = readFileSync('./input.txt', 'utf-8')

let sum: number = 0
file.split('\n').forEach((line: string) => {
  let l = 0
  let r = 0
  let firstNum: number = 0
  let secondNum: number = 0

  for (l = 0; l < line.length; l++) {
    firstNum = parseInt(line[l])
    if (!isNaN(firstNum)) {
      break
    }
  }

  for (r = line.length - 1; r >= l; r--) {
    secondNum = parseInt(line[r])
    if (!isNaN(secondNum)) {
      break
    }
  }

  sum += firstNum * 10 + secondNum
})

console.log(sum)
