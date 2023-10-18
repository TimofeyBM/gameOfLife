#include <iostream>
#include <vector>
#include <thread>
#include <SDL.h>
#include <SDL_ttf.h>
#include "../backend/backend.h"
void drawGrid(SDL_Renderer* renderer, int numRows_, int numCols_, int cellWidth_, int cellHeight_){
    SDL_SetRenderDrawColor(renderer, 14, 59, 1, 155);

    // Рисование горизонтальных линий.
    for (int i = 0; i < numRows_; ++i) {
        SDL_RenderDrawLine(renderer, 0, i * cellHeight_, 1500, i * cellHeight_);
    }

    // Рисование вертикальных линий.
    for (int j = 0; j < numCols_; ++j) {
        SDL_RenderDrawLine(renderer, j * cellWidth_, 0, j * cellWidth_, 800);
    }

}

SDL_Texture* createAliveCellTexture(SDL_Renderer* renderer, int cellWidth, int cellHeight) {
    SDL_Surface* cellSurface = SDL_CreateRGBSurface(0, cellWidth, cellHeight, 32, 0, 0, 0, 0);
    SDL_FillRect(cellSurface, nullptr, SDL_MapRGB(cellSurface->format, 255, 255, 255));
    SDL_Texture* cellTexture = SDL_CreateTextureFromSurface(renderer, cellSurface);
    SDL_FreeSurface(cellSurface);
    return cellTexture;
}
// Функция для создания текстуры белой закрашенной клетки
void drawCells(SDL_Renderer* renderer, SDL_Texture* aliveCellTexture,int numRows_, int numCols_, int cellWidth_, int cellHeight_, GameOfLife& game, std::vector<std::vector<std::shared_ptr<CellState>>> grid) {
    grid = game.getGrid();
    for (int i = 0; i < numRows_; ++i) {
        for (int j = 0; j < numCols_; ++j) {
            if (*grid[i][j] == CellState::Alive) {
                SDL_Rect cellRect = {j * cellWidth_, i * cellHeight_, cellWidth_ - 1, cellHeight_ - 1};
                SDL_RenderCopy(renderer, aliveCellTexture, nullptr, &cellRect);
            }else{
                continue;
            }

        }

    }
}
void runSimulation(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* aliveCellTexture, int numRows_, int numCols_, int cellWidth_, int cellHeight_, GameOfLife& game) {
    bool quit = false;
    Uint32 lastTick = SDL_GetTicks();
    Uint32 tickInterval = 100; // 0.1 секунда

    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }else if (e.type == SDL_WINDOWEVENT) {
                if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    // Окно было изменено в размерах
                    int newWidth = e.window.data1;
                    int newHeight = e.window.data2;

                    // Обновите размер окна
                    SDL_SetWindowSize(window, newWidth, newHeight);

                    // Теперь перерисуйте содержимое с новыми размерами
                    // Обновите область отображения и проекцию OpenGL (если используете)
                }
            }
        }

        Uint32 currentTick = SDL_GetTicks();
        if (currentTick - lastTick >= tickInterval) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            game.step();
            drawGrid(renderer, numRows_, numCols_, cellWidth_, cellHeight_);
            drawCells(renderer, aliveCellTexture, numRows_, numCols_, cellWidth_, cellHeight_, game, game.getGrid());

            SDL_RenderPresent(renderer);
            lastTick = currentTick;
        }
    }
}
