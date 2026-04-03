# GOF (Game Of Life)

GOF - it's a popular implementation of Conway's Game of Life

### Rules

- The game takes place on an infinite (or finite) two-dimensional grid of cells.
- Each cell can be either alive or dead.
- The update follows these rules based on the states of neighboring cells (total of 8 neighbors):
    - Birth: A dead cell becomes alive if it has exactly 3 live neighbors.
    - Death by underpopulation or overpopulation: A live cell dies if it has fewer than 2 neighbors (loneliness) or more than 3 neighbors (overcrowding).
    - Survival: A live cell remains alive if it has 2 or 3 live neighbors.

### Prerequisites

- C++14
- CMake 3.10
- SFML

### Installing SFML
On Linux:
```bash
sudo apt install libsfml-dev
```

### Build
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Run
```bash
./life
```
