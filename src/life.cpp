#include <random>
#include <algorithm>
#include "life.hpp"

int Life::countAliveNeighbors(const std::vector<std::vector<Cell>>& grid, int x, int y) {
    int count = 0;
    for (int offsetY = -1; offsetY <= 1; ++offsetY) {
        for (int offsetX = -1; offsetX <= 1; ++offsetX) {
            if (offsetX == 0 && offsetY == 0)
                continue; // it's middle cell
            
            int neighborX = x + offsetX;
            int neighborY = y + offsetY;

            if (neighborX >= 0 && neighborX < cols && neighborY >= 0 && neighborY < rows) {
                if (grid[neighborY][neighborX].isAlive)
                    ++count;
            }
        }
    }

    return count;
}

void Life::initializeGrid(std::vector<std::vector<Cell>>& grid) {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            // 25% chance of being alive (1 in 4 probability)
            grid[y][x].isAlive = (rand() % 4 == 0);
        }
    }
}

void Life::updateGrid(std::vector<std::vector<Cell>>& grid) {
    std::vector<std::vector<Cell>> newGrid = grid;

    for (int y = 0; y < gridHeight; y++) {
        for (int x = 0; x < gridWidth; x++) {
            int aliveNeighbors = 0;

            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0)
                        continue;

                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight) {
                        if (grid[ny][nx].isAlive)
                            aliveNeighbors++;
                    }
                }
            }

            if (grid[y][x].isAlive) {
                if (aliveNeighbors < 2 || aliveNeighbors > 3)
                    newGrid[y][x].isAlive = false;
            }
            else {
                if (aliveNeighbors == 3)
                    newGrid[y][x].isAlive = true;
            }
        }
    }

    grid = newGrid;
}

void Life::runWindow() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Game of Life");

    std::vector<sf::Vector2f> cells;
    for (int y = 0; y <= gridHeight * squareSize; y += squareSize) {
        for (int x = 0; x <= gridWidth * squareSize; x += squareSize) {
            cells.emplace_back(x, y);
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cells.begin(), cells.end(), gen);

    size_t count = cells.size() / 2;
    std::vector<sf::Vector2f> selectedCells(cells.begin(), cells.begin() + count);

    std::vector<std::vector<Cell>> grid(gridHeight, std::vector<Cell>(gridWidth));

    for (const auto& pos : selectedCells) {
        int xIndex = static_cast<int>(pos.x) / squareSize;
        int yIndex = static_cast<int>(pos.y) / squareSize;

        if (xIndex >= 0 && xIndex < gridWidth && yIndex >= 0 && yIndex < gridHeight) {
            grid[yIndex][xIndex].isAlive = true;
        }
    }

    sf::Clock clock;
    const sf::Time updateInterval = sf::seconds(0.15f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (clock.getElapsedTime() > updateInterval) {
            updateGrid(grid);
            clock.restart();
        }

        window.clear(sf::Color::White);

        for (int y = 0; y < gridHeight; y++) {
            for (int x = 0; x < gridWidth; x++) {
                if (grid[y][x].isAlive) {
                    sf::RectangleShape rectangle(sf::Vector2f(squareSize, squareSize));
                    rectangle.setPosition(x * squareSize, y * squareSize);
                    rectangle.setFillColor(sf::Color::Black);
                    window.draw(rectangle);
                }
            }
        }

        window.display();
    }
}

