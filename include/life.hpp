#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

struct Cell {
    bool isAlive;

    Cell() : isAlive(false) {}
    Cell(bool alive) : isAlive(alive) {}
};

class Life {
public:
    int countAliveNeighbors(const std::vector<std::vector<Cell>>& grid, int x, int y);
    void initializeGrid(std::vector<std::vector<Cell>>& grid);
    void updateGrid(std::vector<std::vector<Cell>>& grid);
    void runWindow();

private:
    int rows = 0;
    int cols = 0;
    const int squareSize = 10;
    const int gridWidth = 100;
    const int gridHeight = 100;
    std::vector<std::vector<Cell>> grid;

};
