#ifndef FRONTEND_H  // Это условие предотвращает повторное включение файла.
#define FRONTEND_H
#include <vector>
#include <memory>
#include "../backend/backend.h"

int runWindow();
void drawCells(SDL_Renderer* renderer, SDL_Texture* aliveCellTexture, int numRows_, int numCols_, int cellWidth_, int cellHeight_, GameOfLife& game, std::vector<std::vector<std::shared_ptr<CellState>>> grid);
void drawGrid(SDL_Renderer* renderer, int numRows_, int numCols_, int cellWidth_, int cellHeight_);
void runSimulation(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* aliveCellTexture, int numRows_, int numCols_, int cellWidth_, int cellHeight_, GameOfLife& game);
SDL_Texture* createAliveCellTexture(SDL_Renderer* renderer, int cellWidth, int cellHeight);
#endif