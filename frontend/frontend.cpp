#include <iostream>
#include <vector>
#include <thread>
#include <SDL.h>
#include <SDL_ttf.h>
#include "../backend/backend.h"



void drawGrid(SDL_Renderer* renderer, SDL_Texture* gridTexture, int numRows_, int numCols_, int width, int height){
    SDL_SetRenderDrawColor(renderer, 14, 59, 1, 155);
    int zoomedGridWidth = width / numCols_;
    int zoomedGridHeight = height / numRows_;
    // Рисование горизонтальных линий.
    for (int i = 0; i < numRows_; ++i) {
        SDL_Rect destRect = {0, i * zoomedGridHeight, width, 1};
        SDL_RenderCopy(renderer, gridTexture, nullptr, &destRect);
        //SDL_RenderDrawLine(renderer, 0, i * zoomedGridHeight, 1500, i * zoomedGridHeight);
    }

    // Рисование вертикальных линий.
    for (int j = 0; j < numCols_; ++j) {
        SDL_Rect destRect = {j * zoomedGridWidth, 0,  1, height};
        SDL_RenderCopy(renderer, gridTexture, nullptr, &destRect);
        //SDL_RenderDrawLine(renderer, j * zoomedGridWidth, 0, j * zoomedGridWidth, 800);
    }


}
SDL_Texture* createGridTexture(SDL_Renderer* renderer, int numRows_, int numCols_, int screenWidth, int screenHeight) {
    // Создайте поверхность с заданными параметрами
    SDL_Surface* gridSurface = SDL_CreateRGBSurface(0, screenWidth, screenHeight, 32, 0, 0, 0, 0);

    // Установите цвет сетки
    SDL_FillRect(gridSurface, nullptr, SDL_MapRGB(gridSurface->format, 14, 59, 1));

    // Создайте текстуру из поверхности
    SDL_Texture* gridTexture = SDL_CreateTextureFromSurface(renderer, gridSurface);

    // Освободите созданную поверхность
    SDL_FreeSurface(gridSurface);

    return gridTexture;
}
SDL_Texture* createAliveCellTexture(SDL_Renderer* renderer, int cellWidth, int cellHeight) {
    SDL_Surface* cellSurface = SDL_CreateRGBSurface(0, cellWidth, cellHeight, 32, 0, 0, 0, 0);
    SDL_FillRect(cellSurface, nullptr, SDL_MapRGB(cellSurface->format, 255, 255, 255));
    SDL_Texture* cellTexture = SDL_CreateTextureFromSurface(renderer, cellSurface);
    SDL_FreeSurface(cellSurface);
    return cellTexture;
}
// Функция для создания текстуры белой закрашенной клетки

void drawCells(SDL_Renderer* renderer, SDL_Texture* aliveCellTexture, int numRows_, int numCols_,
               GameOfLife& game, std::vector<std::vector<std::shared_ptr<CellState>>> grid, int width, int height) {
    grid = game.getGrid();
    int zoomedCellWidth = width / numCols_;
    int zoomedCellHeight = height / numRows_;
    for (int i = 0; i < numRows_; ++i) {
        for (int j = 0; j < numCols_; ++j) {
            if (*grid[i][j] == CellState::Alive) {
                SDL_Rect cellRect = {j * zoomedCellWidth, i * zoomedCellHeight, zoomedCellWidth - 1, zoomedCellHeight - 1};
                SDL_RenderCopy(renderer, aliveCellTexture, nullptr, &cellRect);
            }else{
                SDL_Rect deadCellRect = {j * zoomedCellWidth + 1, i * zoomedCellHeight + 1, zoomedCellWidth - 2, zoomedCellHeight - 2};
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Черный цвет
                SDL_RenderFillRect(renderer, &deadCellRect);
            }

        }

    }

}

