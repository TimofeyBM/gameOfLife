#ifndef FRONTEND_H  // Это условие предотвращает повторное включение файла.
#define FRONTEND_H
#include <vector>
#include <memory>
#include "../backend/backend.h"
#include <SDL.h>

int runWindow();
void runSimulation(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* gridTexture, SDL_Texture* aliveCellTexture, int numRows_, int numCols_, int &width, int &height);
SDL_Texture* createAliveCellTexture(SDL_Renderer* renderer, int cellWidth, int cellHeight);
SDL_Texture* createGridTexture(SDL_Renderer* renderer, int numRows_, int numCols_, int screenWidth, int screenHeight);
#endif