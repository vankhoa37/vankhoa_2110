#ifndef SDL2_IMAGE_RENDERER_HPP
#define SDL2_IMAGE_RENDERER_HPP
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class SDL2ImageRenderer {
public:
    SDL2ImageRenderer(SDL_Renderer* renderer) : m_renderer(renderer), m_texture(nullptr), m_imageWidth(0), m_imageHeight(0) {}
    ~SDL2ImageRenderer() {
        if (m_texture != nullptr) {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
    }

    bool loadImage(const std::string& filePath) {
        SDL_Surface* surface = IMG_Load(filePath.c_str());
        if (surface == nullptr) {
            return false;
        }
        m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        if (m_texture == nullptr) {
            SDL_FreeSurface(surface);
            return false;
        }
        m_imageWidth = surface->w;
        m_imageHeight = surface->h;
        SDL_FreeSurface(surface);
        return true;
    }

    void renderImage(int x, int y) {
        if (m_texture != nullptr) {
            SDL_Rect destRect = {x, y, m_imageWidth, m_imageHeight};
            SDL_RenderCopy(m_renderer, m_texture, nullptr, &destRect);
        }
    }

    void setRenderer(SDL_Renderer* renderer) {
        m_renderer = renderer;
    }

private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    int m_imageWidth;
    int m_imageHeight;
};

#endif // SDL2_IMAGE_RENDERER_HPP
