#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <memory>

class Color {
 public:
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) :
    r(r), g(g), b(b), alpha(alpha) {}
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t alpha;
};

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);
  void ChangeDrawColor(Color RGBAlpha_color);
  SDL_Renderer* get(){return sdl_renderer.get();}

 private:
  struct SDLWindowDestroyer                                                       
  {                                                                               
    void operator()(SDL_Window* w) const                                        
    {                                                                           
        SDL_DestroyWindow(w);                                                   
    }                                                                           
  };         
  struct SDLRendererDestroyer                                                       
  {                                                                               
    void operator()(SDL_Renderer* r) const                                        
    {                                                                           
        SDL_DestroyRenderer(r);                                                   
    }                                                                           
  };         
  struct SDLSurfaceDestroyer{                                                     
    void operator()(SDL_Surface* s) const                                       
    {                                                                           
        SDL_FreeSurface(s);                                                     
    }                                                                           
  };     

 private:
  std::unique_ptr<SDL_Window, SDLWindowDestroyer> sdl_window;
  std::unique_ptr<SDL_Renderer, SDLRendererDestroyer> sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

namespace Palette{
const Color background{0x1E, 0x1E, 0x1E, 0xFF};
const Color food{0xFF, 0xCC, 0x00, 0xFF};
const Color snake_body{0xFF, 0xFF, 0xFF, 0xFF};
const Color snake_head_alive{0x00, 0x7A, 0xCC, 0xFF};
const Color snake_head_dead{0xFF, 0x00, 0x00, 0xFF};
}
#endif