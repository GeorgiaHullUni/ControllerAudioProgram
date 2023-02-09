#include <cstdlib>
#include <iostream>
#include "SDL.h"

int main(int argc, char** argv) 
{
	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		std::cerr << "Window couldn't be created: " << SDL_GetError() << std::endl;
	} 
	else 
	{
		SDL_Surface* surface = SDL_GetWindowSurface(window);
		if (window == nullptr)
		{
			std::cerr << "Couldn't get surface from window: " << SDL_GetError() << std::endl;
		}
		bool quit = false;
		Uint32 colour = SDL_MapRGB(surface->format, 0, 0, 0);
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
					SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0, 255, 0));
					SDL_UpdateWindowSurface(window);
					break;
				case SDLK_p:
					SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 0, 255));
					SDL_UpdateWindowSurface(window);
					break;
				case SDLK_r:
					SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 0, 0));
					SDL_UpdateWindowSurface(window);
					break;
				case SDLK_b:
					SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0, 0, 255));
					SDL_UpdateWindowSurface(window);
					break;
				case SDLK_c:
					colour = SDL_MapRGB(surface->format, 0, 0, 255);
				}
			case SDL_MOUSEMOTION:
				if ((SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(1)) != 0) {
					SDL_Rect rectangle;
					rectangle.x = event.motion.x;
					rectangle.y = event.motion.y;
					rectangle.w = 10;
					rectangle.h = 10;
					SDL_FillRect(surface, &rectangle, colour);
					SDL_UpdateWindowSurface(window);
				}
				break;
			}
		}

		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	return EXIT_SUCCESS;
}
