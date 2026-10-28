/*
** EPITECH PROJECT, 2026
** Display.cpp
** File description:
** SFML display helper for render preview
*/

#include "Display.hpp"

namespace RayTracer {

bool Display::initialize(int width, int height)
{
    this->_width = width;
    this->_height = height;
    this->_window = sf::RenderWindow(sf::VideoMode(sf::Vector2u(width, height)), "Raytracer");
    this->_window.setFramerateLimit(30);

    if (!this->_texture.resize(sf::Vector2u(width, height))) {
        this->_window.close();
        this->_open = false;
        return false;
    }

    this->_sprite.emplace(this->_texture);
    this->_pixelBuffer.assign(static_cast<std::size_t>(width) * height * 4, 0);
    this->_open = true;
    return true;
}

void Display::pumpEvents(void)
{
    if (!this->_open) {
        return;
    }

    while (auto event = this->_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->_window.close();
            this->_open = false;
        }
    }
}

void Display::update(const Image &image, const std::vector<std::atomic<bool>> &rowReady)
{
    if (!this->_open) {
        return;
    }

    for (int y = 0; y < this->_height; ++y) {
        if (!rowReady[static_cast<std::size_t>(y)].load(std::memory_order_acquire)) {
            continue;
        }
        for (int x = 0; x < this->_width; ++x) {
            const Color &color = image._pixels[y * this->_width + x];
            const std::size_t idx = (static_cast<std::size_t>(y) * this->_width + x) * 4;
            this->_pixelBuffer[idx + 0] = color.getRed();
            this->_pixelBuffer[idx + 1] = color.getGreen();
            this->_pixelBuffer[idx + 2] = color.getBlue();
            this->_pixelBuffer[idx + 3] = 255;
        }
    }
    this->updateTexture();
}

void Display::finalize(const Image &image)
{
    if (!this->_open) {
        return;
    }

    for (int y = 0; y < this->_height; ++y) {
        for (int x = 0; x < this->_width; ++x) {
            const Color &color = image._pixels[y * this->_width + x];
            const std::size_t idx = (static_cast<std::size_t>(y) * this->_width + x) * 4;
            this->_pixelBuffer[idx + 0] = color.getRed();
            this->_pixelBuffer[idx + 1] = color.getGreen();
            this->_pixelBuffer[idx + 2] = color.getBlue();
            this->_pixelBuffer[idx + 3] = 255;
        }
    }

    this->updateTexture();
}

void Display::waitUntilClosed(void)
{
    while (this->_open) {
        this->pumpEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_POLL_INTERVAL_MS));
    }
}

bool Display::isOpen(void) const
{
    return this->_open;
}

void Display::updateTexture(void)
{
    if (!this->_sprite) {
        return;
    }

    this->_texture.update(this->_pixelBuffer.data(), sf::Vector2u(this->_width, this->_height), sf::Vector2u(0, 0));
    this->_window.clear();
    this->_window.draw(*this->_sprite);
    this->_window.display();
}

}
