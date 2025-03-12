# Snake Game in C++ with SFML

![Game Preview](https://github.com/sp4r1ng/snake_game/blob/main/2025-03-12%20214643.png?raw=true)

This project is a simple implementation of the classic Snake game using the SFML library for graphics rendering. The game includes obstacles that randomly appear, adding an extra challenge.

## Prerequisites

- **Operating System**: Ubuntu (or any other system compatible with SFML)
- **SFML Library**: Ensure SFML is installed on your system.
- **C++ Compiler**: GCC or any other compiler compatible with C++11 or later.

## Installation

1. **Install SFML**:
   - On Ubuntu, you can install SFML using the following command:
     ```bash
     sudo apt update
     sudo apt install libsfml-dev
     ```

2. **Clone the Repository**:
   - Clone this repository to your local machine:
     ```bash
     git clone https://github.com/sp4r1ng/snake_game
     cd snake_game
     ```

## Compilation and Execution

1. **Compile the Project**:
   - Use `g++` to compile the project with SFML libraries:
     ```bash
     g++ -o snake_game main.cpp -lsfml-graphics -lsfml-window -lsfml-system
     ```

2. **Run the Game**:
   - Once compiled, run the game with:
     ```bash
     ./snake_game
     ```

## Controls

- **Movement**: Use the arrow keys (up, down, left, right) to control the snake.
- **Objective**: Avoid the obstacles that randomly appear on the screen.


