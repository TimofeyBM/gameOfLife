#include <windows.h>

#include <SDL.h>
#include "frontend/frontend.h"



int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    SDL_DisplayMode screenMode;
    if (SDL_GetDesktopDisplayMode(0, &screenMode) != 0) {
        SDL_Log("Unable to get desktop display mode: %s", SDL_GetError());
        return 1;
    }
    int width = screenMode.w;
    int height = screenMode.h;
    int numRows = height / 10;
    int numCols = width / 10;
//
// Размеры ячейки.
      int cellWidth = width / numCols;
      int cellHeight = height / numRows;
//     Создание окна и поверхности для рисования.
    SDL_Window* window = SDL_CreateWindow("Grid Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenMode.w, screenMode.h-80, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Surface* icon = SDL_LoadBMP("./img/icon.bmp"); // Загрузка иконки
    if (icon) {
        SDL_SetWindowIcon(window, icon); // Установка иконки
        SDL_FreeSurface(icon); // Освобождение поверхности
    }
    SDL_Texture* aliveCellTexture = createAliveCellTexture(renderer, cellWidth, cellHeight);
    SDL_Texture* gridTexture = createGridTexture(renderer, numRows, numCols, 1500, 800);

    runSimulation(window, renderer, gridTexture, aliveCellTexture, numRows, numCols, width, height);
    return 0;
}
