#include <cstdlib>
#include <iostream>
#include "SDL.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void DrawRectangle(SDL_Renderer* const renderer, SDL_Texture* const texture, const Uint8 colourRed, const Uint8 colourGreen, const Uint8 colourBlue, SDL_Rect* const rectangle)
{
	SDL_SetRenderDrawColor(renderer, colourRed, colourGreen, colourBlue, 255);
	SDL_SetRenderTarget(renderer, texture);
	SDL_RenderFillRect(renderer, rectangle);

	SDL_SetRenderTarget(renderer, nullptr);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

int main(int argc, char** argv) 
{
	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		std::cerr << "Window couldn't be created: " << SDL_GetError() << std::endl;
	} 
	else 
	{
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
		if (renderer == nullptr)
		{
			std::cerr << "Couldn't get renderer from window: " << SDL_GetError() << std::endl;
		}
		else {
			bool quit = false;
			SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
			if (texture == nullptr)
			{
				std::cerr << "Couldn't get texture from renderer: " << SDL_GetError() << std::endl;
			}
			else {
				Uint8 colourRed = 0;
				Uint8 colourBlue = 0;
				Uint8 colourGreen = 0;

				while (!quit)
				{
					SDL_Event event;
					SDL_WaitEvent(&event);

					switch (event.type) {
					case SDL_QUIT:
						quit = true;
						break;
					case SDL_KEYDOWN:

						switch (event.key.keysym.sym) {
						case SDLK_g:
							DrawRectangle(renderer, texture, 0, 255, 0, nullptr);
							break;
						case SDLK_p:
							DrawRectangle(renderer, texture, 255, 0, 255, nullptr);
							break;
						case SDLK_r:
							DrawRectangle(renderer, texture, 255, 0, 0, nullptr);
							break;
						case SDLK_b:
							DrawRectangle(renderer, texture, 0, 255, 0, nullptr);
							break;
						case SDLK_c:
							colourRed = 0;
							colourGreen = 0;
							colourBlue = 255;
							break;
						}
					case SDL_MOUSEMOTION:
						if ((SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(1)) != 0) {
							SDL_Rect rectangle;
							rectangle.x = event.motion.x;
							rectangle.y = event.motion.y;
							rectangle.w = 10;
							rectangle.h = 10;
							DrawRectangle(renderer, texture, colourRed, colourGreen, colourBlue, &rectangle);
							
						}
						break;
					}
				}
				SDL_DestroyTexture(texture);
			}
			SDL_DestroyRenderer(renderer);
		}
			
		

		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	return EXIT_SUCCESS;
}
