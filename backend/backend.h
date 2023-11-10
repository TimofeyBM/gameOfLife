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
    void clearAllGrid();
    void restoreSavedGrid();
    void initializeBlockRandom();
    void newStateGrid(int _rows, int _cols);
    void moveCellsLeft(int _rows, int _cals);
    void moveCellsRight(int _rows, int _cols);
    void moveCellsUp(int _rows, int _cols);
    void moveCellsDown(int _rows, int _cols);
    void setCellState(int row, int col, CellState state);
    void clearCellState(int row, int col, CellState state);
    void saveStateGrid();
    const std::vector<std::vector<std::shared_ptr<CellState>>>& getGrid() const;
private:
    int rows_;
    int cols_;
    std::vector<std::vector<std::shared_ptr<CellState>>> grid_;
    std::vector<std::vector<std::shared_ptr<CellState>>> saveGrid_;
};

#endif