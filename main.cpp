#include <cstdlib>
#include <iostream>
#include "SDL.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_sdlrenderer.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void DrawRectangle(SDL_Renderer* const renderer, SDL_Texture* const texture, const Uint8 colourRed, const Uint8 colourGreen, const Uint8 colourBlue, SDL_Rect* const rectangle)
{
	SDL_SetRenderDrawColor(renderer, colourRed, colourGreen, colourBlue, 255);
	SDL_SetRenderTarget(renderer, texture);
	SDL_RenderFillRect(renderer, rectangle);

	
}

int main(int argc, char** argv) 
{
	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);

	SDL_LogSetPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR);

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
				// Setup Dear ImGui context
				IMGUI_CHECKVERSION();
				ImGui::CreateContext();
				ImGuiIO& io = ImGui::GetIO(); (void)io;
				//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
				//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

				// Setup Dear ImGui style
				ImGui::StyleColorsDark();
				//ImGui::StyleColorsLight();

				// Setup Platform/Renderer backends
				ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
				ImGui_ImplSDLRenderer_Init(renderer);

				ImVec4 colour = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

				while (!quit)
				{
					// Start the Dear ImGui frame
					ImGui_ImplSDLRenderer_NewFrame();
					ImGui_ImplSDL2_NewFrame();
					ImGui::NewFrame();

					SDL_Event event;
					while (SDL_PollEvent(&event)) {
						ImGui_ImplSDL2_ProcessEvent(&event);
						switch (event.type) {
						case SDL_WINDOWEVENT:
							
							switch (event.window.event)
							{
							case SDL_WINDOWEVENT_SIZE_CHANGED:
								SDL_DestroyTexture(texture);
								texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, event.window.data1, event.window.data2);
								if (texture == nullptr)
								{
									std::cerr << "Couldn't get texture from renderer: " << SDL_GetError() << std::endl;
									quit = true;
								}
								break;
							}
							break;
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
							}
						case SDL_MOUSEMOTION:
							if ((SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(1)) != 0) {
								SDL_Rect rectangle;
								rectangle.x = event.motion.x;
								rectangle.y = event.motion.y;
								rectangle.w = 10;
								rectangle.h = 10;
								DrawRectangle(renderer, texture, colour.x * 255, colour.y * 255, colour.z * 255, &rectangle);

							}
							break;
						}
					}

					ImGui::ShowDemoWindow();

					ImGui::ColorEdit4("MyColor##3", (float*)&colour, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

					ImGui::Render();

					SDL_SetRenderTarget(renderer, nullptr);
					SDL_RenderClear(renderer);
					SDL_RenderCopy(renderer, texture, nullptr, nullptr);
					ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
					SDL_RenderPresent(renderer);
				}

				ImGui_ImplSDLRenderer_Shutdown();
				ImGui_ImplSDL2_Shutdown();
				ImGui::DestroyContext();

				SDL_DestroyTexture(texture);
			}
			SDL_DestroyRenderer(renderer);
		}
			
		

		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	return EXIT_SUCCESS;
}
