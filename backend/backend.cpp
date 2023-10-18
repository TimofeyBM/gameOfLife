#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include "backend.h"

GameOfLife::GameOfLife(int _rows, int _cols) : rows_(_rows), cols_(_cols) {
    // Создаем и инициализируем сетку с использованием shared_ptr
    grid_ = std::vector<std::vector<std::shared_ptr<CellState>>>(_rows, std::vector<std::shared_ptr<CellState>>(_cols));
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            grid_[i][j] = std::make_shared<CellState>(CellState::Dead);
        }
    }
}
const std::vector<std::vector<std::shared_ptr<CellState>>>& GameOfLife::getGrid() const {
    return grid_;
}

void GameOfLife::step() {
    std::vector<std::vector<std::shared_ptr<CellState>>> newGrid = grid_;

    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            int aliveNeighbors = countAliveNeighbors(i, j);

            // Примените правила игры "Жизнь" для обновления состояния ячейки
            if (*grid_[i][j] == CellState::Dead) {
                if (aliveNeighbors == 3) {
                    newGrid[i][j] = std::make_shared<CellState>(CellState::Alive);

                }
            }
            if(*grid_[i][j] == CellState::Alive){
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    newGrid[i][j] = std::make_shared<CellState>(CellState::Dead);
                }
            }
        }
    }

    // Обновление основной сетки
    grid_ = newGrid;
}
int GameOfLife::countAliveNeighbors(int x, int y) {
    int aliveNeighbors = 0;

    // Определите соседей вокруг текущей ячейки, учитывая замкнутую сетку
    int numRows = rows_;
    int numCols = cols_;

    // Переменные для обхода соседей вокруг текущей ячейки
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        int newX = (x + dx[i] + numRows) % numRows; // Обеспечивает замкнутость по вертикали
        int newY = (y + dy[i] + numCols) % numCols; // Обеспечивает замкнутость по горизонтали

        // Проверьте состояние соседа и увеличьте счетчик, если он живой
        if (*grid_[newX][newY] == CellState::Alive) {
            aliveNeighbors++;
        }
    }

    return aliveNeighbors;
}

void GameOfLife::initializeBlock(){
    grid_[0][1] = std::make_shared<CellState>(CellState::Alive);
    grid_[1][2] = std::make_shared<CellState>(CellState::Alive);
    grid_[2][0] = std::make_shared<CellState>(CellState::Alive);
    grid_[2][1] = std::make_shared<CellState>(CellState::Alive);
    grid_[2][2] = std::make_shared<CellState>(CellState::Alive);
}

void GameOfLife::initializeBlockRandom(){
    std::random_device rd;
    std::default_random_engine generator(rd());

    // Генерация случайного значения типа bool (true или false)

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::uniform_int_distribution<int> distribution(0, 1);
            bool randomValue = distribution(generator);
            if(randomValue == true){
                grid_[i][j] = std::make_shared<CellState>(CellState::Alive);
            }
        }
        std::cout << std::endl;
    }
}
void GameOfLife::printGridFull() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if(*grid_[i][j] == CellState::Alive){
                std::cout<< '*';
            }
            if(*grid_[i][j] == CellState ::Dead){
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
}