void runSimulation(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* gridTexture, SDL_Texture* aliveCellTexture,
                   int numRows_, int numCols_, int &width, int &height) {
    GameOfLife game(numRows_, numCols_);
    bool quit = false;
    bool isPause = true;
    bool isDrawing = false;
    bool isClearing = false;
    int rows = numRows_;
    int cols = numCols_;
    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
    SDL_RenderPresent(renderer);
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


                    SDL_SetWindowSize(window, newWidth, newHeight);

                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);

                    SDL_RenderPresent(renderer);
                }

            }

            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    isDrawing = true;
                    int mouseX, mouseY;

                    SDL_GetMouseState(&mouseX, &mouseY);

                    int cellX = mouseX / (width / numCols_);
                    int cellY = mouseY / (height / numRows_);

                    game.setCellState(cellY, cellX, CellState::Alive);

                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);

                    SDL_RenderPresent(renderer);

                }else if (e.button.button == SDL_BUTTON_RIGHT) {
                    isClearing = true;
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                    int cellX = mouseX / (width / numCols_);
                    int cellY = mouseY / (height / numRows_);

                    // Очищаем состояние клетки, устанавливая его в Dead
                    game.clearCellState(cellY, cellX, CellState::Dead);

                    // Затем обновляем отрисовку
                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);

                    SDL_RenderPresent(renderer);

                }
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    isDrawing = false;
                }else if (e.button.button == SDL_BUTTON_RIGHT) {
                    isClearing = false;
                }
            } else if (e.type == SDL_MOUSEMOTION) {
                int mouseX, mouseY;

                SDL_GetMouseState(&mouseX, &mouseY);

                int cellX = mouseX / (width / numCols_);
                int cellY = mouseY / (height / numRows_);

                if(isDrawing){
                    game.setCellState(cellY, cellX, CellState::Alive);

                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);

                    SDL_RenderPresent(renderer);

                }
                if (isClearing) {
                    game.clearCellState(cellY, cellX, CellState::Dead);

                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);
                    SDL_RenderPresent(renderer);
                }

            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    isPause = !isPause;
                }else if(e.key.keysym.sym == SDLK_r){
                    game.initializeBlockRandom();
                    isPause = !isPause;
                }else if(e.key.keysym.sym == SDLK_1){
                    SDL_SetWindowSize(window, 1600, 800);
                    SDL_SetWindowBordered(window, SDL_TRUE);
                }else if(e.key.keysym.sym == SDLK_e){
                    tickInterval -= 10;
                    if(tickInterval <= 0){
                        tickInterval = 10;
                    }
                }else if(e.key.keysym.sym == SDLK_q){
                    tickInterval += 10;

                }else if(e.key.keysym.sym == SDLK_a){
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    game.moveCellsLeft(rows, cols);
                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);

                    SDL_RenderPresent(renderer);
                }else if(e.key.keysym.sym == SDLK_d){
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    game.moveCellsRight(rows, cols);
                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);
                    SDL_RenderPresent(renderer);
                }else if(e.key.keysym.sym == SDLK_w){
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    game.moveCellsUp(rows, cols);
                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);
                    SDL_RenderPresent(renderer);
                }else if(e.key.keysym.sym == SDLK_s){
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    game.moveCellsDown(rows, cols);
                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);
                    SDL_RenderPresent(renderer);
                }else if(e.key.keysym.sym == SDLK_x){
                    game.saveStateGrid();
                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);

                    SDL_RenderPresent(renderer);

                }else if(e.key.keysym.sym == SDLK_c){
                    game.clearAllGrid();
                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);

                    SDL_RenderPresent(renderer);

                }else if(e.key.keysym.sym == SDLK_z){
                    game.restoreSavedGrid();
                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);

                    SDL_RenderPresent(renderer);

                }
                else if (e.key.keysym.sym == SDLK_0) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    numRows_ -= 1;
                    numCols_ -= 1;
                    if(numRows_ <= 1){
                        numRows_ = 1;
                    }if(numCols_ <= 1){
                        numCols_ = 1;
                    }
                    while(true){
                        int flag = 0;
                        if(width % numCols_ != 0){
                            numCols_ -= 1;
                        }
                        if(height % numRows_ != 0){
                            numRows_ -= 1;
                        }
                        if(width % numCols_ == 0){
                            flag += 1;
                        }
                        if(height % numRows_ == 0){
                            flag += 1;
                        }
                        if(flag == 2){
                            break;
                        }
                    }
                    game.newStateGrid(numRows_, numCols_);
                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);
                    SDL_RenderPresent(renderer);
                }else if(e.key.keysym.sym == SDLK_MINUS){

                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    numRows_ += 1;
                    numCols_ += 1;
                    if(numRows_ >= height / 2){
                        numRows_ = height / 2;
                    }if(numCols_ >= width / 2){
                        numCols_ = width / 2;
                    }
                    while(true){
                        int flag = 0;
                        if(width % numCols_ != 0){
                            numCols_ += 1;
                        }
                        if(height % numRows_ != 0){
                            numRows_ += 1;
                        }
                        if(width % numCols_ == 0){
                            flag += 1;
                        }
                        if(height % numRows_ == 0){
                            flag += 1;
                        }
                        if(flag == 2){
                            break;
                        }
                    }
                    rows = numRows_;
                    cols = numCols_;
                    game.newStateGrid(numRows_, numCols_);
                    drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                    drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);

                    SDL_RenderPresent(renderer);
                }
            }

        }

        if(!isPause){
            Uint32 currentTick = SDL_GetTicks();
            if (currentTick - lastTick >= tickInterval) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);


                game.step();
                drawGrid(renderer, gridTexture, numRows_, numCols_, width, height);
                drawCells(renderer, aliveCellTexture, numRows_, numCols_, game, game.getGrid(), width, height);
                SDL_RenderPresent(renderer);
                lastTick = currentTick;
            }
        }

    }
}
