/*
** EPITECH PROJECT, 2026
** Display.hpp
** File description:
** SFML display helper for render preview
*/

#pragma once

#include "Core/Image.hpp"
#include <SFML/Graphics.hpp>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <optional>
#include <thread>
#include <vector>

#define DISPLAY_UPDATE_INTERVAL_MS 100
#define DISPLAY_POLL_INTERVAL_MS 10

namespace RayTracer {

class Display
{
public:
    Display(void) = default;
    ~Display(void) = default;

    bool initialize(int width, int height);
    void pumpEvents(void);
    void update(const Image &image, const std::vector<std::atomic<bool>> &rowReady);
    void finalize(const Image &image);
    void waitUntilClosed(void);
    bool isOpen(void) const;

private:
    void updateTexture(void);

private:
    sf::RenderWindow _window;
    sf::Texture _texture;
    std::optional<sf::Sprite> _sprite;
    std::vector<std::uint8_t> _pixelBuffer;
    int _width = 0;
    int _height = 0;
    bool _open = false;
};

}
