#include "renderer.h"
#include <iostream>
#include <string>

#include "texture.h"
#include "color.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window.reset(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN));

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer.reset(
    SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED));
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  // no need to call destroy window, when unique ptr goes out of scope it will
  // call destroy window.
  // SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  ChangeDrawColor(Palette::background);
  SDL_RenderClear(sdl_renderer.get());

  Texture background(*this);
  background.loadFromFile("../media/sand.jpg");
  background.render(0, 0);

  // Render food
  ChangeDrawColor(Palette::food);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer.get(), &block);

  // Render snake's body
  ChangeDrawColor(Palette::snake_body);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    ChangeDrawColor(Palette::snake_head_alive);
  } else {
    ChangeDrawColor(Palette::snake_head_dead);
  }
  SDL_RenderFillRect(sdl_renderer.get(), &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer.get());
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window.get(), title.c_str());
}

void Renderer::ChangeDrawColor(Color c){
  SDL_SetRenderDrawColor(sdl_renderer.get(), c.r, c.g, c.b, c.alpha);
}