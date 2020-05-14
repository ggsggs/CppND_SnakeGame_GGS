#include "texture.h"

Texture::Texture()
    : _img_width(0), _img_height(0) {}

Texture::~Texture() {}


void Texture::ModulateColor(Color c) {
  SDL_SetTextureColorMod(_texture.get(), c.r, c.g, c.b);
}

void Texture::SetBlendMode(SDL_BlendMode blending) {
  SDL_SetTextureBlendMode(_texture.get(), blending);
}

void Texture::SetAlpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(_texture.get(), alpha);
}

void Texture::Render(SDL_Renderer* renderer,
  SDL_Rect* dstRect, SDL_Rect* srcRect,
  double angle, SDL_Point *center, SDL_RendererFlip flip) {
  SDL_RenderCopyEx(renderer, _texture.get(), srcRect,
   dstRect, angle, center, flip);
}

void Texture::RenderSameSizeAt(SDL_Renderer* renderer, int x, int y){
  SDL_Rect dstRect{x, y, GetWidth(), GetHeight()};

  Render(renderer, &dstRect);
}

uint16_t Texture::GetWidth() { return _img_width; }

uint16_t Texture::GetHeight() { return _img_height; }

ImgTexture::ImgTexture() {}

ImgTexture::~ImgTexture() {}

bool ImgTexture::LoadFromFile(SDL_Renderer* renderer, std::string path) {
  // Load image at specified path
  // Following LazyFoo's method to obtain texture from file.
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    // texture from surface
    _texture.reset(
        SDL_CreateTextureFromSurface(renderer, loadedSurface));
    if (_texture == nullptr) {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
      _img_width = 0;
      _img_height = 0;
    } else {
      _img_width = loadedSurface->w;
      _img_height = loadedSurface->h;
    }

    // free temp surface.
    SDL_FreeSurface(loadedSurface);
  }
  return _texture != nullptr;
}