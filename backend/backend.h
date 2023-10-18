// backend.h
#ifndef BACKEND_H
#define BACKEND_H
#include <vector>
#include <memory>

enum class CellState { Dead, Alive };

class GameOfLife {
public:
    GameOfLife(int rows, int cols);
    void step();
    void initializeBlock();
    int countAliveNeighbors(int x, int y);
    void printGridFull();
    void initializeBlockRandom();
    const std::vector<std::vector<std::shared_ptr<CellState>>>& getGrid() const;
private:
    int rows_;
    int cols_;
    std::vector<std::vector<std::shared_ptr<CellState>>> grid_;
};

#endif