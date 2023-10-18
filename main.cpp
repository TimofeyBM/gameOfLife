#include <windows.h>
#include <SDL.h>
#include "frontend/frontend.h"
#include "backend/backend.h"
int numRows = 400;
int numCols = 750;
// Размеры ячейки.
int cellWidth = 1500 / numCols;
int cellHeight = 800 / numRows;
int width = 1500;
int height = 800;
void f(int _width, int _height) {
    width = _width;
    height = _height;
}
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    // Создание окна и поверхности для рисования.
    SDL_Window* window = SDL_CreateWindow("Grid Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1500, 800, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Texture* aliveCellTexture = createAliveCellTexture(renderer, cellWidth, cellHeight);

    GameOfLife game(numRows, numCols);
    std::vector<std::vector<std::shared_ptr<CellState>> > grid = game.getGrid();
    game.initializeBlockRandom();

    drawGrid(renderer, numRows, numCols, cellWidth, cellHeight);
    drawCells(renderer, aliveCellTexture, numRows, numCols, cellWidth, cellHeight, game, grid);
    runSimulation(window, renderer, aliveCellTexture, numRows, numCols, cellWidth, cellHeight, game);
    SDL_RenderPresent(renderer);
//    bool quit = false;
//    while (!quit) {
//        SDL_Event e;
//        while (SDL_PollEvent(&e)) {
//            if (e.type == SDL_QUIT) {
//                quit = true;
//            }
//        }
//    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}
