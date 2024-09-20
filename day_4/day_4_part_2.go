package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	// Create a scanner to read the file
	scanner := bufio.NewScanner(file)

	linePoints := make([]int, 10)
	lineCounts := make([]int, 10)

	currentLine := 0
	for scanner.Scan() {
		line := scanner.Text()
		currentLinePoints := GetLinePoints(line)
		linePoints = append(linePoints, currentLinePoints)

		// Ensure lineCounts has enough capacity
		currentLine += 1

		for currentLine+currentLinePoints > len(lineCounts) {
			lineCounts = append(lineCounts, 0)
		}
		for i := 0; i < currentLinePoints; i++ {
			lineCounts[currentLine+i] += 1
		}
	}

	// Check for errors during scanning
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	// Read line by line
	totalPoints := 0
	for i, points := range linePoints {
		totalPoints += lineCounts[i] * points
	}

	fmt.Println(totalPoints)
}
