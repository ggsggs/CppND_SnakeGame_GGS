#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "color.h"
#include <memory>

#include "texture.h"

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

  ImgTexture _background;
  ImgTexture _snakeHead;
  ImgTexture _snakeTail;
  ImgTexture _food;
};

const std::string kPathToBackgroundImg{"../media/sand.jpg"};
const std::string kPathToSnakeHeadImg{"../media/snake_head.png"};
const std::string kPathToSnakeTailImg{"../media/snake_tail.png"};
const std::string kPathToFoodImg{"../media/apple.png"};

double DirectionToDegrees(Snake::Direction d);
#endif