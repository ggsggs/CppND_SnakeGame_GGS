#include "texture.h"
#include <iostream>

Texture::Texture() : _img_width(0), _img_height(0) {}

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

void Texture::Render(SDL_Renderer *renderer, SDL_Rect *dstRect,
                     SDL_Rect *srcRect, double angle, SDL_Point *center,
                     SDL_RendererFlip flip) {
  SDL_RenderCopyEx(renderer, _texture.get(), srcRect, dstRect, angle, center,
                   flip);
}

void Texture::RenderSameSizeAt(SDL_Renderer *renderer, int x, int y) {
  SDL_Rect dstRect{x, y, GetWidth(), GetHeight()};

  Render(renderer, &dstRect);
}

uint16_t Texture::GetWidth() { return _img_width; }

uint16_t Texture::GetHeight() { return _img_height; }

const bool ImgTexture::_isIMG_Init = IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG;

ImgTexture::ImgTexture() {
  if (!_isIMG_Init)
    std::cout << "Error loading IMG_INIT_PNG: " << IMG_GetError() << "\n";
}
ImgTexture::~ImgTexture() {}

bool ImgTexture::LoadFromFile(SDL_Renderer *renderer, std::string path,
                              const Color *colorKey) {
  // Load image at specified path
  // Following LazyFoo's method to obtain texture from file.
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    if (colorKey != nullptr) {
      SDL_SetColorKey(loadedSurface, SDL_TRUE,
                      SDL_MapRGB(loadedSurface->format, colorKey->r,
                                 colorKey->b, colorKey->g));
    }
    // texture from surface
    _texture.reset(SDL_CreateTextureFromSurface(renderer, loadedSurface));
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

const bool TextTexture::_isTTF_Init = TTF_Init() != -1;

TextTexture::TextTexture() {
  if (!_isTTF_Init)
    std::cout << "Error loading IMG_TTF_INIT: " << TTF_GetError() << "\n";
}

TextTexture::~TextTexture(){};
bool TextTexture::LoadFromText(SDL_Renderer *renderer, std::string text,
                               Color color) {
  // Adapted from LazyFoo's tutorials, following flow of execution.
  if (nullptr == _font) {
    std::cout << "Cannot load text, no font available\n";
    return false;
  }

  struct SurfaceDestroyer {
    void operator()(SDL_Surface *s) { SDL_FreeSurface(s); }
  };
  std::unique_ptr<SDL_Surface, SurfaceDestroyer> textSurface;
  textSurface.reset(TTF_RenderText_Solid(_font.get(), text.c_str(),
                                         SDL_Color{color.r, color.g, color.b}));
  if (textSurface == nullptr) {
    std::cout << "error creating surface from text: " << TTF_GetError() << "\n";
    return false;
  }

  _texture.reset(SDL_CreateTextureFromSurface(renderer, textSurface.get()));
  if (_texture == nullptr) {
    std::cout << "Error creating texture from surface: " << SDL_GetError()
              << "\n";
  } else {
    _img_width = textSurface->w;
    _img_height = textSurface->h;
  }
  return _texture != nullptr;
}

bool TextTexture::LoadFont(std::string pathToFont, int pSize) {
  _font.reset(TTF_OpenFont(pathToFont.c_str(), pSize));
  bool success = true;
  if (_font == nullptr) {
    std::cout << "Error loading font at " << pathToFont
              << ". Error: " << TTF_GetError();
    success = false;
  }
  return success;
}