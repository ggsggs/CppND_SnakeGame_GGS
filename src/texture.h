#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <memory>

#include "color.h"

class Texture {
public:
  Texture();
  // make class pure virtual
  virtual ~Texture() = 0;

  void ModulateColor(Color color);
  void SetBlendMode(SDL_BlendMode blending);
  void SetAlpha(uint8_t alpha);
  void Render(SDL_Renderer* renderer, SDL_Rect *dstRect, SDL_Rect *srcRect = nullptr,
              double angle = 0.0, SDL_Point *center = nullptr,
              SDL_RendererFlip flip = SDL_FLIP_NONE);
  void RenderSameSizeAt(SDL_Renderer* renderer, int x, int y);

  uint16_t GetWidth();
  uint16_t GetHeight();

private:
  struct DestroyerSDLTexture {
    void operator()(SDL_Texture *t) { SDL_DestroyTexture(t); }
  };

protected:
  std::unique_ptr<SDL_Texture, DestroyerSDLTexture> _texture;

  uint16_t _img_width;
  uint16_t _img_height;
};

class ImgTexture : public Texture{
  public:
  ImgTexture();
  ~ImgTexture();
  bool LoadFromFile(SDL_Renderer* renderer, std::string pathToImg);
};  

#endif