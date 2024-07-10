# John Conway's Game of Life

## Description
This repository contains the implementation of the classic Game of Life, a cellular automaton created by mathematician John Conway. The project is programmed in C and runs in the console. This implementation was developed as part of my final project for the Fundamentals of Programming course in my first semester.

## Features
- **Language**: C
- **Interface**: Console
- **Functionality**: Simulation of the Game of Life according to John Conway's original rules

## Game of Life Rules
1. **Survival**: A live cell with two or three live neighbors remains alive.
2. **Death by loneliness**: A live cell with fewer than two live neighbors dies.
3. **Death by overpopulation**: A live cell with more than three live neighbors dies.
4. **Reproduction**: A dead cell with exactly three live neighbors becomes a live cell.

## Usage
1. Clone this repository: 
    ```bash
    git clone https://github.com/Pinedah/conways-game-of-life.git
    ```
2. Compile the code:
    ```bash
    gcc -o game_of_life game_of_life.c
    ```
3. Run the program:
    ```bash
    game_of_life
    ```

## Learning Objectives
- Understand and apply basic programming concepts in C.
- Implement control structures and loops.
- Work with arrays and data manipulation.
- Develop debugging and code testing skills.

## Synthesis
This repository features John Conway's Game of Life, a cellular automaton simulation. Programmed in C and run in the console, it was developed as my final project for the Fundamentals of Programming course in my first semester. Clone, compile, and run the simulation to explore its rules and behavior.
