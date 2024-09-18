package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

func main() {
	// Parse lines of format:
	// Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53

	// for each line:
	//   add everything to the left to a map
	//   return 2^{count of everything to the right of | that's in the map}

	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	// Create a scanner to read the file
	scanner := bufio.NewScanner(file)

	// Read line by line
	totalPoints := 0
	for scanner.Scan() {
		line := scanner.Text()
		totalPoints += getLinePoints(line)
	}

	// Check for errors during scanning
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	// 26346
	fmt.Println(totalPoints)
}

func getLinePoints(line string) int {
	// Skip until after the line header. It'll always be after char 8
	i := 6
	for ; i < len(line); i++ {
		if line[i] == ':' {
			i += 2
			break
		}
	}

	// skip over all spaces
	for ; line[i] == ' '; i++ {
	}

	winningNumbers := make(map[int]bool)
	currentNumber := 0

	// Parse until the | char
	for ; i < len(line); i++ {
		c := line[i]
		// if we've reached the next number
		if c == ' ' {
			winningNumbers[currentNumber] = true
			currentNumber = 0

			if i+1 < len(line) && line[i+1] == ' ' {
				i += 1
			}

		} else if c == '|' {
			i += 2
			break

		} else if c >= '0' && c <= '9' {
			currentNumber *= 10
			currentNumber += int(c - '0')
		}
	}

	// Skip over all spaces
	for ; line[i] == ' '; i++ {
	}

	res := getLineWinningNumberCount(line, &winningNumbers, i)
	return res
}

func getLineWinningNumberCount(line string, winningNumbers *map[int]bool, startIdx int) int {
	// if count is 0, return 0
	// else, 2^(n-1)
	// we'll start winning number at 1 and multiply by 2 at each iteration to avoid an extra
	// conditional check in each iteration. But if winningNumber remains 1, we return 0
	// because of this, we need to return winningNumber / 2

	winningNumber := 1
	currentNumber := 0
	for ; startIdx < len(line); startIdx++ {
		c := line[startIdx]

		if c == ' ' {
			if _, exists := (*winningNumbers)[currentNumber]; exists {
				winningNumber *= 2
			}

			// if we have two spaces in a row (if the next number is single-digit)
			if startIdx+1 < len(line) && line[startIdx+1] == ' ' {
				startIdx += 1
			}

			currentNumber = 0
		} else if c >= '0' && c <= '9' {
			currentNumber *= 10
			currentNumber += int(c - '0')
		}
	}

	// add the last number if it's in the map
	if currentNumber != 0 {
		if _, exists := (*winningNumbers)[currentNumber]; exists {
			winningNumber *= 2
		}
	}

	if winningNumber == 1 {
		return 0
	}

	return winningNumber / 2
}
